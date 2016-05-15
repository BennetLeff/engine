#include "Shader.h"

#include <stdio.h>
#include <glm/vec3.hpp>

Shader::Shader(std::string file)
{
    program = glCreateProgram();

    auto file_str = std::string("./res/shaders");

    // shaders[0] = createShader(load(file_str + ".vs"), GL_VERTEX_SHADER);
    // shaders[1] = createShader(load(file_str + ".fs"), GL_FRAGMENT_SHADER);


    shaders[0] = createShader(std::string("#version 330\n"
                                                  "\n"
                                                  "layout (location = 0) in vec2 texcoord;\n"
                                                  "layout (location = 1) in vec3 position;\n"
                                                  "layout (location = 2) in vec3 normals;\n"
                                                  "\n"
                                                  "out vec2 TexCoord;\n"
                                                  "out vec3 Normals;\n"
                                                  "out vec3 Vertex;\n"
                                                  "\n"
                                                  "out vec3 FragPos;\n"
                                                  "\n"
                                                  "// transform\n"
                                                  "uniform mat4 model;\n"
                                                  "// perspective matrix\n"
                                                  "uniform mat4 persp;\n"
                                                  "// view matrix\n"
                                                  "uniform mat4 view;\n"
                                                  "\n"
                                                  "void main()\n"
                                                  "{\n"
                                                  "    gl_Position = persp * view * model * vec4(position, 1.0);\n"
                                                  "    TexCoord = texcoord;\n"
                                                  "    Normals = normals;\n"
                                                  "    Vertex = position;\n"
                                                  "    FragPos = vec3(model *  vec4(position, 1.0f));\n"
                                                  "}"), GL_VERTEX_SHADER);
    shaders[1] = createShader(std::string("#version 330\n"
                                               "\n"
                                               "#define NUMPOINTLIGHTS 10\n"
                                               "\n"
                                               "in vec2 TexCoord;\n"
                                               "in vec3 Normals;\n"
                                               "in vec3 Vertex;\n"
                                               "\n"
                                               "in vec3 FragPos;\n"
                                               "\n"
                                               "out vec4 outColor;\n"
                                               "\n"
                                               "uniform sampler2D tex;\n"
                                               "// transform\n"
                                               "uniform mat4 model;\n"
                                               "// perspective matrix\n"
                                               "uniform mat4 persp;\n"
                                               "// view matrix\n"
                                               "uniform mat4 view;\n"
                                               "// camera position\n"
                                               "uniform vec3 campos;\n"
                                               "\n"
                                               "uniform struct PointLight\n"
                                               "{\n"
                                               "    float intensity;\n"
                                               "    vec3  position;\n"
                                               "    vec3  color;\n"
                                               "} pointLight [NUMPOINTLIGHTS];\n"
                                               "\n"
                                               "\n"
                                               "vec3 createLight(int i)\n"
                                               "{\n"
                                               "    vec3 lightColor = pointLight[i].color * pointLight[i].intensity;\n"
                                               "\n"
                                               "    // ambient component\n"
                                               "    float ambientStrength = 0.1f;\n"
                                               "    vec3 ambient = ambientStrength * lightColor;\n"
                                               "\n"
                                               "    // diffuse component\n"
                                               "    mat3 normalMatrix = transpose(inverse(mat3(model)));\n"
                                               "    vec3 normal = normalize(normalMatrix * Normals);\n"
                                               "    vec3 lightDir = normalize(pointLight[i].position - FragPos);\n"
                                               "    float diff = max(dot(normal, lightDir), 0.0);\n"
                                               "    vec3 diffuse = diff * lightColor;\n"
                                               "\n"
                                               "    // Specular\n"
                                               "    float specularStrength = 0.5f;\n"
                                               "    vec3 viewDir = normalize(campos - FragPos);\n"
                                               "    vec3 reflectDir = reflect(-lightDir, normal);\n"
                                               "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
                                               "    vec3 specular = specularStrength * spec * lightColor;\n"
                                               "\n"
                                               "    return (diffuse + ambient + specular);\n"
                                               "}\n"
                                               "\n"
                                               "\n"
                                               "void main()\n"
                                               "{\n"
                                               "    vec3 lightingTotal = vec3(0);\n"
                                               "    for (int index = 0; index < NUMPOINTLIGHTS; index++)\n"
                                               "    {\n"
                                               "        lightingTotal += createLight(index);\n"
                                               "    }\n"
                                               "\n"
                                               "\n"
                                               "    vec3 result = lightingTotal * vec3(texture(tex, TexCoord));\n"
                                               "    outColor = vec4(result, 1.0f);\n"
                                               "}"), GL_FRAGMENT_SHADER);

    for (int i = 0; i < NUMSHADERS; i++)
        glAttachShader(program, shaders[i]);

    glLinkProgram(program);
    checkShaderError(program, GL_LINK_STATUS, true, "Error linking shader.\n");

    glValidateProgram(program);
    checkShaderError(program, GL_VALIDATE_STATUS, true, "Error invalid shader.\n");

    if (!glGetError())
    {
        printf("Error in shader class: ");
        printf("%u\n", glGetError());
    }

    // Assign the transform uniform to the location of its attribute.
    uniforms[MODEL_U] = glGetUniformLocation(program, "model");
    uniforms[VIEW_U] = glGetUniformLocation(program, "view");
    uniforms[PERSPECTIVE_U] = glGetUniformLocation(program, "persp");
    uniforms[CAMPOS_U] = glGetUniformLocation(program, "campos");

    // Create point lights
    auto light = PointLight(1.0f, glm::vec3(5), glm::vec3(1, 1, 1));
    // auto light2 = PointLight(1.0f, glm::vec3(-5, 5, 5), glm::vec3(1, 1, 1));
    pointLights.push_back(light);
    // pointLights.push_back(light2);
}

