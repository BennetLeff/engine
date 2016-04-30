#pragma once

#include <vector>
#include <OpenGL/gl3.h>
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
//		for (int i = 0; i < vertices.size(); i++)
//			printf ("vertices: vec3(x: %g, y: %g, z: %g)\n", vertices[i].x, vertices[i].y, vertices[i].z);
//		for (int i = 0; i < texCoords.size(); i++)
//			printf ("texCoords: vec2(x: %g, y: %g)\n", texCoords[i].x, texCoords[i].y);
//		for (int i = 0; i < indices.size(); i++)
//			printf ("indices: uint: %d\n", indices[i]);

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
    Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textures, std::vector<GLuint> indices);
    ~Mesh();
    void draw();
    glm::vec3 pos;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> textures;
    std::vector<GLuint> elms;
private:
    enum {
    	POSITION_VB,
		INDEX_VB,
		TEXCOORD_VB,
    	NUMBUFFERS
    };

    GLuint vertexArrayObject_;
    GLuint vertexBufferObject_[NUMBUFFERS];
    unsigned int drawCount_;
};
