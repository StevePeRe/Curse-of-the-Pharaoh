#version 330 core
layout (location = 0) in vec4 aLocation;

out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    TexCoords = aLocation.zw;
    gl_Position = projection * vec4(aLocation.x, aLocation.y, 1.0, 1.0);
}