std::string Shader::load(std::string file)
{
    // Read the Vertex Shader code from the file
    std::string shaderCode;
    std::ifstream shaderStream(file.c_str(), std::ios::in);
    if(shaderStream.is_open())
    {
        std::string line = "";
        while(getline(shaderStream, line))
            shaderCode += "\n" + line;
        shaderStream.close();
    } 
    else 
    {
        printf("Impossible to open %s. Are you in the right directory?\n", file.c_str());
        getchar();
        return 0;
    }

    return shaderCode;
}

GLuint Shader::createShader(std::string text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    // The array to store the shader in.
    const GLchar* shaderSource[1];
    GLint shaderSourceLenghts[1];
    // Store the shader and get its length.
    shaderSource[0] = text.c_str();
    shaderSourceLenghts[0] = (int) text.length();
    // Compile the shader.
    glShaderSource(shader, 1, shaderSource, shaderSourceLenghts);
    glCompileShader(shader);

    return shader;
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, std::string errorMessage)
{
    GLint success = 0;
    GLchar error[1024];

    glGetShaderiv(shader, flag, &success);

    /*
    if (success)
    {
         glGetProgramInfoLog(shader, sizeof(error), NULL, error);
         printf("%s%s\n", errorMessage.c_str(), error);
    }
    */
}

void Shader::update(const Transform* trans, const Camera* cam)
{
	// Multiply the camera projection matrix by the
	// transform matrix to apply a camera.
	glm::mat4 model = trans->getModel();
	// Model attribute set here.
	glUniformMatrix4fv(uniforms[MODEL_U], 1, GL_FALSE, &model[0][0]);
    glm::mat4 view = cam->getView();
    // Model attribute set here.
    glUniformMatrix4fv(uniforms[VIEW_U], 1, GL_FALSE, &view[0][0]);
    glm::mat4 perspectice = cam->getPerspective();
    // Model attribute set here.
    glUniformMatrix4fv(uniforms[PERSPECTIVE_U], 1, GL_FALSE, &perspectice[0][0]);

    glUniform3fv(uniforms[CAMPOS_U], 1, &cam->getStartPosition()[0]);
    
    for (int i = 0; i < pointLights.size(); i++)
    {
        int_loc = glGetUniformLocation(program, ("pointLight[" + std::to_string(i) + "].intensity").c_str());
        pos_loc = glGetUniformLocation(program, ("pointLight[" + std::to_string(i) + "].position").c_str());
        col_loc = glGetUniformLocation(program, ("pointLight[" + std::to_string(i) + "].color").c_str());

        glUniform1f(int_loc, pointLights[i].intensity);
        glUniform3fv(pos_loc, 1, &pointLights[i].position[0]);
        glUniform3fv(col_loc, 1, &pointLights[i].color[0]);
    }
}

void Shader::draw()
{
    glUseProgram(program);
}
