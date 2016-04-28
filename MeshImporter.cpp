/*
 * MeshImporter.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: bennetleff
 */

#include "MeshImporter.h"

MeshImporter::MeshImporter(std::string path) {
	loadModel(path);
}

void MeshImporter::draw()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].draw();
	}
}

void MeshImporter::loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("Error importing mesh %s", import.GetErrorString());
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void MeshImporter::processNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (int j = 0; j < node->mNumChildren; j++)
	{
		processNode(node->mChildren[j], scene);
	}
}

Mesh MeshImporter::processMesh(aiMesh* mesh, const aiScene* scene)
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

//	if (mesh->mMaterialIndex >= 0)
//	{
//		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//		printf("need to load a texture");
//	}


	/////// Mesh data
	std::vector<GLuint> elements2 =  {
			0, 1, 2,
			2, 3, 0
		};

	std::vector<glm::vec3> vertices2 =  {
		glm::vec3(-0.5f,  0.5f, 0.0f),  // Top-left
		glm::vec3(0.5f,  0.5f, 0.0f),  	// Top-right
		glm::vec3(0.5f, -0.5f, 0.0f), 	// Bottom-right
		glm::vec3(-0.5f, -0.5f, 0.0f)	// Bottom-left
	};

	std::vector<glm::vec2> texCoords2 =  {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f)
	};

	//////////////////

	// struct ModelData mData(vertices2, texCoords2, elements2);

	indices_ = indices;
	position_ = vertices;
	texCoords_ = textures;

	return Mesh(vertices, textures, indices);
}
