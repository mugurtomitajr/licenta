//
//  SceneManager.cpp
//  practice
//

#include "SceneManager.hpp"

SceneManager::SceneManager() {
    this -> _assetManager = nullptr;
    this -> _runtimeQueueManager = RuntimeQueueManager();
    
    this -> _instances = std::vector<Instance*>();
    this -> _instancesId = std::map<std::string, Instance*>();
    this -> _instanceShaderLink = std::map<Shader*, std::vector<Instance*>>();
    this -> _instancesParentsOnly = std::vector<Instance*>();
    
    this -> _pointLights = std::vector<PointLight*>();
    this -> _pointLightsId = std::map<std::string, PointLight*>();
    
    this -> _spotLights = std::vector<SpotLight*>();
    this -> _spotLightsId = std::map<std::string, SpotLight*>();
}

SceneManager::SceneManager(AssetManager *p_assetManager) : SceneManager() {
    this -> _assetManager = p_assetManager;
}

SceneManager::~SceneManager() {
    this -> _clear();
}



Instance* SceneManager::AddInstance(const char *p_shaderId, const char *p_modelId, Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale) {
    return this -> AddInstance(("generated-instance-" + std::to_string(this -> _instances.size())).c_str(), p_shaderId, p_modelId, p_parent, p_position, p_rotation, p_scale);
}

Instance* SceneManager::AddInstance(const char *p_id, const char *p_shaderId, const char *p_modelId, Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale) {
    if(this -> _instancesId.count(p_id)) {
        return this -> _instancesId[p_id];
    }
    
    Shader *shader = this -> _assetManager -> GetShader(p_shaderId);
    Model *model = this -> _assetManager -> GetModel(p_modelId);
    
    Instance *instance = new Instance(p_parent, p_position, p_rotation, p_scale);
    if(instance -> Load(shader, model)) {
        this -> _instances.push_back(instance);
        this -> _instancesId[p_id] = instance;
        
        if(!this -> _instanceShaderLink.count(shader)) {
            this -> _instanceShaderLink[shader] = std::vector<Instance*>();
        }
        this -> _instanceShaderLink[shader].push_back(instance);
        
        if( !p_parent ) {
            this -> _instancesParentsOnly.push_back(instance);
        }
        
        instance -> LoadOtherInstances(this -> _assetManager, &(this -> _runtimeQueueManager));
        
        return instance;
    } else {
        delete instance;
        fprintf(stdout, "Scene Manager: Instance %s - %s failed to load...\n", p_id, p_modelId);
    }
    return nullptr;
}

Instance* SceneManager::AddInstance(const char *p_shaderId, Instance *p_template) {
    return this -> AddInstance(("custom-instance-" + std::to_string(this -> _instances.size())).c_str(), p_shaderId, p_template);
}

Instance* SceneManager::AddInstance(const char *p_id, const char *p_shaderId, Instance *p_template) {
    if(this -> _instancesId.count(p_id)) {
        return this -> _instancesId[p_id];
    }
    
    Shader *shader = this -> _assetManager -> GetShader(p_shaderId);
    Model *model = nullptr;
    const char *modelId = p_template -> LoadCustomModelId();
    const char *modelPath = p_template -> LoadCustomModelFilepath();
    glm::vec3 modelPosition = p_template -> LoadCustomModelPosition();
    glm::vec3 modelRotation = p_template -> LoadCustomModelRotation();
    glm::vec3 modelScale = p_template -> LoadCustomModelScale();
    //std::map<std::string, Instance*> otherInstances = p_template -> LoadOtherInstances();
    if(strlen(modelId) > 0) {
        model = this -> _assetManager -> AddModel(modelId, modelPath, modelPosition, modelRotation, modelScale);
    } else {
        if(strlen(modelPath) > 0) {
            model = this -> _assetManager -> AddModel(modelPath, modelPosition, modelRotation, modelScale);
        }
    }
    if(p_template -> Load(shader, model)) {
        this -> _instances.push_back(p_template);
        this -> _instancesId[p_id] = p_template;
        
        if(!this -> _instanceShaderLink.count(shader)) {
            this -> _instanceShaderLink[shader] = std::vector<Instance*>();
        }
        this -> _instanceShaderLink[shader].push_back(p_template);
        
        if( !p_template -> Parent() ) {
            this -> _instancesParentsOnly.push_back(p_template);
        }
        
        p_template -> LoadOtherInstances(this -> _assetManager, &(this -> _runtimeQueueManager));
        
        return p_template;
    } else {
        /*for(auto additionalInstanceMap : otherInstances) {
            delete additionalInstanceMap.second;
        }*/
        delete p_template;
        fprintf(stdout, "Scene Manager: Instance (custom) %s failed to load...\n", p_id);
    }
    return nullptr;
}

