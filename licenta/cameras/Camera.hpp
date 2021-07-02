//
//  Camera.hpp
//  practice
//

#ifndef Camera_hpp
#define Camera_hpp

#include <cstdio>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "io.hpp"
#include "constants.hpp"

class Camera {
public:
    Camera();
    Camera(GLfloat p_verticalFov, GLfloat p_displayRatio, glm::vec3 p_position, glm::vec3 p_up, GLfloat p_yaw, GLfloat p_pitch);
    ~Camera();
    
    virtual void Start();
    virtual void Update(const double &dt, glm::vec2 p_deltaMouse, bool *p_keyPressedArray);
    virtual void Stop();
    
    glm::mat4 ViewMatrix();
    glm::mat4 ProjectionMatrix();
    
    glm::vec3 Position();
    glm::vec3 Front();
    glm::vec3 Up();
    glm::vec3 Right();
    
protected:
    GLfloat _verticalFov;
    GLfloat _displayRatio;
    glm::vec3 _position;
    glm::vec3 _speed;
    
    glm::vec3 _front, _up, _right;
    glm::vec3 _globalUp;
    
    GLfloat _yaw, _pitch, _roll;
    
    GLfloat _moveSpeed; // Only for Controllable Camera - can remove it from here 
    GLfloat _turnSpeed;
    
    glm::mat4 _projectionMatrix;
    bool _projectionMatrixUpToDate;
    
    glm::mat4 _viewMatrix;
    bool _viewMatrixUpToDate;
    
    void _recalculateVectors();
    void _recalculateViewMatrix();
    void _recalculateProjectionMatrix();
    
    virtual void _copy(const Camera &p_that);
    virtual void _clear();
};

#endif /* Camera_hpp */
