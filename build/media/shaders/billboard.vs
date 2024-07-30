#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //vec4 worldOrigin = mul(model, vec4(0,0,0,1));
    //vec4 viewOrigin = vec4(mul(model * view, vec4(0,0,0,1)).xyz, 1); 
    //vec4 worldPos = mul(model, aPos);
    //vec4 flipedWorldPos = vec4(-1,1,-1,1) * (worldPos - worldOrigin) + worldOrigin;
    //vec4 viewPos = worldPos - worldOrigin + viewOrigin;
    //gl_Position = mul(projection, viewPos);
    gl_Position = projection * view * model * vec4(aPos,1.0f);
    TexCoords = aTexCoords;
}