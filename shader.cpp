#include "shader.h"

#include <stdio.h>

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
    uniforms[TRANSFORM_U] = glGetUniformLocation(program, "trans");
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
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", file.c_str());
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

void Shader::update(const Transform& trans, const Camera& cam)
{
	// Multiply the camera projection matrix by the
	// transform matrix to apply a camera.
	glm::mat4 model = cam.getProjection() * trans.getModel();

	// Transformation attribute set here.
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

void Shader::draw()
{
    glUseProgram(program);
}
