//
// Created by bennet on 5/17/16.
//

#pragma once

#include <vector>

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

class EditorRenderer : public QMainWindow
{
	Q_OBJECT

public:
    EditorRenderer(RenderEngine* renderEngine, int width, int height);
    ~EditorRenderer() { }

    GUIWindow* getWindow() { return window; }

    // void paintGL();
    void addModel(Model* model);
    // Call instead of QMainWindow.show()
    // so that all widgets are properly shown.
    void showEditor();

    int getSliderValue() { return sliderPos; };

private slots:
    void onValueChanged(int value);
    // Menu bar slots
    void newFile();
    void open();
    void save();

protected:
    // sets up main menu
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private:
    void initialize();
    void setupWidgets();

    // Used to create menu widgets.
    void createActions();
    void createMenus();

    int frame;
    Camera* cam;
    int width;
    int height;
    int sliderPos = 0;

    RenderEngine* engine;
    GUIWindow* window;
    QSlider *slider;

    QMenuBar* menubar;
    QMenu* fileMenu;
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;

    QWidget* mainWidget;
};
