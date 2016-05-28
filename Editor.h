//
// Created by bennet on 5/17/16.
//

#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>

// Include GUIWindow first to include GLEW before GL
#include "Model.h"
#include "GUIWindow.h"
#include "Camera.h"
#include "RenderEngine.h"

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QContextMenuEvent>
#include <QLabel>
#include <QActionGroup>
#include <QFileDialog>
#include <QListWidget>

class Editor : public QMainWindow
{
	Q_OBJECT

public:
    Editor(RenderEngine* renderEngine, int width, int height);
    ~Editor() { }

    // Returns the Window that OpenGL is rendered to.
    GUIWindow* getWindow() { return window; }

    // Wraps RenderEngine::addModel()
    void addModel(Model model);

    // Call instead of QMainWindow.show()
    // so that all widgets are properly shown.
    void showEditor();

private slots:
    // Menu bar slots
    void newFile();
    void open();
    void save();
    void addModelToScene();

protected:
    // sets up main menu
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private:
    void initialize();
    void setupWidgets();
    void setupLayout();
    void setupSiderBarLayout();

    // Used to create menu widgets.
    void createMenus();
    QMenu* createFileMenu();
    QMenu* createComponentsMenu();

    // Sets up the side bar where GameObjects are listed.
    QListWidget* createSideBar();

    // Add GameObject to GameObject side bar viewer.
    void addGameObjectListItem(std::string objectName);

    // Returns path from file dialog
    std::string createFileDialogPath(std::string caption, std::string directory, std::string fileTypes);

    int width;
    int height;

    RenderEngine* engine;
    GUIWindow* window;

    QMenuBar* menubar = new QMenuBar();

    // New file, Open file, Save file commands.
    QMenu* fileMenu;
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;

    // Menu for component commands.
    QMenu* componentsMenu;
    QAction* addModelAct;

    QWidget* mainWidget;

    // The main layout for the Editor.
    QHBoxLayout* layout;

    QVBoxLayout* sideBarLayout;

    // Contains the GameObjects added
    // To the scene.
    QListWidget *gameObjectList;

    // Stores all GameObject list items so they can be edited.
    std::vector<QListWidgetItem*> gameObjectListItems;

    // The count of GameObjects added to the scene.
    int gameObjectCount = 0;
};
