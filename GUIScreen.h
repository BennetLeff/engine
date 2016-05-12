//
// Created by bennet on 5/11/16.
//

#pragma once

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#define GLFW_INCLUDE_GLCOREARB
#include "GLFW/glfw3.h"
#include <nanogui/widget.h>

using namespace nanogui;
using namespace std;
using namespace Eigen;

class GUIScreen : public Widget {
    friend class Widget;
    friend class nanogui::Window;
public:
    /**
     * Create a new GUIScreen instance
     *
     * \param size
     *    Size in pixels at 96 dpi (on high-DPI screens, the actual resolution
     *    in terms of hardware pixels may be larger by an integer factor)
     *
     * \param caption
     *    Window title (in UTF-8 encoding)
     *
     * \param resizable
     *    If creating a window, should it be resizable?
     *
     * \param fullscreen
     *    Specifies whether to create a windowed or full-screen view
     *
     * \param colorBits
     *    Number of bits per pixel dedicated to the R/G/B color components
     *
     * \param alphaBits
     *    Number of bits per pixel dedicated to the alpha channel
     *
     * \param depthBits
     *    Number of bits per pixel dedicated to the Z-buffer
     *
     * \param stencilBits
     *    Number of bits per pixel dedicated to the stencil buffer (recommended
     *    to set this to 8. NanoVG can draw higher-quality strokes using a
     *    stencil buffer)
     *
     * \param nSamples
     *    Number of MSAA samples (set to 0 to disable)
     */
    GUIScreen(const Vector2i &size, const std::string &caption,
           bool resizable = true, bool fullscreen = false, int colorBits = 8,
           int alphaBits = 8, int depthBits = 24, int stencilBits = 8,
           int nSamples = 0);

    /// Release all resources
    virtual ~GUIScreen();

    /// Get the window title bar caption
    const std::string &caption() const { return mCaption; }

    /// Set the window title bar caption
    void setCaption(const std::string &caption);

    /// Return the screen's background color
    const Vector3f &background() const { return mBackground; }

    /// Set the screen's background color
    void setBackground(const Vector3f &background) { mBackground = background; }

    /// Set the top-level window visibility (no effect on full-screen windows)
    void setVisible(bool visible);

    /// Set window size
    void setSize(const Vector2i& size);

    /// Draw the GUIScreen contents
    virtual void drawAll();

    /// Draw the window contents -- put your OpenGL draw calls here
    virtual void drawContents() { /* To be overridden */ }

    /// Handle a file drop event
    virtual bool dropEvent(const std::vector<std::string> & /* filenames */) { return false; /* To be overridden */ }

    /// Default keyboard event handler
    virtual bool keyboardEvent(int key, int scancode, int action, int modifiers);

    /// Text input event handler: codepoint is native endian UTF-32 format
    virtual bool keyboardCharacterEvent(unsigned int codepoint);

    /// Window resize event handler
    virtual bool resizeEvent(const Vector2i &) { return false; }

    /// Return the last observed mouse position value
    Vector2i mousePos() const { return mMousePos; }

    /// Return a pointer to the underlying GLFW window data structure
    GLFWwindow *glfwWindow() { return mGLFWWindow; }

    /// Return a pointer to the underlying nanoVG draw context
    NVGcontext *nvgContext() { return mNVGContext; }

    void setShutdownGLFWOnDestruct(bool v) { mShutdownGLFWOnDestruct = v; }
    bool shutdownGLFWOnDestruct() { return mShutdownGLFWOnDestruct; }

    using Widget::performLayout;

    /// Compute the layout of all widgets
    void performLayout() {
        Widget::performLayout(mNVGContext);
    }

public:
    /********* API for applications which manage GLFW themselves *********/

    /**
     * \brief Default constructor
     *
     * Performs no initialization at all. Use this if the application is
     * responsible for setting up GLFW, OpenGL, etc.
     *
     * In this case, override \ref GUIScreen and call \ref initalize() with a
     * pointer to an existing \c GLFWwindow instance
     *
     * You will also be responsible in this case to deliver GLFW callbacks
     * to the appropriate callback event handlers below
     */
    GUIScreen();

    /// Initialize the \ref GUIScreen
    void initialize(GLFWwindow *window, bool shutdownGLFWOnDestruct);

    /* Event handlers */
    bool cursorPosCallbackEvent(double x, double y);
    bool mouseButtonCallbackEvent(int button, int action, int modifiers);
    bool keyCallbackEvent(int key, int scancode, int action, int mods);
    bool charCallbackEvent(unsigned int codepoint);
    bool dropCallbackEvent(int count, const char **filenames);
    bool scrollCallbackEvent(double x, double y);
    bool resizeCallbackEvent(int width, int height);

    /* Internal helper functions */
    void updateFocus(nanogui::Widget *widget);
    void disposeWindow(nanogui::Window *window);
    void centerWindow(nanogui::Window *window);
    void moveWindowToFront(nanogui::Window *window);
    void drawWidgets();

    GLFWwindow* getWindow();
    void clear(float r, float g, float b, float a);
    bool close();
protected:
    GLFWwindow *mGLFWWindow;
    NVGcontext *mNVGContext;
    GLFWcursor *mCursors[(int) Cursor::CursorCount];
    Cursor mCursor;
    std::vector<Widget *> mFocusPath;
    Vector2i mFBSize;
    float mPixelRatio;
    int mMouseState, mModifiers;
    Vector2i mMousePos;
    bool mDragActive;
    Widget *mDragWidget = nullptr;
    double mLastInteraction;
    bool mProcessEvents;
    Vector3f mBackground;
    std::string mCaption;
    bool mShutdownGLFWOnDestruct;
    bool mFullscreen;
};