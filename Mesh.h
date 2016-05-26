#pragma once

#include <vector>
#include <stdio.h>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
	#include <GL/glew.h>
#endif

#include <glm/glm.hpp>

class Mesh
{
public:
    Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textures, std::vector<GLuint> indices);
    ~Mesh();
    void draw();

private:
    enum {
    	POSITION_VB,
		INDEX_VB,
		TEXCOORD_VB,
        NORMAL_VB,
    	NUMBUFFERS
    };

    GLuint vertexArrayObject;
    GLuint vertexBufferObject[NUMBUFFERS];
    unsigned int drawCount;
};
