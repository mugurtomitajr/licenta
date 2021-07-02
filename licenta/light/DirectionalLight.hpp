//
//  DirectionalLight.hpp
//  practice
//

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include <cstdio>

#include "Light.hpp"

class DirectionalLight : public Light {
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 p_direction, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity);
    ~DirectionalLight();
    
    void Use(GLuint p_uniformLightDirection, GLuint p_uniformLightColor, GLuint p_uniformDiffuseIntensity, GLuint p_uniformAmbientIntensity, GLuint p_uniformSpecularIntensity);
    
private:
    glm::vec3 _direction;
    
    virtual void _copy(const DirectionalLight &p_that);
    virtual void _clear();
};

#endif /* DirectionalLight_hpp */
