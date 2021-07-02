//
//  GeneratedBoardTile.hpp
//  practice
//

#ifndef GeneratedBoardTile_hpp
#define GeneratedBoardTile_hpp

#include <cstdio>
#include <string>
#include "../Instance.hpp"
#include "../../support/threedim.hpp"
#include "../../support/calculations.hpp"
#include "GeneratedTileModel.hpp"

class GeneratedBoardTile : public Instance {
public:
    GeneratedBoardTile();
    GeneratedBoardTile(glm::ivec2 p_index, unsigned int p_resolution, Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    ~GeneratedBoardTile();
    
    void LoadOtherInstances(AssetManager *p_assetManager, RuntimeQueueManager *p_runtimeQueueManager);
    
    void Start();
    void Update(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray);
    void CheckLODLevel(glm::vec3 p_origin);
    
private:
    glm::ivec2 _index;
    std::string _id;
    unsigned int _resolution;
    void _clear();
};

#endif /* GeneratedBoardTile_hpp */
