#include "assetviewer.h"

AssetViewer::AssetViewer(QWidget* parent) {}

void AssetViewer::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void AssetViewer::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
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

void main() {
    color = aColor;
    gl_Position = vec4(aPosition, 1.0);
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

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
