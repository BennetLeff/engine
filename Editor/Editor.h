//
// Created by bennet on 5/17/16.
//

#pragma once

#include <vector>

// Include GUIWindow first to include GLEW before GL
#include "Core/Model.h"
#include "Editor/GUIWindow.h"
#include "Core/Camera.h"
#include "Core/RenderEngine.h"
#include "Core/GameObject.h"
#include "Editor/SideBarList.h"

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

protected:
    // sets up main menu
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private slots:
    // Menu bar slots
    void newFile();
    void open();
    void save();
    void addModelToScene();

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
    SideBarList* createSideBar();

    // Add GameObject to GameObject side bar viewer.
    void addGameObjectListItem(GameObject gameObject);

    // Create an inspector for a GameObject based on QTableWidget.
    QVBoxLayout* createInspector(GameObject gameObject);

    // Returns path from file dialog
    std::string createFileDialogPath(std::string caption, std::string directory, std::string fileTypes);

    // Window width and height.
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

    // Action for adding model
    QAction* addModelAct;

    // Menu for component commands.
    QMenu* componentsMenu;

    QWidget* mainWidget;

    // The layouts for the Editor.
    QHBoxLayout* layout;
    QVBoxLayout* sideBarLayout;
    QVBoxLayout* inspectorLayout;

    // The count of GameObjects added to the scene.
    int gameObjectCount = 0;

    SideBarList* sideBar;
};
