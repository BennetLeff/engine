//
// Created by bennet on 5/11/16.
//

#include "GUIScreen.h"

#include <nanogui/theme.h>
#include <nanogui/opengl.h>
#include <nanogui/window.h>
#include <nanogui/popup.h>
#include <iostream>
#include <map>

#include "Window.h"

#ifndef NANOVG_GL_H
    #define NANOVG_GL3_IMPLEMENTATION
    #include <nanovg_gl.h>
#endif

std::map<GLFWwindow *, GUIScreen *> __nanogui_screens;


using namespace nanogui;
using namespace std;
using namespace Eigen;

/* Calculate pixel ratio for hi-dpi devices. */
static float get_pixel_ratio(GLFWwindow *window) {
    Vector2i fbSize, size;
    glfwGetFramebufferSize(window, &fbSize[0], &fbSize[1]);
    glfwGetWindowSize(window, &size[0], &size[1]);
    return (float)fbSize[0] / (float)size[0];
}
GUIScreen::GUIScreen()
        : Widget(nullptr), mGLFWWindow(nullptr), mNVGContext(nullptr),
          mCursor(Cursor::Arrow), mBackground(0.3f, 0.3f, 0.32f),
          mShutdownGLFWOnDestruct(false), mFullscreen(false) {
    memset(mCursors, 0, sizeof(GLFWcursor *) * (int) Cursor::CursorCount);
}

GUIScreen::GUIScreen(const Vector2i &size, const std::string &caption, bool resizable,
               bool fullscreen, int colorBits, int alphaBits, int depthBits,
               int stencilBits, int nSamples)
        : Widget(nullptr), mNVGContext(nullptr),
          mCursor(Cursor::Arrow), mBackground(0.3f, 0.3f, 0.32f), mCaption(caption),
          mShutdownGLFWOnDestruct(false), mFullscreen(fullscreen) {
    memset(mCursors, 0, sizeof(GLFWcursor *) * (int) Cursor::CursorCount);

    if (!glfwInit())
        printf("GLFW could not be initialized. A window could not be created.\n");

    // Necessary window hints to make OSX happy.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // auto win = new Engine::Window(640, 800);

//    if (!win->getWindow())
//        throw std::runtime_error("Could not create an OpenGL 3.3 context!");

    // mGLFWWindow = win->getWindow();

    mGLFWWindow = glfwCreateWindow(640, 480, "title", NULL, NULL);

    glfwMakeContextCurrent(mGLFWWindow);

    glfwGetFramebufferSize(mGLFWWindow, &mFBSize[0], &mFBSize[1]);

    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);

    // If not on OSX we need to include
    // OpenGL as an extension
    #ifndef __APPLE__
        glewExperimental = GL_TRUE;

        GLenum err = glewInit();
        if (GLEW_OK != err) {
            /* Problem: glewInit failed, something is seriously wrong. */
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        }
    #endif

    /* Propagate GLFW events to the appropriate GUIScreen instance */
    glfwSetCursorPosCallback(mGLFWWindow,
                             [](GLFWwindow *w, double x, double y) {
                                 auto it = __nanogui_screens.find(w);
                                 if (it == __nanogui_screens.end())
                                     return;
                                 GUIScreen *s = it->second;
                                 if (!s->mProcessEvents)
                                     return;
                                 s->cursorPosCallbackEvent(x, y);
                             }
    );

    glfwSetMouseButtonCallback(mGLFWWindow,
                               [](GLFWwindow *w, int button, int action, int modifiers) {
                                   auto it = __nanogui_screens.find(w);
                                   if (it == __nanogui_screens.end())
                                       return;
                                   GUIScreen *s = it->second;
                                   if (!s->mProcessEvents)
                                       return;
                                   s->mouseButtonCallbackEvent(button, action, modifiers);
                               }
    );

    glfwSetKeyCallback(mGLFWWindow,
                       [](GLFWwindow *w, int key, int scancode, int action, int mods) {
                           auto it = __nanogui_screens.find(w);
                           if (it == __nanogui_screens.end())
                               return;
                           GUIScreen *s = it->second;
                           if (!s->mProcessEvents)
                               return;
                           s->keyCallbackEvent(key, scancode, action, mods);
                       }
    );

    glfwSetCharCallback(mGLFWWindow,
                        [](GLFWwindow *w, unsigned int codepoint) {
                            auto it = __nanogui_screens.find(w);
                            if (it == __nanogui_screens.end())
                                return;
                            GUIScreen *s = it->second;
                            if (!s->mProcessEvents)
                                return;
                            s->charCallbackEvent(codepoint);
                        }
    );

    glfwSetDropCallback(mGLFWWindow,
                        [](GLFWwindow *w, int count, const char **filenames) {
                            auto it = __nanogui_screens.find(w);
                            if (it == __nanogui_screens.end())
                                return;
                            GUIScreen *s = it->second;
                            if (!s->mProcessEvents)
                                return;
                            s->dropCallbackEvent(count, filenames);
                        }
    );

    glfwSetScrollCallback(mGLFWWindow,
                          [](GLFWwindow *w, double x, double y) {
                              auto it = __nanogui_screens.find(w);
                              if (it == __nanogui_screens.end())
                                  return;
                              GUIScreen *s = it->second;
                              if (!s->mProcessEvents)
                                  return;
                              s->scrollCallbackEvent(x, y);
                          }
    );

    /* React to framebuffer size events -- includes window
       size events and also catches things like dragging
       a window from a Retina-capable GUIScreen to a normal
       GUIScreen on Mac OS X */
    glfwSetFramebufferSizeCallback(mGLFWWindow,
                                   [](GLFWwindow* w, int width, int height) {
                                       auto it = __nanogui_screens.find(w);
                                       if (it == __nanogui_screens.end())
                                           return;
                                       GUIScreen* s = it->second;

                                       if (!s->mProcessEvents)
                                           return;

                                       s->resizeCallbackEvent(width, height);
                                   }
    );

    initialize(mGLFWWindow, true);
}

