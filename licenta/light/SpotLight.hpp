//
//  SpotLight.hpp
//  practice
//

#ifndef SpotLight_hpp
#define SpotLight_hpp

#include <cstdio>

#include "PointLight.hpp"

class SpotLight : public PointLight {
public:
    SpotLight();
    SpotLight(glm::vec3 p_direction, GLfloat p_edge, glm::vec3 p_position, glm::vec3 p_attenuationFactors, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity);
    ~SpotLight();
    
    void Use(GLuint p_uniformLightDirection, GLuint p_uniformLightEdge, GLuint p_uniformLightPosition, GLuint p_uniformLightAttenuation, GLuint p_uniformLightColor, GLuint p_uniformDiffuseIntensity, GLuint p_uniformAmbientIntensity, GLuint p_uniformSpecularIntensity);
    
    void Direction(glm::vec3 p_direction);
    glm::vec3 Direction();
    
protected:
    glm::vec3 _direction;
    GLfloat _edge, _transformedEdge;
    
    virtual void _copy(const SpotLight &p_that);
    virtual void _clear();
};

#endif /* SpotLight_hpp */
