//
//  FollowingCamera.cpp
//  practice
//

#include "FollowingCamera.hpp"

FollowingCamera::FollowingCamera() : Camera() {}

FollowingCamera::FollowingCamera(Instance* p_target, GLfloat p_verticalFov, GLfloat p_displayRatio, glm::vec3 p_position, glm::vec3 p_up, GLfloat p_yaw, GLfloat p_pitch) : Camera(p_verticalFov, p_displayRatio, p_position, p_up, p_yaw, p_pitch) {
    this -> _target = p_target;
}

void FollowingCamera::Start() {
    
}

void FollowingCamera::Update(const double &dt, glm::vec2 p_deltaMouse, bool *p_keyPressedArray) {
    glm::vec3 followPoint = this -> _target -> WorldPosition() + this -> _target -> FollowOffset();
    GLfloat followSpeed = 8.0f;
    if(glm::length(followPoint - this -> _position) > EPSILON) {
        this -> _position = calc::Lerp(this -> _position, followPoint, dt * followSpeed);
        this -> _viewMatrixUpToDate = false;
    }
    
    bool directionChanged = this -> _checkMouseChange(p_deltaMouse, this -> _target -> YRotationFollowOffset());
    if(directionChanged) {
        this -> _recalculateVectors();
        this -> _viewMatrixUpToDate = false;
    }
    this -> _checkKeysPressed(dt, p_keyPressedArray);
}

void FollowingCamera::Stop() {
    
}

bool FollowingCamera::_checkMouseChange(glm::vec2 p_deltaMouse, GLfloat yRotationFollowOffset) {
    bool changed = p_deltaMouse.y != 0.0f; // p_deltaMouse.x != 0.0f ||
    if(changed) {
        p_deltaMouse *= this -> _turnSpeed;
        //this -> _yaw += p_deltaMouse.x;
        this -> _pitch += p_deltaMouse.y;
    }
    
    if( this -> _pitch > -15.0f ) {
        this -> _pitch = -15.0f;
    } else if( this -> _pitch < -55.0f ) {
        this -> _pitch = -55.0f;
    }
    
    GLfloat offset = 90.0f + glm::degrees(yRotationFollowOffset);
    /*if( this -> _yaw > offset + 30.0f ) {
        this -> _yaw = offset + 30.0f;
    } else if( this -> _yaw < offset + -30.0f ) {
        this -> _yaw = offset + -30.0f;
    }*/
    if(this -> _yaw != offset) {
        this -> _yaw = offset;
        changed = true;
    }
    
    return changed;
}

void FollowingCamera::_checkKeysPressed(const double &dt, bool *p_keyPressedArray) {
    
}

