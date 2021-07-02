//
//  GeneratedTileModel.cpp
//  practice
//

#include "GeneratedTileModel.hpp"

GeneratedTileModel::GeneratedTileModel() : LODModel() {
    this -> _lodLevelResolution = std::map<int, int>();
    this -> _index = glm::ivec2(0, 0);
}

GeneratedTileModel::GeneratedTileModel(glm::ivec2 p_index, std::map<int, int> p_lodLevelResolution, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale) : LODModel(p_position, p_rotation, p_scale) {
    this -> _index = p_index;
    this -> _lodLevelResolution = p_lodLevelResolution;
}

GeneratedTileModel::~GeneratedTileModel() {
    this -> _clear();
}

std::vector<Mesh*> GeneratedTileModel::_requestLODMeshes(int p_lodLevel) {
    int resolution = 64;
    if(this -> _lodLevelResolution.count(p_lodLevel)) {
        resolution = this -> _lodLevelResolution[p_lodLevel];
    }
    threedim::MeshData meshData = threedim::GeneratePerlinPlane(this -> _index, resolution);
    Mesh *generatedMesh = new Mesh();
    if(generatedMesh -> Load(meshData.vertices.data(), (unsigned int) meshData.vertices.size(), meshData.indices.data(), (unsigned int) meshData.indices.size())) {
        return {generatedMesh};
    }
    return {};
}

void GeneratedTileModel::_copy(const GeneratedTileModel &p_that) {
    
}

void GeneratedTileModel::_clear() {
    LODModel::_clear();
    this -> _index = glm::ivec2(0, 0);
    this -> _lodLevelResolution = std::map<int, int>();
}
