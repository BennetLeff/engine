#include "RenderEngine.h"

RenderEngine::RenderEngine(Camera* cam)
    : cam(cam)
{
    this->init();
}

void RenderEngine::init()
{
    // If not on OSX we need to include
    // OpenGL as an extension
    #ifndef __APPLE__
        glewExperimental = GL_TRUE;

        GLenum err = glewInit();
        if (GLEW_OK != err) {
            /* Problem: glewInit failed, something is seriously wrong. */
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        }
    #endif

    glEnable(GL_DEPTH_TEST);
}

void RenderEngine::addModel(Model* model)
{
    this->models.push_back(model);
}

void RenderEngine::draw()
{
    for (int i = 0; i < this->models.size(); i++)
    	models[i]->draw(this->cam);
}