void GUIScreen::initialize(GLFWwindow *window, bool shutdownGLFWOnDestruct) {
    if (!window)
        fprintf(stderr, "window is null \n");
    else
        fprintf(stderr, "window not null \n");

    mGLFWWindow = window;

    if (!mGLFWWindow)
        fprintf(stderr, "glfw window is null \n");
    else
        fprintf(stderr, "glfw window not null \n");

    mShutdownGLFWOnDestruct = shutdownGLFWOnDestruct;
    glfwGetWindowSize(mGLFWWindow, &mSize[0], &mSize[1]);
    glfwGetFramebufferSize(mGLFWWindow, &mFBSize[0], &mFBSize[1]);

    mPixelRatio = get_pixel_ratio(window);
    
    /* Detect framebuffer properties and set up compatible NanoVG context */
    GLint nStencilBits = 0, nSamples = 0;
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER,
                                          GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &nStencilBits);
    glGetIntegerv(GL_SAMPLES, &nSamples);

    int flags = 0;
    if (nStencilBits >= 8)
        flags |= NVG_STENCIL_STROKES;
    if (nSamples <= 1)
        flags |= NVG_ANTIALIAS;

    mNVGContext = nvgCreateGL3(flags);
    if (mNVGContext == nullptr)
        throw std::runtime_error("Could not initialize NanoVG!");

    mVisible = glfwGetWindowAttrib(window, GLFW_VISIBLE) != 0;
    setTheme(new Theme(mNVGContext));
    mMousePos = Vector2i::Zero();
    mMouseState = mModifiers = 0;
    mDragActive = false;
    mLastInteraction = glfwGetTime();

    mProcessEvents = true;
    __nanogui_screens[mGLFWWindow] = this;

    for (int i=0; i < (int) Cursor::CursorCount; ++i)
        mCursors[i] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR + i);
}

GUIScreen::~GUIScreen() {
    __nanogui_screens.erase(mGLFWWindow);
    for (int i=0; i < (int) Cursor::CursorCount; ++i) {
        if (mCursors[i])
            glfwDestroyCursor(mCursors[i]);
    }
    if (mNVGContext)
        nvgDeleteGL3(mNVGContext);
    if (mGLFWWindow && mShutdownGLFWOnDestruct)
        glfwDestroyWindow(mGLFWWindow);
}

void GUIScreen::setVisible(bool visible) {
    if (mVisible != visible) {
        mVisible = visible;

        if (visible)
            glfwShowWindow(mGLFWWindow);
        else
            glfwHideWindow(mGLFWWindow);
    }
}

void GUIScreen::setCaption(const std::string &caption) {
    if (caption != mCaption) {
        glfwSetWindowTitle(mGLFWWindow, caption.c_str());
        mCaption = caption;
    }
}

