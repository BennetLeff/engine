#pragma once
#include <OpenGL/gl3.h>

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
