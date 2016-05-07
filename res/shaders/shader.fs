#version 330

#define NUMPOINTLIGHTS 10

in vec2 TexCoord;
in vec3 Normals;
in vec3 Vertex;

in vec3 FragPos;

out vec4 outColor;

uniform sampler2D tex;
// transform
uniform mat4 model;
// perspective matrix
uniform mat4 persp;
// view matrix
uniform mat4 view;
// camera position
uniform vec3 campos;

uniform struct PointLight
{
    float intensity;
    vec3  position;
    vec3  color;
} pointLight [NUMPOINTLIGHTS];


vec3 createLight(int i)
{
    vec3 lightColor = pointLight[i].color * pointLight[i].intensity;

    // ambient component
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse component
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * Normals);
    vec3 lightDir = normalize(pointLight[i].position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(campos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    return (diffuse + ambient + specular);
}


void main()
{
    vec3 lightingTotal = vec3(0);
    for (int index = 0; index < NUMPOINTLIGHTS; index++)
    {
        lightingTotal += createLight(index);
    }


    vec3 result = lightingTotal * vec3(texture(tex, TexCoord));
    outColor = vec4(result, 1.0f);
}