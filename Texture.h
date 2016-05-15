#pragma once
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

class Texture
{
public:
    Texture(std::string filePath);
    void bind(GLuint unit);
private:
    GLuint tex;
    unsigned char* image;
    int width;
    int height;
    int comp;
};
