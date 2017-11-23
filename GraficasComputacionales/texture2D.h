#pragma once

#include <IL/il.h>
#include <GL/glew.h>
#include <vector>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <string>

using namespace std;
using namespace glm;

class texture2D{
public:
	texture2D();
	~texture2D();

	void LoadTexture(string path);
	//void LoadTexture(GLint format, GLsizei width, GLsizei height, const void * pixels);
	void Bind();
	void Unbind();

private:
	GLuint _textureID;
};