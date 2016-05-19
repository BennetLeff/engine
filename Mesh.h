#pragma once

#include <vector>
#include <stdio.h>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
	#include <GL/glew.h>
#endif

#include <glm/glm.hpp>

struct ModelData
{
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec2> texCoords_;
	std::vector<GLuint> indices_;
	std::vector<glm::vec3> normals_;

	ModelData(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::vector<GLuint> indices)
		: vertices_(vertices), texCoords_(texCoords), indices_(indices)
	{
		if (texCoords.size() == 0)
		{
			printf("no texCoords");
		}
		if (indices.size() == 0)
		{
			printf("no indices");
		}
	}
};

class Mesh
{
public:
    Mesh();
    Mesh(ModelData modelData);
    Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textures, std::vector<GLuint> indices);
    ~Mesh();
    void draw();
    glm::vec3 pos;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textures;
    std::vector<GLuint> elms;
private:
    enum {
    	POSITION_VB,
		INDEX_VB,
		TEXCOORD_VB,
        NORMAL_VB,
    	NUMBUFFERS
    };

    GLuint vertexArrayObject_;
    GLuint vertexBufferObject_[NUMBUFFERS];
    unsigned int drawCount_;
};
