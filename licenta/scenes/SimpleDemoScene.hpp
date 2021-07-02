//
//  SimpleDemoScene.hpp
//  practice
//

#ifndef SimpleDemoScene_hpp
#define SimpleDemoScene_hpp

#include <cstdio>
#include "Scene.hpp"

class SimpleDemoScene : public Scene {
public:
    SimpleDemoScene();
    ~SimpleDemoScene();
    
    void Start();
    void Update(double dt, const glm::vec2 &p_deltaMouse, bool *p_keyPressedArray);
    void Stop();
    
    void _loadModels();
    void _loadInstances();
    void _loadLights();
    
private:
    struct SimpleDemoSceneData {
        PointLight *blueLight, *redLight;
        double lightCircleRadians = 0.0f;
    } _data;
    
    void _clear();
};

#endif /* SimpleDemoScene_hpp */
