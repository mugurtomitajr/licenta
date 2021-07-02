//
//  Skybox.hpp
//  practice
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include <cstdio>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "AssetManager.hpp"

class Skybox {
public:
    Skybox();
    ~Skybox();
    
    bool Load(Shader *p_shader, Mesh *p_mesh, std::vector<std::string> p_textures);
    void Render(glm::mat4 p_projectionMatrix, glm::mat4 p_viewMatrix);
    
private:
    Mesh* _mesh;
    Shader* _shader;
    
    GLuint _glId;
    
    void _copy(const Skybox &p_that);

    void _clear();

};

#endif /* Skybox_hpp */
