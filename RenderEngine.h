/*
	This class should handle all components
	to be drawn. It should manage them and draw them.
	It should be embedable in any OpenGL context, such
	as a window or Qt context.
*/

#include "Model.h"
#include "Camera.h"
#include <GL/glew.h>

class RenderEngine
{
public:
    RenderEngine();
    void draw(Camera* cam);
    void addModel(Model* model);
private:
    void init();
    std::vector<Model*> models;
};