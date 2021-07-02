//
//  AssetManager.hpp
//  practice
//

#ifndef AssetManager_hpp
#define AssetManager_hpp

#include <GL/glew.h>

#include <cstdio>
#include <vector>
#include <map>
#include <string>

#include <glm/vec3.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "LightingMaterial.hpp"
#include "Shader.hpp"

class AssetManager {
public:
    AssetManager();
    ~AssetManager();
    
    Texture *AddTexture(const char *p_filepath);
    Texture *AddTexture(const char *p_id, const char *p_filepath);
    Texture *GetTexture(const char *p_id);
    
    LightingMaterial *AddLightingMaterial(GLfloat p_specularIntensity, GLfloat p_specularPower);
    LightingMaterial *AddLightingMaterial(const char *p_id, GLfloat p_specularIntensity, GLfloat p_specularPower);
    LightingMaterial *GetLightingMaterial(const char *p_id);
    
    Mesh *AddMesh(GLfloat *p_vertices, unsigned int p_numOfVertices, unsigned int *p_indices, unsigned int p_numOfIndices, const char* p_meshMaterialId, const char* p_meshMaterialFilepath, const char *p_propertiesMaterialId);
    Mesh *AddMesh(const char *p_id, GLfloat *p_vertices, unsigned int p_numOfVertices, unsigned int *p_indices, unsigned int p_numOfIndices, const char* p_meshMaterialId, const char* p_meshMaterialFilepath, const char *p_propertiesMaterialId);
    void DeleteMesh(const char *p_id);
    void DeleteMesh(Mesh *p_mesh);
    Mesh *GetMesh(const char *p_id);
    
    Model *AddModel(const char *p_filepath, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    Model *AddModel(const char *p_id, const char *p_filepath, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    Model *AddMeshlessModel(Model* p_model);
    Model *AddMeshlessModel(const char *p_id, Model* p_model);
    Model *CreateModel(glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale, std::vector<std::string> p_meshesId);
    Model *CreateModel(const char *p_id, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale, std::vector<std::string> p_meshesId);
    void DeleteModel(const char *p_id);
    void DeleteModel(Model *p_model);
    Model *GetModel(const char *p_id);
    
    Shader *AddShader(const char *p_vertexShaderPath, const char *p_fragmentShaderPath);
    Shader *AddShader(const char *p_id, const char *p_vertexShaderPath, const char *p_fragmentShaderPath);
    Shader *GetShader(const char *p_id);
    
    void Print();
    
private:
    std::vector<Model*> _models = std::vector<Model*>();
    std::map<std::string, Model*> _modelsId = std::map<std::string, Model*>();
    
    std::vector<Texture*> _textures = std::vector<Texture*>();
    std::map<std::string, Texture*> _texturesId = std::map<std::string, Texture*>();
    
    std::vector<Mesh*> _meshes = std::vector<Mesh*>();
    std::map<std::string, Mesh*> _meshesId = std::map<std::string, Mesh*>();
    
    std::vector<LightingMaterial*> _lightingMaterials = std::vector<LightingMaterial*>();
    std::map<std::string, LightingMaterial*> _lightingMaterialsId = std::map<std::string, LightingMaterial*>();
    
    std::vector<Shader*> _shaders = std::vector<Shader*>();
    std::map<std::string, Shader*> _shadersId = std::map<std::string, Shader*>();
    
    void _loadModelNodeRecursively(Model *p_model, aiNode *p_node, const aiScene *p_scene);
    void _loadModelMesh(Model *p_model, aiMesh *p_mesh, const aiScene *p_scene);
    
    void _deleteModel(const char *p_id, Model *p_model);
    void _deleteMesh(const char *p_id, Mesh *p_mesh);
    
    virtual void _copy(const AssetManager &p_that);
    void _clear();
};

#endif /* AssetManager_hpp */
