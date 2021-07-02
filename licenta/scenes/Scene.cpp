//
//  Scene.cpp
//  practice
//

#include "Scene.hpp"

Scene::Scene() {
    this -> _loaded = false;
    this -> _instanceShaderLinkArray = nullptr;
    this -> _instanceParentOnlyArray = nullptr;
    this -> _directionalLight = nullptr;
    this -> _pointLightsArray = nullptr;
    this -> _spotLightsArray = nullptr;
    this -> _camera = nullptr;
    this -> _skybox = nullptr;
}

Scene::~Scene() {
    this -> _clear();
}

void Scene::Start() {
    for(auto instance : *(this -> _instanceParentOnlyArray)) {
        instance -> Start();
    }
}

bool Scene::Load(GLfloat p_verticalFov, GLfloat p_displayRatio) {
    if( !this -> _loaded ) {
        this -> _assetManager = AssetManager();
        this -> _sceneManager = SceneManager(&(this -> _assetManager));
        
        this -> _loadDefaultTextures();
        this -> _loadDefaultLightingMaterials();
        this -> _loadDefaultShaders();
        this -> _loadDefaultMeshes();
        this -> _loadDefaultModels();
        this -> _loadDefaultLights();
        
        this -> _loadTextures();
        this -> _loadLightingMaterials();
        this -> _loadShaders();
        this -> _loadMeshes();
        this -> _loadModels();
        this -> _loadInstances();
        this -> _loadLights();
        this -> _loadCamera(p_verticalFov, p_displayRatio);
        this -> _loadSkybox();
        
        this -> _instanceShaderLinkArray = this -> _sceneManager.InstanceShaderLinkArray();
        this -> _instanceParentOnlyArray = this -> _sceneManager.InstancesParentsOnly();
        this -> _directionalLight = this -> _sceneManager.DirectionalLightReference();
        this -> _pointLightsArray = this -> _sceneManager.PointLightsArray();
        this -> _spotLightsArray = this -> _sceneManager.SpotLightsArray();
        
        this -> _assetManager.Print();
        this -> _sceneManager.Print();
        
        this -> _loaded = true;
    }
    
    return true;
}

void Scene::MasterUpdate(double dt, const glm::vec2 &p_deltaMouse, bool *p_keyPressedArray) {
    this -> _sceneManager.RuntimeQueueCheck();
    this -> Update(dt, p_deltaMouse, p_keyPressedArray);
    for(auto instance : *(this -> _instanceParentOnlyArray)) {
        instance -> MasterUpdate(dt, p_deltaMouse, p_keyPressedArray);
    }
}

void Scene::Update(double dt, const glm::vec2 &p_deltaMouse, bool *p_keyPressedArray) {
    this -> _camera -> Update(dt, p_deltaMouse, p_keyPressedArray);
}

void Scene::Render(double dt, double inter) {
    // TODO: check for camera
    if(this -> _skybox) {
        this -> _skybox -> Render(this -> _camera -> ProjectionMatrix(), this -> _camera -> ViewMatrix());
    }
    for(auto sceneShader : *(this -> _instanceShaderLinkArray)) {
        Shader* shader = sceneShader.first;
        std::vector<Instance*> instances = sceneShader.second;
        
        shader -> Use();
        shader -> ApplyProjectionMatrix(this -> _camera -> ProjectionMatrix());
        shader -> ApplyDirectionalLight(this -> _directionalLight);
        shader -> ApplyPointLights(this -> _pointLightsArray, this -> _sceneManager.PointLightsArrayCount());
        shader -> ApplySpotLights(this -> _spotLightsArray, this -> _sceneManager.SpotLightsArrayCount());
        
        shader -> ApplyObserverPosition(this -> _camera -> Position());
        shader -> ApplyViewMatrix(this -> _camera -> ViewMatrix());
        
        for(auto instance : instances) {
            instance -> Render(dt, inter);
        }
        
        Shader::Remove();
    }
}

void Scene::Stop() {
    for(auto instance : *(this -> _instanceParentOnlyArray)) {
        instance -> Stop();
    }
}



void Scene::_loadDefaultShaders() {
    this -> _assetManager.AddShader("default", "resources/shaders/default.vert", "resources/shaders/default.frag");
    this -> _assetManager.GetShader("default") -> BindDefaults(this -> _assetManager.GetLightingMaterial("default"), this -> _assetManager.GetTexture("default"));
    
    this -> _assetManager.AddShader("skybox", "resources/shaders/skybox.vert", "resources/shaders/skybox.frag");
    this -> _assetManager.GetShader("skybox") -> BindDefaults(this -> _assetManager.GetLightingMaterial("default"), this -> _assetManager.GetTexture("default"));
}

