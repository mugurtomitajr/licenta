//
//  GeneratedBoardTile.cpp
//  practice
//

#include "GeneratedBoardTile.hpp"

GeneratedBoardTile::GeneratedBoardTile() : Instance() {
    this -> _index = glm::ivec2(0, 0);
    this -> _id = "";
    this -> _resolution = 2;
}

GeneratedBoardTile::GeneratedBoardTile(glm::ivec2 p_index, unsigned int p_resolution, Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale) : Instance(p_parent, p_position, p_rotation, p_scale) {
    this -> _index = p_index;
    this -> _id = "tile-" + std::to_string(this -> _index.x) + "-" + std::to_string(this -> _index.y);
    this -> _resolution = p_resolution;
}

GeneratedBoardTile::~GeneratedBoardTile() {this -> _clear();}

void GeneratedBoardTile::LoadOtherInstances(AssetManager *p_assetManager, RuntimeQueueManager *p_runtimeQueueManager) {
    Instance::LoadOtherInstances(p_assetManager, p_runtimeQueueManager);
    
    std::map<int, int> lodLevels = std::map<int, int>();
    lodLevels[0] = 129;
    lodLevels[1] = 65;
    lodLevels[2] = 33;
    lodLevels[3] = 17;
    
    GeneratedTileModel *model = new GeneratedTileModel(this -> _index, lodLevels, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    model -> CurrentLOD(3);
    this -> OverrideLightingMaterial(this -> _assetManager -> GetLightingMaterial("dull"));
    this -> _assetManager -> AddMeshlessModel(this -> _id.c_str(), model);
    this -> _model = model;
    this -> OverrideDiffuseMap(this -> _assetManager -> AddTexture("grass", "resources/textures/grass-repeating-2.jpg"));
    
    /*Instance *instance = new Instance(nullptr, glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(100, 1.0, 100));
    instance -> CurrentModel(this -> _assetManager -> GetModel("water-model"));
    this -> _runtimeQueueManager -> AddInstance(("water-" + this -> _id).c_str(), "water", instance);*/
}

void GeneratedBoardTile::Start() {
    
}

void GeneratedBoardTile::Update(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray) {
    
}

void GeneratedBoardTile::CheckLODLevel(glm::vec3 p_origin) {
    GLfloat distanceSquared = calc::DistancePointSquare2DSquared(glm::vec2(p_origin.x, p_origin.z), glm::vec2(this -> _position.x, this -> _position.z), 50.0f);
    int correctLOD = 0;
    if(distanceSquared <= 600) {
        correctLOD = 0;
    } else if(distanceSquared <= 2000) {
        correctLOD = 1;
    } else if(distanceSquared <= 6000) {
        correctLOD = 2;
    } else {
        correctLOD = 3;
    }
    if(this -> _model && ((GeneratedTileModel*) this -> _model) -> CurrentLOD() != correctLOD) {
        ((GeneratedTileModel*) this -> _model) -> CurrentLOD(correctLOD);
    }
}

void GeneratedBoardTile::_clear() {
    this -> _index = glm::ivec2(0, 0);
    this -> _id = "";
    this -> _resolution = 2;
}

