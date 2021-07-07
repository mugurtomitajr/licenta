//
//  threedim.hpp
//  practice
//

#ifndef threedim_hpp
#define threedim_hpp

#include <cstdio>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "PerlinNoise2D.hpp"
#include "../library/perlin_noise.hpp"

namespace threedim {

void RecalculateNormals(unsigned int *indices, int numOfIndices, GLfloat *vertices, int numOfVertices, unsigned int vertexDataCount, unsigned int normalDataOffset);

struct MeshData {
    std::vector<unsigned int> indices = std::vector<unsigned int>();
    std::vector<GLfloat> vertices = std::vector<GLfloat>();
};

MeshData GenerateCube();

MeshData GeneratePerlinPlane(glm::ivec2 index, unsigned int p_resolution);

MeshData GeneratePlane(unsigned int p_resolution, GLfloat *p_heightMap);

void AveragePointsOnEdgeToLowestResolution(unsigned int p_resolution, GLfloat *p_heightMap);

MeshData GeneratePerlinPlaneBySkipCount(glm::ivec2 index, unsigned int p_skip);

MeshData GeneratePlaneBySkipCount(unsigned int p_skip, GLfloat *p_heightMap);

GLfloat CurveLongValleysSteepMountains(GLfloat p_in);

GLfloat CurveSmoothTransition(GLfloat p_in);

GLfloat CurvePlatous(GLfloat p_in);

GLfloat CurveValleysAndPlatous(GLfloat p_in);

GLfloat CurveThreeLevels(GLfloat p_in);

void generatePerlinSeed(int p_resolution, GLfloat *p_seed);

void perlinNoise2D(int p_resolution, GLfloat *p_seed, int p_numOfOctaves, GLfloat p_bias, GLfloat *p_output);

};

#endif /* threedim_hpp */
