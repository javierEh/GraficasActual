#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
using namespace std;
using namespace glm;

class Mesh
{
public:
	Mesh();
	~Mesh();
	void CreateMesh(GLint vertexCount);
	void Draw(GLenum primitive);
	void SetPositionAttribute(vector<vec2> positions, GLenum usage, GLuint locationIndex);
	void SetPositionAttribute(vector<vec3> positions, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(vector<vec3> colors, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(vector<vec4> colors, GLenum usage, GLuint locationIndex);
	void SetIndices(vector<unsigned int> indices, GLenum usage);
private:
	GLuint _vertexArrayObject;
	GLuint _positionsVertexBufferObject;
	GLuint _colorsVertexBufferObject;
	GLint  _vertexCount;
	void   SetAttributeData(GLuint& buffer, const GLsizeiptr size, const void* data, GLenum usage, GLuint locationIndex, const GLint components);
	GLuint _indicesBufferObject;
	GLint  _indicesCount;
};