//
//  Material.hpp
//  practice
//

#ifndef Material_hpp
#define Material_hpp

#include <cstdio>
#include <string>
#include <GL/glew.h>

#include "Texture.hpp"

class LightingMaterial {
public:
    LightingMaterial();
    ~LightingMaterial();
    
    bool Load(GLfloat p_specularIntensity, GLfloat p_specularPower);
    void Use(GLuint uniformSpecularIntensity, GLuint uniformSpecularPower) const;
    void Free();
    
    static void Remove();
    
    GLfloat SpecularIntensity();
    GLfloat SPecularPower();
    
private:
    GLfloat _specularIntensity;
    GLfloat _specularPower;
    
    virtual void _copy(const LightingMaterial &p_that);
    virtual void _clear();
};

#endif /* Material_hpp */
