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

class EditorRenderer : public GUIWindow
{
public:
    EditorRenderer(RenderEngine renderEngine, int width, int height);
    ~EditorRenderer() { }

    void paintGL();
    void addModel(Model* model);
private:
    void initialize();

    int frame;
    Camera* cam;
    std::vector<Model*> models;
    Model* mod;
    int width;
    int height;

    RenderEngine engine;
};
