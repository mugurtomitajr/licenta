//
//  Texture.cpp
//  practice
//

#include "Texture.hpp"

Texture::Texture() {
    this -> _glId = 0;
    
    this -> _width = 0;
    this -> _height = 0;
    this -> _bitDepth = 0;
    
    this -> _hasAlphaChannel = false;
    
    this -> _filepath = "";
}

Texture::Texture(const char *p_filepath) : Texture() {
    this -> _filepath = p_filepath;
}

Texture::~Texture() {
    this -> _clear();
}

bool Texture::Load() {
    unsigned char *textureData = stbi_load(this -> _filepath, &this -> _width, &this -> _height, &this -> _bitDepth, 0);
    
    if(this -> _bitDepth == 4) {
        this -> _hasAlphaChannel = true;
    } else if(this -> _bitDepth < 3) {
        stbi_image_free(textureData);
        return false;
    }
    
    if( !textureData ) {
        fprintf(stdout, "Texture %s not found...\n", this -> _filepath);
        return false;
    }
    
    glGenTextures(1, &this -> _glId);
    glBindTexture(GL_TEXTURE_2D, this -> _glId);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if(this -> _hasAlphaChannel) {
        if(textureData) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this -> _width, this -> _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        }
    } else {
        if(textureData) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this -> _width, this -> _height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        }
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    stbi_image_free(textureData);
    
    return true;
}

void Texture::Use() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this -> _glId);
}

bool Texture::IsLoaded() {
    return this -> _glId != 0;
}

void Texture::Remove() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::_clear() {
    if( this -> _glId != 0 ) {
        glDeleteTextures(1, &this -> _glId);
    }
    this -> _glId = 0;
    this -> _width = 0;
    this -> _height = 0;
    this -> _bitDepth = 0;
    
    this -> _hasAlphaChannel = false;
    
    this -> _filepath = "";
}

void Texture::_copy(const Texture &p_that) {
    
}

