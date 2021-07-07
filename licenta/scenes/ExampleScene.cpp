//
//  ExampleScene.cpp
//  practice
//

#include "ExampleScene.hpp"

ExampleScene::ExampleScene() : Scene() {}
ExampleScene::~ExampleScene() { this -> _clear(); }

void ExampleScene::Start() {
    this -> _data.drone = this -> _sceneManager.GetInstance("drone");
    this -> _data.water = this -> _sceneManager.GetInstance("water");
    
    this -> _data.droneSpotLightLeft = this -> _sceneManager.GetSpotLight("drone-spot-light-left");
    this -> _data.droneSpotLightRight = this -> _sceneManager.GetSpotLight("drone-spot-light-right");
    this -> _data.blueLight = this -> _sceneManager.GetPointLight("drone-blue-light");
    this -> _data.redLight = this -> _sceneManager.GetPointLight("drone-red-light");
    
    this -> _data.lightCircleRadians = 0.0f;
    Scene::Start();
}

void ExampleScene::Update(double dt, const glm::vec2 &p_deltaMouse, bool *p_keyPressedArray) {
    Scene::Update(dt, p_deltaMouse, p_keyPressedArray);
    
    glm::vec3 spotPosition = this -> _data.drone -> WorldPosition() + (this -> _camera -> Front() * 0.4f);
    this -> _data.droneSpotLightLeft -> Position(spotPosition + (this -> _camera -> Right() * -0.6f));
    this -> _data.droneSpotLightLeft -> Direction(this -> _camera -> Front());
    
    this -> _data.droneSpotLightRight -> Position(spotPosition + (this -> _camera -> Right() * 0.6f));
    this -> _data.droneSpotLightRight -> Direction(this -> _camera -> Front());
    
    this -> _data.lightCircleRadians += dt * 10.0f;
    if(this -> _data.lightCircleRadians > 360.0f) {
        this -> _data.lightCircleRadians -= 360.0f;
    }
    GLfloat distance = 1.0f;
    this -> _data.blueLight -> Position(this -> _data.drone -> Position() + glm::vec3(distance * sin(this -> _data.lightCircleRadians), 0.0, distance * cos(this -> _data.lightCircleRadians)));
    this -> _data.redLight -> Position(this -> _data.drone -> Position() + glm::vec3(0.0f, distance * sin(this -> _data.lightCircleRadians), distance * cos(this -> _data.lightCircleRadians)));
    
    //this -> _data.water -> Position(glm::vec3(this -> _camera -> Position().x, 0.0f, this -> _camera -> Position().z));
}

void ExampleScene::Stop() {
    
}

void ExampleScene::_loadShaders() {
    this -> _assetManager.AddShader("ground", "resources/shaders/ground.vert", "resources/shaders/ground.frag");
    this -> _assetManager.GetShader("ground") -> BindDefaults(this -> _assetManager.GetLightingMaterial("dull"), this -> _assetManager.AddTexture("grass", "resources/textures/grass-repeating-2.jpg"));
    
    this -> _assetManager.AddShader("water", "resources/shaders/water.vert", "resources/shaders/water.frag");
    this -> _assetManager.GetShader("water") -> BindDefaults(this -> _assetManager.GetLightingMaterial("shiny"), this -> _assetManager.AddTexture("water", "resources/textures/water-1.jpeg"));
}

void ExampleScene::_loadTextures() {
    Scene::_loadTextures();
}

void ExampleScene::_loadModels() {
    Scene::_loadModels();
    
    threedim::MeshData meshData = threedim::GeneratePlane(20, nullptr);
    Mesh *waterMesh = this -> _assetManager.AddMesh("water-mesh", meshData.vertices.data(), (unsigned int)meshData.vertices.size(), meshData.indices.data(), (unsigned int)meshData.indices.size(), "water-texture", "", "water-material");
    Model *waterModel = this -> _assetManager.CreateModel("water-model", glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), {"water-mesh"});
    
    //this -> _assetManager.AddModel("bloc", "resources/models/bloc/Blocuri vip.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(0.001f, 0.001f, 0.001f));
}

void ExampleScene::_loadInstances() {
    ControllableDrone *drone = new ControllableDrone(nullptr, glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f));
    this -> _sceneManager.AddInstance("drone", "default", drone);
    
    FollowingDrone *followDrone1 = new FollowingDrone(1, nullptr, glm::vec3(10.0f, 20.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f));
    this -> _sceneManager.AddInstance("follow-drone-1", "default", followDrone1);
    
    FollowingDrone *followDrone2 = new FollowingDrone(2, nullptr, glm::vec3(-10.0f, 20.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f));
    this -> _sceneManager.AddInstance("follow-drone-2", "default", followDrone2);
        
    //this -> _sceneManager.AddInstance("bloc-instance-1", "default", "bloc", nullptr, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    
    GeneratedBoardManager *boardManager = new GeneratedBoardManager(nullptr, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    this -> _sceneManager.AddInstance("board-manager", "default", boardManager);
    boardManager -> Position(glm::vec3(0.0f, -2.0f, 0.0f));
    
    this -> _sceneManager.AddInstance("water", "water", "water-model", nullptr, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(400.0f, 1.0f, 400.0f));

    this -> _data.boardManager = boardManager;
}

void ExampleScene::_loadLights() {
    this -> _sceneManager.SetDirectionalLight(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.40f, 0.4f, 0.4f);
    this -> _sceneManager.AddSpotLight("drone-spot-light-left", glm::vec3(0.0f, 0.0f, 1.0f), 40.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.02f, 0.02f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), 1.8f, 1.6f, 1.2f);
    this -> _sceneManager.AddSpotLight("drone-spot-light-right", glm::vec3(0.0f, 0.0f, 1.0f), 40.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.02f, 0.02f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), 1.8f, 1.6f, 1.2f);
    
    this -> _sceneManager.AddPointLight("drone-blue-light", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.4f, 0.6f, 1.0f), glm::vec3(0.8f, 0.8f, 1.0f), 0.4f, 0.4f, 0.4f);
    this -> _sceneManager.AddPointLight("drone-red-light", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.4f, 0.6f, 1.0f), glm::vec3(1.0f, 0.8f, 0.8f), 0.4f, 0.4f, 0.4f);
}

void ExampleScene::_loadCamera(GLfloat p_verticalFov, GLfloat p_displayRatio) {
    Instance* cameraTarget = this -> _sceneManager.GetInstance("drone");
    this -> _camera = new FollowingCamera(cameraTarget, p_verticalFov, p_displayRatio, glm::vec3(0.0f, 40.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, -20.0f);
    this -> _data.boardManager -> CameraObserver(this -> _camera);
}


void ExampleScene::_clear() {}
