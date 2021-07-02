//
//  Material.cpp
//  practice
//

#include "LightingMaterial.hpp"

LightingMaterial::LightingMaterial() {
    this -> _specularIntensity = 0.0f;
    this -> _specularPower = 0.0f;
}

LightingMaterial::~LightingMaterial() {
    this -> _clear();
}

bool LightingMaterial::Load(GLfloat p_specularIntensity, GLfloat p_specularPower) {
    this -> _specularIntensity = p_specularIntensity;
    this -> _specularPower = p_specularPower;
    return true;
}

void LightingMaterial::Use(GLuint uniformSpecularIntensity, GLuint uniformSpecularPower) const {
    glUniform1f(uniformSpecularIntensity, this -> _specularIntensity);
    glUniform1f(uniformSpecularPower, this -> _specularPower);
}

void LightingMaterial::Remove() {
    
}

GLfloat LightingMaterial::SpecularIntensity() { return this -> _specularIntensity; }

GLfloat LightingMaterial::SPecularPower() { return this -> _specularPower; }

void LightingMaterial::_copy(const LightingMaterial &p_that){
    
}

void LightingMaterial::_clear() {
    this -> _specularIntensity = 0.0f;
    this -> _specularPower = 0.0f;
}
