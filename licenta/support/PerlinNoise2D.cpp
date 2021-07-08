//
//  PerlinNoise2D.cpp
//  licenta
//

#include "PerlinNoise2D.hpp"

PerlinNoise2D::PerlinNoise2D(unsigned int p_dimension) {
    this -> _dimension = p_dimension;
    this -> _dimensionMask = p_dimension - 1;
    this -> _permutations = new unsigned int[this -> _dimension * 2];
    this -> _vectors = new glm::vec3[this -> _dimension];
}

PerlinNoise2D::~PerlinNoise2D() {
    this -> _clear();
}

void PerlinNoise2D::Start(int p_seed) {
    std::mt19937 generator(p_seed);
    std::uniform_real_distribution<float> distribution;
    auto randomFloatUniformDistribution = std::bind(distribution, generator);
    for (unsigned i = 0; i < this -> _dimension; ++i) {
        this -> _vectors[i] = glm::vec3(2 * randomFloatUniformDistribution() - 1, 2 * randomFloatUniformDistribution() - 1, 2 * randomFloatUniformDistribution() - 1);
        this -> _vectors[i] = glm::normalize(this -> _vectors[i]);
        this -> _permutations[i] = i;
    }

    std::uniform_int_distribution<int> distributionInt;
    auto randomIntUniformDistribution = std::bind(distributionInt, generator);

    for (unsigned int i = 0; i < this -> _dimension; ++i) {
        std::swap(this -> _permutations[i], this -> _permutations[randomIntUniformDistribution() & this -> _dimensionMask]);
    }
    for (unsigned int i = 0; i < this -> _dimension; ++i) {
        this -> _permutations[this -> _dimension + i] = this -> _permutations[i];
    }
}

GLfloat PerlinNoise2D::Sample(GLfloat p_x, GLfloat p_y) {
    return this -> Sample(p_x, p_y, 8, 2.0f, 2.0f);
}

GLfloat PerlinNoise2D::Sample(GLfloat p_x, GLfloat p_y, int p_octaves, GLfloat p_amplitudeReduction, GLfloat p_sampleFactor) {
    
    GLfloat result = 0.0f;
    GLfloat amplification = 1.0f;

    for (unsigned int i = 0; i < p_octaves; ++i){
        result += this -> _valueAt(p_x, p_y) * amplification;
        p_x *= p_sampleFactor;
        p_y *= p_sampleFactor;
        amplification /= p_amplitudeReduction;
    }

    return result;
}

GLfloat PerlinNoise2D::_valueAt(GLfloat p_x, GLfloat p_y) {
    
    GLfloat p_z = 0.0f;
    glm::ivec3 directMatchPoint = glm::ivec3(((int)std::floor(p_x)) & this -> _dimensionMask, ((int)std::floor(p_y)) & this -> _dimensionMask, ((int)std::floor(p_z)) & this -> _dimensionMask);
    glm::ivec3 offsetMatchPoint = glm::ivec3((directMatchPoint.x + 1) & this -> _dimensionMask,  (directMatchPoint.y + 1) & this -> _dimensionMask,  (directMatchPoint.z + 1) & this -> _dimensionMask);

    glm::vec3 fractional = glm::vec3(p_x - ((int)std::floor(p_x)), p_y - ((int)std::floor(p_y)), p_z - ((int)std::floor(p_z)));
    glm::vec3 step = glm::vec3(this -> _smoothstep(fractional.x), this -> _smoothstep(fractional.y), this -> _smoothstep(fractional.z));

    const glm::vec3 &vector000 = this -> _vectors[this -> _permute(directMatchPoint.x, directMatchPoint.y, directMatchPoint.z)];
    const glm::vec3 &vector100 = this -> _vectors[this -> _permute(offsetMatchPoint.x, directMatchPoint.y, directMatchPoint.z)];
    const glm::vec3 &vector010 = this -> _vectors[this -> _permute(directMatchPoint.x, offsetMatchPoint.y, directMatchPoint.z)];
    const glm::vec3 &vector110 = this -> _vectors[this -> _permute(offsetMatchPoint.x, offsetMatchPoint.y, directMatchPoint.z)];

    const glm::vec3 &vector001 = this -> _vectors[this -> _permute(directMatchPoint.x, directMatchPoint.y, offsetMatchPoint.z)];
    const glm::vec3 &vector101 = this -> _vectors[this -> _permute(offsetMatchPoint.x, directMatchPoint.y, offsetMatchPoint.z)];
    const glm::vec3 &vector011 = this -> _vectors[this -> _permute(directMatchPoint.x, offsetMatchPoint.y, offsetMatchPoint.z)];
    const glm::vec3 &vector111 = this -> _vectors[this -> _permute(offsetMatchPoint.x, offsetMatchPoint.y, offsetMatchPoint.z)];
    
    glm::vec3 directPoint = glm::vec3(fractional.x, fractional.y, fractional.z);
    glm::vec3 offsetPoint = glm::vec3(fractional.x - 1, fractional.y - 1, fractional.z - 1);

    glm::vec3 point000 = glm::vec3(directPoint.x, directPoint.y, directPoint.z);
    glm::vec3 point100 = glm::vec3(offsetPoint.x, directPoint.y, directPoint.z);
    glm::vec3 point010 = glm::vec3(directPoint.x, offsetPoint.y, directPoint.z);
    glm::vec3 point110 = glm::vec3(offsetPoint.x, offsetPoint.y, directPoint.z);

    glm::vec3 point001 = glm::vec3(directPoint.x, directPoint.y, offsetPoint.z);
    glm::vec3 point101 = glm::vec3(offsetPoint.x, directPoint.y, offsetPoint.z);
    glm::vec3 point011 = glm::vec3(directPoint.x, offsetPoint.y, offsetPoint.z);
    glm::vec3 point111 = glm::vec3(offsetPoint.x, offsetPoint.y, offsetPoint.z);

    float a = glm::lerp(glm::dot(vector000, point000), glm::dot(vector100, point100), step.x);
    float b = glm::lerp(glm::dot(vector010, point010), glm::dot(vector110, point110), step.x);
    float c = glm::lerp(glm::dot(vector001, point001), glm::dot(vector101, point101), step.x);
    float d = glm::lerp(glm::dot(vector011, point011), glm::dot(vector111, point111), step.x);

    float e = glm::lerp(a, b, step.y);
    float f = glm::lerp(c, d, step.y);

    return glm::lerp(e, f, step.z);
}

int PerlinNoise2D::_permute(int p_x, int p_y, int p_z) {
    return this -> _permutations[this -> _permutations[this -> _permutations[p_x] + p_y] + p_z];
}

GLfloat PerlinNoise2D::_smoothstep(GLfloat p_in) {
    GLfloat p_out = glm::clamp(p_in, 0.0f, 1.0f);
    return p_out * p_out * (3 - 2 * p_out);
}

void PerlinNoise2D::_clear() {
    if(this -> _permutations) {
        delete[] this -> _permutations;
        this -> _permutations = nullptr;
    }
    if(this -> _vectors) {
        delete[] this -> _vectors;
        this -> _vectors = nullptr;
    }
    this -> _dimension = 0;
    this -> _dimensionMask = 0;
}
