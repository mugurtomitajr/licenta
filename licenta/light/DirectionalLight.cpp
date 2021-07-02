//
//  DirectionalLight.cpp
//  practice
//

#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight() : Light() {
    this -> _direction = glm::vec3(0.0f, -1.0f, 0.0f); // TODO: normalize direction and remove from fragment shader
}

DirectionalLight::DirectionalLight(glm::vec3 p_direction, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity) : Light(p_color, p_diffuseIntensity, p_ambientIntensity, p_specularIntensity) {
    this -> _direction = p_direction;
}

DirectionalLight::~DirectionalLight() {
    this -> _clear();
}

void DirectionalLight::Use(GLuint p_uniformLightDirection, GLuint p_uniformLightColor, GLuint p_uniformDiffuseIntensity, GLuint p_uniformAmbientIntensity, GLuint p_uniformSpecularIntensity) {
    Light::Use(p_uniformLightColor, p_uniformDiffuseIntensity, p_uniformAmbientIntensity, p_uniformSpecularIntensity);
    glUniform3fv(p_uniformLightDirection, 1, glm::value_ptr(this -> _direction));
}


void DirectionalLight::_copy(const DirectionalLight &p_that) {
    Light::_copy(p_that);
}

void DirectionalLight::_clear() {
    Light::_clear();
    this -> _direction = glm::vec3(0.0f, -1.0f, 0.0f);
}
