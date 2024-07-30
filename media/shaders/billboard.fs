#version 330 core
out vec4 FragColor;
uniform sampler2D Texture;
uniform vec3 particleColor;

in vec2 TexCoords;

void main() 
{
    //FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
    //FragColor = vec4(color, 1.0);
    if (particleColor == vec3(1.0f,1.0f,1.0f)) 
        FragColor = texture(Texture, TexCoords);
    else 
        FragColor = vec4(particleColor, 1.0f);
}
