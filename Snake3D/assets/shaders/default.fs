#version 450 core

in vec2 fTexCoord;

uniform sampler2D uTexture;

out vec4 Color;

void main() {
    Color = vec4(0.18, 0.54, 0.82, 1.0);
}