//
//  Shader.hpp
//  practice
//

#ifndef Shader_hpp
#define Shader_hpp

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../support/io.hpp"
#include "../support/constants.hpp"

#include "../light/DirectionalLight.hpp"
#include "../light/PointLight.hpp"
#include "../light/SpotLight.hpp"
#include "Texture.hpp"
#include "LightingMaterial.hpp"

class Shader {
public:
    Shader();
    ~Shader();
    
    bool Load(const char* p_vertexPath, const char* p_fragmentPath);
    
    void ApplyWorldMatrix(const glm::mat4 &p_worldMatrix);
    void ApplyViewMatrix(const glm::mat4 &p_viewMatrix);
    void ApplyProjectionMatrix(const glm::mat4 &p_projectionMatrix);
    void ApplyObserverPosition(const glm::vec3 &p_observerPosition);
    
    void ApplyLightingMaterial(const LightingMaterial &p_material);
    void ApplyDefaultLightingMaterial();
    void ApplyDiffuseMap(const Texture &p_diffuseMap);
    void ApplyDefaultDiffuseMap();
    
    void ApplyDirectionalLight(DirectionalLight* p_directionalLight);
    void ApplyPointLights(PointLight** p_pointLightsArray, unsigned int p_pointLightsArrayLength);
    void ApplySpotLights(SpotLight** p_spotLightsArray, unsigned int p_spotLightsArrayLength);
    
    void BindDefaults(LightingMaterial *p_material, Texture *p_texture);

    void Use();
    
    static void Remove();
    
private:
    GLuint _glId;
    GLuint _uniformWorldMatrix, _uniformViewMatrix, _uniformProjectionMatrix;
    GLuint _uniformSpecularIntensity, _uniformSpecularPower;
    GLuint _uniformObserverPosition;
    GLuint _uniformNumOfPointLights, _uniformNumOfSpotLights;

    bool _compileShader(const char* p_vertexCode, const char* p_fragmentCode);
    void _addShaderStage(GLuint p_program, const char* p_shaderCode, GLenum p_shaderType);
    
    virtual void _copy(const Shader &p_that);
    virtual void _clear();
    
    struct LightCommonUniformLayout {
        GLuint uniformColor = 0;
        GLuint uniformAmbientIntensity = 0;
        GLuint uniformDiffuseIntensity = 0;
        GLuint uniformSpecularIntensity = 0;
    };
    
    struct LightDirectionalUniformLayout {
        LightCommonUniformLayout shared;
        GLuint uniformDirection;
    };
    
    struct LightPointUniformLayout {
        LightCommonUniformLayout shared;
        GLuint uniformPosition;
        GLuint uniformAttenuation;
    };
    
    struct LightSpotUniformLayout {
        LightPointUniformLayout point;
        GLuint uniformDirection;
        GLuint uniformEdge;
    };
    
    LightDirectionalUniformLayout _uniformDirectionalLight;
    
    unsigned int _numOfPointLights = 0;
    LightPointUniformLayout _uniformPointLights[SHADER_MAX_POINT_LIGHTS];
    
    unsigned int _numOfSpotLights = 0;
    LightSpotUniformLayout _uniformSpotLights[SHADER_MAX_SPOT_LIGHTS];
    
    LightingMaterial *_defaultLightingMaterial;
    Texture *_defaultDiffuseMap;
};

#endif /* Shader_hpp */
