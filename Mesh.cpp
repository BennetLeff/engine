#include "Mesh.h"
#include "Transform.h"

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textures, std::vector<GLuint> indices)
{
	drawCount_ = indices.size();

    glGenVertexArrays(1, &vertexArrayObject_);
    glBindVertexArray(vertexArrayObject_);

    glGenBuffers(NUMBUFFERS, vertexBufferObject_);

    // Position Attrib
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Texture Attrib
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textures[0]) * textures.size(), textures.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Normals Attrib
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferObject_[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject_);
}

void Mesh::draw()
{
	glBindVertexArray(vertexArrayObject_);
	glDrawElements(GL_TRIANGLES, drawCount_, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
