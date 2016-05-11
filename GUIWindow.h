//
// Created by Bennet Leff on 5/11/16.
//

#pragma once

#define GLFW_INCLUDE_GLCOREARB
#include "GLFW/glfw3.h"
#include <nanogui/widget.h>

class GUIWindow : public nanogui::Widget {
public:
    GUIWindow(int width, int height);
    ~GUIWindow();
private:
    GLFWwindow* glfwWindow;
};

