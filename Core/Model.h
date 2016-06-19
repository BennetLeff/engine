/*
 * Model.h
 *
 *  Created on: Apr 28, 2016
 *      Author: bennetleff
 */

#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"
#include "GameObject.h"

#include <QObject>


class Model : public GameObject
{
    Q_OBJECT
    Q_PROPERTY(Transform* Transform READ getTransform)
	Q_PROPERTY(Texture* Texture MEMBER tex)
public:
	Model(std::string path, std::string texture, Transform* trans);
	Model(std::string path, std::string texture);
	Mesh* loadModel(std::string path);
	void draw(Camera* cam);
	// If a texture has not been added
	// Allows one to be bound. 
	void bindTexture(Texture* tex);
	// void bindTexture(std::string texPath);
    Transform* getTransform() { return transform; }
	Transform* transform;
    void attachLight(Light* light);
    Texture* texture(){ return tex; }
    bool textureSet = false;

private:
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::string path;
	std::string directory;
	std::vector<Mesh> meshes;
	Mesh* modelMesh;
	Texture* tex;
	Shader* shader;
};

