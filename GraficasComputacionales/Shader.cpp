#include "shader.h"
#include "InputFile.h"

shader::shader() {
	_shaderHandle = 0;
}

shader::~shader() {
	glDeleteShader(_shaderHandle);
}

void shader::CreateShader(string path, GLenum type) {

	if (_shaderHandle != 0) {
		glDeleteShader(_shaderHandle);
	}

	// Creamos un objeto para leer archivos
	InputFile myfile;

	// VERTEX SHADER
	// Leemos el archivo Default.vert donde está el código del vertex shader.
	myfile.Read(path);
	// Obtenemos el código fuente y lo guardamos en un string
	string ShaderSource = myfile.GetContents();
	// Creamos un shader de tipo vertex guardamos su identificador en una variable
	_shaderHandle = glCreateShader(type);

	// Obtener los datos en el formato correcto: Vil Cast
	const GLchar *ShaderSource_c = (const GLchar*)ShaderSource.c_str();
	// Le estamos dando el código fuente a OpenGL para que se los asigne al shader
	glShaderSource(_shaderHandle, 1, &ShaderSource_c, nullptr);
	// Compilamos el shader en busca de errores.
	// Vamos a asumir que no hay ningún error.
	glCompileShader(_shaderHandle);
}

GLuint shader::getHandle() {
	return _shaderHandle;
}