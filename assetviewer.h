#ifndef ASSETVIEWER_H
#define ASSETVIEWER_H

#include <QOpenGLWidget>
#include <qopenglfunctions_4_5_core.h>

class AssetViewer : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
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
