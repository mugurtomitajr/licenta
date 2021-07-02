//
//  Scene.hpp
//  practice
//

#ifndef Scene_hpp
#define Scene_hpp

#include <cstdio>
#include "AssetManager.hpp"
#include "SceneManager.hpp"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "Camera.hpp"
#include "threedim.hpp"

class Scene {
public:
    Scene();
    ~Scene();
    
    bool Load(GLfloat p_verticalFov, GLfloat _displayRatio);
    virtual void Start();
    virtual void MasterUpdate(double dt, const glm::vec2 &p_deltaMouse, bool *p_keyPressedArray);
    virtual void Update(double dt, const glm::vec2 &p_deltaMouse, bool *p_keyPressedArray);
    void Render(double dt, double inter);
    virtual void Stop();
    
protected:
    AssetManager _assetManager;
    SceneManager _sceneManager;
    Camera *_camera;
    Skybox *_skybox;
    
    std::map<Shader*, std::vector<Instance*>>* _instanceShaderLinkArray;
    std::vector<Instance*>* _instanceParentOnlyArray;
    DirectionalLight* _directionalLight;
    PointLight** _pointLightsArray;
    SpotLight** _spotLightsArray;
    
    bool _loaded = false;
    
    virtual void _loadDefaultShaders();
    virtual void _loadDefaultTextures();
    virtual void _loadDefaultLightingMaterials();
    virtual void _loadDefaultMeshes();
    virtual void _loadDefaultModels();
    virtual void _loadDefaultLights();
    
    virtual void _loadShaders();
    virtual void _loadTextures();
    virtual void _loadLightingMaterials();
    virtual void _loadMeshes();
    virtual void _loadModels();
    virtual void _loadInstances();
    virtual void _loadLights();
    virtual void _loadCamera(GLfloat p_verticalFov, GLfloat p_displayRatio);
    virtual void _loadSkybox();
    
    virtual void _copy(const Scene &p_that);
    virtual void _clear();
};

#endif /* Scene_hpp */
