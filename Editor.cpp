//
// Created by bennet on 5/17/16.
//

#include "Editor.h"

Editor::Editor(RenderEngine* renderEngine, int width, int height)
{
	frame = 0;
	this->width = width;
	this->height = height;
	this->engine = renderEngine;
	this->window = new GUIWindow(0, renderEngine);
}

void Editor::initialize()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    // initializeOpenGLFunctions();
    glViewport(0, 0, width, height);
    setupWidgets();
}

void Editor::onSliderValueChanged(int value)
{
    sliderPos = slider->sliderPosition();
}

void Editor::onSliderManValueChanged(int value)
{
    sliderPosForMan = slidermanPos->sliderPosition();
}

// Set up slots.
void Editor::newFile()
{
    fprintf(stderr, "newFile \n");
}

void Editor::open()
{
    fprintf(stderr, "Opened \n");
}

void Editor::save()
{
    fprintf(stderr, "Saved \n");
}

float Editor::getRandNum()
{
    srand(time(0));
    float num = rand() % 10 + 1;
    fprintf(stderr, "%d \n", num);
    return num;
}

void Editor::addModelToScene()
{
//    Model* modelToAdd = new Model("./res/Alfred/Alfred.obj", "./res/Alfred/alfred_dif.png");
    srand (time(NULL));
//    modelToAdd->transform->getPosition()->z = 0;
//    modelToAdd->transform->getPosition()->x = getRandNum();

    auto trans = new Transform();
    trans->getPosition()->x = rand() % 10 + 1;
    trans->getPosition()->y = rand() % 10 + 1;
    trans->getPosition()->z = rand() % 10 + 1;
    engine->addModel(Model("./res/Alfred/Alfred.obj", "./res/Alfred/alfred_dif.png", trans));
    fprintf(stderr, "Add a Model \n");
}

void Editor::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    menu.exec(event->globalPos());
}

QMenu* Editor::createFileMenu()
{
    // New File action.
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &Editor::newFile);

    // Open file action.
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a scene file"));
    connect(openAct, &QAction::triggered, this, &Editor::open);

    // Save scene action.
    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setStatusTip(tr("Saves the scene"));
    connect(saveAct, &QAction::triggered, this, &Editor::save);

    fileMenu = menubar->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();

    return fileMenu;
}

QMenu* Editor::createComponentsMenu()
{
    addModelAct = new QAction(tr("&Add Model"), this);
    addModelAct->setStatusTip(tr("Add a Model to the scene"));
    connect(addModelAct, &QAction::triggered, this, &Editor::addModelToScene);

    componentsMenu = menubar->addMenu(tr("&Components"));
    componentsMenu->addAction(addModelAct);
    componentsMenu->addSeparator();

    return componentsMenu;
}

void Editor::createMenus()
{
    // Update the QMenuBar of the MainWindow.
    menuBar()->addMenu(createFileMenu());
    menuBar()->addMenu(createComponentsMenu());

    menuBar()->show();
}

void Editor::setupWidgets()
{
    this->resize(width, height);

    // Set up buttons and set layout.
    slidermanPos = new QSlider(Qt::Horizontal);
    slidermanPos->setMinimum(0);
    slidermanPos->setMaximum(20);
    slidermanPos->setSliderPosition(10);

    QObject::connect(slidermanPos, SIGNAL(valueChanged(int)),
                     this, SLOT(onSliderManValueChanged(int)));

    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(314);
    slider->setSliderPosition(314 / 2);
    slider->setSingleStep(10);
    slider->resize(400, 40);
    slider->move(50, 100);

    QObject::connect(slider, SIGNAL(valueChanged(int)),
                     this, SLOT(onSliderValueChanged(int)));

    // Creates Actions and creates the Menu bar.
    createMenus();

    // Set layout
    auto layout = new QGridLayout;
    layout->addWidget(slidermanPos);
    layout->addWidget(slider);
    layout->addWidget(window);

    // Set layout in QWidget
    mainWidget = new QWidget();
    mainWidget->setLayout(layout);

    // Set QWidget as the central layout of the main window
    setCentralWidget(mainWidget);

    setMinimumSize(400, 400);
}

void Editor::showEditor()
{
    // Sets up the rest of the widgets locations.
    setupWidgets();
    // Sets up the QMainWindow.
    this->show();
}

void Editor::addModel(Model model)
{
    engine->addModel(model);
}


