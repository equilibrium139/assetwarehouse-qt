#pragma once

#include <vector>
#include <QOpenGLFunctions_4_3_Core>

struct ColorAttachmentInfo
{
	GLint internalFormat;
	GLint minFilterMode;
	GLint magFilterMode;
};

// TODO: possibly store state like blending mode and set it on Bind(). Blend mode in OpenGL is not tied to framebuffer, but it would be 
// convenient to treat it as if it were.
struct Framebuffer: protected QOpenGLFunctions_4_3_Core
{
	std::vector<GLuint> colorTextures;
	GLuint id;
	GLuint depthStencilRBO;
	int width, height;

	Framebuffer(int width, int height, const std::vector<ColorAttachmentInfo>& colorAttachmentsInfo, GLint depthStencilInternalFormat);
	void Bind();
};
