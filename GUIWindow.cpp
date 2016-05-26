//
// Created by bennet on 5/14/16.
//

#include <GL/glew.h>
#include "GUIWindow.h"

GUIWindow::GUIWindow(QWidget* parent, RenderEngine* engine) :
    QOpenGLWidget(parent), engine(engine) { }

void GUIWindow::initializeGL()
{
    initializeOpenGLFunctions();

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
}

void GUIWindow::resizeGL(int w, int h) {  }

void GUIWindow::paintGL()
{
    this->makeCurrent();

    // Draw the scene
    clear(0.1, 0.4, 0.6, 1.0);

    // Depth test not enabled by default.
    glEnable(GL_DEPTH_TEST);
    
    // Draw all Models
    engine->draw();
}

void GUIWindow::clear(float r, float g, float b, float a)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(r, g, b, a);
}

GUIWindow::~GUIWindow() { }
