/*
	This class should handle all components
	to be drawn. It should manage them and draw them.
	It should be embedable in any OpenGL context, such
	as a window or Qt context.
*/

#pragma once

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

#include "Model.h"
#include "Camera.h"

class RenderEngine
{
public:
    RenderEngine(Camera* cam);
    void draw();
    void addModel(Model model);
    Camera* getCamera() { return cam; }
    void init();
private:
    std::vector<Model> models;
    Camera* cam;
};