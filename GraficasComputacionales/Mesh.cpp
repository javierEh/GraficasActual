#include "Mesh.h"


/*********************************************************
Materia: Gráficas Computacionales
Fecha: 16 de agosto del 2017
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
	glBindVertexArray(0);

}

void Mesh::CreateMesh(GLuint vertexCount) {
	_vertexCount = vertexCount;
	glGenVertexArrays(1, &_vertexArrayObject);
}

void Mesh::Draw(GLenum primitive) {
	glBindVertexArray(_vertexArrayObject);
	if (_indexCount == 0) {
		glDrawArrays(primitive, 0, _vertexCount);
	}
	else {
		(_vertexArrayObject);
		glDrawElements(primitive, _indexCount, GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);
}

void Mesh::SetPositionAttribute(vector<vec2> positions, GLenum usage, GLuint locationIndex) {
	if (positions.size() == 0 || positions.size() != _vertexCount) {
		return;
	}
	else {
		SetAttributeData(_positionsVertexBufferObject, sizeof(vec2) * positions.size(), positions.data(), usage, locationIndex, 2);
	}
}

void Mesh::SetPositionAttribute(vector<vec3> positions, GLenum usage, GLuint locationIndex) {
	if (positions.size() == 0 || positions.size() != _vertexCount) {
		return;
	}
	else {
		SetAttributeData(_positionsVertexBufferObject, sizeof(vec3) * positions.size(), positions.data(), usage, locationIndex, 3);
	}
}

void Mesh::SetColorAttribute(vector<vec3> colors, GLenum usage, GLuint locationIndex) {
	if (colors.size() == 0 || colors.size() != _vertexCount) {
		return;
	}
	else {
		SetAttributeData(_colorsVertexBufferObject, sizeof(vec3) * colors.size(), colors.data(), usage, locationIndex, 3);
	}
}

void Mesh::SetColorAttribute(vector<vec4> colors, GLenum usage, GLuint locationIndex) {
	if (colors.size() == 0 || colors.size() != _vertexCount) {
		return;
	}
	else {
		SetAttributeData(_colorsVertexBufferObject, sizeof(vec4) * colors.size(), colors.data(), usage, locationIndex, 4);
	}
}

void Mesh::SetNormalAttribute(std::vector<glm::vec3> normal, GLenum usage, GLuint locationIndex)
{
	if (normal.size() > 0 && normal.size() == _vertexCount) {
		SetAttributeData(_normalsVertexBufferObject, sizeof(glm::vec3) * normal.size(), normal.data(), usage, locationIndex, 3);
	}
	else {
		return;
	}
}


void Mesh::SetIndices(vector<unsigned int> indices, GLenum usage) {
	_indexCount = indices.size();

	if (_indexCount > 0) {
		glBindVertexArray(_vertexArrayObject);
		glGenBuffers(1, &_indexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* indices.size(), indices.data(), GL_STATIC_DRAW);
		glBindVertexArray(0);
	}
}

void Mesh::SetAttributeData(GLuint & buffer, const GLsizeiptr size, const void * data, GLenum usage, GLuint locationIndex, const GLuint components) {
	if (buffer != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(_vertexArrayObject);
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
	glBindVertexArray(0);

}

void Mesh::SetTexCoordAttribute(vector<vec2> texCoords, GLenum usage, GLuint locationIndex) {
	if (texCoords.size() > 0 && texCoords.size() == _vertexCount) {
		SetAttributeData(_texCoordsVertexBufferObject, sizeof(glm::vec3) * texCoords.size(), texCoords.data(), usage, locationIndex, 2);
	}
	else {
		return;
	}
}