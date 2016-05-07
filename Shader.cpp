#include "Shader.h"

#include <stdio.h>
#include <glm/vec3.hpp>

Shader::Shader(std::string file)
{
    program = glCreateProgram();

    shaders[0] = createShader(load(file + ".vs"), GL_VERTEX_SHADER);
    shaders[1] = createShader(load(file + ".fs"), GL_FRAGMENT_SHADER);

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

    // create a point light
    PointLight light;
    light.intensity = 1.0f;
    light.position = glm::vec3(5, 5, 5);
    light.color = glm::vec3(1.0, 0.0, 0.0);

    // add light to list of lights
    pointLights.push_back(light);
    // create a second point light
    PointLight light2;
    light2.intensity = 1.0f;
    light2.position = glm::vec3(-5, 5, 5);
    light2.color = glm::vec3(0.0, 0.0, 1.0);
    pointLights.push_back(light2);
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
