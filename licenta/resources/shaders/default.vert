#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 norm;

out vec4 vertexColor;
out vec2 textureCoord;
out vec3 normal;
out vec3 fragmentPosition;
//flat out vec3 normal; - picks provoking vertex

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0);
    vertexColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
    textureCoord = uv;
    normal = mat3(transpose(inverse(model))) * norm;
    fragmentPosition = (model * vec4(pos, 1.0)).xyz;
}
