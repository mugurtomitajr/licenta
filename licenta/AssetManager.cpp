//
//  AssetManager.cpp
//  practice
//

#include "AssetManager.hpp"

AssetManager::AssetManager() {
    this -> _models = std::vector<Model*>();
    this -> _modelsId = std::map<std::string, Model*>();
    this -> _textures = std::vector<Texture*>();
    this -> _texturesId = std::map<std::string, Texture*>();
    this -> _meshes = std::vector<Mesh*>();
    this -> _meshesId = std::map<std::string, Mesh*>();
    this -> _lightingMaterials = std::vector<LightingMaterial*>();
    this -> _lightingMaterialsId = std::map<std::string, LightingMaterial*>();
}

AssetManager::~AssetManager() {
    this -> _clear();
}



Texture* AssetManager::AddTexture(const char *p_filepath) {
    return this -> AddTexture(p_filepath, p_filepath);
}

Texture* AssetManager::AddTexture(const char *p_id, const char *p_filepath) {
    if(this -> _texturesId.count(p_id)) {
        return this -> _texturesId[p_id];
    }
    
    Texture* texture = new Texture(p_filepath);
    
    if(texture -> Load()) {
        this -> _textures.push_back(texture);
        this -> _texturesId[p_id] = texture;
        return texture;
    } else {
        delete texture;
        fprintf(stdout, "Asset Manager: Texture %s - %s failed to load...\n", p_id, p_filepath);
    }
    
    return nullptr;
}

Texture* AssetManager::GetTexture(const char *p_id) {
    if(this -> _texturesId.count(p_id)) {
        return this -> _texturesId[p_id];
    }
    return nullptr;
}



LightingMaterial* AssetManager::AddLightingMaterial(GLfloat p_specularIntensity, GLfloat p_specularPower) {
    return this -> AddLightingMaterial(("generated-material-" + std::to_string(this -> _lightingMaterials.size())).c_str(), p_specularIntensity, p_specularPower);
}

LightingMaterial* AssetManager::AddLightingMaterial(const char *p_id, GLfloat p_specularIntensity, GLfloat p_specularPower) {
    if(this -> _lightingMaterialsId.count(p_id)) {
        return this -> _lightingMaterialsId[p_id];
    }
    
    LightingMaterial* material = new LightingMaterial();
    
    if(material -> Load(p_specularIntensity, p_specularPower)) {
        this -> _lightingMaterials.push_back(material);
        this -> _lightingMaterialsId[p_id] = material;
        return material;
    } else {
        delete material;
        fprintf(stdout, "Asset Manager: Material %s failed to load...\n", p_id);
    }
    
    return nullptr;
}

LightingMaterial* AssetManager::GetLightingMaterial(const char *p_id) {
    if(this -> _lightingMaterialsId.count(p_id)) {
        return this -> _lightingMaterialsId[p_id];
    }
    return nullptr;
}



Mesh* AssetManager::AddMesh(GLfloat *p_vertices, unsigned int p_numOfVertices, unsigned int *p_indices, unsigned int p_numOfIndices, const char* p_diffuseMapId, const char* p_diffuseMapFilepath, const char *p_propertiesMaterialId) {
    return AddMesh(("generated-mesh-" + std::to_string(this -> _meshes.size())).c_str(), p_vertices, p_numOfVertices, p_indices, p_numOfIndices, p_diffuseMapId, p_diffuseMapFilepath, p_propertiesMaterialId);
}

