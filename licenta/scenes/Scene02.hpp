//
//  SimpleDemoScene.hpp
//  practice
//

#ifndef Scene02_hpp
#define Scene02_hpp

#include <cstdio>
#include "Scene.hpp"
#include "../cameras/ControllableCamera.hpp"
#include "../instances/generation/GeneratedBoardManager.hpp"

class Scene02 : public Scene {
public:
    Scene02();
    ~Scene02();
    
    void Start();
    void Update(double dt, const glm::vec2 &p_deltaMouse, bool *p_keyPressedArray);
    void Stop();
    
    void _loadShaders();
    void _loadModels();
    void _loadInstances();
    void _loadLights();
    void _loadCamera(GLfloat p_verticalFov, GLfloat p_displayRatio);
    
private:
    struct SceneData {
        GeneratedBoardManager *boardManager;
    } _data;
    
    void _clear();
};

#endif /* Scene02_hpp */
