//
// Created by bennet on 5/15/16.
//

#pragma once

#include "GUIWindow.h"
#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>

class ModelWindow : public GUIWindow {
public:
    ModelWindow();
    ~ModelWindow() {};
    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;
private:
    int m_frame;
};