Mesh* AssetManager::AddMesh(const char *p_id, GLfloat *p_vertices, unsigned int p_numOfVertices, unsigned int *p_indices, unsigned int p_numOfIndices, const char* p_diffuseMapId, const char* p_diffuseMapFilepath, const char *p_propertiesMaterialId) {
    if(this -> _meshesId.count(p_id)) {
        return this -> _meshesId[p_id];
    }
    
    Mesh *mesh = new Mesh();
    if(mesh->Load(p_vertices, p_numOfVertices, p_indices, p_numOfIndices)) {
        
        Texture *texture = nullptr;
        if (strlen(p_diffuseMapFilepath) > 0) {
            if (strlen(p_diffuseMapId) > 0) {
                texture = this -> AddTexture(p_diffuseMapId, p_diffuseMapFilepath);
            } else {
                texture = this -> AddTexture(p_diffuseMapFilepath);
            }
        } else if(strlen(p_diffuseMapId) > 0) {
            texture = this -> GetTexture(p_diffuseMapId);
        }
        mesh -> DiffuseMap(texture);
        
        LightingMaterial *lightingMaterial = nullptr;
        if(strlen(p_propertiesMaterialId) > 0) {
            lightingMaterial = this -> GetLightingMaterial(p_propertiesMaterialId);
        }
        mesh -> PropertiesMaterial(lightingMaterial);
        
        this -> _meshes.push_back(mesh);
        this -> _meshesId[p_id] = mesh;
        return mesh;
    } else {
        delete mesh;
        fprintf(stdout, "Asset Manager: Mesh %s failed to load...\n", p_id);
    }
    
    return nullptr;
}

void AssetManager::DeleteMesh(const char *p_id) {
    Mesh *mesh = nullptr;
    if(this -> _meshesId.count(p_id)) {
        mesh = this -> _meshesId[p_id];
    } else {
        fprintf(stdout, "Asset Manager: Mesh %s not found to delete...\n", p_id);
        return;
    }
    
    this -> _deleteMesh(p_id, mesh);
}

void AssetManager::DeleteMesh(Mesh *p_mesh) {
    if(!p_mesh) {
        fprintf(stdout, "Asset Manager: Mesh null in delete...\n");
        return;
    }
    
    std::string id = "";
    for(auto meshMapEntry : this -> _meshesId) {
        if(meshMapEntry.second == p_mesh) {
            id = meshMapEntry.first;
            break;
        }
    }
    
    if(id.length() == 0) {
        fprintf(stdout, "Asset Manager: Mesh reference not found to delete...\n");
        return;
    }
    
    this -> _deleteMesh(id.c_str(), p_mesh);
}

Mesh* AssetManager::GetMesh(const char *p_id) {
    if(this -> _meshesId.count(p_id)) {
        return this -> _meshesId[p_id];
    }
    return nullptr;
}



Model* AssetManager::AddModel(const char *p_filepath, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale) {
    return this -> AddModel(p_filepath, p_filepath, p_position, p_rotation, p_scale);
}

