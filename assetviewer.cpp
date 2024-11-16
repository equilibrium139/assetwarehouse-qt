#include "assetviewer.h"

AssetViewer::AssetViewer(QWidget* parent) {}

void AssetViewer::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(1.0f, 0.1f, 0.1f, 1.0f);
}

void AssetViewer::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void AssetViewer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
