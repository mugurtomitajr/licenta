//
//  PointLight.cpp
//  practice
//

#include "PointLight.hpp"

PointLight::PointLight() : Light() {
    this -> _position = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _attenuationFactors = glm::vec3(0.1f, 0.2f, 0.3f); // aF.x * x^2 + aF.y * x + aF.z
}

PointLight::PointLight(glm::vec3 p_position, glm::vec3 p_attenuationFactors, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity) : Light(p_color, p_diffuseIntensity, p_ambientIntensity, p_specularIntensity) {
    this -> _position = p_position;
    this -> _attenuationFactors = p_attenuationFactors;
}

PointLight::~PointLight() {
    this -> _clear();
}

void PointLight::Use(GLuint p_uniformLightPosition, GLuint p_uniformLightAttenuation, GLuint p_uniformLightColor, GLuint p_uniformDiffuseIntensity, GLuint p_uniformAmbientIntensity, GLuint p_uniformSpecularIntensity) {
    Light::Use(p_uniformLightColor, p_uniformDiffuseIntensity, p_uniformAmbientIntensity, p_uniformSpecularIntensity);
    glUniform3fv(p_uniformLightPosition, 1, glm::value_ptr(this -> _position));
    glUniform3fv(p_uniformLightAttenuation, 1, glm::value_ptr(this -> _attenuationFactors));
}

void PointLight::Position(glm::vec3 p_value) {
    this -> _position = p_value;
}

glm::vec3 PointLight::Position() {
    return this -> _position;
}

void PointLight::_copy(const PointLight &p_that) {
    Light::_copy(p_that);
}

void PointLight::_clear() {
    Light::_clear();
    this -> _position = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _attenuationFactors = glm::vec3(0.1f, 0.2f, 0.3f);
}
