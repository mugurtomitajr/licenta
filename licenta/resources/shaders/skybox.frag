#version 330

in vec3 textureCoord;

out vec4 color;

uniform samplerCube textureSampler;

void main() {
    color = texture(textureSampler, textureCoord);
}
