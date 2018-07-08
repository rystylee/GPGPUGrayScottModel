#version 400 core

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;

out vec4 vPosition;
out vec2 vTexCoord;

void main()
{
    vPosition = position;
    vTexCoord = texcoord;
    gl_Position = modelViewProjectionMatrix * position;
}
