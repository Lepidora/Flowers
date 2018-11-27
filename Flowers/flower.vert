#version 330 core

uniform mat4 mvp;

layout(location = 0) in vec3 worldspacePosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec4 data;

out vec2 UV;
out vec2 colormod;

void main() {
    
    float x = 500.0;//worldspacePosition.x * data.x;
    float y = 500.0;//worldspacePosition.y * data.y;
    float q = data.x * data.y * 0 + 1;
    float p = worldspacePosition.x;
    mat4 z = mvp;
    gl_Position = mvp * vec4(worldspacePosition, 1) + vec4(data.xy, 1, 1);
    UV = vertexUV;
    UV.x /= 8;
    UV.x += (data.z / 8);
    colormod = data.xy;
}
