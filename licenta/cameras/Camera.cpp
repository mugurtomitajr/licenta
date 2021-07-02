//
//  Camera.cpp
//  practice
//

#include "Camera.hpp"

Camera::Camera() {
    this -> _verticalFov = 45.0f;
    this -> _displayRatio = 1.0f;
    this -> _position = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _speed = glm::vec3(0.0f, 0.0f, 0.0f);
    
    this -> _front = glm::vec3(0.0f, 0.0f, -1.0f);
    this -> _up = glm::vec3(0.0f, 1.0f, 0.0f);
    this -> _right = glm::vec3(1.0f, 0.0f, 0.0f);
    
    this -> _globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
    
    this -> _yaw = 0.0f;
    this -> _pitch = 0.0f;
    this -> _roll = 0.0f; // TODO: roll not used
    
    this -> _moveSpeed = 10.0f; // Only for Controllable Camera - can remove it from here
    this -> _turnSpeed = 0.1f;
    
    this -> _projectionMatrix = glm::mat4(1.0f);
    this -> _projectionMatrixUpToDate = false;
    
    this -> _viewMatrix = glm::mat4(1.0f);
    this -> _viewMatrixUpToDate = false;
    
    this -> _recalculateVectors();
}

Camera::Camera(GLfloat p_verticalFov, GLfloat p_displayRatio, glm::vec3 p_position, glm::vec3 p_up, GLfloat p_yaw, GLfloat p_pitch) : Camera() {
    this -> _verticalFov = p_verticalFov;
    this -> _displayRatio = p_displayRatio;
    this -> _position = p_position;
    this -> _up = p_up;
    this -> _yaw = p_yaw;
    this -> _pitch = p_pitch;
    
    this -> _recalculateVectors();
}

Camera::~Camera() {
    this -> _clear();
}

void Camera::Start() {}

void Camera::Update(const double &dt, glm::vec2 p_deltaMouse, bool *p_keyPressedArray) {}

void Camera::Stop() {}

glm::mat4 Camera::ViewMatrix() {
    if(!this -> _viewMatrixUpToDate) {
        this -> _recalculateViewMatrix();
    }
    return this -> _viewMatrix;
}

glm::mat4 Camera::ProjectionMatrix() {
    if(!this -> _projectionMatrixUpToDate) {
        this -> _recalculateProjectionMatrix();
    }
    return this -> _projectionMatrix;
}

glm::vec3 Camera::Position() { return this -> _position; }

glm::vec3 Camera::Front() { return this -> _front; }

glm::vec3 Camera::Up() { return this -> _up; }

glm::vec3 Camera::Right() { return this -> _right; }

void Camera::_recalculateVectors() {
    this -> _front = glm::vec3( cos(glm::radians(this -> _yaw)) * cos(glm::radians(this -> _pitch)),
                                sin(glm::radians(this -> _pitch)),
                                sin(glm::radians(this -> _yaw)) * cos(glm::radians(this -> _pitch)));
    this -> _front = glm::normalize(this -> _front);
    
    this -> _right = glm::normalize(glm::cross(this -> _front, this -> _globalUp)); // TODO: roll not used
    
    this -> _up = glm::normalize(glm::cross(this -> _right, this -> _front));
    
    this -> _viewMatrixUpToDate = false;
    this -> _recalculateViewMatrix();
}

void Camera::_recalculateViewMatrix() {
    this -> _viewMatrix = glm::lookAt(this -> _position, this -> _position + this -> _front, this -> _up);
    this -> _viewMatrixUpToDate = true;
}

void Camera::_recalculateProjectionMatrix() {
    this -> _projectionMatrix = glm::perspective(glm::radians(this -> _verticalFov), this -> _displayRatio, 0.1f, 200.0f);
    this -> _projectionMatrixUpToDate = true;
}

void Camera::_clear() {
    this -> _verticalFov = 45.0f;
    this -> _displayRatio = 1.0f;
    this -> _position = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _speed = glm::vec3(0.0f, 0.0f, 0.0f);
    
    this -> _front = glm::vec3(0.0f, 0.0f, -1.0f);
    this -> _up = glm::vec3(0.0f, 1.0f, 0.0f);
    this -> _right = glm::vec3(1.0f, 0.0f, 0.0f);
    
    this -> _globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
    
    this -> _yaw = 0.0f;
    this -> _pitch = 0.0f;
    this -> _roll = 0.0f; // TODO: roll not used
    
    this -> _moveSpeed = 10.0f;
    this -> _turnSpeed = 0.1f;
    
    this -> _projectionMatrix = glm::mat4(1.0f);
    this -> _projectionMatrixUpToDate = false;
    
    this -> _viewMatrix = glm::mat4(1.0f);
    this -> _viewMatrixUpToDate = false;
}

void Camera::_copy(const Camera &p_that) {
    
}
