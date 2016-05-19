#pragma once

#include <QMainWindow>
#include <QOpenGLFunctions>
#include <QWindow>
#include <QOpenGLPaintDevice>
#include <QCoreApplication>
#include <QPainter>
#include <QOpenGLWidget>

class GUIWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GUIWindow(QWidget *parent = 0);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void clear(float r, float g, float b, float a);

    ~GUIWindow();
};
