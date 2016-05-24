#pragma once

#include "RenderEngine.h"

#include <QMainWindow>
#include <QWindow>
#include <QOpenGLPaintDevice>
#include <QCoreApplication>
#include <QPainter>
#include <QOpenGLWidget>

class GUIWindow : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GUIWindow(QWidget *parent = 0, RenderEngine* engine = nullptr);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void clear(float r, float g, float b, float a);

    ~GUIWindow();

private:
    int frame;
    Camera* cam;
    std::vector<Model*> models;
    Model* mod;
    int width;
    int height;

    RenderEngine* engine;
};
