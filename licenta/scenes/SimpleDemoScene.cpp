//
//  SimpleDemoScene.cpp
//  practice
//

#include "SimpleDemoScene.hpp"

SimpleDemoScene::SimpleDemoScene() : Scene() {}
SimpleDemoScene::~SimpleDemoScene() { this -> _clear(); }

void SimpleDemoScene::Start() {
    this -> _data.blueLight = this -> _sceneManager.GetPointLight("blue-light");
    this -> _data.redLight = this -> _sceneManager.GetPointLight("red-light");
    this -> _data.lightCircleRadians = 0.0f;
}

void SimpleDemoScene::Update(double dt, const glm::vec2 &p_deltaMouse, bool *p_keyPressedArray) {
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

void SimpleDemoScene::Stop() {
    
}

void SimpleDemoScene::_loadModels() {
    Scene::_loadModels();
}

void SimpleDemoScene::_loadInstances() {
    this -> _sceneManager.AddInstance("default", "plane", nullptr, glm::vec3(0.0f, -4.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
}

void SimpleDemoScene::_loadLights() {
    this -> _sceneManager.AddPointLight("blue-light", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.2f, 0.3f), glm::vec3(0.1f, 0.1f, 1.0f), 1.0f, 0.4f, 1.0f);
    this -> _sceneManager.AddPointLight("red-light", glm::vec3(2.0f, 2.0f, -2.0f), glm::vec3(0.1f, 0.2f, 0.3f), glm::vec3(1.0f, 0.1f, 0.2f), 1.0f, 0.4f, 1.0f);
    this -> _sceneManager.AddSpotLight("flash-light", glm::vec3(0.0f, 0.0f, 0.0f), 20.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.05f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), 0.6f, 0.6f, 0.2f);
}


void SimpleDemoScene::_clear() {}
