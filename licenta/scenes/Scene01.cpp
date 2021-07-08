//
//  SimpleDemoScene.cpp
//  practice
//

#include "Scene01.hpp"

Scene01::Scene01() : Scene() {}
Scene01::~Scene01() { this -> _clear(); }

void Scene01::Start() {
    this -> _data.blueLight = this -> _sceneManager.GetPointLight("blue-light");
    this -> _data.redLight = this -> _sceneManager.GetPointLight("red-light");
    this -> _data.lightCircleRadians = 0.0f;
    Scene::Start();
}

void Scene01::Update(double dt, const glm::vec2 &p_deltaMouse, bool *p_keyPressedArray) {
    Scene::Update(dt, p_deltaMouse, p_keyPressedArray);
    
    SpotLight *flashLight = this -> _sceneManager.GetSpotLight("flash-light");
    if(flashLight) {
        glm::vec3 flashLightPosition = this -> _camera -> Position() - glm::vec3(0.0f, 0.3f, 0.0f);
        flashLight -> Position(flashLightPosition);
        flashLight -> Direction(this -> _camera -> Front());
    }
    
    this -> _data.lightCircleRadians += dt * 10.0f;
    if(this -> _data.lightCircleRadians > 360.0f) {
        this -> _data.lightCircleRadians -= 360.0f;
    }
    GLfloat distance = 4.0f;
    this -> _data.blueLight -> Position(this -> _camera -> Position() + glm::vec3(distance * sin(this -> _data.lightCircleRadians), 0.0, distance * cos(this -> _data.lightCircleRadians)));
    this -> _data.redLight -> Position(this -> _camera -> Position() + glm::vec3(0.0f, distance * sin(this -> _data.lightCircleRadians), distance * cos(this -> _data.lightCircleRadians)));
}

void Scene01::Stop() {
    
}

void Scene01::_loadShaders() {
    this -> _assetManager.AddShader("ground", "resources/shaders/ground.vert", "resources/shaders/ground.frag");
    this -> _assetManager.GetShader("ground") -> BindDefaults(this -> _assetManager.GetLightingMaterial("dull"), this -> _assetManager.AddTexture("grass", "resources/textures/grass-repeating-2.jpg"));
    
    this -> _assetManager.AddShader("water", "resources/shaders/water.vert", "resources/shaders/water.frag");
    this -> _assetManager.GetShader("water") -> BindDefaults(this -> _assetManager.GetLightingMaterial("shiny"), this -> _assetManager.AddTexture("water", "resources/textures/water-1.jpeg"));
}

void Scene01::_loadModels() {
    Scene::_loadModels();
}

void Scene01::_loadInstances() {
    GeneratedBoardManager *boardManager = new GeneratedBoardManager(nullptr, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    this -> _sceneManager.AddInstance("board-manager", "default", boardManager);
    boardManager -> Position(glm::vec3(0.0f, -2.0f, 0.0f));

    this -> _data.boardManager = boardManager;
}

void Scene01::_loadCamera(GLfloat p_verticalFov, GLfloat p_displayRatio) {
    this -> _camera = new ControllableCamera(p_verticalFov, p_displayRatio, glm::vec3(0.0f, 40.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f);
    this -> _data.boardManager -> CameraObserver(this -> _camera);
}

void Scene01::_loadLights() {
    this -> _sceneManager.SetDirectionalLight(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.60f, 0.6f, 0.6f);
    this -> _sceneManager.AddPointLight("blue-light", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.2f, 0.3f), glm::vec3(0.1f, 0.1f, 1.0f), 1.0f, 0.4f, 1.0f);
    this -> _sceneManager.AddPointLight("red-light", glm::vec3(2.0f, 2.0f, -2.0f), glm::vec3(0.1f, 0.2f, 0.3f), glm::vec3(1.0f, 0.1f, 0.2f), 1.0f, 0.4f, 1.0f);
    this -> _sceneManager.AddSpotLight("flash-light", glm::vec3(0.0f, 0.0f, 0.0f), 20.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.05f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), 0.6f, 0.6f, 0.2f);
}


void Scene01::_clear() {}
