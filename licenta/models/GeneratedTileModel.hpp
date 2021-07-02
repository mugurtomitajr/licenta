//
//  GeneratedTileModel.hpp
//  practice
//

#ifndef GeneratedTileModel_hpp
#define GeneratedTileModel_hpp

#include <cstdio>
#include "LODModel.hpp"
#include "threedim.hpp"

class GeneratedTileModel : public LODModel {
public:
    GeneratedTileModel();
    GeneratedTileModel(glm::ivec2 p_index, std::map<int, int> p_lodLevelResolution, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    ~GeneratedTileModel();
    
protected:
    std::map<int, int> _lodLevelResolution;
    std::vector<Mesh*> _requestLODMeshes(int p_lodLevel);
    glm::ivec2 _index;
    
    void _copy(const GeneratedTileModel &p_that);
    void _clear();
};

#endif /* GeneratedTileModel_hpp */
