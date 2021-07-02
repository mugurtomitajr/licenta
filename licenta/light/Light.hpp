//
//  Light.hpp
//  practice
//

#ifndef Light_hpp
#define Light_hpp

#include <cstdio>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light {
public:
    Light();
    Light(glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity);
    ~Light();
    
    void Use(GLuint p_uniformLightColor, GLuint p_uniformDiffuseIntensity, GLuint p_uniformAmbientIntensity, GLuint p_uniformSpecularIntensity);
    
protected:
    glm::vec3 _color;
    
    GLfloat _diffuseIntensity;
    GLfloat _ambientIntensity;
    GLfloat _specularIntensity;
    
    virtual void _copy(const Light &p_that);
    virtual void _clear();
};

#endif /* Light_hpp */
