#version 330 core

uniform sampler2D tex;
uniform vec4 color;

in vec2 _uv;
out vec4 frag_color;

// to alter texture color : color * texture
void main() {
    frag_color = texture(tex, _uv);
}
