//
//  Instance.cpp
//  practice
//

#include "Instance.hpp"

Instance::Instance() {
    this -> _shader = nullptr;
    this -> _model = nullptr;
    this -> _parent = nullptr;
    
    this -> _position = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    
    this -> _velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _maximumVelocity = 0.0f;
    this -> _frictionCoefficient = 3.0f;
    this -> _mobileInstance = false;
    
    this -> _worldMatrix = glm::mat4(1.0f);
    this -> _worldMatrixUpToDate = false;
    
    this -> _runtimeQueueManager = nullptr;
    this -> _assetManager = nullptr;
    this -> _overrideDiffuseMap = nullptr;
    this -> _overrideLightingMaterial = nullptr;
}

Instance::Instance(Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale) : Instance() {
    this -> _parent = p_parent;
    this -> _position = p_position;
    this -> _rotation = p_rotation;
    this -> _scale = p_scale;
    this -> _recalculateWorldMatrix();
}

Instance::~Instance() {
    this -> _clear();
}

bool Instance::Load(Shader *p_shader, Model *p_model){
    this -> _shader = p_shader;
    this -> _model = p_model;
    return this -> _shader != nullptr;
}

const char* Instance::LoadCustomModelId(){ return ""; }

const char* Instance::LoadCustomModelFilepath(){ return ""; }

glm::vec3 Instance::LoadCustomModelPosition() { return glm::vec3(0.0f, 0.0f, 0.0f); }

glm::vec3 Instance::LoadCustomModelRotation() { return glm::vec3(0.0f, 0.0f, 0.0f); }

glm::vec3 Instance::LoadCustomModelScale() { return glm::vec3(1.0f, 1.0f, 1.0f); }

void Instance::LoadOtherInstances(AssetManager *p_assetManager, RuntimeQueueManager *p_runtimeQueueManager) {
    this -> _assetManager = p_assetManager;
    this -> _runtimeQueueManager = p_runtimeQueueManager;
}

void Instance::Start() {
    for(auto child : this -> _children) {
        child -> Start();
    }
}

void Instance::MasterUpdate(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray) {
    if(this -> _mobileInstance) {
        glm::vec3 resultingAcceleration = this -> _acceleration - (this -> _velocity * this -> _frictionCoefficient);
        if(glm::length(resultingAcceleration) > EPSILON) {
            this -> _velocity += (resultingAcceleration) * (float) dt;
            if(glm::length(this -> _velocity) > this -> _maximumVelocity) {
                this -> _velocity = glm::normalize(this -> _velocity) * this -> _maximumVelocity;
            }
        }
        if(glm::length(this -> _velocity) > EPSILON) {
            this -> _position += (this -> _velocity) * (float) dt;
            this -> _worldMatrixUpToDate = false;
        }
    }
    this -> Update(dt, p_mouseDelta, p_keyPressedArray);
    for(auto child : this -> _children) {
        child -> MasterUpdate(dt, p_mouseDelta, p_keyPressedArray);
    }
}

void Instance::Update(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray) {
    
}

void Instance::Render(double dt, double inter) { // TODO: optimize calls
    if(this -> _shader && this -> _model) {
        glm::mat4 worldMatrix = glm::mat4(1.0f);
        worldMatrix *= *(this -> _model -> WorldMatrix());
        if(this -> _parent) { // TODO: check if order is correct
            worldMatrix *= *(this -> _parent -> WorldMatrix());
        }
        worldMatrix *= *this -> WorldMatrix();
        this -> _shader -> ApplyWorldMatrix(worldMatrix);
        std::vector<Mesh*> *meshesArray = this -> _model -> Meshes();
        for (auto mesh : *(meshesArray)) {
            LightingMaterial *lightingMaterial = nullptr;
            if(mesh -> PropertiesMaterial()) { lightingMaterial = mesh -> PropertiesMaterial();}
            if(this -> OverrideLightingMaterial()) {lightingMaterial = this -> OverrideLightingMaterial(); }
            if(lightingMaterial) {
                this -> _shader -> ApplyLightingMaterial(*lightingMaterial);
            } else {
                this -> _shader -> ApplyDefaultLightingMaterial();
            }
            
            Texture *diffuseMap = nullptr;
            if(mesh -> DiffuseMap()) { diffuseMap = mesh -> DiffuseMap(); }
            if(this -> _model -> OverrideDiffuseMap()) { diffuseMap = this -> _model -> OverrideDiffuseMap(); }
            if(this -> OverrideDiffuseMap()) { diffuseMap = this -> OverrideDiffuseMap(); }
            if(diffuseMap) {
                this -> _shader -> ApplyDiffuseMap(*(diffuseMap));
            } else {
                this -> _shader -> ApplyDefaultDiffuseMap();
            }
            
            mesh -> Render(dt, inter);
        }
    }
}

