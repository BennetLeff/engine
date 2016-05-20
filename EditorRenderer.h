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
#include <QHBoxLayout>
#include <QSlider>

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

private slots:
    void onValueChanged(int value);

private:
    void initialize();
    void setupWidgets();

    int frame;
    Camera* cam;
    int width;
    int height;

    RenderEngine* engine;
    GUIWindow* window;
    QSlider *slider;
};
