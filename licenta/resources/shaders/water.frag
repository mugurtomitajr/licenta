#version 330

const int SHADER_MAX_POINT_LIGHTS = 3;
const int SHADER_MAX_SPOT_LIGHTS = 3;

struct LightLayout {
    vec3 color;
    float diffuseIntensity;
    float ambientIntensity;
    float specularIntensity;
};

struct DirectionalLightLayout {
    LightLayout shared;
    vec3 direction;
};

struct PointLightLayout {
    LightLayout shared;
    vec3 position;
    vec3 attenuation;
};

struct SpotLightLayout {
    PointLightLayout point;
    vec3 direction;
    float edge;
};

struct Material {
    float specularIntensity;
    float specularPower;
};

uniform DirectionalLightLayout directionalLight;
uniform PointLightLayout pointLights[SHADER_MAX_POINT_LIGHTS];
uniform int numOfPointLights;
uniform SpotLightLayout spotLights[SHADER_MAX_POINT_LIGHTS];
uniform int numOfSpotLights;

uniform Material material;

uniform sampler2D textureSampler;
uniform vec3 observerPosition;

in vec4 vertexColor;
in vec2 textureCoord;
in vec3 normal;
in vec3 fragmentPosition;

out vec4 color;

vec4 lightFromDirection(LightLayout light, vec3 direction) {
    vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;
    
    float diffuseFactor = max(dot(normalize(normal), normalize(direction)), 0.0f);
    vec4 diffuseColor = vec4(light.color, 1.0f) * light.diffuseIntensity * diffuseFactor;
    
    vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    
    if (diffuseFactor > 0.0f) {
        vec3 fragmentToObserver = normalize(observerPosition - fragmentPosition);
        vec3 reflectedDirection = normalize(reflect(direction, normalize(normal)));
        float specularFactor = dot(fragmentToObserver, reflectedDirection);
        if(specularFactor > 0.0f) {
            specularFactor = pow(specularFactor, material.specularPower);
            specularColor = vec4(light.color * light.specularIntensity * material.specularIntensity * specularFactor, 1.0f);
        }
    }
    
    return (ambientColor + diffuseColor + specularColor);
}

vec4 lightFromPoint(PointLightLayout light) {
    vec3 directionToSource = fragmentPosition - light.position;
    float distanceToSource = length(directionToSource);
    directionToSource = normalize(directionToSource);
    
    float attenuation = light.attenuation.x * distanceToSource * distanceToSource +
                        light.attenuation.y * distanceToSource +
                        light.attenuation.z;
    
    return lightFromDirection(light.shared, directionToSource) / attenuation;
}

void main() {
    vec4 result = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    result += lightFromDirection(directionalLight.shared, directionalLight.direction);
    
    for(int i = 0; i < numOfPointLights; ++i) {
        result += lightFromPoint(pointLights[i]);
    }
    
    for(int i = 0; i < numOfSpotLights; ++i) {
        vec3 directionToSource = normalize(fragmentPosition - spotLights[i].point.position);
        float cutoffCheck = dot(directionToSource, spotLights[i].direction);
        if(cutoffCheck > spotLights[i].edge) {
            vec4 spotLightColor = lightFromPoint(spotLights[i].point);
            spotLightColor *= (1.0f - (1.0f - cutoffCheck) * (1.0f / (1.0f - spotLights[i].edge))); // remap for dropoff
            result += spotLightColor;
        }
    }
    vec4 basecolor = texture(textureSampler, textureCoord * 10) * vec4(0.4, 0.4, 1.0, 0.4);
    color = vec4((basecolor * result).xyz, 0.4f); // TODO: set scale
}
