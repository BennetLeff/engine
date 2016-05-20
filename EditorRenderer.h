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

class EditorRenderer : public QMainWindow
{
public:
    EditorRenderer(RenderEngine* renderEngine, int width, int height);
    ~EditorRenderer() { }

    GUIWindow* getWindow() { return window; }

    // void paintGL();
    void addModel(Model* model);
    // Call instead of QMainWindow.show()
    // so that all widgets are properly shown.
    void showEditor();
private:
    void initialize();
    void setupWidgets();

    int frame;
    Camera* cam;
    std::vector<Model*> models;
    Model* mod;
    int width;
    int height;

    RenderEngine* engine;
    GUIWindow* window;
};
