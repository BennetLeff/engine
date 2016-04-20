#include "OpenGL/gl3.h"
#include <string>
#include <vector> 
#include <fstream>

class Shader
{
public:
    GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);
    // GLuint loadShader(const char* file_path);
    Shader(std::string file);
    
    GLuint createShader(std::string text, GLenum shaderType);
    void checkShaderError(GLuint shader, GLuint flag, bool isProgram, std::string errorMessage);
    void draw();
    std::string load(std::string file);
private:
    static const short NUMSHADERS = 2;
    GLuint VertexShaderID;
    GLuint FragmentShaderID;

    GLuint shaders[NUMSHADERS];
    GLuint program;
};