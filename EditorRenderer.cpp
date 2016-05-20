//
// Created by bennet on 5/17/16.
//

#include "EditorRenderer.h"

EditorRenderer::EditorRenderer(RenderEngine* renderEngine, int width, int height)
{
	frame = 0;
	this->width = width;
	this->height = height;
	this->engine = renderEngine;
	this->window = new GUIWindow(0, renderEngine);

}

void EditorRenderer::initialize()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    // initializeOpenGLFunctions();
    glViewport(0, 0, width, height);
    setupWidgets();
}

void EditorRenderer::setupWidgets()
{
    this->setCentralWidget(this->window);
}

void EditorRenderer::showEditor()
{
    // Sets up the QMainWindow.
    this->show();
    // Sets up the rest of the widgets locations.
    setupWidgets();
    // Shows the GUIWindow.
    this->window->show();
}

void EditorRenderer::addModel(Model *model)
{
    engine->addModel(model);
}

// Draws OpenGL
// void EditorRenderer::paintGL()
// {
//     // Draw the scene
//     clear(0.1, 0.4, 0.6, 1.0);

//     glEnable(GL_DEPTH_TEST);

    

//     engine.draw();
// }

