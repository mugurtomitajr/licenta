//
//  Shader.cpp
//  practice
//

#include "Shader.hpp"

Shader::Shader() {
    this -> _glId = 0;
    
    this -> _uniformWorldMatrix = 0;
    this -> _uniformViewMatrix = 0;
    this -> _uniformProjectionMatrix = 0;
    
    this -> _uniformDirectionalLight.shared.uniformColor = 0; 
    this -> _uniformDirectionalLight.shared.uniformAmbientIntensity = 0;
    this -> _uniformDirectionalLight.shared.uniformDiffuseIntensity = 0;
    this -> _uniformDirectionalLight.shared.uniformSpecularIntensity = 0;
    this -> _uniformDirectionalLight.uniformDirection = 0;
    
    this -> _uniformSpecularIntensity = 0;
    this -> _uniformSpecularPower = 0;
    
    this -> _uniformObserverPosition = 0;
    
    this -> _uniformNumOfPointLights = 0;
    this -> _uniformNumOfSpotLights = 0;
    
    this -> _numOfPointLights = 0;
    this -> _numOfSpotLights = 0;
}

Shader::~Shader() {
    this -> _clear();
}

bool Shader::Load(const char* p_vertexPath, const char* p_fragmentPath) {
    std::string vertexString = io::StringFromFile(p_vertexPath);
    std::string fragmentString = io::StringFromFile(p_fragmentPath);
    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    return this -> _compileShader(vertexCode, fragmentCode);
}

void Shader::ApplyWorldMatrix(const glm::mat4 &p_worldMatrix) {
    glUniformMatrix4fv(this -> _uniformWorldMatrix, 1, GL_FALSE, glm::value_ptr(p_worldMatrix));
}

void Shader::ApplyViewMatrix(const glm::mat4 &p_viewMatrix) {
    glUniformMatrix4fv(this -> _uniformViewMatrix, 1, GL_FALSE, glm::value_ptr(p_viewMatrix));
}

void Shader::ApplyProjectionMatrix(const glm::mat4 &p_projectionMatrix) {
    glUniformMatrix4fv(this -> _uniformProjectionMatrix, 1, GL_FALSE, glm::value_ptr(p_projectionMatrix));
}

void Shader::ApplyObserverPosition(const glm::vec3 &p_observerPosition) {
    glUniformMatrix3fv(this -> _uniformObserverPosition, 1, GL_FALSE, glm::value_ptr(p_observerPosition));
}

void Shader::ApplyLightingMaterial(const LightingMaterial &p_material) {
    p_material.Use(this -> _uniformSpecularIntensity, this -> _uniformSpecularPower);
}

void Shader::ApplyDefaultLightingMaterial() {
    if(this -> _defaultLightingMaterial) {
        this -> _defaultLightingMaterial -> Use(this -> _uniformSpecularIntensity, this -> _uniformSpecularPower);
    } else {
        glUniform1f(this -> _uniformSpecularIntensity, 0.4);
        glUniform1f(this -> _uniformSpecularPower, 4);
    }
}

void Shader::ApplyDiffuseMap(const Texture &p_diffuseMap) {
    p_diffuseMap.Use();
}

void Shader::ApplyDefaultDiffuseMap() {
    if(this -> _defaultDiffuseMap) {
        this -> _defaultDiffuseMap -> Use();
    } else {
        Texture::Remove();
    }
}

void Shader::ApplyDirectionalLight(DirectionalLight* p_directionalLight) {
    p_directionalLight -> Use(this -> _uniformDirectionalLight.uniformDirection,
                           this -> _uniformDirectionalLight.shared.uniformColor,
                           this -> _uniformDirectionalLight.shared.uniformDiffuseIntensity,
                           this -> _uniformDirectionalLight.shared.uniformAmbientIntensity,
                           this -> _uniformDirectionalLight.shared.uniformSpecularIntensity);
}

void Shader::ApplyPointLights(PointLight** p_pointLightsArray, unsigned int p_pointLightsArrayLength) {
    if(p_pointLightsArrayLength > SHADER_MAX_POINT_LIGHTS) {
        p_pointLightsArrayLength = SHADER_MAX_POINT_LIGHTS;
    }
    
    glUniform1i(this -> _uniformNumOfPointLights, p_pointLightsArrayLength);
    for(unsigned int i = 0; i < p_pointLightsArrayLength; ++i) {
        p_pointLightsArray[i] -> Use(this -> _uniformPointLights[i].uniformPosition,
                             this -> _uniformPointLights[i].uniformAttenuation,
                             this -> _uniformPointLights[i].shared.uniformColor,
                             this -> _uniformPointLights[i].shared.uniformDiffuseIntensity,
                             this -> _uniformPointLights[i].shared.uniformAmbientIntensity,
                             this -> _uniformPointLights[i].shared.uniformSpecularIntensity);
    }
}

