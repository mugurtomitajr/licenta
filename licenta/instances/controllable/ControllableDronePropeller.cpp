//
//  ControllableDronePropellerPropeller.cpp
//  practice
//

#include "ControllableDronePropeller.hpp"

ControllableDronePropeller::ControllableDronePropeller() : Instance() {}

ControllableDronePropeller::ControllableDronePropeller(bool p_isLeft, Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale) : Instance(p_parent, p_position, p_rotation, p_scale){
    this -> _isLeft = p_isLeft;
}

const char* ControllableDronePropeller::LoadCustomModelFilepath() {
    return "resources/models/drone/propeller.obj";
}

glm::vec3 ControllableDronePropeller::LoadCustomModelPosition() {
    return glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 ControllableDronePropeller::LoadCustomModelScale() {
    return glm::vec3(1.0f, 1.0f, 1.0f);
}

void ControllableDronePropeller::Start() {
    Instance::Start();
}

void ControllableDronePropeller::Update(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray) {
    Instance::Update(dt, p_mouseDelta, p_keyPressedArray);
    GLfloat delta = 720.0f * dt * (this -> _isLeft ? 1 : -1);
    this -> Rotation(glm::vec3(this -> _rotation.x, this -> _rotation.y + delta, this -> _rotation.z));
}
