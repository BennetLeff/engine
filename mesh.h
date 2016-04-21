#include <OpenGL/gl3.h>

class Mesh
{
public:
    Mesh(GLuint shaderProgram);
    void draw();
private:
    GLuint shaderProgram;
    GLuint vao;
    GLuint vbo;
};