//
//  Model.cpp
//  practice
//

#include "Model.hpp"
 
Model::Model() {
    this -> _meshes = std::vector<Mesh*>();
    this -> Filepath("");
    this -> _position = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    this -> _worldMatrix = glm::mat4(1.0f);
    this -> _overrideDiffuseMap = nullptr;
}

Model::Model(glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale) : Model() {
    this -> _position = p_position;
    this -> _rotation = p_rotation;
    this -> _scale = p_scale;
    this -> _worldMatrix = glm::translate(this -> _worldMatrix, this -> _position);
    this -> _worldMatrix = glm::rotate(this -> _worldMatrix, glm::radians(this -> _rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    this -> _worldMatrix = glm::rotate(this -> _worldMatrix, glm::radians(this -> _rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this -> _worldMatrix = glm::rotate(this -> _worldMatrix, glm::radians(this -> _rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    this -> _worldMatrix = glm::scale(this -> _worldMatrix, this -> _scale);
}

Model::~Model() {
    this -> _clear();
}

bool Model::Load() {
    this -> Filepath("");
    return true;
}

bool Model::Load(const char *p_filepath) {
    this -> Filepath(p_filepath);
    return true;
}

void Model::AddMesh(Mesh *p_mesh) {
    this -> _meshes.push_back(p_mesh);
}

std::vector<Mesh*>* Model::Meshes() {
    return &(this -> _meshes);
}

std::vector<Mesh*> Model::AllMeshes() {
    return this -> _meshes;
}

glm::mat4* Model::WorldMatrix() { return &(this -> _worldMatrix); }

glm::vec3 Model::Position() { return this -> _position; }

void Model::Filepath(const char *p_filepath) {
    this -> _filepath = p_filepath;
    this -> _rootpath = io::RootpathFromFilepath(p_filepath);
    this -> _filename = io::FilenameFromFilepath(p_filepath);
}

const char* Model::Filepath() { return this -> _filepath.c_str(); }

const char* Model::Rootpath() { return this -> _rootpath.c_str(); }

const char* Model::Filename() { return this -> _filename.c_str(); }

void Model::OverrideDiffuseMap(Texture *p_overrideDiffuseMap) { this -> _overrideDiffuseMap = p_overrideDiffuseMap; }

Texture* Model::OverrideDiffuseMap() { return this -> _overrideDiffuseMap; }

void Model::DeleteRuntimeGeneratedMeshes() {}

void Model::_copy(const Model &p_that) {
    
}

void Model::_clear() {
    this -> _meshes = std::vector<Mesh*>();
    this -> Filepath("");
    this -> _position = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    this -> _worldMatrix = glm::mat4(1.0f);
    this -> _overrideDiffuseMap = nullptr;
}
