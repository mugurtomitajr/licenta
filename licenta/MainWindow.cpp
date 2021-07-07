//
//  MainWindow.cpp
//  practice
//

#include "MainWindow.hpp"

MainWindow::MainWindow() {
    this -> _originalWidth = 1200;
    this -> _originalHeight = 900;
    
    this -> _mouseInputInitialised = false;
    this -> _mouseLastPosition = glm::vec2(0.0f, 0.0f);
    this -> _mouseDeltaPosition = glm::vec2(0.0f, 0.0f);
    memset(this -> _keyPressed, 0, sizeof(this -> _keyPressed));
}

MainWindow::MainWindow(GLint p_windowWidth, GLint p_windowHeight) : MainWindow() {
    this -> _originalWidth = p_windowWidth;
    this -> _originalHeight = p_windowHeight;
}

MainWindow::~MainWindow() {
    this -> _clear();
}

int MainWindow::Initialise() {
    if ( !glfwInit() ) {
        fprintf(stdout, "Error Initialising GLFW...\n");
        glfwTerminate();
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this -> _window = glfwCreateWindow(this -> _originalWidth, this -> _originalHeight, "Practice Window", NULL, NULL);
    if ( !this -> _window ) {
        fprintf(stdout, "Error creating GLFW window...\n");
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(this -> _window, &this -> _windowWidth, &this -> _windowHeight);

    glfwMakeContextCurrent(this -> _window);
    
    this -> _initialiseCallbacks();
    
    glfwSetInputMode(this -> _window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;

    GLenum error = glewInit();
    if ( error != GLEW_OK ) {
        fprintf(stdout, "GLEW error: %s\n", glewGetErrorString(error));
        glfwDestroyWindow(this -> _window);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, this -> _windowWidth, this -> _windowHeight);
    
    glfwSetWindowUserPointer(this -> _window, this);
    
    return 0;
}

GLint MainWindow::WindowWidth() { return this -> _windowWidth; }

GLint MainWindow::WindowHeight() { return this -> _windowHeight; }

bool MainWindow::ShouldClose() { return glfwWindowShouldClose(this -> _window); }

bool* MainWindow::KeyPressedArray() { return this -> _keyPressed; } //TODO: change key pressed array pointer passing

glm::vec2 MainWindow::MouseDelta() {
    // TODO: change mouse delta reset method
    glm::vec2 mouseDelta = this -> _mouseDeltaPosition;
    this -> _mouseDeltaPosition = glm::vec2(0.0f, 0.0f);
    return mouseDelta;
}

void MainWindow::SwapBuffers() { glfwSwapBuffers(this -> _window); }

void MainWindow::_initialiseCallbacks() {
    glfwSetKeyCallback(this -> _window, MainWindow::_onKeyChange);
    glfwSetCursorPosCallback(this -> _window, MainWindow::_onMouseChange);
}

void MainWindow::_onKeyChange(GLFWwindow *p_window, int p_key, int p_code, int p_action, int p_mode) {
    MainWindow *window = static_cast<MainWindow*>(glfwGetWindowUserPointer(p_window));
    
    if( p_key == GLFW_KEY_ESCAPE && p_action == GLFW_PRESS ) {
        glfwSetWindowShouldClose(p_window, GL_TRUE);
    }
    
    if( p_key >= 0 && p_key < 1024 ) {
        if( p_action == GLFW_PRESS ) {
            window -> _keyPressed[p_key] = true;
        } else if( p_action == GLFW_RELEASE ) {
            window -> _keyPressed[p_key] = false;
        }
    }
}

void MainWindow::_onMouseChange(GLFWwindow *p_window, double p_xPosition, double p_yPosition) {
    MainWindow *window = static_cast<MainWindow*>(glfwGetWindowUserPointer(p_window));
    glm::vec2 currentPosition = glm::vec2(p_xPosition, p_yPosition);
    
    if( !window -> _mouseInputInitialised ) {
        window -> _mouseInputInitialised = true;
        window -> _mouseLastPosition = currentPosition;
    }
    
    // TODO: check inverted vertical axis movement
    window -> _mouseDeltaPosition = currentPosition - window -> _mouseLastPosition;
    window -> _mouseDeltaPosition.y *= -1;
    
    window -> _mouseLastPosition = currentPosition;
}

void MainWindow::_clear() {
    glfwDestroyWindow(this -> _window);
    glfwTerminate();
}

void MainWindow::_copy(const MainWindow &p_that) {
    
}
    
