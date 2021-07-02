//
//  GeneratedBoardManager.hpp
//  practice
//

#ifndef GeneratedBoardManager_hpp
#define GeneratedBoardManager_hpp

#include <cstdio>
#include <string>
#include <glm/glm.hpp>
#include "../generation/GeneratedBoardTile.hpp"
#include "../../cameras/Camera.hpp"

class GeneratedBoardManager : public Instance {
public:
    GeneratedBoardManager();
    GeneratedBoardManager(Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    ~GeneratedBoardManager();
    
    void LoadOtherInstances(AssetManager *p_assetManager, RuntimeQueueManager *p_runtimeQueueManager);
    
    void Start();
    void Update(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray);
    
    void CameraObserver(Camera *p_camera);
    
private:
    GLfloat _tileSize;
    GeneratedBoardTile* _addTile(glm::ivec2 p_index);
    std::map<long int, GeneratedBoardTile*> _tilesIndices;
    
    class Camera *_camera;
    void _clear();
};

#endif /* GeneratedBoardManager_hpp */
