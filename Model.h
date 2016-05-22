/*
 * Model.h
 *
 *  Created on: Apr 28, 2016
 *      Author: bennetleff
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

class Model
{
public:
	Model(std::string path, std::string texture, Transform* trans);
	Model(std::string path, std::string texture);
	Mesh* loadModel(std::string path);
	void draw(Camera* cam);
	// If a texture has not been added
	// Allows one to be bound. 
	void bindTexture(Texture tex);
	Transform* transform;
private:
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::string path;
	std::string directory;
	std::vector<Mesh> meshes;
	Mesh* modelMesh;
	Texture tex;
	Shader shader;
};

#endif /* MODEL_H_ */
