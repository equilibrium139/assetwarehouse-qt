#ifndef ASSETVIEWER_H
#define ASSETVIEWER_H

#include "camera.h"
#include "input.h"
#include <QElapsedTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <qopenglfunctions_4_3_core.h>

class AssetViewer : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT

public:
    AssetViewer(QWidget* parent = nullptr);



protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    // void wheelEvent(QWheelEvent* event) override;

private:
    void updateScene();
    Camera camera;
    Input input{};
    int updatePeriodMS = 16; // doesn't guarantee fixed update, still have to calculate deltaTime
    float deltaTimeSeconds = 0.0f;
    QElapsedTimer frameTimer;
};

#endif // ASSETVIEWER_H
