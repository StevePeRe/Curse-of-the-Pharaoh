#version 330 core
out vec4 FragColor;
uniform sampler2D texture_diffuse1;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(-vec3(0.5f,-0.5f,0.0f));

    // Componente ambiente
    // tocar este 0.3
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * vec3(0.923f,0.729f,0.239f);

    // Componente difusa
    float diff = max(dot(norm, lightDirection), 0.0f);
    // shader cartoon
    diff = floor(diff * float(3)) / float(3);
    vec3 diffuse = diff * vec3(0.923f,0.729f,0.239f);

    // Ambient bajo y diffuso alto para tener mas oscuro con toques de luz
    // Componente especular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos);  // Dirección de la vista
    vec3 reflectDir = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = specularStrength * spec * vec3(0.923f,0.729f,0.239f);

    FragColor = vec4(vec3(ambient + diffuse + specular), 1.0f) * texture(texture_diffuse1, TexCoords);

    //FragColor = texture(texture_diffuse1, TexCoords);
}