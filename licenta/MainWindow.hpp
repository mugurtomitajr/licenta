//
//  MainWindow.hpp
//  practice
//

#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <cstdio>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class MainWindow {
public:
    MainWindow();
    MainWindow(GLint p_windowWidth, GLint p_windowHeight);
    ~MainWindow();

    int Initialise();

    GLint WindowWidth();
    
    GLint WindowHeight();

    bool ShouldClose();
    
    bool *KeyPressedArray();
    
    glm::vec2 MouseDelta();

    void SwapBuffers();
    
private:
    GLFWwindow* _window;

    GLint _originalWidth, _originalHeight;
    GLint _windowWidth, _windowHeight;
    
    bool _keyPressed[1024];
    bool _mouseInputInitialised;
    glm::vec2 _mouseLastPosition, _mouseDeltaPosition;
    
    void _initialiseCallbacks();
    static void _onKeyChange(GLFWwindow *p_window, int p_key, int p_code, int p_action, int p_mode);
    static void _onMouseChange(GLFWwindow *p_window, double p_xPosition, double p_yPosition);
    
    virtual void _copy(const MainWindow &p_that);
    virtual void _clear();
};

#endif /* MainWindow_hpp */
