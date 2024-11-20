#include "assetviewer.h"

#include <QTimer>
#include <glm/gtc/type_ptr.hpp>

AssetViewer::AssetViewer(QWidget* parent): QOpenGLWidget(parent) {
    QTimer* updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &AssetViewer::updateScene);
    frameTimer.start();
    updateTimer->start(updatePeriodMS);
    camera.position.z = 3.0f;
}

void AssetViewer::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void AssetViewer::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void AssetViewer::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_W:
        input.wPressed = true;
        break;
    case Qt::Key_S:
        input.sPressed = true;
        break;
    case Qt::Key_A:
        input.aPressed = true;
        break;
    case Qt::Key_D:
        input.dPressed = true;
        break;
    default:
        QOpenGLWidget::keyPressEvent(event);
    }
}

void AssetViewer::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_W:
        input.wPressed = false;
        break;
    case Qt::Key_S:
        input.sPressed = false;
        break;
    case Qt::Key_A:
        input.aPressed = false;
        break;
    case Qt::Key_D:
        input.dPressed = false;
        break;
    default:
        QOpenGLWidget::keyReleaseEvent(event);
    }
}

void AssetViewer::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        input.leftMousePressed = true;
        QPoint mousePos = event->pos();
        input.mouseX = mousePos.x();
        input.mouseY = mousePos.y();
        input.mouseDeltaX = 0.0f;
        input.mouseDeltaY = 0.0f;
    }
}

void AssetViewer::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        input.leftMousePressed = false;
    }
}

void AssetViewer::mouseMoveEvent(QMouseEvent* event) {
    if (input.leftMousePressed) {
        QPoint currentMousePosition = event->pos();
        float currentX = currentMousePosition.x();
        float currentY = currentMousePosition.y();
        input.mouseDeltaX = currentX - input.mouseX;
        input.mouseDeltaY = input.mouseY - currentY; // y axis is top down in screen space so subtraction is flipped
        input.mouseX = currentX;
        input.mouseY = currentY;
    }
}

void AssetViewer::updateScene() {
    qint64 frameTimeMS = frameTimer.restart();
    deltaTimeSeconds = frameTimeMS / 1000.0f;

    if (input.wPressed) {
        camera.ProcessKeyboard(Camera_Movement::CAM_FORWARD, deltaTimeSeconds);
    }
    if (input.sPressed) {
        camera.ProcessKeyboard(Camera_Movement::CAM_BACKWARD, deltaTimeSeconds);
    }
    if (input.aPressed) {
        camera.ProcessKeyboard(Camera_Movement::CAM_LEFT, deltaTimeSeconds);
    }
    if (input.dPressed) {
        camera.ProcessKeyboard(Camera_Movement::CAM_RIGHT, deltaTimeSeconds);
    }
    if (input.leftMousePressed) {
        camera.ProcessMouseMovement(input.mouseDeltaX, input.mouseDeltaY);
    }

    input.mouseDeltaX = input.mouseDeltaY = 0.0f;

    update();
}

void AssetViewer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float triangleVertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));

    const char* vsSource =
R"(
#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 mvp;

void main() {
    color = aColor;
    gl_Position = mvp * vec4(aPosition, 1.0);
}
)";

    const char* fsSource =
R"(
#version 450 core

in vec3 color;
out vec4 fragColor;
void main() {
    fragColor = vec4(color, 1.0);
}
)";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSource, 0);
    glCompileShader(GL_VERTEX_SHADER);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSource, 0);
    glCompileShader(GL_FRAGMENT_SHADER);

    GLuint shader = glCreateProgram();
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);
    glUseProgram(shader);

    glm::mat4 mvp = camera.GetProjectionMatrix() * camera.GetViewMatrix();
    int mvpLocation = glGetUniformLocation(shader, "mvp");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
