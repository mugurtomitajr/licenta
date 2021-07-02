//
//  Light.cpp
//  practice
//

#include "Light.hpp"

Light::Light() {
    this -> _color = glm::vec3(1.0f, 1.0f, 1.0f);
    this -> _diffuseIntensity = 1.0f;
    this -> _ambientIntensity = 1.0f;
    this -> _specularIntensity = 1.0f;
}

Light::Light(glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity) : Light() {
    this -> _color = p_color;
    this -> _diffuseIntensity = p_diffuseIntensity;
    this -> _ambientIntensity = p_ambientIntensity;
    this -> _specularIntensity = p_specularIntensity;
}

Light::~Light() {
    this -> _clear();
}

void Light::Use(GLuint p_uniformLightColor, GLuint p_uniformDiffuseIntensity, GLuint p_uniformAmbientIntensity, GLuint p_uniformSpecularIntensity) {
    glUniform3fv(p_uniformLightColor, 1, glm::value_ptr(this -> _color));
    glUniform1f(p_uniformDiffuseIntensity, this -> _diffuseIntensity);
    glUniform1f(p_uniformAmbientIntensity, this -> _ambientIntensity);
    glUniform1f(p_uniformSpecularIntensity, this -> _specularIntensity);
}

void Light::_copy(const Light &p_that) {
    
}

void Light::_clear() {
    this -> _color = glm::vec3(1.0f, 1.0f, 1.0f);
    this -> _diffuseIntensity = 1.0f;
    this -> _ambientIntensity = 1.0f;
    this -> _specularIntensity = 1.0f;
}
