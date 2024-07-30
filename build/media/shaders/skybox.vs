#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 position = projection * view * vec4(aPos, 1.0f);
    gl_Position = vec4(position.x, position.y, position.w, position.w);
    TexCoords = vec3(aPos.x, aPos.y, -aPos.z);
}