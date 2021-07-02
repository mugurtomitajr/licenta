//
//  PointLight.hpp
//  practice
//

#ifndef PointLight_hpp
#define PointLight_hpp

#include <cstdio>

#include "Light.hpp"

class PointLight : public Light {
public:
    PointLight();
    PointLight(glm::vec3 p_position, glm::vec3 p_attenuationFactors, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity);
    ~PointLight();
    
    void Use(GLuint p_uniformLightPosition, GLuint p_uniformLightAttenuation, GLuint p_uniformLightColor, GLuint p_uniformDiffuseIntensity, GLuint p_uniformAmbientIntensity, GLuint p_uniformSpecularIntensity);
    
    void Position(glm::vec3 p_value);
    glm::vec3 Position();
    
protected:
    glm::vec3 _position;
    glm::vec3 _attenuationFactors;
    
    virtual void _copy(const PointLight &p_that);
    virtual void _clear();
};

#endif /* PointLight_hpp */
