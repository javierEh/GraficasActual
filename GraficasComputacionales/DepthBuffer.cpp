#include "DepthBuffer.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <vector> 
#include <glm/glm.hpp>
#include <IL/il.h>

DepthBuffer::DepthBuffer()
{
	_frameBuffer = 0;
	_depthmap = 0;
	_resolution = 0;
}

DepthBuffer::~DepthBuffer()
{
	glDeleteFramebuffers(1, &_frameBuffer);
	glDeleteTextures(1, &_depthmap);
}

void DepthBuffer::Create(int resolution)
{
	_resolution = resolution;
	
	glGenFramebuffers(1, &_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	glGenTextures(1, &_depthmap);
	BindDepthMap();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _resolution, _resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthmap, 0);

	Unbind();
}

void DepthBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
	glViewport(0, 0, _resolution, _resolution);
}

void DepthBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DepthBuffer::BindDepthMap()
{
	glBindTexture(GL_TEXTURE_2D, _depthmap);
}

void DepthBuffer::UnbindDepthMap()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
