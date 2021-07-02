//
//  Skybox.cpp
//  practice
//

#include "Skybox.hpp"

Skybox::Skybox() {
    
}

Skybox::~Skybox() {
    this -> _clear();
}

bool Skybox::Load(Shader *p_shader, Mesh *p_mesh, std::vector<std::string> p_textureFilepaths) {
    this -> _shader = p_shader;
    this -> _mesh = p_mesh;
    if(p_textureFilepaths.size() < 6) {
        fprintf(stdout, "Skybox: Not enough textures for skybox...\n");
        return false;
    }
    
    glGenTextures(1, &(this -> _glId));
    glBindTexture(GL_TEXTURE_CUBE_MAP, this -> _glId);
    int width = 0, height = 0, bitDepth = 0;
    for(unsigned int i = 0; i < 6; ++i) {
        unsigned char *textureData = stbi_load(p_textureFilepaths[i].c_str(), &width, &height, &bitDepth, 0);
        if(!textureData) {
            fprintf(stdout, "Skybox: Failed to load texture %s...\n", p_textureFilepaths[i].c_str());
            return false;
        }
        
        if(bitDepth == 3) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        } else if(bitDepth == 4) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        } else {
            fprintf(stdout, "Skybox: Unknown number of channels %s...\n", p_textureFilepaths[i].c_str());
            stbi_image_free(textureData);
            return false;
        }
        stbi_image_free(textureData);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    return true;
}

void Skybox::Render(glm::mat4 p_projectionMatrix, glm::mat4 p_viewMatrix) {
    glDepthMask(GL_FALSE);
    
    this -> _shader -> Use();
    p_viewMatrix = glm::mat4(glm::mat3(p_viewMatrix));
    this -> _shader -> ApplyProjectionMatrix(p_projectionMatrix);
    this -> _shader -> ApplyViewMatrix(p_viewMatrix);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this -> _glId);
    
    this -> _mesh -> Render(0.0f, 0.0f);
    
    glDepthMask(GL_TRUE);
}

void Skybox::_copy(const Skybox &p_that) {
    
}

void Skybox::_clear() {
    
}