Instance* SceneManager::GetInstance(const char *p_id) {
    if(this -> _instancesId.count(p_id)) {
        return this -> _instancesId[p_id];
    }
    return nullptr;
}

std::map<Shader*, std::vector<Instance*>>* SceneManager::InstanceShaderLinkArray() { return &(this -> _instanceShaderLink); }

std::vector<Instance*>* SceneManager::Instances() { return &(this -> _instances); }

std::vector<Instance*>* SceneManager::InstancesParentsOnly() { return &(this -> _instancesParentsOnly); }



DirectionalLight* SceneManager::SetDirectionalLight(glm::vec3 p_direction, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity){
    this -> _directionalLight = DirectionalLight(p_direction, p_color, p_diffuseIntensity, p_ambientIntensity, p_specularIntensity);
    return &(this -> _directionalLight);
}

DirectionalLight* SceneManager::DirectionalLightReference() {
    return &(this -> _directionalLight);
}



PointLight* SceneManager::AddPointLight(glm::vec3 p_position, glm::vec3 p_attenuationFactors, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity){
    return AddPointLight(("point-light-" + std::to_string(this -> _pointLights.size())).c_str(), p_position, p_attenuationFactors, p_color, p_diffuseIntensity, p_ambientIntensity, p_specularIntensity);
}

PointLight* SceneManager::AddPointLight(const char *p_id, glm::vec3 p_position, glm::vec3 p_attenuationFactors, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity){
    if(this -> _pointLightsId.count(p_id)) {
        return this -> _pointLightsId[p_id];
    }
    
    if(this -> _pointLights.size() >= SHADER_MAX_POINT_LIGHTS) {
        fprintf(stdout, "Scene Manager: Point light %s failed to load...\n", p_id);
        return nullptr;
    }
    
    PointLight *pointLight = new PointLight(p_position, p_attenuationFactors, p_color, p_diffuseIntensity, p_ambientIntensity, p_specularIntensity);
    this -> _pointLights.push_back(pointLight);
    this -> _pointLightsId[p_id] = pointLight;
    
    return pointLight;
}

PointLight* SceneManager::GetPointLight(const char *p_id){
    if(this -> _pointLightsId.count(p_id)) {
        return this -> _pointLightsId[p_id];
    }
    return nullptr;
}

PointLight** SceneManager::PointLightsArray() {
    return &(this -> _pointLights)[0];
}

unsigned int SceneManager::PointLightsArrayCount() {
    return (unsigned int) this -> _pointLights.size();
}



SpotLight* SceneManager::AddSpotLight(glm::vec3 p_direction, GLfloat p_edge, glm::vec3 p_position, glm::vec3 p_attenuationFactors, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity){
    return this -> AddSpotLight(("spot-light-" + std::to_string(this -> _spotLights.size())).c_str(), p_direction, p_edge, p_position, p_attenuationFactors, p_color, p_diffuseIntensity, p_ambientIntensity, p_specularIntensity);
}

SpotLight* SceneManager::AddSpotLight(const char *p_id, glm::vec3 p_direction, GLfloat p_edge, glm::vec3 p_position, glm::vec3 p_attenuationFactors, glm::vec3 p_color, GLfloat p_diffuseIntensity, GLfloat p_ambientIntensity, GLfloat p_specularIntensity){
    if(this -> _spotLightsId.count(p_id)) {
        return this -> _spotLightsId[p_id];
    }
    
    if(this -> _spotLights.size() >= SHADER_MAX_SPOT_LIGHTS) {
        fprintf(stdout, "Scene Manager: Spot light %s failed to load...\n", p_id);
        return nullptr;
    }
    
    SpotLight *spotLight = new SpotLight(p_direction, p_edge, p_position, p_attenuationFactors, p_color, p_diffuseIntensity, p_ambientIntensity, p_specularIntensity);
    this -> _spotLights.push_back(spotLight);
    this -> _spotLightsId[p_id] = spotLight;
    
    return spotLight;
}

SpotLight* SceneManager::GetSpotLight(const char *p_id){
    if(this -> _spotLightsId.count(p_id)) {
        return this -> _spotLightsId[p_id];
    }
    return nullptr;
}

SpotLight** SceneManager::SpotLightsArray() {
    return &(this -> _spotLights)[0];
}

unsigned int SceneManager::SpotLightsArrayCount() {
    return (unsigned int) this -> _spotLights.size();
}