void GUIScreen::setSize(const Vector2i &size) {
    Widget::setSize(size);
    glfwSetWindowSize(mGLFWWindow, size.x(), size.y());
}

void GUIScreen::drawAll() {
    drawContents();
    drawWidgets();
}

void GUIScreen::drawWidgets() {
    if (!mVisible)
        return;

    glfwMakeContextCurrent(mGLFWWindow);
    float newPixelRatio = get_pixel_ratio(mGLFWWindow);


    mPixelRatio = newPixelRatio;
    glfwGetFramebufferSize(mGLFWWindow, &mFBSize[0], &mFBSize[1]);
    glfwGetWindowSize(mGLFWWindow, &mSize[0], &mSize[1]);

//    glViewport(0, 0, mFBSize[0], mFBSize[1]);

    /* Calculate pixel ratio for hi-dpi devices. */
    mPixelRatio = (float) mFBSize[0] / (float) mSize[0];
    nvgBeginFrame(mNVGContext, mSize[0], mSize[1], mPixelRatio);

    draw(mNVGContext);

    nvgEndFrame(mNVGContext);
}

bool GUIScreen::keyboardEvent(int key, int scancode, int action, int modifiers) {
    if (mFocusPath.size() > 0) {
        for (auto it = mFocusPath.rbegin() + 1; it != mFocusPath.rend(); ++it)
            if ((*it)->focused() && (*it)->keyboardEvent(key, scancode, action, modifiers))
                return true;
    }

    return false;
}

bool GUIScreen::keyboardCharacterEvent(unsigned int codepoint) {
    if (mFocusPath.size() > 0) {
        for (auto it = mFocusPath.rbegin() + 1; it != mFocusPath.rend(); ++it)
            if ((*it)->focused() && (*it)->keyboardCharacterEvent(codepoint))
                return true;
    }
    return false;
}

bool GUIScreen::cursorPosCallbackEvent(double x, double y) {
    Vector2i p((int) x, (int) y);
#if defined(_WIN32)
    p /= mPixelRatio;
#endif
    bool ret = false;
    mLastInteraction = glfwGetTime();
    try {
        p -= Vector2i(1, 2);

        if (!mDragActive) {
            Widget *widget = findWidget(p);
            if (widget != nullptr && widget->cursor() != mCursor) {
                mCursor = widget->cursor();
                glfwSetCursor(mGLFWWindow, mCursors[(int) mCursor]);
            }
        } else {
            ret = mDragWidget->mouseDragEvent(
                    p - mDragWidget->parent()->absolutePosition(), p - mMousePos,
                    mMouseState, mModifiers);
        }

        if (!ret)
            ret = mouseMotionEvent(p, p - mMousePos, mMouseState, mModifiers);

        mMousePos = p;

        return ret;
    } catch (const std::exception &e) {
        std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
        abort();
    }
}

bool GUIScreen::mouseButtonCallbackEvent(int button, int action, int modifiers) {
    mModifiers = modifiers;
    mLastInteraction = glfwGetTime();
    try {
        if (mFocusPath.size() > 1) {
            const Window *window =
                    dynamic_cast<Window *>(mFocusPath[mFocusPath.size() - 2]);
            if (window && window->modal()) {
                if (!window->contains(mMousePos))
                    return false;
            }
        }

        if (action == GLFW_PRESS)
            mMouseState |= 1 << button;
        else
            mMouseState &= ~(1 << button);

        auto dropWidget = findWidget(mMousePos);
        if (mDragActive && action == GLFW_RELEASE &&
            dropWidget != mDragWidget)
            mDragWidget->mouseButtonEvent(
                    mMousePos - mDragWidget->parent()->absolutePosition(), button,
                    false, mModifiers);

        if (dropWidget != nullptr && dropWidget->cursor() != mCursor) {
            mCursor = dropWidget->cursor();
            glfwSetCursor(mGLFWWindow, mCursors[(int) mCursor]);
        }

        if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_1) {
            mDragWidget = findWidget(mMousePos);
            if (mDragWidget == this)
                mDragWidget = nullptr;
            mDragActive = mDragWidget != nullptr;
            if (!mDragActive)
                updateFocus(nullptr);
        } else {
            mDragActive = false;
            mDragWidget = nullptr;
        }

        return mouseButtonEvent(mMousePos, button, action == GLFW_PRESS,
                                mModifiers);
    } catch (const std::exception &e) {
        std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
        abort();
    }
}

