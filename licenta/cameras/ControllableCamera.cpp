//
//  ControllableCamera.cpp
//  practice
//

#include "ControllableCamera.hpp"

ControllableCamera::ControllableCamera() : Camera() {}

ControllableCamera::ControllableCamera(GLfloat p_verticalFov, GLfloat p_displayRatio, glm::vec3 p_position, glm::vec3 p_up, GLfloat p_yaw, GLfloat p_pitch) : Camera(p_verticalFov, p_displayRatio, p_position, p_up, p_yaw, p_pitch) {}

void ControllableCamera::Update(const double &dt, glm::vec2 p_deltaMouse, bool *p_keyPressedArray) {
    bool directionChanged = this -> _checkMouseChange(p_deltaMouse);
    if(directionChanged) {
        this -> _recalculateVectors();
        this -> _viewMatrixUpToDate = false;
    }
    this -> _checkKeysPressed(dt, p_keyPressedArray);
}

bool ControllableCamera::_checkMouseChange(glm::vec2 p_deltaMouse) {
    bool changed = p_deltaMouse.x != 0.0f || p_deltaMouse.y != 0.0f;
    if(changed) {
        p_deltaMouse *= this -> _turnSpeed;
        this -> _yaw += p_deltaMouse.x;
        this -> _pitch += p_deltaMouse.y;
        
        if( this -> _pitch > 89.0f ) {
            this -> _pitch = 89.0f;
        } else if( this -> _pitch < -89.0f ) {
            this -> _pitch = -89.0f;
        }
    }
    return changed;
}

void ControllableCamera::_checkKeysPressed(const double &dt, bool *p_keyPressedArray) {
    bool moved = false;
    float speed = this -> _moveSpeed * dt;
    glm::vec3 direction = io::MovementDirectionFromKeyboard(p_keyPressedArray);
    if(abs(direction.z) > EPSILON) {
        this -> _position += this -> _front * speed * direction.z;
        moved = true;
    }
    
    if(abs(direction.x) > EPSILON) {
        this -> _position += this -> _right * speed * direction.x;
        moved = true;
    }
    
    if(moved) {
        this -> _viewMatrixUpToDate = false;
    }
}

