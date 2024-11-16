#ifndef ASSETVIEWER_H
#define ASSETVIEWER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class AssetViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    AssetViewer(QWidget* parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // ASSETVIEWER_H