bool GUIScreen::keyCallbackEvent(int key, int scancode, int action, int mods) {
    mLastInteraction = glfwGetTime();
    try {
        return keyboardEvent(key, scancode, action, mods);
    } catch (const std::exception &e) {
        std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
        abort();
    }
}

bool GUIScreen::charCallbackEvent(unsigned int codepoint) {
    mLastInteraction = glfwGetTime();
    try {
        return keyboardCharacterEvent(codepoint);
    } catch (const std::exception &e) {
        std::cerr << "Caught exception in event handler: " << e.what()
        << std::endl;
        abort();
    }
}

bool GUIScreen::dropCallbackEvent(int count, const char **filenames) {
    std::vector<std::string> arg(count);
    for (int i = 0; i < count; ++i)
        arg[i] = filenames[i];
    return dropEvent(arg);
}

bool GUIScreen::scrollCallbackEvent(double x, double y) {
    mLastInteraction = glfwGetTime();
    try {
        if (mFocusPath.size() > 1) {
            const Window *window =
                    dynamic_cast<Window *>(mFocusPath[mFocusPath.size() - 2]);
            if (window && window->modal()) {
                if (!window->contains(mMousePos))
                    return false;
            }
        }
        return scrollEvent(mMousePos, Vector2f(x, y));
    } catch (const std::exception &e) {
        std::cerr << "Caught exception in event handler: " << e.what()
        << std::endl;
        abort();
    }
}

bool GUIScreen::resizeCallbackEvent(int, int) {
    Vector2i fbSize, size;
    glfwGetFramebufferSize(mGLFWWindow, &fbSize[0], &fbSize[1]);
    glfwGetWindowSize(mGLFWWindow, &size[0], &size[1]);
#if defined(_WIN32)
    size /= mPixelRatio;
#endif

    if (mFBSize == Vector2i(0, 0) || size == Vector2i(0, 0))
        return false;

    mFBSize = fbSize; mSize = size;
    mLastInteraction = glfwGetTime();

    try {
        return resizeEvent(mSize);
    } catch (const std::exception &e) {
        std::cerr << "Caught exception in event handler: " << e.what()
        << std::endl;
        abort();
    }
}

void GUIScreen::updateFocus(Widget *widget) {
    for (auto w: mFocusPath) {
        if (!w->focused())
            continue;
        w->focusEvent(false);
    }
    mFocusPath.clear();
    Widget *window = nullptr;
    while (widget) {
        mFocusPath.push_back(widget);
        if (dynamic_cast<Window *>(widget))
            window = widget;
        widget = widget->parent();
    }
    for (auto it = mFocusPath.rbegin(); it != mFocusPath.rend(); ++it)
        (*it)->focusEvent(true);

    if (window)
        moveWindowToFront((Window *) window);
}

void GUIScreen::disposeWindow(nanogui::Window *window) {
    if (std::find(mFocusPath.begin(), mFocusPath.end(), window) != mFocusPath.end())
        mFocusPath.clear();
    if (mDragWidget == window)
        mDragWidget = nullptr;
    removeChild(window);
}

void GUIScreen::centerWindow(Window *window) {
    if (window->size() == Vector2i::Zero()) {
        window->setSize(window->preferredSize(mNVGContext));
        window->performLayout(mNVGContext);
    }
    window->setPosition((mSize - window->size()) / 2);
}

void GUIScreen::moveWindowToFront(Window *window) {
    mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), window), mChildren.end());
    mChildren.push_back(window);
    /* Brute force topological sort (no problem for a few windows..) */
    bool changed = false;
    do {
        size_t baseIndex = 0;
        for (size_t index = 0; index < mChildren.size(); ++index)
            if (mChildren[index] == window)
                baseIndex = index;
        changed = false;
        for (size_t index = 0; index < mChildren.size(); ++index) {
            Popup *pw = dynamic_cast<Popup *>(mChildren[index]);
            if (pw && pw->parentWindow() == window && index < baseIndex) {
                moveWindowToFront(pw);
                changed = true;
                break;
            }
        }
    } while (changed);
}

GLFWwindow* GUIScreen::getWindow()
{
    return mGLFWWindow;
}

void GUIScreen::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

bool GUIScreen::close()
{
    return (bool) glfwWindowShouldClose(mGLFWWindow);
}