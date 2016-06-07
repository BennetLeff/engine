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
    Q_PROPERTY(double position_x READ getPosition_x WRITE setPosition_x)
    Q_PROPERTY(double position_y READ getPosition_y WRITE setPosition_y)
    Q_PROPERTY(double position_z READ getPosition_z WRITE setPosition_z)

public:
	Model(std::string path, std::string texture, Transform* trans);
	Model(std::string path, std::string texture);
	Mesh* loadModel(std::string path);
	void draw(Camera* cam);
	// If a texture has not been added
	// Allows one to be bound. 
	void bindTexture(Texture tex);
    Transform* getTransform() { return transform; }
	Transform* transform;

private:
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::string path;
	std::string directory;
	std::vector<Mesh> meshes;
	Mesh* modelMesh;
	Texture tex;
    bool textureSet = false;
	Shader shader;

    // These methods are so that Q_PROPERTY can acess certain fields
    double getPosition_x()
    {
        return transform->getPosition()->x;
    }
    double getPosition_y()
    {
        return transform->getPosition()->y;
    }
    double getPosition_z()
    {
        return transform->getPosition()->z;
    }

    double setPosition_x(int x)
    {
        transform->getPosition()->x = x;
    }
    double setPosition_y(int y)
    {
        transform->getPosition()->y = y;
    }
    double setPosition_z(int z)
    {
        transform->getPosition()->z = z;
    }
};
