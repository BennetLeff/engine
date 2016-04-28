/*
 * MeshImporter.h
 *
 *  Created on: Apr 26, 2016
 *      Author: bennetleff
 */

#ifndef MESHIMPORTER_H_
#define MESHIMPORTER_H_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"

struct Vertex {
	glm::vec3 position_;
	glm::vec2 texCoords_;
	glm::vec3 normals_;
};

struct Tex {
	GLuint id;
	std::string type;
};

class MeshImporter {
public:
	MeshImporter(std::string path);
	void loadModel(std::string path);
	void draw();
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	Mesh getMesh()
	{
		return meshes[0];
	}

	std::vector<glm::vec3> position_;
	std::vector<glm::vec2> texCoords_;
	std::vector<GLuint> indices_;
	std::vector<Mesh> meshes;

private:
	std::string directory;

	void processNode(aiNode* node, const aiScene* scene);
};

#endif /* MESHIMPORTER_H_ */