Model* AssetManager::AddModel(const char *p_id, const char *p_filepath, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale) {
    if(this -> _modelsId.count(p_id)) {
        return this -> _modelsId[p_id];
    }
    
    Model* model = new Model(p_position, p_rotation, p_scale);
    
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(p_filepath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if ( !scene ) {
        printf("Asset Manager: Model %s failed to load: %s\n", p_filepath, importer.GetErrorString());
        delete model;
        return nullptr;
    }

    if(model -> Load(p_filepath)) {
        this -> _loadModelNodeRecursively(model, scene -> mRootNode, scene);
        this -> _models.push_back(model);
        this -> _modelsId[p_id] = model;
        return model;
    } else {
        delete model;
        fprintf(stdout, "Asset Manager: Model %s - %s failed to load...\n", p_id, p_filepath);
    }
    
    return nullptr;
}

Model* AssetManager::AddMeshlessModel(Model* p_model) {
    return this -> AddMeshlessModel(("meshless-model-" + std::to_string(this -> _models.size())).c_str(), p_model);
}

Model* AssetManager::AddMeshlessModel(const char *p_id, Model* p_model) {
    if(this -> _modelsId.count(p_id)) {
        return this -> _modelsId[p_id];
    }
    
    if(p_model -> Load()) {
        this -> _models.push_back(p_model);
        this -> _modelsId[p_id] = p_model;
        return p_model;
    } else {
        fprintf(stdout, "Asset Manager: Model %s failed to load...\n", p_id);
        delete p_model;
    }
    
    return nullptr;
}

Model* AssetManager::CreateModel(glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale, std::vector<std::string> p_meshesId) {
    return this -> CreateModel(("generated-model-" + std::to_string(this -> _models.size())).c_str(), p_position, p_rotation, p_scale, p_meshesId);
}

Model* AssetManager::CreateModel(const char *p_id, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale, std::vector<std::string> p_meshesId) {
    if(this -> _modelsId.count(p_id)) {
        return this -> _modelsId[p_id];
    }
    
    Model* model = new Model(p_position, p_rotation, p_scale);

    if(model -> Load()) {
        for(auto meshId : p_meshesId) {
            Mesh *mesh = this -> GetMesh(meshId.c_str());
            if(!mesh) {
                fprintf(stdout, "Asset Manager: Model %s failed to load mesh %s ...\n", p_id, meshId.c_str());
                delete model;
                return nullptr; // TODO: reorganize ext conditions in all these functions
            }
            model -> AddMesh(mesh);
        }
        this -> _models.push_back(model);
        this -> _modelsId[p_id] = model;
        return model;
    } else {
        fprintf(stdout, "Asset Manager: Model %s failed to load...\n", p_id);
        delete model;
    }
    
    return nullptr;
}

void AssetManager::DeleteModel(const char *p_id) {
    Model *model = nullptr;
    if(this -> _modelsId.count(p_id)) {
        model = this -> _modelsId[p_id];
    } else {
        fprintf(stdout, "Asset Manager: Model %s not found to delete...\n", p_id);
        return;
    }
    
    this -> _deleteModel(p_id, model);
}

void AssetManager::DeleteModel(Model *p_model) {
    if(!p_model) {
        fprintf(stdout, "Asset Manager: Model null in delete...\n");
        return;
    }
    
    std::string id = "";
    for(auto modelMapEntry : this -> _modelsId) {
        if(modelMapEntry.second == p_model) {
            id = modelMapEntry.first;
            break;
        }
    }
    
    if(id.length() == 0) {
        fprintf(stdout, "Asset Manager: Model reference not found to delete...\n");
        return;
    }
    
    this -> _deleteModel(id.c_str(), p_model);
}

Model* AssetManager::GetModel(const char *p_id) {
    if(this -> _modelsId.count(p_id)) {
        return this -> _modelsId[p_id];
    }
    return nullptr;
}



Shader* AssetManager::AddShader(const char *p_vertexShaderPath, const char *p_fragmentShaderPath) {
    return this -> AddShader(("generated-shader-" + std::to_string(this -> _shaders.size())).c_str(), p_vertexShaderPath, p_fragmentShaderPath);
}

Shader* AssetManager::AddShader(const char *p_id, const char *p_vertexShaderPath, const char *p_fragmentShaderPath) {
    if(this -> _shadersId.count(p_id)) {
        return this -> _shadersId[p_id];
    }
    
    Shader *shader = new Shader();
    if(shader->Load(p_vertexShaderPath, p_fragmentShaderPath)) {
        this -> _shaders.push_back(shader);
        this -> _shadersId[p_id] = shader;
        return shader;
    } else {
        delete shader;
        fprintf(stdout, "Asset Manager: Shader %s - %s - %s failed to load...\n", p_id, p_vertexShaderPath, p_fragmentShaderPath);
    }
    return nullptr;
}

Shader* AssetManager::GetShader(const char *p_id){
    if(this -> _shadersId.count(p_id)) {
        return this -> _shadersId[p_id];
    }
    return nullptr;
}



void AssetManager::Print() {
    fprintf(stdout, "Models:\n");
    for (std::map<std::string, Model*>::iterator it = this -> _modelsId.begin(); it != this -> _modelsId.end(); ++it) {
        fprintf(stdout, "\t%s\n", it -> first.c_str());
    }
    
    fprintf(stdout, "Materials:\n");
    for (std::map<std::string, LightingMaterial*>::iterator it = this -> _lightingMaterialsId.begin(); it != this -> _lightingMaterialsId.end(); ++it) {
        fprintf(stdout, "\t%s\n", it -> first.c_str());
    }
    
    fprintf(stdout, "Textures:\n");
    for (std::map<std::string, Texture*>::iterator it = this -> _texturesId.begin(); it != this -> _texturesId.end(); ++it) {
        fprintf(stdout, "\t%s\n", it -> first.c_str());
    }
    
    fprintf(stdout, "Meshes:\n");
    for (std::map<std::string, Mesh*>::iterator it = this -> _meshesId.begin(); it != this -> _meshesId.end(); ++it) {
        fprintf(stdout, "\t%s\n", it -> first.c_str());
    }
}



void AssetManager::_deleteModel(const char *p_id, Model *p_model) {
    std::vector<Mesh*> meshes = p_model -> AllMeshes();
    // TODO: decide which to use: Delete from AllMeshes or DeleteRuntimeGeneratedMeshes
    // Not all these meshes are not registered in AssetManager!!
    for(auto mesh : meshes) {
        this -> DeleteMesh(mesh);
    }
    p_model -> DeleteRuntimeGeneratedMeshes();
    
    this -> _modelsId.erase(p_id);
    this -> _models.erase(std::remove(this -> _models.begin(), this -> _models.end(), p_model), this -> _models.end());
    delete p_model;
}

void AssetManager::_deleteMesh(const char *p_id, Mesh *p_mesh) {
    this -> _meshesId.erase(p_id);
    this -> _meshes.erase(std::remove(this -> _meshes.begin(), this -> _meshes.end(), p_mesh), this -> _meshes.end());
    delete p_mesh;
}



void AssetManager::_loadModelNodeRecursively(Model *p_model, aiNode *p_node, const aiScene *p_scene) {
    for (unsigned int i = 0; i < p_node -> mNumMeshes; ++i) {
        this -> _loadModelMesh(p_model, p_scene -> mMeshes[p_node -> mMeshes[i]], p_scene);
    }

    for (unsigned int i = 0; i < p_node -> mNumChildren; ++i) {
        this -> _loadModelNodeRecursively(p_model, p_node -> mChildren[i], p_scene);
    }
}

void AssetManager::_loadModelMesh(Model *p_model, aiMesh *p_mesh, const aiScene *p_scene) {
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < p_mesh -> mNumVertices; ++i) {
        vertices.insert(vertices.end(), { p_mesh -> mVertices[i].x, p_mesh -> mVertices[i].y, p_mesh -> mVertices[i].z });
        if (p_mesh -> mTextureCoords[0]) {
            vertices.insert(vertices.end(), { p_mesh -> mTextureCoords[0][i].x, p_mesh -> mTextureCoords[0][i].y });
        } else {
            vertices.insert(vertices.end(), { 0.0f, 0.0f });
        }
        vertices.insert(vertices.end(), { -p_mesh -> mNormals[i].x, -p_mesh -> mNormals[i].y, -p_mesh -> mNormals[i].z });
    }

    for (unsigned int i = 0; i < p_mesh -> mNumFaces; ++i) {
        aiFace face = p_mesh -> mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }
    
    std::string diffuseMapFilepath = "";
    unsigned int materialIndex = p_mesh -> mMaterialIndex;
    aiMaterial* material = p_scene -> mMaterials[materialIndex];
    if(material -> GetTextureCount(aiTextureType_DIFFUSE)) {
        aiString path;
        if (material -> GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
            std::string textureFilename = io::FilenameFromFilepath(path.data);
            diffuseMapFilepath = p_model -> Rootpath() + textureFilename;
        }
    }
    
    Mesh *mesh = this -> AddMesh(&vertices[0], (unsigned int) vertices.size(), &indices[0], (unsigned int) indices.size(), "", diffuseMapFilepath.c_str(), "default");
    p_model -> AddMesh(mesh);
}



void AssetManager::_copy(const AssetManager &p_that) {
    
}

void AssetManager::_clear() {
    for (auto texture : this -> _textures) {
        delete texture;
    }
    for (auto material : this -> _lightingMaterials) {
        delete material;
    }
    for (auto mesh : this -> _meshes) {
        delete mesh;
    }
    for (auto model : this -> _models) {
        delete model;
    }
    
    this -> _models = std::vector<Model*>();
    this -> _modelsId = std::map<std::string, Model*>();
    this -> _textures = std::vector<Texture*>();
    this -> _texturesId = std::map<std::string, Texture*>();
    this -> _meshes = std::vector<Mesh*>();
    this -> _meshesId = std::map<std::string, Mesh*>();
    this -> _lightingMaterials = std::vector<LightingMaterial*>();
    this -> _lightingMaterialsId = std::map<std::string, LightingMaterial*>();
}
