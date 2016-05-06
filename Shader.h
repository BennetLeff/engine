#pragma once

#include <string>
#include <vector> 
#include <fstream>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

#include "Camera.h"
#include "Transform.h"

class Shader
{
public:
    GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);
    Shader(std::string file);
    
    GLuint createShader(std::string text, GLenum shaderType);
    void checkShaderError(GLuint shader, GLuint flag, bool isProgram, std::string errorMessage);
    void draw();
    void update(const Transform* trans, const Camera* cam);
    std::string load(std::string file);
private:
    static const short NUMSHADERS = 2;

    enum {
    	MODEL_U,
        VIEW_U,
        PERSPECTIVE_U,
        LIGHT_U,
		NUMUNIFORMS
    };

    GLuint shaders[NUMSHADERS];
    GLuint uniforms[NUMUNIFORMS];
    GLuint program;
    Transform transform;
};
