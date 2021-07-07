//
//  GeneratedBoardManager.cpp
//  practice
//

#include "GeneratedBoardManager.hpp"

GeneratedBoardManager::GeneratedBoardManager() : Instance() {}

GeneratedBoardManager::GeneratedBoardManager(Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale) : Instance(p_parent, p_position, p_rotation, p_scale) {}

GeneratedBoardManager::~GeneratedBoardManager() {this -> _clear();}

void GeneratedBoardManager::LoadOtherInstances(AssetManager *p_assetManager, RuntimeQueueManager *p_runtimeQueueManager) {
    Instance::LoadOtherInstances(p_assetManager, p_runtimeQueueManager);
}

void GeneratedBoardManager::Start() {
    this -> _tileSize = 60.0f;
}

void GeneratedBoardManager::Update(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray) {
    glm::vec3 cameraPosition = this -> _camera -> Position(); // (this -> _camera -> Front() * this -> _camera -> Position().y * 1.0f) - maybe instead use cos(cameraFront, tileCenter-cameraPos) < cos(90deg)
    glm::ivec2 currentIndex = glm::ivec2((int) floor((cameraPosition.x + (this -> _tileSize / 2.0f)) / this -> _tileSize), (int) floor((cameraPosition.z + (this -> _tileSize / 2.0f)) / this -> _tileSize));
    long int loopIndex;
    std::map<long int, bool> activeTiles = std::map<long int, bool> ();
    std::vector<long int> removed = std::vector<long int> ();
    int offsetSearch = 4;
    
    //currentIndex = glm::ivec2(-2, -1);
    //offsetSearch = 0;
    
    for(int i = currentIndex.x - offsetSearch; i <= currentIndex.x + offsetSearch; ++i) {
        for(int j = currentIndex.y - offsetSearch; j <= currentIndex.y + offsetSearch; ++j) {
            loopIndex = i * GENERATED_BOARD_MAX_ELEMENT_SIZE * 2 + j; // * 2 to compensate for indices in j with (-)
            activeTiles[loopIndex] = true;
            if(!this -> _tilesIndices.count(loopIndex)) {
                GeneratedBoardTile *tile = this -> _addTile(glm::ivec2(i, j));
                this -> _tilesIndices[loopIndex] = tile;
            }
        }
    }
    
    for(auto tile : this -> _tilesIndices) {
        if(!activeTiles.count(tile.first)) {
            //tile.second -> DeleteModel();
            this -> _runtimeQueueManager -> RemoveInstance("", tile.second, true);
            removed.push_back(tile.first);
        }
    }
    
    for(auto removedTile : removed) {
        this -> _tilesIndices.erase(removedTile);
    }
    
    for(auto tile : this -> _tilesIndices) {
        tile.second -> CheckLODLevel(cameraPosition);
    }
    
    //fprintf(stdout, "Nb of tiles: %d\n", this -> _tilesIndices.size());
    
    //fprintf(stdout, "position (%llf, %llf) - index (%d, %d) - %d - %d\n", cameraPosition.x, cameraPosition.z, currentIndex.x, currentIndex.y, currentIndex.x * GENERATED_BOARD_MAX_ELEMENT_SIZE * 2 + currentIndex.y, this -> _tilesIndices.size());
}

void GeneratedBoardManager::CameraObserver(Camera *p_camera) {
    this -> _camera = p_camera;
}

GeneratedBoardTile* GeneratedBoardManager::_addTile(glm::ivec2 p_index) {
    GeneratedBoardTile *tile = new GeneratedBoardTile(p_index, 32, this, glm::vec3(p_index.x * this -> _tileSize, 0.0f, p_index.y * this -> _tileSize), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(this -> _tileSize, 1.0f, this -> _tileSize));
    this -> _runtimeQueueManager -> AddInstance(("plane-" + std::to_string(p_index.x) + "-" + std::to_string(p_index.y)).c_str(), "ground", tile);
    return tile;
}

void GeneratedBoardManager::_clear() {
    
}
