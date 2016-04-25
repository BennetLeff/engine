#include <vector>
#include <OpenGL/gl3.h>
#include <glm/glm.hpp>

struct ModelData
{
	std::vector<float> vertices_;
	std::vector<float> texCoords_;
	std::vector<GLuint> indices_;
	std::vector<float> normals_;

	ModelData(std::vector<float> vertices, std::vector<float> texCoords, std::vector<GLuint> indices)
		: vertices_(vertices), texCoords_(texCoords), indices_(indices) {}
};

class Vertex
{
public:
	Vertex(const glm::vec3& pos) :
		pos_(pos) {}
private:
	glm::vec3 pos_;
};


class Mesh
{
public:
    Mesh();
    Mesh(ModelData modelData);
    ~Mesh();
    void draw();
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
