//
// Created by Bennet Leff on 5/11/16.
//


#include "GUIWindow.h"

GUIWindow::GUIWindow(int width, int height) :
        Widget(nullptr), glfwWindow(nullptr)
{
    glfwInit();

    if (!glfwInit())
        printf("GLFW could not be initialized. A window could not be created.\n");

    // Necessary window hints to make OSX happy.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    glfwWindow = glfwCreateWindow(width, height, "Window", NULL, NULL);

    if (!glfwWindow)
    {
        glfwTerminate();
        printf("Window could not be created. \n");
    }
    glfwMakeContextCurrent(glfwWindow);
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);

    // If not on OSX we need to include
    // OpenGL as an extension
    #ifndef __APPLE__
        glewExperimental = GL_TRUE;

            GLenum err = glewInit();
            if (GLEW_OK != err)
            {
              /* Problem: glewInit failed, something is seriously wrong. */
              fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
            }
    #endif
}

GUIWindow::~GUIWindow()
{
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}