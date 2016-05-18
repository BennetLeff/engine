//
// Created by bennet on 5/17/16.
//

#include "EditorRenderer.h"

EditorRenderer::EditorRenderer(Camera* cam)
    : frame(0), cam(cam) { }

void EditorRenderer::initialize()
{
    glewExperimental = GL_TRUE;
    glewInit();

    models.push_back(new Model("/home/bennet/Desktop/engine/res/Alfred/Alfred.obj", "/home/bennet/Desktop/engine/res/Alfred/alfred_dif.png"));
}

void EditorRenderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.1, 0.4, 0.6, 1.0);

    for (int i = 0; i < this->models.size(); i++)
        models[i]->draw(this->cam);

    ++frame;
}