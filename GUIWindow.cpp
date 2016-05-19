//
// Created by bennet on 5/14/16.
//

#include <GL/glew.h>
#include "GUIWindow.h"

GUIWindow::GUIWindow(QWidget *parent) :
    QOpenGLWidget(parent) { }

void GUIWindow::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.:
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
    // Draw the scene
    clear(1.0, 1.0, 1.0, 1.0);
}

void GUIWindow::clear(float r, float g, float b, float a)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(r, g, b, a);
}

GUIWindow::~GUIWindow() { }
