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
#include <QGridLayout>
#include <QSlider>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QContextMenuEvent>
#include <QLabel>
#include <QActionGroup>

class Editor : public QMainWindow
{
	Q_OBJECT

public:
    Editor(RenderEngine* renderEngine, int width, int height);
    ~Editor() { }

    GUIWindow* getWindow() { return window; }

    // Wraps RenderEngine::addModel()
    void addModel(Model model);
    // Call instead of QMainWindow.show()
    // so that all widgets are properly shown.
    void showEditor();

    // Some dummy functions for testing sliders.
    int getSliderValue() { return sliderPos; };
    int getManValue() { return sliderPosForMan; }

private slots:
    void onSliderValueChanged(int value);
    void onSliderManValueChanged(int value);

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

    // Used to create menu widgets.
    void createActions();
    void createMenus();
    QMenu* createFileMenu();
    QMenu* createComponentsMenu();

    int frame;
    Camera* cam;
    int width;
    int height;
    int sliderPos = 0;
    int sliderPosForMan = 0;

    RenderEngine* engine;
    GUIWindow* window;
    QSlider *slider;
    QSlider *slidermanPos;

    QMenuBar* menubar = new QMenuBar();
    // New file, Open file, Save file commands.
    QMenu* fileMenu;
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;

    // Add GameObject.
    QMenu* componentsMenu;
    QAction* addModelAct;

    QWidget* mainWidget;
};
