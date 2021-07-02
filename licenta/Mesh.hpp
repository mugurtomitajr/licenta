//
//  Mesh.hpp
//  practice
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <cstdio>
#include <vector>
#include <string>
#include <GL/glew.h>

#include "Texture.hpp"
#include "LightingMaterial.hpp"

class Mesh {
public:
    Mesh();
    ~Mesh();
    
    bool Load(GLfloat *p_vertices, unsigned int p_numOfVertices, unsigned int *p_indices, unsigned int p_numOfIndices);
    void Render(double dt, double inter);
    void static Remove();
    
    void DiffuseMap(Texture *p_diffuseMap);
    Texture *DiffuseMap();
    
    void PropertiesMaterial(LightingMaterial *p_propertiesMaterial);
    LightingMaterial *PropertiesMaterial();
    
private:
    GLuint _vao, _vbo, _ibo;
    GLsizei _numOfIndices;
    Texture *_diffuseMap;
    LightingMaterial *_propertiesMaterial;
    
    virtual void _copy(const Mesh &p_that);
    virtual void _clear();
};

#endif /* Mesh_hpp */
