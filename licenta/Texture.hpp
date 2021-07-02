//
//  Texture.hpp
//  practice
//

#ifndef Texture_hpp
#define Texture_hpp

#include <cstdio>
#include <GL/glew.h>
#include "library/stb_image.h" 

class Texture {
public:
    Texture();
    Texture(const char *p_filepath);
    ~Texture();
    
    bool Load();
    void Use() const;
    
    bool IsLoaded();
    
    static void Remove();
    
private:
    GLuint _glId;
    int _width, _height, _bitDepth;
    bool _hasAlphaChannel;
    const char *_filepath;
    
    virtual void _copy(const Texture &p_that);
    virtual void _clear();
};

#endif /* Texture_hpp */
