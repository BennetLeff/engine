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


void EditorRenderer::onValueChanged(int value)
{
    int pos = slider->sliderPosition();
    fprintf(stderr, "slider pos: %d", pos);
}

void EditorRenderer::setupWidgets()
{
    this->resize(width, height);
    // Set GUIWindow to be Central Widget
    this->setCentralWidget(window);

    // Set up buttons and set layout.
    QPushButton *button1 = new QPushButton("One");
    button1->move(50, 50);
    button1->resize(50, 50);
    this->layout()->addWidget(button1);

    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->setSliderPosition(50);
    slider->setSingleStep(1);
    slider->resize(400, 40);
    slider->move(50, 100);

    QObject::connect(slider, SIGNAL(valueChanged(int)),
                     this, SLOT(onValueChanged(int)));

    this->layout()->addWidget(slider);
}

void EditorRenderer::showEditor()
{
    // Sets up the QMainWindow.
    this->show();
    // Sets up the rest of the widgets locations.
    setupWidgets();
    // Shows the GUIWindow.
    window->show();
}

void EditorRenderer::addModel(Model *model)
{
    engine->addModel(model);
}


