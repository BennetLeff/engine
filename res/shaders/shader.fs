#version 330

in vec2 TexCoord;
in vec3 Normals;
in vec3 Vertex;

in vec3 FragPos;

out vec4 outColor;

uniform sampler2D tex;
uniform mat4 model;

void main()
{
    float intensity = 1.0f;
    vec3 lightIntensity = vec3(intensity);
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f) * lightIntensity;

    // ambient component
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse component
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * Normals);
    vec3 lightDir = normalize(vec3(2, 1, 3) - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(vec3(0, 15, -40) - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 result = (diffuse + ambient) * vec3(texture(tex, TexCoord));
    // vec3 result = vec3(texture(tex, TexCoord));
    outColor = vec4(result, 1.0f);
}