//
//  ControllableDrone.cpp
//  practice
//

#include "ControllableDrone.hpp"

ControllableDrone::ControllableDrone() : Instance() {}

ControllableDrone::ControllableDrone(Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale) : Instance(p_parent, p_position, p_rotation, p_scale){}

const char* ControllableDrone::LoadCustomModelFilepath() {
    return "resources/models/drone/scheleton.obj";
}

glm::vec3 ControllableDrone::LoadCustomModelScale() {
    return glm::vec3(1.0f, 1.0f, 1.0f);
}

void ControllableDrone::LoadOtherInstances(AssetManager *p_assetManager, RuntimeQueueManager *p_runtimeQueueManager) {
    Instance::LoadOtherInstances(p_assetManager, p_runtimeQueueManager);
    ControllableDronePropeller *dronePropellerLeft = new ControllableDronePropeller(true, this, glm::vec3(0.253f, -0.008f, 0.01f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    ControllableDronePropeller *dronePropellerRight = new ControllableDronePropeller(false, this, glm::vec3(-0.253f, -0.008f, 0.01f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

    this -> AddChild(dronePropellerLeft);
    this -> AddChild(dronePropellerRight);
    
    this -> _runtimeQueueManager -> AddInstance("drone-propeller-left", "default", dronePropellerLeft);
    dronePropellerLeft -> OverrideDiffuseMap(this -> _assetManager -> AddTexture("plain-white", "resources/textures/plain-white.png"));
    this -> _runtimeQueueManager -> AddInstance("drone-propeller-right", "default", dronePropellerRight);
    dronePropellerRight -> OverrideDiffuseMap(this -> _assetManager -> AddTexture("plain-white", "resources/textures/plain-white.png"));
    
    this -> OverrideDiffuseMap(this -> _assetManager -> AddTexture("tex1", "resources/textures/tex1.jpg"));
}

void ControllableDrone::Start() {
    this -> _front = glm::vec3(0.0f, 0.0f, 1.0f);
    this -> _right = glm::vec3(-1.0f, 0.0f, 0.0f);
    this -> _up = glm::vec3(0.0f, 1.0f, 0.0f);
    this -> MobileInstance(true);
    this -> MaximumVelocity(10.0f);
    this -> Acceleration(glm::vec3(0.0f, 0.0f, -2.5f));
    this -> _rotationSpeed = 2.0f;
    this -> _yaw = 0.0f;
    Instance::Start();
}

void ControllableDrone::Update(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray) {
    Instance::Update(dt, p_mouseDelta, p_keyPressedArray);
    this -> _checkKeysPressed(dt, p_keyPressedArray);
    this -> Rotation(glm::vec3(this -> Velocity().z * 4.0f, glm::degrees(-this -> _yaw), this -> Velocity().x * -3.0f));
    glm::vec3 direction = io::MovementDirectionFromKeyboard(p_keyPressedArray);
    if(glm::length(direction) > EPSILON) {
        this -> Acceleration(((this -> _front * direction.z) + (this -> _up * direction.y) + (this -> _right * direction.x)) * 20.0f);
    } else {
        this -> Acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

glm::vec3 ControllableDrone::FollowOffset() {
    return (this -> _front * -3.0f) + (this -> _up * 2.0f);
}

void ControllableDrone::_checkKeysPressed(double dt, bool *p_keyPressedArray) {
    bool changed = false;
    if(p_keyPressedArray[GLFW_KEY_Q]) {
        this -> _yaw -= this -> _rotationSpeed * dt;
        changed = true;
    }
    if(p_keyPressedArray[GLFW_KEY_E]) {
        this -> _yaw += this -> _rotationSpeed * dt;
        changed = true;
    }
    if(changed) {
        this -> _recalculateVectors();
    }
}

GLfloat ControllableDrone::YRotationFollowOffset() { return this -> _yaw; }

void ControllableDrone::_recalculateVectors() {
    this -> _front = glm::vec3(-sin(this -> _yaw), 0, cos(this -> _yaw));
    this -> _front = glm::normalize(this -> _front);
    
    this -> _right = glm::normalize(glm::cross(this -> _front, glm::vec3(0.0, 1.0, 0.0))); // TODO: roll not used
    
    this -> _up = glm::normalize(glm::cross(this -> _right, this -> _front));
}