void Scene::_loadDefaultTextures() {
    this -> _assetManager.AddTexture("default", "resources/textures/plain-white.png");
}

void Scene::_loadDefaultLightingMaterials() {
    this -> _assetManager.AddLightingMaterial("default", 0.4f, 32);
    this -> _assetManager.AddLightingMaterial("shiny", 1.0f, 256);
    this -> _assetManager.AddLightingMaterial("dull", 0.1f, 2);
}

void Scene::_loadDefaultMeshes() {
    threedim::MeshData cubeData = threedim::GenerateCube();
    this -> _assetManager.AddMesh("cube-skybox", cubeData.vertices.data(), (unsigned int)cubeData.vertices.size(), cubeData.indices.data(), (unsigned int)cubeData.indices.size(), "default", "", "default");
}

void Scene::_loadDefaultModels() {
    //this -> _assetManager.CreateModel("cube-skybox", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), {"cube-skybox"});
}

void Scene::_loadDefaultLights() {
    this -> _sceneManager.SetDirectionalLight(glm::vec3(2.0f, -1.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.40f, 0.20f, 0.10f);
}



void Scene::_loadShaders() {}

void Scene::_loadTextures() {}

void Scene::_loadLightingMaterials() {}

void Scene::_loadMeshes() {}

void Scene::_loadModels() {}

void Scene::_loadInstances() {}

void Scene::_loadLights() {}

void Scene::_loadCamera(GLfloat p_verticalFov, GLfloat p_displayRatio) {
    this -> _camera = new Camera(p_verticalFov, p_displayRatio, glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f);
}

void Scene::_loadSkybox() {
    Skybox *skybox = new Skybox();
    /*skybox -> Load(this -> _assetManager.GetShader("skybox"), this -> _assetManager.GetMesh("cube-skybox"), {
        "resources/textures/skyboxes/skybox-1/skybox_rt.tga",
        "resources/textures/skyboxes/skybox-1/skybox_lf.tga",
        "resources/textures/skyboxes/skybox-1/skybox_up.tga",
        "resources/textures/skyboxes/skybox-1/skybox_dn.tga",
        "resources/textures/skyboxes/skybox-1/skybox_bk.tga",
        "resources/textures/skyboxes/skybox-1/skybox_ft.tga",
    });*/
    
    /*skybox -> Load(this -> _assetManager.GetShader("skybox"), this -> _assetManager.GetMesh("cube-skybox"), {
        "resources/textures/skyboxes/skybox-2/galaxy+X.tga",
        "resources/textures/skyboxes/skybox-2/galaxy-X.tga",
        "resources/textures/skyboxes/skybox-2/galaxy+Y.tga",
        "resources/textures/skyboxes/skybox-2/galaxy-Y.tga",
        "resources/textures/skyboxes/skybox-2/galaxy+Z.tga",
        "resources/textures/skyboxes/skybox-2/galaxy-Z.tga",
    });*/
    
    skybox -> Load(this -> _assetManager.GetShader("skybox"), this -> _assetManager.GetMesh("cube-skybox"), {
        "resources/textures/skyboxes/skybox-3/1.png",
        "resources/textures/skyboxes/skybox-3/3.png",
        "resources/textures/skyboxes/skybox-3/5.png",
        "resources/textures/skyboxes/skybox-3/6.png",
        "resources/textures/skyboxes/skybox-3/2.png",
        "resources/textures/skyboxes/skybox-3/4.png",
    });
    
    /*skybox -> Load(this -> _assetManager.GetShader("skybox"), this -> _assetManager.GetMesh("cube-skybox"), {
        "resources/textures/skyboxes/skybox-4/posx.jpg",
        "resources/textures/skyboxes/skybox-4/negx.jpg",
        "resources/textures/skyboxes/skybox-4/posy.jpg",
        "resources/textures/skyboxes/skybox-4/negy.jpg",
        "resources/textures/skyboxes/skybox-4/posz.jpg",
        "resources/textures/skyboxes/skybox-4/negz.jpg",
    });*/
    
    this -> _skybox = skybox;
}



void Scene::_copy(const Scene &p_that) {
    
}

void Scene::_clear() {
    delete this -> _camera;
    delete this -> _skybox;
    this -> _camera = nullptr;
    this -> _skybox = nullptr;
    
    this -> _loaded = false;
    this -> _instanceShaderLinkArray = nullptr;
    this -> _instanceParentOnlyArray = nullptr;
    this -> _directionalLight = nullptr;
    this -> _pointLightsArray = nullptr;
    this -> _spotLightsArray = nullptr;
}
