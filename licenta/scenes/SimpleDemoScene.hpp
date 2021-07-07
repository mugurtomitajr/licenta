//
//  SimpleDemoScene.hpp
//  practice
//

#ifndef SimpleDemoScene_hpp
#define SimpleDemoScene_hpp

#include <cstdio>
#include "Scene.hpp"
#include "../cameras/ControllableCamera.hpp"
#include "../instances/generation/GeneratedBoardManager.hpp"

class SimpleDemoScene : public Scene {
public:
    SimpleDemoScene();
    ~SimpleDemoScene();
    
    void Start();
    void Update(double dt, const glm::vec2 &p_deltaMouse, bool *p_keyPressedArray);
    void Stop();
    
    void _loadShaders();
    void _loadModels();
    void _loadInstances();
    void _loadLights();
    void _loadCamera(GLfloat p_verticalFov, GLfloat p_displayRatio);
    
private:
    struct SimpleDemoSceneData {
        GeneratedBoardManager *boardManager;
        PointLight *blueLight, *redLight;
        double lightCircleRadians = 0.0f;
    } _data;
    
    void _clear();
};

#endif /* SimpleDemoScene_hpp */
