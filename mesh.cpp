#include "mesh.h"
#include "transform.h"


Mesh::Mesh(ModelData modelData)
{
	drawCount_ = modelData.indices_.size();

    glGenVertexArrays(1, &vertexArrayObject_);
   	glBindVertexArray(vertexArrayObject_);

   	glGenBuffers(NUMBUFFERS, vertexBufferObject_);

   	// Position Attrib
   	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_[POSITION_VB]);
   	glBufferData(GL_ARRAY_BUFFER, sizeof(modelData.vertices_[0]) * modelData.vertices_.size(), modelData.vertices_.data(), GL_STATIC_DRAW);
   	glEnableVertexAttribArray(1);
   	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

   	// Texture Attrib
   	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_[TEXCOORD_VB]);
   	glBufferData(GL_ARRAY_BUFFER, sizeof(modelData.texCoords_[0]) * modelData.texCoords_.size(), modelData.texCoords_.data(), GL_STATIC_DRAW);
   	glEnableVertexAttribArray(0);
   	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


   	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferObject_[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(modelData.indices_[0]) * modelData.indices_.size(), modelData.indices_.data(), GL_STATIC_DRAW);

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
