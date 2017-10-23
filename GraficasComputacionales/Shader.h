#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
using namespace std;
using namespace glm;


class Shader
{
public:
	Shader();
	~Shader();
	void CreateShader(string path, GLenum  type);
	GLuint GetHandle();
private:
	GLuint _shaderHandle;
};