void Instance::Stop() {
    for(auto child : this -> _children) {
        child -> Stop();
    }
}

glm::mat4* Instance::WorldMatrix() {
    if(!this -> _worldMatrixUpToDate) {
        this -> _recalculateWorldMatrix();
    }
    return &(this -> _worldMatrix);
}

glm::vec3 Instance::Position() { return this -> _position; }

void Instance::Position(glm::vec3 p_position) {
    this -> _position = p_position;
    this -> _worldMatrixUpToDate = false;
}

glm::vec3 Instance::Rotation() { return this -> _rotation; }

void Instance::Rotation(glm::vec3 p_rotation) {
    this -> _rotation = p_rotation;
    this -> _worldMatrixUpToDate = false;
}

glm::vec3 Instance::Scale() { return this -> _scale; }

void Instance::Scale(glm::vec3 p_scale) {
    this -> _scale = p_scale;
    this -> _worldMatrixUpToDate = false;
}

glm::vec3 Instance::Velocity() { return this -> _velocity; }
void Instance::Velocity(glm::vec3 p_velocity) { this -> _velocity = p_velocity; }

glm::vec3 Instance::Acceleration() { return this -> _acceleration; }
void Instance::Acceleration(glm::vec3 p_acceleration) {this -> _acceleration = p_acceleration; }

GLfloat Instance::MaximumVelocity() { return this -> _maximumVelocity; }
void Instance::MaximumVelocity(GLfloat p_maximumVelocity) { this -> _maximumVelocity = p_maximumVelocity; }

bool Instance::MobileInstance() { return this -> _mobileInstance; }
void Instance::MobileInstance(bool p_mobileInstance) { this -> _mobileInstance = p_mobileInstance; }

Instance* Instance::Parent() { return this -> _parent; }
void Instance::Parent(Instance* p_parent) { this -> _parent = p_parent; }

void Instance::AddChild(Instance *p_child) {
    p_child -> _parent = this;
    this -> _children.push_back(p_child);
}

glm::vec3 Instance::WorldPosition() {
    glm::vec3 result = this -> _position;
    if(this -> _model) { // TODO: verify if this should be here
        result += this -> _model -> Position();
    }
    if(this -> _parent) {
        result += this -> _parent -> WorldPosition();
    }
    return result;
}

glm::vec3 Instance::FollowOffset() { return glm::vec3(0.0f, 0.0f, 0.0f); }

GLfloat Instance::YRotationFollowOffset() { return 0.0f; }

void Instance::OverrideDiffuseMap(Texture *p_overrideDiffuseMap) { this -> _overrideDiffuseMap = p_overrideDiffuseMap; }

Texture* Instance::OverrideDiffuseMap() { return this -> _overrideDiffuseMap; }

LightingMaterial* Instance::OverrideLightingMaterial() { return this -> _overrideLightingMaterial; }

void Instance::OverrideLightingMaterial(LightingMaterial *p_lightingMaterial) { this -> _overrideLightingMaterial = p_lightingMaterial; }

void Instance::CurrentModel(Model *p_model) { this -> _model = p_model; }

Model* Instance::CurrentModel() { return this -> _model; }

Shader* Instance::CurrentShader() { return this -> _shader; }

Instance* Instance::CurrentParent() { return this -> _parent; }

std::vector<Instance*>* Instance::Children() { return &(this -> _children); }

void Instance::_recalculateWorldMatrix() {
    this -> _worldMatrix = glm::mat4(1.0f);
    this -> _worldMatrix = glm::translate(this -> _worldMatrix, this -> _position);
    
    this -> _worldMatrix = glm::rotate(this -> _worldMatrix, glm::radians(this -> _rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    this -> _worldMatrix = glm::rotate(this -> _worldMatrix, glm::radians(this -> _rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this -> _worldMatrix = glm::rotate(this -> _worldMatrix, glm::radians(this -> _rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    
    this -> _worldMatrix = glm::scale(this -> _worldMatrix, this -> _scale);
    this -> _worldMatrixUpToDate = true;
}

void Instance::_copy(const Instance &p_that) {
    
}

void Instance::_clear() {
    this -> _parent = nullptr;
    this -> _shader = nullptr;
    this -> _model = nullptr;
    
    this -> _position = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    
    this -> _velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> _maximumVelocity = 0.0f;
    this -> _frictionCoefficient = 3.0f;
    this -> _mobileInstance = false;
    
    this -> _worldMatrix = glm::mat4(1.0f);
    this -> _worldMatrixUpToDate = false;
    
    this -> _runtimeQueueManager = nullptr;
    this -> _assetManager = nullptr;
    this -> _overrideDiffuseMap = nullptr;
    this -> _overrideLightingMaterial = nullptr;
}
