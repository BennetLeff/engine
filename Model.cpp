/*
 * Model.cpp
 *
 *  Created on: Apr 28, 2016
 *      Author: bennetleff
 */

#include "Model.h"

Model::Model(std::string path) {
	this->path = path;
	modelMesh_ = loadModel();
}

Mesh* Model::loadModel()
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("Error importing mesh %s", import.GetErrorString());
	}

	// Just process the first mesh. Support
	// for multiple meshes will be added.
	return processMesh(scene->mMeshes[0], scene);
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textures;
	std::vector<GLuint> indices;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		glm::vec3 vertex;
		vertex.x = mesh->mVertices[i].x;
		vertex.y = mesh->mVertices[i].y;
		vertex.z = mesh->mVertices[i].z;
		vertices.push_back(vertex);

		glm::vec3 normal;
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;
		normals.push_back(normal);

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 texture;
			texture.x = mesh->mTextureCoords[0][i].x;
			texture.y = mesh->mTextureCoords[0][i].y;
			textures.push_back(texture);
		}
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return new Mesh(vertices, textures, indices);
}

void Model::draw()
{
	modelMesh_->draw();
}
