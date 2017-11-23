#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Mesh {
public:
	Mesh();
	~Mesh();

	void CreateMesh(GLint vertexCount);
	void Draw(GLenum primitive);
	
	void SetPositionAttribute(vector<vec2> positions, GLenum usage, GLuint locationIndex);
	void SetPositionAttribute(vector<vec3> positions, GLenum usage, GLuint locationIndex);
	
	void SetColorAttribute(vector<vec3> colors, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(vector<vec4> colors, GLenum usage, GLuint locationIndex);
	
	void SetNormalAttribute(vector<vec3> normal, GLenum usage, GLuint locationIndex);
	
	void SetIndices(vector<unsigned int> indices, GLenum usage);
	
	//Para texturas
	void SetTexCoordAttribute(vector<vec2> texCoords, GLenum usage, GLuint locationIndex);

private:
	void SetAttributeData(GLuint& buffer, const GLsizeiptr size, const void* data, GLenum usage,
		GLuint locationIndex, const GLint components);

	GLuint _vertexArrayObject;
	GLuint _positionsVertexBufferObject;
	GLuint _colorsVertexBufferObject;
	GLuint _normalsVertexBufferObject;
	GLint _vertexCount;

	GLuint _indexBufferObject;
	GLint  _indexCount;

	//Texturas 
	GLuint _texCoordsVertexBufferObject;

};