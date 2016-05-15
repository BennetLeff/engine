#pragma once

#include <QMainWindow>
#include <QOpenGLFunctions>
#include <QWindow>
#include <QOpenGLPaintDevice>
#include <QCoreApplication>
#include <QPainter>

class GUIWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GUIWindow(QWindow *parent = 0);
    ~GUIWindow();

    virtual void render(QPainter *painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;

private:
    bool m_update_pending;
    bool m_animating;
    QOpenGLContext* m_context;
    QOpenGLPaintDevice* m_device;
};
