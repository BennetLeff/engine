//
// Created by bennet on 5/17/16.
//

#pragma once

// Include GUIWindow first to include GLEW before GL
#include "Model.h"
#include "GUIWindow.h"

#include <vector>

#include <QtGui/QGuiApplication>

#include "Camera.h"

class EditorRenderer : public GUIWindow
{
public:
    EditorRenderer(Camera* cam);
    ~EditorRenderer() { }
    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;
private:
    int frame;
    Camera* cam;
    std::vector<Model*> models;
    Model* mod;
};
