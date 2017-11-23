#include "Mesh.h"
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <IL/il.h>

using namespace std;
using namespace glm;

/*********************************************************
Materia: Gráficas Computacionales
Fecha: 19 noviembre de 2017
Autor: A01370699 Abraham Soto
Autor: A01374645 Javier Esponda
*********************************************************/

Mesh::Mesh() {
	_vertexArrayObject = 0;
	_positionsVertexBufferObject = 0;
	_colorsVertexBufferObject = 0;
	_vertexCount = 0;
	_normalsVertexBufferObject = 0;
	_indexCount = 0;
	_indexBufferObject = 0;
	_texCoordsVertexBufferObject = 0;

}

Mesh::~Mesh() {
	glDeleteBuffers(1, &_positionsVertexBufferObject);
	glDeleteBuffers(1, &_colorsVertexBufferObject);
	glDeleteVertexArrays(1, &_vertexArrayObject);
	glDeleteBuffers(1, &_normalsVertexBufferObject);
	//glDeleteBuffers(1, &_texCoordsVertexBufferObject);
	glBindVertexArray(0);

}

void Mesh::CreateMesh(GLint vertexCount) {
	_vertexCount = vertexCount;
	glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);
}

void Mesh::Draw(GLenum primitive) {
	//glBindVertexArray(_vertexArrayObject);
	if (_indexCount == 0) {
		glBindVertexArray(_vertexArrayObject);
		glDrawArrays(primitive, 0, _vertexCount);
		glBindVertexArray(0);
	}
	else {
		glBindVertexArray(_vertexArrayObject);
		glDrawElements(primitive, _indexCount, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
	//glBindVertexArray(0);
}

//VEC2
void Mesh::SetPositionAttribute(vector<vec2> positions, GLenum usage, GLuint locationIndex) {
	if (positions.empty() || positions.size() != _vertexCount) {
		;
	}
	else {
		SetAttributeData(_positionsVertexBufferObject, sizeof(vec2)*positions.size(), positions.data(), usage, locationIndex, 2);
	}
}

//VEC3
void Mesh::SetPositionAttribute(vector<vec3> positions, GLenum usage, GLuint locationIndex) {
	if (positions.empty() || positions.size() != _vertexCount) {
		;
	}
	else {
		SetAttributeData(_positionsVertexBufferObject, sizeof(vec3)*positions.size(), positions.data(), usage, locationIndex, 3);
	}
}

//VEC3
void Mesh::SetColorAttribute(vector<vec3> colors, GLenum usage, GLuint locationIndex) {
	if (colors.empty() || colors.size() != _vertexCount) {
		;
	}
	else {
		SetAttributeData(_colorsVertexBufferObject, sizeof(vec3)*colors.size(), colors.data(), usage, locationIndex, 3);
	}
}

//VEC4
void Mesh::SetColorAttribute(vector<vec4> colors, GLenum usage, GLuint locationIndex) {
	if (colors.empty() || colors.size() != _vertexCount) {
		;
	}
	else {
		SetAttributeData(_colorsVertexBufferObject, sizeof(vec4)*colors.size(), colors.data(), usage, locationIndex, 4);
	}
}

void Mesh::SetNormalAttribute(vector<glm::vec3> normal, GLenum usage, GLuint locationIndex)
{
	if (normal.size() > 0 && normal.size() == _vertexCount) {
		SetAttributeData(_normalsVertexBufferObject, sizeof(vec3)*normal.size(), normal.data(), usage, locationIndex, 3);
	}
	else {
		;
	}
}

void Mesh::SetIndices(vector<unsigned int> indices, GLenum usage) {
	//_indexCount = indices.size();
	if (indices.empty()) {
		;
	}
	else {
		if (_indexBufferObject != 0) {
			glDeleteBuffers(1, &_indexBufferObject);
		}
		_indexCount = indices.size();
		glBindVertexArray(_vertexArrayObject);
		glGenBuffers(1, &_indexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*_indexCount, indices.data(), usage);
		glBindVertexArray(0);
	}
}

void Mesh::SetTexCoordAttribute(vector<vec2> texCoords, GLenum usage, GLuint locationIndex) {
	if (texCoords.size() > 0 && texCoords.size() == _vertexCount) {
		SetAttributeData(_texCoordsVertexBufferObject, sizeof(vec2)*texCoords.size(), texCoords.data(), usage, locationIndex, 2);
	}
	else {
		;
	}
}

void Mesh::SetAttributeData(GLuint& buffer, const GLsizeiptr size, const void* data, GLenum usage, GLuint locationIndex, const GLint components) {
	if(&buffer != 0) {
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &buffer);
	}
	//glBindVertexArray(_vertexArrayObject);
	glGenBuffers(1, &buffer);
	// Activamos el buffer de posiciones para poder utilizarlo, este buffer ES UN ATRIBUTO (GL ARRAY BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	// Creamos la memoria y la inicializamos con los datos del atributo de posiciones
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	// Activamos el atributo en la tarjeta de video
	glEnableVertexAttribArray(locationIndex);
	// Configuramos los datos del atributo en la tarjeta de video
	glVertexAttribPointer(locationIndex, components, GL_FLOAT, GL_FALSE, 0, nullptr);
	// Ya no vamos a utilizar este Vertex Buffer Object en este momento
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

}