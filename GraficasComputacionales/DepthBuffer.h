#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

class DepthBuffer {
public:
	DepthBuffer();
	~DepthBuffer();
	
	void Create(int resolution);
	void Bind();
	void Unbind();
	void BindDepthMap();
	void UnbindDepthMap();


private: 
	GLuint _frameBuffer;
	GLuint _depthmap;
	GLsizei _resolution;
};