void SceneManager::RuntimeQueueCheck() {
    RuntimeQueueManager::InstanceQueueData data;
    while(!this -> _runtimeQueueManager._instancesToAdd.empty()) {
        data = this -> _runtimeQueueManager._instancesToAdd.front();
        this -> _runtimeQueueManager._instancesToAdd.pop();
        this -> AddInstance(data._id.c_str(), data._shaderId.c_str(), (Instance*)data._reference);
    }
    
    while(!this -> _runtimeQueueManager._instancesToRemove.empty()) {
        data = this -> _runtimeQueueManager._instancesToRemove.front();
        this -> _runtimeQueueManager._instancesToRemove.pop();
        this -> _deleteInstance(data._id.c_str(), (Instance *)data._reference, data._deleteModel);
    }
    // TODO: check for removal of instances
}



void SceneManager::Print() {
    fprintf(stdout, "Instances:\n");
    for (auto instance : this -> _instancesId) {
        fprintf(stdout, "\t%s\n", instance.first.c_str());
    }
    fprintf(stdout, "Point lights:\n");
    for (auto pointLight : this -> _pointLightsId) {
        fprintf(stdout, "\t%s\n", pointLight.first.c_str());
    }
    fprintf(stdout, "Spot lights:\n");
    for (auto spotLight : this -> _spotLightsId) {
        fprintf(stdout, "\t%s\n", spotLight.first.c_str());
    }
}

void SceneManager::_deleteInstance(const char *p_id, Instance *p_instance, bool p_deleteModel) {
    std::string id = p_id;
    if(id.length() <= 0) {
        if(!p_instance){
            fprintf(stdout, "Scene Manager: Can not delete instance with no info...\n");
            return;
        }
        for(auto instanceMapEntry : this -> _instancesId) {
            if(instanceMapEntry.second == p_instance) {
                id = instanceMapEntry.first;
                break;
            }
        }
    }
    if(id.length() <= 0) {
        fprintf(stdout, "Scene Manager: Instance id not found in delete...\n");
        return;
    }
    if(!p_instance) {
        if(this -> _instancesId.count(id)) {
            p_instance = this -> _instancesId[id];
        } else {
            fprintf(stdout, "Scene Manager: Instance %s not found to delete...\n", id.c_str());
            return;
        }
    }
    
    // _instances
    this -> _instances.erase(std::remove(this -> _instances.begin(), this -> _instances.end(), p_instance), this -> _instances.end());
    
    // _instancesId
    this -> _instancesId.erase(this -> _instancesId.find(id));
    
    // _instanceShaderLink
    if(p_instance -> CurrentShader()) {
        Shader *shader = p_instance -> CurrentShader();
        if(this -> _instanceShaderLink.count(shader)) {
            this -> _instanceShaderLink[shader].erase(std::remove(this -> _instanceShaderLink[shader].begin(), this -> _instanceShaderLink[shader].end(), p_instance), this -> _instanceShaderLink[shader].end());
        }
    }
    
    // _instancesParentsOnly
    if(!p_instance -> CurrentParent()) {
        this -> _instancesParentsOnly.erase(std::remove(this -> _instancesParentsOnly.begin(), this -> _instancesParentsOnly.end(), p_instance), this -> _instancesParentsOnly.end());
    }
    
    // model
    if(p_deleteModel && p_instance -> CurrentModel()) {
        this -> _assetManager -> DeleteModel(p_instance -> CurrentModel());
        p_instance -> CurrentModel(nullptr);
    }
    
    // children
    std::vector<Instance *> *children = p_instance -> Children();
    for(auto child : *(children)) {
        this -> _deleteInstance("", child, p_deleteModel);
    }
    
    // itself
    delete p_instance;
}

void SceneManager::_copy(const SceneManager &p_that) {
    
}

void SceneManager::_clear() {
    for (auto instance : this -> _instances) {
        delete instance;
    }
    
    for (auto pointLight : this -> _pointLights) {
        delete pointLight;
    }
    
    for (auto spotLight : this -> _spotLights) {
        delete spotLight;
    }
    
    this -> _instances = std::vector<Instance*>();
    this -> _instancesId = std::map<std::string, Instance*>();
    this -> _instanceShaderLink = std::map<Shader*, std::vector<Instance*>>();
    this -> _instancesParentsOnly = std::vector<Instance*>();
    
    this -> _pointLights = std::vector<PointLight*>();
    this -> _pointLightsId = std::map<std::string, PointLight*>();
    
    this -> _spotLights = std::vector<SpotLight*>();
    this -> _spotLightsId = std::map<std::string, SpotLight*>();
    
    this -> _assetManager = nullptr;
    this -> _runtimeQueueManager = RuntimeQueueManager();
}

