#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;


out vec2 _uv;
uniform mat4 p;

void main() {
    gl_Position = p * vec4(pos, 1.0);
    _uv = uv;
}
