//
// Created by bennet on 5/17/16.
//

#include "Editor/Editor.h"

Editor::Editor(RenderEngine* renderEngine, int width, int height)
{
	this->width = width;
	this->height = height;
	this->engine = renderEngine;
	this->window = new GUIWindow(0, renderEngine);
    this->layout = new QHBoxLayout();
    this->sideBarLayout = new QVBoxLayout();

    this->sideBar = createSideBar();
    this->inspector = new Inspector();
}

void Editor::initialize()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    // initializeOpenGLFunctions();
    glViewport(0, 0, width, height);
    setupWidgets();
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

std::string Editor::createFileDialogPath(std::string caption, std::string directory, std::string fileTypes)
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr(caption.data()),
                                                    directory.data(),
                                                    tr(fileTypes.data()));
    return fileName.toStdString();
}


void Editor::addModelToScene()
{
    srand (time(NULL));

    auto trans = new Transform();
    trans->getPosition()->x = rand() % 10 + 1;
    trans->getPosition()->y = rand() % 10 + 1;
    trans->getPosition()->z = rand() % 10 + 1;

    /*
     * Need to make the context current so
     * OpenGL calls will work. Otherwise no mesh
     * will be drawn on Linux. It still works on OSX,
     * I'm not quite sure why though.
     */
    auto meshPath = createFileDialogPath("Mesh File", "./res/", "Mesh (*.obj *.fbx *.3ds)");
    if (meshPath != "")
    {
        window->makeCurrent();
        addModel(Model(meshPath, "", trans));
    }
    else
    {
        fprintf(stderr, "Error: Could not create mesh from that path.");
    }
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

SideBarList* Editor::createSideBar()
{
    sideBar = new SideBarList();
    sideBar->setupSideBar();
    return sideBar;
}

void Editor::setupSideBarLayout()
{
    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Raised);
    label->setText("Game Objects");
    label->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    sideBarLayout->addWidget(label);
    sideBarLayout->addWidget(sideBar->getGameObjectList());

    sideBarLayout->setSpacing(0);
}

void Editor::addGameObjectListItem(GameObject gameObject)
{
    sideBar->addSideBarListItem(gameObject);
}

void Editor::setupLayout()
{
    setupSideBarLayout();

    layout->addLayout(sideBarLayout);


    // Adds the GUIWindow to the layout.
    window->setMinimumHeight(400);

    layout->addWidget(window);

    layout->addLayout(inspector->getLayout());

    /*
     * Set a main widget that the other
     * widgets are attached to. The main
     * widget acts as an empty parent for
     * the rest of the editor's widgets.
     */
    mainWidget = new QWidget();
    mainWidget->setLayout(layout);

    // Set QWidget as the central layout of the main window
    setCentralWidget(mainWidget);
}

void Editor::setupWidgets()
{
    this->resize(width, height);

    // Creates Actions and creates the Menu bar.
    createMenus();
    setupLayout();

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
    model.setName("Game Object " + std::to_string(gameObjectCount));
    engine->addModel(model);

    // Add the Model to the gameObjectList
    addGameObjectListItem(model);
    gameObjectCount += 1;

    updateEditor(&model);
}

void Editor::updateEditor(GameObject* gameObject)
{
    inspector->clearLayout();
    inspector->getLayout()->addWidget(new QLabel("Inspector"));
    inspector->getLayout()->addWidget(new QLabel(gameObject->getName().data()));

    // Cast gameObject to Model and get properties.
    auto model = dynamic_cast<Model*>(gameObject);
    if (model != nullptr)
    {
        inspector->insertRow("x: ", std::to_string(model->transform->getPosition()->x));
        inspector->insertRow("y: ", std::to_string(model->transform->getPosition()->y));
        inspector->insertRow("z: ", std::to_string(model->transform->getPosition()->z));
    }
    else
    {
        fprintf(stderr, "Error: Model pointer not passed to update editor. ");
    }

    inspector->getLayout()->setSpacing(10);
}