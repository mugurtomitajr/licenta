//
//  SpotLight.cpp
//  practice
//

#include "SpotLight.hpp"
 
SpotLight::SpotLight() : PointLight() {
    this -> _direction = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));
    this -> _edge = 20.0f;
    this -> _transformedEdge = cosf(glm::radians(this -> _edge));
}

SpotLight::SpotLight(glm::vec3 p_direction, GLfloat p_edge, glm::vec3 p_position, glm::vec3 p_attenuationFactors, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity) : PointLight(p_position, p_attenuationFactors, p_color, p_diffuseIntensity, p_ambientIntensity, p_specularIntensity) {
    this -> _direction = glm::normalize(p_direction);
    this -> _edge = p_edge;
    this -> _transformedEdge = cosf(glm::radians(this -> _edge));
}

SpotLight::~SpotLight() {
    this -> _clear();
}

void SpotLight::Use(GLuint p_uniformLightDirection, GLuint p_uniformLightEdge, GLuint p_uniformLightPosition, GLuint p_uniformLightAttenuation, GLuint p_uniformLightColor, GLuint p_uniformDiffuseIntensity, GLuint p_uniformAmbientIntensity, GLuint p_uniformSpecularIntensity) {
    PointLight::Use(p_uniformLightPosition, p_uniformLightAttenuation, p_uniformLightColor, p_uniformDiffuseIntensity, p_uniformAmbientIntensity, p_uniformSpecularIntensity);
    glUniform3fv(p_uniformLightDirection, 1, glm::value_ptr(this -> _direction));
    glUniform1f(p_uniformLightEdge, this -> _transformedEdge);
}

void SpotLight::Direction(glm::vec3 p_direction) {
    this -> _direction = glm::normalize(p_direction);
}

glm::vec3 SpotLight::Direction() {
    return this -> _direction;
}

void SpotLight::_copy(const SpotLight &p_that) {
    PointLight::_copy(p_that);
}

void SpotLight::_clear() {
    PointLight::_clear();
    this -> _direction = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));
    this -> _edge = 20.0f;
    this -> _transformedEdge = cosf(glm::radians(this -> _edge));
}

