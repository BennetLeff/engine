#include <OpenGL/gl3.h>

class Texture
{
public:
    Texture();

private:
    GLuint tex;
    unsigned char* image;
    int width;
    int height;
    int comp;
};