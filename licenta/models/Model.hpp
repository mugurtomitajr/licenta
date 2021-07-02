//
//  Model.hpp
//  practice
//

#ifndef Model_hpp
#define Model_hpp

#include <cstdio>
#include <vector>
#include <string>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.hpp"
#include "../support/io.hpp"

class Model {
public:
    Model();
    Model(glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    ~Model();
    
    bool Load();
    bool Load(const char *p_filepath);
    void Render(const double &dt, const double &inter);
    
    void AddMesh(Mesh *p_mesh);
    virtual std::vector<Mesh*> *Meshes();
    virtual std::vector<Mesh*> AllMeshes();
    
    glm::mat4 *WorldMatrix();
    glm::vec3 Position();
    
    void Filepath(const char *p_filepath);
    const char *Filepath();
    const char *Rootpath();
    const char *Filename();
    
    Texture *OverrideDiffuseMap();
    void OverrideDiffuseMap(Texture *p_overrideDiffuseMap);
    
    virtual void DeleteRuntimeGeneratedMeshes();
    
protected:
    std::vector<Mesh*> _meshes = std::vector<Mesh*>();
    std::string _filepath, _rootpath, _filename;
    glm::vec3 _position, _rotation, _scale;
    glm::mat4 _worldMatrix;
    
    Texture *_overrideDiffuseMap;
    
    virtual void _copy(const Model &p_that);
    virtual void _clear();
};

#endif /* Model_hpp */
