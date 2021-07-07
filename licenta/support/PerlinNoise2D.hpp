//
//  PerlinNoise2D.hpp
//  licenta
//

#ifndef PerlinNoise2D_hpp
#define PerlinNoise2D_hpp

#include <cstdio>
#include <random>
#include <algorithm>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>

class PerlinNoise2D {
public:
    PerlinNoise2D(unsigned int p_dimension);
    ~PerlinNoise2D();
    
    void Start(int p_seed);
    
    GLfloat Sample(GLfloat p_x, GLfloat p_y);
    GLfloat Sample(GLfloat p_x, GLfloat p_y, int p_octaves, GLfloat p_amplitudeReduction, GLfloat p_sampleFactor);
private:
    
    unsigned int _dimension;
    unsigned int _dimensionMask;
    unsigned int *_permutations;
    glm::vec3 *_vectors;
    
    
    GLfloat _valueAt(GLfloat p_x, GLfloat p_y);
    int _permute(int p_x, int p_y, int p_z);
    GLfloat _smoothstep(GLfloat p_in);
    
    void _clear();
};

#endif /* PerlinNoise2D_hpp */
