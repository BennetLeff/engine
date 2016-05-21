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
    sliderPos = slider->sliderPosition();
}

// Set up slots.
void EditorRenderer::newFile()
{
    fprintf(stderr, "newFile ");
}

void EditorRenderer::open()
{
    fprintf(stderr, "Opened ");
}

void EditorRenderer::save()
{
    fprintf(stderr, "Saved ");
}

void EditorRenderer::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    // menu.addAction(cutAct);
    // menu.addAction(copyAct);
    // menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}

void EditorRenderer::createActions()
{
    // New File action.
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &EditorRenderer::newFile);

    // Open file action.
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a scene file"));
    connect(openAct, &QAction::triggered, this, &EditorRenderer::open);

    // Save scene action.
    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setStatusTip(tr("Saves the scene"));
    connect(saveAct, &QAction::triggered, this, &EditorRenderer::save);
}

void EditorRenderer::createMenus()
{
    menubar = new QMenuBar;
    fileMenu = menubar->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();

    // Update the QMenuBar of the MainWindow.
    menuBar()->addMenu(fileMenu);

    menuBar()->show();
}

void EditorRenderer::setupWidgets()
{
    this->resize(width, height);

    // Set up buttons and set layout.
    QPushButton *button1 = new QPushButton("One");
    button1->move(50, 50);
    button1->resize(50, 50);

    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(314);
    slider->setSliderPosition(314 / 2);
    slider->setSingleStep(10);
    slider->resize(400, 40);
    slider->move(50, 100);

    QObject::connect(slider, SIGNAL(valueChanged(int)),
                     this, SLOT(onValueChanged(int)));

    // Creates the actions to be performed for
    // their respective GUI elements.
    createActions();
    // Draws the Menu bar.
    createMenus();

    // Set layout
    auto layout = new QGridLayout;
    layout->addWidget(button1);
    layout->addWidget(slider);
    layout->addWidget(window);

    // Set layout in QWidget
    mainWidget = new QWidget();
    mainWidget->setLayout(layout);

    // Set QWidget as the central layout of the main window
    setCentralWidget(mainWidget);

    setMinimumSize(400, 400);
}

void EditorRenderer::showEditor()
{
    // Sets up the rest of the widgets locations.
    setupWidgets();
    // Sets up the QMainWindow.
    this->show();
}

void EditorRenderer::addModel(Model *model)
{
    engine->addModel(model);
}


