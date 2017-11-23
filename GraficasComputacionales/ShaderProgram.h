#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "shader.h"
#include "InputFile.h"

using namespace std;
using namespace glm;

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();

	void CreateProgram();
	void AttachShader(string path, GLenum type);
	void LinkProgram();
	void Activate();
	void Deactivate();
	void SetAttribute(GLuint locationIndex, string name);
	void SetUniformf(string name, float value);
	void SetUniformi(string name, int value);
	void SetUniformf(string name, float x, float y);
	void SetUniformf(string name, float x, float y, float z);
	void SetUniformf(string name, float x, float y, float z, float w);
	void SetUniformMatrix(string name, mat4 matrix);
	void SetUniformMatrix3(string name, mat3 matrix);
	void SetUniformVector(string name, vec3 vector);

private:
	GLuint _programHandle;
	vector<unique_ptr<Shader>> _attachedShaders;

	void DeleteAndDetachShaders();
	void DeleteProgram();
};