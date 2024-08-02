#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 p;

void main() {
   gl_Position = p * vec4(pos, 1.0);
}
