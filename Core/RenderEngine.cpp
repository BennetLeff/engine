#include "RenderEngine.h"

RenderEngine::RenderEngine(Camera* cam)
    : cam(cam)
{
    this->init();
}

void RenderEngine::init() { }

void RenderEngine::addModel(Model* model)
{
    for (int i = 0; i < this->lights.size(); i++)
    {
        model->attachLight(this->lights[i]);
    }

    this->models.push_back(model);
}

void RenderEngine::attachLight(Light *light)
{
    this->lights.push_back(light);

    for (int i = 0; i < this->models.size(); i++)
    {
        models[i]->attachLight(light);
    }
}

void RenderEngine::draw()
{
     for (int i = 0; i < this->models.size(); i++)
    	models[i]->draw(this->cam);
}