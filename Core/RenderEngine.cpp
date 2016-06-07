#include "RenderEngine.h"

RenderEngine::RenderEngine(Camera* cam)
    : cam(cam)
{
    this->init();
}

void RenderEngine::init() { }

void RenderEngine::addModel(Model* model)
{
    this->models.push_back(model);
}

void RenderEngine::draw()
{
     for (int i = 0; i < this->models.size(); i++)
    	models[i]->draw(this->cam);
}