void Shader::ApplySpotLights(SpotLight** p_spotLightsArray, unsigned int p_spotLightsArrayLength) {
    if(p_spotLightsArrayLength > SHADER_MAX_SPOT_LIGHTS) {
        p_spotLightsArrayLength = SHADER_MAX_SPOT_LIGHTS;
    }
    
    glUniform1i(this -> _uniformNumOfSpotLights, p_spotLightsArrayLength);
    
    for(unsigned int i = 0; i < p_spotLightsArrayLength; ++i) {
        p_spotLightsArray[i] -> Use(this -> _uniformSpotLights[i].uniformDirection,
                            this -> _uniformSpotLights[i].uniformEdge,
                            this -> _uniformSpotLights[i].point.uniformPosition,
                            this -> _uniformSpotLights[i].point.uniformAttenuation,
                            this -> _uniformSpotLights[i].point.shared.uniformColor,
                            this -> _uniformSpotLights[i].point.shared.uniformDiffuseIntensity,
                            this -> _uniformSpotLights[i].point.shared.uniformAmbientIntensity,
                            this -> _uniformSpotLights[i].point.shared.uniformSpecularIntensity);
    }
}

void Shader::BindDefaults(LightingMaterial *p_material, Texture *p_texture) {
    this -> _defaultLightingMaterial = p_material;
    this -> _defaultDiffuseMap = p_texture;
}

void Shader::Use() {
    glUseProgram(this -> _glId);
}

void Shader::Remove() {
    glUseProgram(0);
}

bool Shader::_compileShader(const char* p_vertexCode, const char* p_fragmentCode) {
    this -> _glId = glCreateProgram();

    if ( !this -> _glId ) {
        fprintf(stdout, "Error creating shader program...\n");
        return false;
    }

    this -> _addShaderStage(this -> _glId, p_vertexCode, GL_VERTEX_SHADER);
    this -> _addShaderStage(this -> _glId, p_fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(this -> _glId);
    glGetProgramiv(this -> _glId, GL_LINK_STATUS, &result);
    if ( !result ) {
        glGetProgramInfoLog(this -> _glId, sizeof(eLog), NULL, eLog);
        fprintf(stdout, "Error linking program: %s\n", eLog);
        return false;
    }

    glValidateProgram(this -> _glId);
    glGetProgramiv(this -> _glId, GL_VALIDATE_STATUS, &result);
    if ( !result ) {
        glGetProgramInfoLog(this -> _glId, sizeof(eLog), NULL, eLog);
        fprintf(stdout, "Error validating program: %s\n", eLog);
    }

    this -> _uniformWorldMatrix = glGetUniformLocation(this -> _glId, "model");
    this -> _uniformViewMatrix = glGetUniformLocation(this -> _glId, "view");
    this -> _uniformProjectionMatrix = glGetUniformLocation(this -> _glId, "projection");
    
    this -> _uniformDirectionalLight.shared.uniformColor = glGetUniformLocation(this -> _glId, "directionalLight.shared.color");
    this -> _uniformDirectionalLight.shared.uniformAmbientIntensity = glGetUniformLocation(this -> _glId, "directionalLight.shared.ambientIntensity");
    this -> _uniformDirectionalLight.shared.uniformDiffuseIntensity = glGetUniformLocation(this -> _glId, "directionalLight.shared.diffuseIntensity");
    this -> _uniformDirectionalLight.shared.uniformSpecularIntensity = glGetUniformLocation(this -> _glId, "directionalLight.shared.specularIntensity");
    this -> _uniformDirectionalLight.uniformDirection = glGetUniformLocation(this -> _glId, "directionalLight.direction");
    
    this -> _uniformSpecularIntensity = glGetUniformLocation(this -> _glId, "material.specularIntensity");
    this -> _uniformSpecularPower = glGetUniformLocation(this -> _glId, "material.specularPower");
    
    this -> _uniformObserverPosition = glGetUniformLocation(this -> _glId, "observerPosition");
    
    this -> _uniformNumOfPointLights = glGetUniformLocation(this -> _glId, "numOfPointLights");
    
    for(unsigned int i = 0; i < SHADER_MAX_POINT_LIGHTS; ++i) {
        char identifierBuffer[256] = {'\0'};
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "pointLights[%d].shared.color", i);
        this -> _uniformPointLights[i].shared.uniformColor = glGetUniformLocation(this -> _glId, identifierBuffer);
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "pointLights[%d].shared.ambientIntensity", i);
        this -> _uniformPointLights[i].shared.uniformAmbientIntensity = glGetUniformLocation(this -> _glId, identifierBuffer);
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "pointLights[%d].shared.diffuseIntensity", i);
        this -> _uniformPointLights[i].shared.uniformDiffuseIntensity = glGetUniformLocation(this -> _glId, identifierBuffer);
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "pointLights[%d].shared.specularIntensity", i);
        this -> _uniformPointLights[i].shared.uniformSpecularIntensity = glGetUniformLocation(this -> _glId, identifierBuffer);
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "pointLights[%d].position", i);
        this -> _uniformPointLights[i].uniformPosition = glGetUniformLocation(this -> _glId, identifierBuffer);
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "pointLights[%d].attenuation", i);
        this -> _uniformPointLights[i].uniformAttenuation = glGetUniformLocation(this -> _glId, identifierBuffer);
    }
    
    this -> _uniformNumOfSpotLights = glGetUniformLocation(this -> _glId, "numOfSpotLights");
    
    for(unsigned int i = 0; i < SHADER_MAX_SPOT_LIGHTS; ++i) {
        char identifierBuffer[256] = {'\0'};
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "spotLights[%d].point.shared.color", i);
        this -> _uniformSpotLights[i].point.shared.uniformColor = glGetUniformLocation(this -> _glId, identifierBuffer);
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "spotLights[%d].point.shared.ambientIntensity", i);
        this -> _uniformSpotLights[i].point.shared.uniformAmbientIntensity = glGetUniformLocation(this -> _glId, identifierBuffer);
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "spotLights[%d].point.shared.diffuseIntensity", i);
        this -> _uniformSpotLights[i].point.shared.uniformDiffuseIntensity = glGetUniformLocation(this -> _glId, identifierBuffer);
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "spotLights[%d].point.shared.specularIntensity", i);
        this -> _uniformSpotLights[i].point.shared.uniformSpecularIntensity = glGetUniformLocation(this -> _glId, identifierBuffer);
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "spotLights[%d].point.position", i);
        this -> _uniformSpotLights[i].point.uniformPosition = glGetUniformLocation(this -> _glId, identifierBuffer);
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "spotLights[%d].point.attenuation", i);
        this -> _uniformSpotLights[i].point.uniformAttenuation = glGetUniformLocation(this -> _glId, identifierBuffer);
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "spotLights[%d].direction", i);
        this -> _uniformSpotLights[i].uniformDirection = glGetUniformLocation(this -> _glId, identifierBuffer);
        
        snprintf(identifierBuffer, sizeof(identifierBuffer), "spotLights[%d].edge", i);
        this -> _uniformSpotLights[i].uniformEdge = glGetUniformLocation(this -> _glId, identifierBuffer);
    }
    return true;
}

