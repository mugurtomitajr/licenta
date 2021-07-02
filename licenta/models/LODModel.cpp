//
//  LODModel.cpp
//  practice
//

#include "LODModel.hpp"

LODModel::LODModel() : Model() {
    this -> _currentLODLevel = 0;
    this -> _lodMeshes = std::map<int, std::vector<Mesh*>>();
    this -> _runtimeGeneratedMeshes = std::vector<Mesh*>();
}

LODModel::LODModel(glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale) : Model(p_position, p_rotation, p_scale) {
    this -> _currentLODLevel = 0;
    this -> _lodMeshes = std::map<int, std::vector<Mesh*>>();
    this -> _runtimeGeneratedMeshes = std::vector<Mesh*>();
}

LODModel::~LODModel() {
    this -> _clear();
}

std::vector<Mesh*>* LODModel::Meshes() {
    if(!this -> _lodMeshes.count(this -> _currentLODLevel)) {
        this -> _lodMeshes[this -> _currentLODLevel] = this -> _requestLODMeshes(this -> _currentLODLevel);
    }
    return &(this -> _lodMeshes[this -> _currentLODLevel]);
}

std::vector<Mesh*> LODModel::AllMeshes() {
    return this -> _meshes; // TODO: decide if remove DeleteRuntimeGeneratedMeshes
}

void LODModel::CurrentLOD(int p_lod) {
    this -> _currentLODLevel = p_lod;
}

int LODModel::CurrentLOD() {
    return this -> _currentLODLevel;
}

void LODModel::DeleteRuntimeGeneratedMeshes() {
    for(auto mesh : this -> _runtimeGeneratedMeshes) {
        delete mesh;
    }
    this -> _lodMeshes = std::map<int, std::vector<Mesh*>>();
    this -> _runtimeGeneratedMeshes = std::vector<Mesh*>();
}

void LODModel::_addRuntimeGeneratedMesh(Mesh *p_mesh) {
    this -> _runtimeGeneratedMeshes.push_back(p_mesh);
}

std::vector<Mesh*> LODModel::_requestLODMeshes(int p_lodLevel) {
    return this -> _meshes;
}

void LODModel::_copy(const LODModel &p_that) {
    
}

void LODModel::_clear() {
    Model::_clear();
    this -> _currentLODLevel = 0;
    this -> _lodMeshes = std::map<int, std::vector<Mesh*>>();
    this -> _runtimeGeneratedMeshes = std::vector<Mesh*>();
}

