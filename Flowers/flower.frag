#version 330 core

in vec2 UV;
in vec2 colormod;

out vec4 color;

uniform sampler2D textureSampler;

void main() {
    
    vec4 b = texture(textureSampler, UV);
    //color = vec4(colormod.x/500.0, colormod.y/500.0, 0.3, 1.0);
    vec4 colorz = vec4(colormod.x/500.0, colormod.y/500.0, 0.3, 1.0);
    color = b;
}
