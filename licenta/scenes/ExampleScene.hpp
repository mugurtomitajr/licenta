//
//  ExampleScene.hpp
//  practice
//

#ifndef ExampleScene_hpp
#define ExampleScene_hpp

#include <cstdio>

#include "Scene.hpp"
#include "../instances/Instance.hpp"
#include "../instances/controllable/ControllableDrone.hpp"
#include "../instances/controllable/FollowingDrone.hpp"
#include "../instances/generation/GeneratedBoardManager.hpp"
#include "../cameras/FollowingCamera.hpp"

class ExampleScene : public Scene {
public:
    ExampleScene();
    ~ExampleScene();
    
    void Start();
    void Update(double dt, const glm::vec2 &p_deltaMouse, bool *p_keyPressedArray);
    void Stop();
    
    void _loadShaders();
    void _loadTextures();
    void _loadModels();
    void _loadInstances();
    void _loadLights();
    void _loadCamera(GLfloat p_verticalFov, GLfloat p_displayRatio);
    
private:
    struct ExampleSceneData {
        GeneratedBoardManager *boardManager;
        SpotLight *droneSpotLightLeft, *droneSpotLightRight;
        PointLight *blueLight, *redLight;
        Instance *drone, *water;
        double lightCircleRadians = 0.0f;
    } _data;
    
    void _clear();
};

#endif /* ExampleScene_hpp */
