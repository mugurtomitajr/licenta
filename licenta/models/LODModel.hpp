//
//  LODModel.hpp
//  practice
//

#ifndef LODModel_hpp
#define LODModel_hpp

#include <cstdio>
#include <map>

#include "Model.hpp"

class LODModel : public Model {
public:
    LODModel();
    LODModel(glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    ~LODModel();
    
    std::vector<Mesh*> *Meshes();
    std::vector<Mesh*> AllMeshes();
    
    void CurrentLOD(int p_lod);
    int CurrentLOD();
    
    void DeleteRuntimeGeneratedMeshes();
    
protected:
    int _currentLODLevel = 0;
    std::map<int, std::vector<Mesh*>> _lodMeshes;
    std::vector<Mesh*> _runtimeGeneratedMeshes;
    
    void _addRuntimeGeneratedMesh(Mesh *p_mesh);
    virtual std::vector<Mesh*> _requestLODMeshes(int p_lodLevel);
    
    virtual void _copy(const LODModel &p_that);
    virtual void _clear();
};

#endif /* LODModel_hpp */
