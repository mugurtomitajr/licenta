//
//  Scene03.cpp
//  licenta
//

#include "Scene03.hpp"

Scene03::Scene03() : Scene() {}
Scene03::~Scene03() { this -> _clear(); }

void Scene03::Start() {
    Scene::Start();
}

void Scene03::Update(double dt, const glm::vec2 &p_deltaMouse, bool *p_keyPressedArray) {
    Scene::Update(dt, p_deltaMouse, p_keyPressedArray);
    
    SpotLight *flashLight = this -> _sceneManager.GetSpotLight("flash-light");
    if(flashLight) {
        glm::vec3 flashLightPosition = this -> _camera -> Position() - glm::vec3(0.0f, 0.3f, 0.0f);
        flashLight -> Position(flashLightPosition);
        flashLight -> Direction(this -> _camera -> Front());
    }
}

void Scene03::Stop() {
    
}

void Scene03::_loadShaders() {
    this -> _assetManager.AddShader("ground", "resources/shaders/ground.vert", "resources/shaders/ground.frag");
    this -> _assetManager.GetShader("ground") -> BindDefaults(this -> _assetManager.GetLightingMaterial("dull"), this -> _assetManager.AddTexture("grass", "resources/textures/grass-repeating-2.jpg"));
    
    this -> _assetManager.AddShader("water", "resources/shaders/water.vert", "resources/shaders/water.frag");
    this -> _assetManager.GetShader("water") -> BindDefaults(this -> _assetManager.GetLightingMaterial("shiny"), this -> _assetManager.AddTexture("water", "resources/textures/water-1.jpeg"));
}

void Scene03::_loadModels() {
    Scene::_loadModels();
}

void Scene03::_loadInstances() {
    GeneratedBoardManager *boardManager = new GeneratedBoardManager(nullptr, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    this -> _sceneManager.AddInstance("board-manager", "default", boardManager);
    boardManager -> Position(glm::vec3(0.0f, -2.0f, 0.0f));
    
    this -> _data.boardManager = boardManager;
}

void Scene03::_loadCamera(GLfloat p_verticalFov, GLfloat p_displayRatio) {
    this -> _camera = new ControllableCamera(p_verticalFov, p_displayRatio, glm::vec3(0.0f, 40.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f);
    this -> _data.boardManager -> CameraObserver(this -> _camera);
}

void Scene03::_loadLights() {
    this -> _sceneManager.SetDirectionalLight(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.60f, 0.6f, 0.6f);
    this -> _sceneManager.AddSpotLight("flash-light", glm::vec3(0.0f, 0.0f, 0.0f), 20.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.05f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), 0.6f, 0.6f, 0.2f);
}


void Scene03::_clear() {}
