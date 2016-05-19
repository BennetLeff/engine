//
// Created by bennet on 5/17/16.
//

#include "EditorRenderer.h"
#include <chrono>

EditorRenderer::EditorRenderer(RenderEngine renderEngine, int width, int height)
    : frame(0), engine(renderEngine), width(width), height(height)
{ }

void EditorRenderer::initialize()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    initializeOpenGLFunctions();

    glViewport(0, 0, width, height);
}

void EditorRenderer::addModel(Model *model)
{
    engine.addModel(model);
}

// Draws OpenGL
void EditorRenderer::paintGL()
{
    // Draw the scene
    clear(0.1, 0.4, 0.6, 1.0);

    glEnable(GL_DEPTH_TEST);

    auto house = new Model("/home/bennet/Desktop/engine/res/farm house/OBJ/Farmhouse OBJ.obj", "/home/bennet/Desktop/engine/res/farm house/Textures/Farmhouse Texture.jpg");

    house->transform->getPosition()->z = 40;
    house->transform->getRotation()->y = -1.9;

    engine.addModel(house);

    engine.draw();
}

