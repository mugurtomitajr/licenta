//
//  threedim.cpp
//  practice
//

#include "threedim.hpp"

void threedim::RecalculateNormals(unsigned int *indices, int numOfIndices, GLfloat *vertices, int numOfVertices, unsigned int vertexDataCount, unsigned int normalDataOffset) {
    for(unsigned int i = 0; i < numOfIndices; i+=3) {
        unsigned int in0 = indices[i] * vertexDataCount;
        unsigned int in1 = indices[i+1] * vertexDataCount;
        unsigned int in2 = indices[i+2] * vertexDataCount;
        glm::vec3 v1 = glm::vec3(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2 = glm::vec3(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
        in0 += normalDataOffset;
        in1 += normalDataOffset;
        in2 += normalDataOffset;
        vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
        vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
        vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
    }
    for(unsigned int i = 0; i < numOfVertices / vertexDataCount; ++i) {
        unsigned int normalOffset = i * vertexDataCount + normalDataOffset;
        glm::vec3 newNormal = glm::vec3(vertices[normalOffset], vertices[normalOffset + 1], vertices[normalOffset + 2]);
        newNormal = glm::normalize(newNormal);
        vertices[normalOffset] = newNormal.x;
        vertices[normalOffset + 1] = newNormal.y;
        vertices[normalOffset + 2] = newNormal.z;
    }
}

threedim::MeshData threedim::GenerateCube() {
    MeshData result;
    result.vertices = {
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };
    result.indices = {
        0, 1, 2,
        2, 1, 3,
        2, 3, 5,
        5, 3, 7,
        5, 7, 4,
        4, 7, 6,
        4, 6, 0,
        0, 6, 1,
        4, 0, 5,
        5, 0, 2,
        1, 6, 3,
        3, 6, 7
    };
    return result;
}

threedim::MeshData threedim::GeneratePerlinPlane(glm::ivec2 index, unsigned int p_resolution) {
    unsigned int doubleResolution = p_resolution * p_resolution;
    GLfloat *heightMap = new float[doubleResolution];
    std::memset(heightMap, 0, sizeof(GLfloat) * doubleResolution);
    GLfloat sampleScale = 1.0f;
    GLfloat terrainScale = 20.0f;
    
    //GLfloat *perlinSeed = new GLfloat[p_resolution * p_resolution];
    //generatePerlinSeed(p_resolution, perlinSeed);
    //perlinNoise2D(p_resolution, perlinSeed, 4, 1.0f, heightMap);
    
    const siv::PerlinNoise perlin(123);
    PerlinNoise2D perlinNoise = PerlinNoise2D(256);
    perlinNoise.Start(123);
    
    float mini = 200000;
    float maxi = -200000;
    
    for(unsigned int i = 0; i < p_resolution; ++i) {
        for(unsigned int j = 0; j < p_resolution; ++j) {
            int loc = i * p_resolution + j;
            //heightMap[loc] = perlin.accumulatedOctaveNoise2D_0_1((index.y + ((float)i / (float)(p_resolution - 1))) * scale, (index.x + ((float)j / (float)(p_resolution - 1))) * scale, 8);
            heightMap[loc] = perlinNoise.Sample((index.y + ((float)i / (float)(p_resolution - 1))) * sampleScale, (index.x + ((float)j / (float)(p_resolution - 1))) * sampleScale);
            if(heightMap[loc] < mini) {
                mini = heightMap[loc];
            }
            if(heightMap[loc] > maxi) {
                maxi = heightMap[loc];
            }
        }
    }
    
    float fractionalPart = 0.0f;
    int integerPart = 0;
    for(int i = 0; i < doubleResolution; ++i) {
        heightMap[i] = heightMap[i] + 0.5f;
        integerPart = (int) std::floor(heightMap[i]);
        fractionalPart = heightMap[i] - integerPart;
        
        //heightMap[i] = integerPart + fractionalPart;
        heightMap[i] = integerPart + CurveValleysAndPlatous(fractionalPart);
        //heightMap[i] = integerPart + CurveLongValleysSteepMountains(fractionalPart);
        //heightMap[i] = integerPart + CurveSmoothTransition(fractionalPart);
        
        
        heightMap[i] *= terrainScale;
    }
    
    //fprintf(stdout, "mini: %llf; maxi: %llf;\n", mini, maxi);
    
    AveragePointsOnEdgeToLowestResolution(p_resolution, heightMap);
    threedim::MeshData result = GeneratePlane(p_resolution, heightMap);
    //delete[] perlinSeed;
    delete[] heightMap;
    return result;
}

GLfloat threedim::CurveLongValleysSteepMountains(GLfloat p_in) {
    GLfloat out = p_in * p_in * p_in * p_in;
    return glm::clamp(out, 0.0f, 1.0f);
}

GLfloat threedim::CurveSmoothTransition(GLfloat p_in) {
    GLfloat out = sin(p_in * 1.5708);
    out = out * out;
    return glm::clamp(out, 0.0f, 1.0f);
}

GLfloat threedim::CurvePlatous(GLfloat p_in) {
    if(p_in > 0.6f) return 1.0f;
    GLfloat out = sin(p_in * 1.5708 + p_in);
    out = out * out;
    return glm::clamp(out, 0.0f, 1.0f);
}

GLfloat threedim::CurveValleysAndPlatous(GLfloat p_in) {
    if(p_in > 0.73f) return 1.0f;
    if(p_in < 0.122) return 0.0f;
    GLfloat out = sin((p_in-0.2f) * 1.5708 + p_in);
    out = out * out;
    return glm::clamp(out, 0.0f, 1.0f);
}

GLfloat threedim::CurveThreeLevels(GLfloat p_in) {
    if(p_in > 0.9) return 1.0f;
    if(p_in < 0.1) return 0.0f;
    GLfloat out = 2 * p_in - 1;
    out = out * out * out + 0.5f;
    return glm::clamp(out, 0.0f, 1.0f);
}


void threedim::AveragePointsOnEdgeToLowestResolution(unsigned int p_resolution, GLfloat *p_heightMap) {
    int relevantPow = 0;
    
    if(p_resolution == 17) relevantPow = 1;
    else if(p_resolution == 33) relevantPow = 2;
    else if(p_resolution == 65) relevantPow = 4;
    else if(p_resolution == 129) relevantPow = 8;
    
    if(relevantPow == 0) {
        return; // not a good resolution
    }
    
    int correctPoint = 0;
    int nextCorrectPoint = correctPoint + relevantPow;
    int offset = p_resolution * (p_resolution - 1);
    
    for(int i = 1; i < p_resolution - 1; ++i) {
        if(i % relevantPow == 0) {
            correctPoint += relevantPow;
            nextCorrectPoint = correctPoint + relevantPow;
            if(nextCorrectPoint > p_resolution) {
                break;
            }
        } else {
            p_heightMap[i] = p_heightMap[correctPoint] + (p_heightMap[nextCorrectPoint] - p_heightMap[correctPoint]) * (i % relevantPow) / (float) relevantPow;
            p_heightMap[i + offset] = p_heightMap[correctPoint + offset] + (p_heightMap[nextCorrectPoint + offset] - p_heightMap[correctPoint + offset]) * (i % relevantPow) / (float) relevantPow;
            
            p_heightMap[i*p_resolution] = p_heightMap[correctPoint*p_resolution] + (p_heightMap[nextCorrectPoint*p_resolution] - p_heightMap[correctPoint*p_resolution]) * (i % relevantPow) / (float) relevantPow;
            p_heightMap[i*p_resolution + (p_resolution - 1)] = p_heightMap[correctPoint*p_resolution + (p_resolution - 1)] + (p_heightMap[nextCorrectPoint*p_resolution + (p_resolution - 1)] - p_heightMap[correctPoint*p_resolution + (p_resolution - 1)]) * (i % relevantPow) / (float) relevantPow;
        }
    }
}

threedim::MeshData threedim::GeneratePlane(unsigned int p_resolution, GLfloat *p_heightMap) {
    
    threedim::MeshData result;
    result.indices = std::vector<unsigned int>();
    result.vertices = std::vector<GLfloat>();
    float u = 0.0f;
    float v = 0.0f;
    if(p_resolution <= 1) return result;
    for(unsigned int i = 0; i < p_resolution; ++i) {
        for(unsigned int j = 0; j < p_resolution; ++j) {
            u = (1.0f / (float) (p_resolution - 1)) * j;
            v = (1.0f / (float) (p_resolution - 1)) * i;
            result.vertices.push_back(u - 0.5f);
            if(p_heightMap) {
                result.vertices.push_back(p_heightMap[i * p_resolution + j]);
            } else {
                result.vertices.push_back(0.0f);
            }
            result.vertices.push_back(v - 0.5f);
            
            result.vertices.push_back(u);
            result.vertices.push_back(v);
            
            result.vertices.push_back(0.0f);
            result.vertices.push_back(0.0f);
            result.vertices.push_back(0.0f);
        }
    }
    
    for(unsigned int i = 0; i < p_resolution-1; ++i) {
        for(unsigned int j = 0; j < p_resolution-1; ++j) {
            unsigned int currentVertex = i * p_resolution + j;
            unsigned int nextLineVertex = (i + 1) * p_resolution + j;
            result.indices.push_back(currentVertex);
            result.indices.push_back(nextLineVertex);
            result.indices.push_back(currentVertex + 1);
            
            result.indices.push_back(currentVertex + 1);
            result.indices.push_back(nextLineVertex);
            result.indices.push_back(nextLineVertex + 1);
        }
    }
    
    RecalculateNormals(result.indices.data(), result.indices.size(), result.vertices.data(), result.vertices.size(), 8, 5);
    
    return result;
}

threedim::MeshData threedim::GeneratePerlinPlaneBySkipCount(glm::ivec2 index, unsigned int p_skip) {
    unsigned int defaultResolution = 97;
    
    GLfloat *heightMap = new float[defaultResolution * defaultResolution];
    std::memset(heightMap, 0, sizeof(GLfloat) * defaultResolution * defaultResolution);
    
    const siv::PerlinNoise perlin(123);
    
    for(unsigned int i = 0; i < defaultResolution; ++i) {
        for(unsigned int j = 0; j < defaultResolution; ++j) {
            heightMap[i * defaultResolution + j] = perlin.accumulatedOctaveNoise2D_0_1(index.y + ((float)i / (float)(defaultResolution - 1)), index.x + ((float)j / (float)(defaultResolution - 1)), 16) * 20.0f;
        }
    }
    
    threedim::MeshData result = GeneratePlaneBySkipCount(p_skip, heightMap);
    delete[] heightMap;
    return result;
}

threedim::MeshData threedim::GeneratePlaneBySkipCount(unsigned int p_skip, GLfloat *p_heightMap) {
    threedim::MeshData result;
    unsigned int step = p_skip + 1;
    unsigned int defaultResolution = 97;
    unsigned int nbOfVerticesPerLine = ((defaultResolution - 1) / step) + 1; // step can be 1, 2, 3, 4 - so it divides perfectly
    result.indices = std::vector<unsigned int>();
    result.vertices = std::vector<GLfloat>();
    float u = 0.0f;
    float v = 0.0f;
    for(unsigned int i = 0; i < defaultResolution; i += step) {
        for(unsigned int j = 0; j < defaultResolution; j += step) {
            u = (1.0f / (float) (defaultResolution - 1)) * j;
            v = (1.0f / (float) (defaultResolution - 1)) * i;
            result.vertices.push_back(u - 0.5f);
            if(p_heightMap) {
                result.vertices.push_back(p_heightMap[i * defaultResolution + j]);
            } else {
                result.vertices.push_back(0.0f);
            }
            result.vertices.push_back(v - 0.5f);
            
            result.vertices.push_back(u);
            result.vertices.push_back(v);
            
            result.vertices.push_back(0.0f);
            result.vertices.push_back(0.0f);
            result.vertices.push_back(0.0f);
        }
    }
    
    for(unsigned int i = 0; i < nbOfVerticesPerLine-1; ++i) {
        for(unsigned int j = 0; j < nbOfVerticesPerLine-1; ++j) {
            unsigned int currentVertex = i * nbOfVerticesPerLine + j;
            unsigned int nextLineVertex = (i + 1) * nbOfVerticesPerLine + j;
            result.indices.push_back(currentVertex);
            result.indices.push_back(nextLineVertex);
            result.indices.push_back(currentVertex + 1);
            
            result.indices.push_back(currentVertex + 1);
            result.indices.push_back(nextLineVertex);
            result.indices.push_back(nextLineVertex + 1);
        }
    }
    
    RecalculateNormals(result.indices.data(), result.indices.size(), result.vertices.data(), result.vertices.size(), 8, 5);
    
    return result;
}



void threedim::generatePerlinSeed(int p_resolution, GLfloat *p_seed) {
    int length = p_resolution * p_resolution;
    for (int i = 0; i < length; ++i) {
        p_seed[i] = (GLfloat) rand() / (GLfloat) RAND_MAX;
    }
}

void threedim::perlinNoise2D(int p_resolution, GLfloat *p_seed, int p_numOfOctaves, GLfloat p_bias, GLfloat *p_output){
    for (int x = 0; x < p_resolution; x++) {
        for (int y = 0; y < p_resolution; y++) {
            
            GLfloat fNoise = 0.0f;
            GLfloat fScaleAcc = 0.0f;
            GLfloat fScale = 1.0f;

            for (int o = 0; o < p_numOfOctaves; o++) {
                int nPitch = (p_resolution - 1) >> o;
                int nSampleX1 = (x / nPitch) * nPitch;
                int nSampleY1 = (y / nPitch) * nPitch;
                
                int nSampleX2 = (nSampleX1 + nPitch) % p_resolution;
                int nSampleY2 = (nSampleY1 + nPitch) % p_resolution;

                GLfloat fBlendX = (GLfloat)(x - nSampleX1) / (GLfloat)nPitch;
                GLfloat fBlendY = (GLfloat)(y - nSampleY1) / (GLfloat)nPitch;

                GLfloat fSampleT = (1.0f - fBlendX) * p_seed[nSampleY1 * p_resolution + nSampleX1] + fBlendX * p_seed[nSampleY1 * p_resolution + nSampleX2];
                GLfloat fSampleB = (1.0f - fBlendX) * p_seed[nSampleY2 * p_resolution + nSampleX1] + fBlendX * p_seed[nSampleY2 * p_resolution + nSampleX2];

                fScaleAcc += fScale;
                fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
                fScale = fScale / p_bias;
            }

            p_output[y * p_resolution + x] = fNoise / fScaleAcc;
        }
    }
    
}
