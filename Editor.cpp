//
// Created by bennet on 5/17/16.
//

#include "Editor.h"

Editor::Editor(RenderEngine* renderEngine, int width, int height)
{
	this->width = width;
	this->height = height;
	this->engine = renderEngine;
	this->window = new GUIWindow(0, renderEngine);
    this->layout = new QHBoxLayout();
    this->sideBarLayout = new QVBoxLayout();
    this->gameObjectList = createSideBar();
    // this->inspector = new QTableWidget(this);
    this->inspectorLayout = new QVBoxLayout();
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

QListWidget* Editor::createSideBar()
{
    auto list = new QListWidget(this);
    list->setMaximumWidth(150);

    return list;
}

void Editor::setupSiderBarLayout()
{
    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Raised);
    label->setText("Game Objects");
    label->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    sideBarLayout->addWidget(label);
    sideBarLayout->addWidget(gameObjectList);

    sideBarLayout->setSpacing(0);
}

void Editor::addGameObjectListItem(GameObject gameObject)
{
    auto item = new QListWidgetItem(tr(gameObject.getName().data()), gameObjectList);
    gameObjectListItems.push_back(item);
}

QVBoxLayout* Editor::createInspector(GameObject gameObject)
{
    // Set up the main inspector label
    auto inspectorLabel = new QLabel(this);
    inspectorLabel->setText("Inspector");
    inspectorLabel->setAlignment(Qt::AlignLeft);

    // Set up the name label to signify a GameObject's name.
    auto name = new QLabel(this);
    name->setAlignment(Qt::AlignCenter);

    // If the GameObject is set up.
    if (gameObject.getName() != "")
    {
        name->setText(gameObject.getName().data());

        // Set up the QTable with contains the GameObject data.
        auto inspector = new QTableWidget(3, 2, this);
        auto gameObjectPosition = new QTableWidgetItem("Position");
        inspector->setItem(1, 1, gameObjectPosition);

        inspector->setMaximumWidth(150);

        inspectorLayout = new QVBoxLayout();

        inspectorLayout->addWidget(inspectorLabel);
        inspectorLayout->addWidget(name);
        inspectorLayout->addWidget(inspector);
    }
    else
    {
        name->setText("Place Holder Name!");

        // Set up the QTable with contains the GameObject data.
        auto inspector = new QTableWidget(this);

        inspector->setMaximumWidth(300);

        inspectorLayout = new QVBoxLayout();

        inspectorLayout->addWidget(inspectorLabel);
        inspectorLayout->addWidget(name);
        inspectorLayout->addWidget(inspector);
    }

    inspectorLayout->setSpacing(0);

    return inspectorLayout;
}

void Editor::setupLayout()
{
    setupSiderBarLayout();

    layout->addLayout(sideBarLayout);

    // Adds the GUIWindow to the layout.
    layout->addWidget(window);

    layout->addLayout(createInspector(GameObject()));

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
}
