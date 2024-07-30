#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;


out vec2 TexCoords;

uniform mat4 position;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = position * vec4(aPos, 1.0);
}