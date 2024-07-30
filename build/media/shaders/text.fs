#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D charTexture;
uniform vec3 color;

void main() 
{
    if (texture(charTexture, TexCoords).a < 0.1) discard;
    vec4 sample = vec4(1.0,1.0,1.0,texture(charTexture, TexCoords).r);
    FragColor = vec4(color, 1.0) * sample;
}