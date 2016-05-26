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
#include "Light.h"

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
    // Use to set texture drawing uniform
    void canDrawTexture(bool canDraw);
private:
    static const short NUMSHADERS = 2;

    enum {
    	MODEL_U,
        VIEW_U,
        PERSPECTIVE_U,
        LIGHT_U,
        CAMPOS_U,
        TEXSET_U,
		NUMUNIFORMS
    };

    std::vector<PointLight> pointLights;

    GLuint shaders[NUMSHADERS];
    GLuint uniforms[NUMUNIFORMS];
    GLuint program;
    Transform transform;

    // Point light uniform locations
    GLuint int_loc;
    GLuint pos_loc;
    GLuint col_loc;

    bool textureIsSetup = false;
};
