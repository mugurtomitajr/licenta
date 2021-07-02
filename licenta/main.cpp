//
//  main.cpp
//  licenta
//


#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <cstdlib>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "support/constants.hpp"

#include "scenes/Scene.hpp"
#include "scenes/ExampleScene.hpp"
#include "scenes/SimpleDemoScene.hpp"
#include "MainWindow.hpp"

MainWindow mainWindow;

double lastTime = 0.0f;
double fpsPrintCumulativeTime = 0.0f;
int fpsCounter = 0;

Scene* requestScene(int sceneNb) {
    switch (sceneNb) {
        case 0:
            return new ExampleScene();
        case 1:
            return new ExampleScene();
        case 2:
            return new ExampleScene();
        case 3:
            return new ExampleScene();
        case 4:
            return new ExampleScene();
        case 5:
            return new ExampleScene();
        case 6:
            return new ExampleScene();
        case 7:
            return new ExampleScene();
        case 8:
            return new ExampleScene();
        case 9:
            return new ExampleScene();
            
        default:
            return new ExampleScene();
    }
}

int main(int argc, const char * argv[]) {
    
    mainWindow = MainWindow(DEFAULT_WINDOW_SIZE_WIDTH, DEFAULT_WINDOW_SIZE_HEIGHT);
    mainWindow.Initialise();
    
    Scene *currentScene = nullptr;
    int currentSceneNb = 0;
    
    currentScene = requestScene(currentSceneNb);
    currentScene -> Load(60.0f, (GLfloat)mainWindow.WindowWidth() / mainWindow.WindowHeight());
    
    lastTime = glfwGetTime();
    
    currentScene -> Start();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    while ( !mainWindow.ShouldClose() ) {
        
        double now = glfwGetTime();
        double deltaTime = now - lastTime;
        lastTime = now;
        
        // FPS regulation
        // TODO: check if FPS regulation already done by OpenGL
        
        fpsPrintCumulativeTime += deltaTime;
        if(fpsPrintCumulativeTime > FPS_PRINT_TIME) {
            fpsPrintCumulativeTime -= FPS_PRINT_TIME;
            fprintf(stdout, "Average FPS: %d\n", (int)((double) fpsCounter / FPS_PRINT_TIME));
            fpsCounter = 0;
        }
        
        glfwPollEvents();
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::vec2 deltaMouse = mainWindow.MouseDelta();
        bool *keyPressedArray = mainWindow.KeyPressedArray();
        
        int newSceneNumber = io::NumberKeyPressed(keyPressedArray);
        if(newSceneNumber >= 0) {
            currentScene -> Stop();
            delete currentScene;
            currentSceneNb = newSceneNumber;
            currentScene = requestScene(currentSceneNb);
            currentScene -> Load(60.0f,  (GLfloat)mainWindow.WindowWidth() / mainWindow.WindowHeight());
            currentScene -> Start();
        }
        
        currentScene -> MasterUpdate(deltaTime, deltaMouse, keyPressedArray);
        currentScene -> Render(deltaTime, 0.0f);

        mainWindow.SwapBuffers();
        
        fpsCounter += 1;
    }
    
    currentScene -> Stop();
    
    delete currentScene;
    
    return 0;
    
}
