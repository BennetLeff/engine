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
#include <QVBoxLayout>
#include <QSlider>

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

private:
    void initialize();
    void setupWidgets();

    int frame;
    Camera* cam;
    int width;
    int height;
    int sliderPos = 0;

    RenderEngine* engine;
    GUIWindow* window;
    QSlider *slider;
};
