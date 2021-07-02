//
//  Instance.hpp
//  practice
//

#ifndef Instance_hpp
#define Instance_hpp

#include <cstdio>
#include <map>

#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Model.hpp"
#include "RuntimeQueueManager.hpp"
#include "AssetManager.hpp"

class Instance {
public:
    Instance();
    Instance(Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    ~Instance();
    
    bool Load(Shader *p_shader, Model *p_model);
    virtual const char* LoadCustomModelId();
    virtual const char* LoadCustomModelFilepath();
    virtual glm::vec3 LoadCustomModelPosition();
    virtual glm::vec3 LoadCustomModelRotation();
    virtual glm::vec3 LoadCustomModelScale();
    
    virtual void LoadOtherInstances(AssetManager *p_assetManager, RuntimeQueueManager *p_runtimeQueueManager);
    
    virtual void Start();
    virtual void MasterUpdate(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray);
    virtual void Update(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray);
    void Render(double dt, double inter);
    virtual void Stop();
    
    glm::mat4 *WorldMatrix();
    
    glm::vec3 Position();
    void Position(glm::vec3 p_position); // TODO: optimize passing arguments
    
    glm::vec3 Rotation();
    void Rotation(glm::vec3 p_rotation);
    
    glm::vec3 Scale();
    void Scale(glm::vec3 p_scale);
    
    glm::vec3 Velocity();
    void Velocity(glm::vec3 p_velocity);
    
    glm::vec3 Acceleration();
    void Acceleration(glm::vec3 p_acceleration);
    
    GLfloat MaximumVelocity();
    void MaximumVelocity(GLfloat p_maximumVelocity);
    
    GLfloat FrictionCoefficient();
    void FrictionCoefficient(GLfloat p_frictionCoefficient);
    
    Instance* Parent();
    void Parent(Instance* p_parent);
    
    bool MobileInstance();
    void MobileInstance(bool p_mobileInstance);
    
    Texture *OverrideDiffuseMap();
    void OverrideDiffuseMap(Texture *p_overrideDiffuseMap);
    
    LightingMaterial *OverrideLightingMaterial();
    void OverrideLightingMaterial(LightingMaterial *p_lightingMaterial);
    
    void CurrentModel(Model *p_model);
    Model *CurrentModel();
    Shader *CurrentShader();
    Instance *CurrentParent();
    std::vector<Instance*> *Children();
    
    void AddChild(Instance* p_child);
    
    glm::vec3 WorldPosition();
    virtual glm::vec3 FollowOffset();
    virtual GLfloat YRotationFollowOffset();
    
protected:
    Shader *_shader;
    Model *_model;
    Instance *_parent;
    std::vector<Instance*> _children;
    
    glm::vec3 _position, _rotation, _scale;
    glm::vec3 _velocity, _acceleration;
    
    glm::mat4 _worldMatrix;
    GLfloat _maximumVelocity, _frictionCoefficient;
    bool _mobileInstance;
    RuntimeQueueManager *_runtimeQueueManager;
    AssetManager *_assetManager;
    
    Texture *_overrideDiffuseMap;
    LightingMaterial *_overrideLightingMaterial;
    
    bool _worldMatrixUpToDate = false;
    void _recalculateWorldMatrix();
    
    virtual void _copy(const Instance &p_that);
    virtual void _clear();
};

#endif /* Instance_hpp */
