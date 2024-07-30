#version 330 core
out vec4 FragColor;
uniform sampler2D Texture;

uniform vec3 color;
uniform vec3 LightColor;
uniform float AmbientStrength;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


void main() 
{
    // al recurso material se le pasa difuso float, ambiente float y especular float
    // y a las luces direccion(ligthdirection vec3) e intensidad(color o ligthcolor vec3)
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(-vec3(0.0f,1.5f,-1.0f));

    // Componente ambiente
    // tocar este 0.3
    float ambientStrength = AmbientStrength;
    //vec3 ambient = ambientStrength * vec3(0.923f,0.729f,0.239f);
    vec3 ambient = ambientStrength * LightColor;

    // Componente difusa
    // shader cartoon
    float diff = max(dot(norm, lightDirection), 0.0f);
    diff = floor(diff * float(3)) / float(3);
    vec3 diffuse = diff * LightColor;
    //vec3 diffuse = diff * vec3(0.923f,0.729f,0.239f);

    // Ambient bajo y diffuso alto para tener mas oscuro con toques de luz
    // Componente especular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos);  // Dirección de la vista
    vec3 reflectDir = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = specularStrength * spec * LightColor;
    //vec3 specular = specularStrength * spec * vec3(0.923f,0.729f,0.239f);

    FragColor = vec4(vec3(ambient + diffuse + specular), 1.0f) * texture(Texture, TexCoords);
    //FragColor = vec4(result, 1.0f);
    //FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
    //FragColor = vec4(color, 1.0);
    //FragColor = texture(Texture, TexCoords);
}

