#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>

using namespace std;

class Shader {
public:
	Shader();
	~Shader();

	void CreateShader(string path, GLenum type);
	GLuint GetHandle();
private:
	GLuint _shaderHandle;
};