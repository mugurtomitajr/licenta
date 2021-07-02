//
//  SceneManager.hpp
//  practice
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <cstdio>
#include <vector>
#include <map>
#include <string>

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "AssetManager.hpp"
#include "RuntimeQueueManager.hpp"
#include "Instance.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "LightingMaterial.hpp"
#include "Shader.hpp"

class SceneManager {
public:
    SceneManager();
    SceneManager(AssetManager *p_assetManager);
    ~SceneManager();
    
    Instance *AddInstance(const char *p_shaderId, const char *p_modelId, Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    Instance *AddInstance(const char *p_id, const char *p_shaderId, const char *p_modelId, Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    Instance *AddInstance(const char *p_shaderId, Instance *p_template);
    Instance *AddInstance(const char *p_id, const char *p_shaderId, Instance *p_template);
    Instance *GetInstance(const char *p_id);
    
    DirectionalLight *SetDirectionalLight(glm::vec3 p_direction, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity);
    DirectionalLight *DirectionalLightReference();
    
    PointLight *AddPointLight(glm::vec3 p_position, glm::vec3 p_attenuationFactors, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity);
    PointLight *AddPointLight(const char *p_id, glm::vec3 p_position, glm::vec3 p_attenuationFactors, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity);
    PointLight *GetPointLight(const char *p_id);
    PointLight **PointLightsArray();
    unsigned int PointLightsArrayCount();
    
    SpotLight *AddSpotLight(glm::vec3 p_direction, GLfloat p_edge, glm::vec3 p_position, glm::vec3 p_attenuationFactors, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity);
    SpotLight *AddSpotLight(const char *p_id, glm::vec3 p_direction, GLfloat p_edge, glm::vec3 p_position, glm::vec3 p_attenuationFactors, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity);
    SpotLight *GetSpotLight(const char *p_id);
    SpotLight **SpotLightsArray();
    unsigned int SpotLightsArrayCount();
    
    void RuntimeQueueCheck();
    
    std::map<Shader*, std::vector<Instance*>> *InstanceShaderLinkArray();
    std::vector<Instance*>* Instances();
    std::vector<Instance*>* InstancesParentsOnly();
    
    void Print();
    
private:
    AssetManager *_assetManager;
    RuntimeQueueManager _runtimeQueueManager;
    
    std::vector<Instance*> _instances = std::vector<Instance*>();
    std::map<std::string, Instance*> _instancesId = std::map<std::string, Instance*>();
    std::map<Shader*, std::vector<Instance*>> _instanceShaderLink = std::map<Shader*, std::vector<Instance*>>();
    std::vector<Instance*> _instancesParentsOnly = std::vector<Instance*>();
    
    DirectionalLight _directionalLight;
    
    std::vector<PointLight*> _pointLights = std::vector<PointLight*>();
    std::map<std::string, PointLight*> _pointLightsId = std::map<std::string, PointLight*>();
    
    std::vector<SpotLight*> _spotLights = std::vector<SpotLight*>();
    std::map<std::string, SpotLight*> _spotLightsId = std::map<std::string, SpotLight*>();
    
    void _deleteInstance(const char *p_id, Instance *p_instance, bool p_deleteModel);
    
    virtual void _copy(const SceneManager &p_that);
    void _clear();
};


#endif /* SceneManager_hpp */