void Shader::_addShaderStage(GLuint p_program, const char* p_shaderCode, GLenum p_shaderType) {
    GLuint stage = glCreateShader(p_shaderType);

    const GLchar* stageCode[1];
    stageCode[0] = p_shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(p_shaderCode);

    glShaderSource(stage, 1, stageCode, codeLength);
    glCompileShader(stage);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(stage, GL_COMPILE_STATUS, &result);
    if ( !result ) {
        glGetShaderInfoLog(stage, sizeof(eLog), NULL, eLog);
        fprintf(stdout, "Error compiling the %d shader: %s\n", p_shaderType, eLog);
        return;
    }

    glAttachShader(p_program, stage);
}

void Shader::_clear() {
    if ( this -> _glId != 0 ) {
        glDeleteProgram(this -> _glId);
        this -> _glId = 0;
    }

    this -> _uniformWorldMatrix = 0;
    this -> _uniformViewMatrix = 0;
    this -> _uniformProjectionMatrix = 0;
    
    this -> _uniformDirectionalLight.shared.uniformColor = 0;
    this -> _uniformDirectionalLight.shared.uniformAmbientIntensity = 0;
    this -> _uniformDirectionalLight.shared.uniformDiffuseIntensity = 0;
    this -> _uniformDirectionalLight.shared.uniformSpecularIntensity = 0;
    this -> _uniformDirectionalLight.uniformDirection = 0;
    
    this -> _uniformSpecularIntensity = 0;
    this -> _uniformSpecularPower = 0;
    
    this -> _uniformObserverPosition = 0;
    
    this -> _uniformNumOfPointLights = 0;
    this -> _uniformNumOfSpotLights = 0;
    
    this -> _numOfPointLights = 0;
    this -> _numOfSpotLights = 0;
}

void Shader::_copy(const Shader &p_that) {
    
}
        
