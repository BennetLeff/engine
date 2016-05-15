//
// Created by bennet on 5/15/16.
//

#include "Model.h"
#include "ModelWindow.h"

ModelWindow::ModelWindow()
    : m_frame(0)
{

}

void ModelWindow::initialize()
{
    glewExperimental = GL_TRUE;
    glewInit();
}

void ModelWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    Model m = Model("/home/bennet/Desktop/engine/res/Alfred/Alfred.obj", "/home/bennet/Desktop/engine/res/Alfred/alfred_dif.png");

    m.draw(new Camera(glm::vec3(0, 6, -15), 70.0f, (float) 640 / (float) 400, 0.01f, 1000.0f));

    ++m_frame;
}
