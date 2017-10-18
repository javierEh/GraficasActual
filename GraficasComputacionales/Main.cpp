/*********************************************************
Materia: Gráficas Computacionales
Fecha: 16 de agosto del 2017
Autor: A01370699 Abraham Soto
Autor: A01374645 Javier Esponda
*********************************************************/

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>

#include "inputFile.h"
#include "Mesh.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Camera.h"

using namespace std;
using namespace glm;

Mesh mesh;
ShaderProgram program;
Transform _transform;
Camera _camera;

void Initialize() {

	vector<vec3> positions;
	vector<vec3> colors;

	//Colores por cara
	colors.push_back(vec3(1.0f, 1.0f, 0));
	colors.push_back(vec3(1.0f, 1.0f, 0));
	colors.push_back(vec3(1.0f, 1.0f, 0));
	colors.push_back(vec3(1.0f, 1.0f, 0));

	colors.push_back(vec3(0.93f, 0.51f, 0.93f));
	colors.push_back(vec3(0.93f, 0.51f, 0.93f));
	colors.push_back(vec3(0.93f, 0.51f, 0.93f));
	colors.push_back(vec3(0.93f, 0.51f, 0.93f));

	colors.push_back(vec3(0.19f, 0.80f, 0.19f));
	colors.push_back(vec3(0.19f, 0.80f, 0.19f));
	colors.push_back(vec3(0.19f, 0.80f, 0.19f));
	colors.push_back(vec3(0.19f, 0.80f, 0.19f));

	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));

	colors.push_back(vec3(0.68f, 0.93f, 0.93f));
	colors.push_back(vec3(0.68f, 0.93f, 0.93f));
	colors.push_back(vec3(0.68f, 0.93f, 0.93f));
	colors.push_back(vec3(0.68f, 0.93f, 0.93f));

	colors.push_back(vec3(0.98f, 0.50f, 0.44f));
	colors.push_back(vec3(0.98f, 0.50f, 0.44f));
	colors.push_back(vec3(0.98f, 0.50f, 0.44f));
	colors.push_back(vec3(0.98f, 0.50f, 0.44f));

	//Posiciones por cara
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));

	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));

	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));

	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));

	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));

	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));



	vector<unsigned int> indices = {
		0, 1, 2, 2, 1, 3,
		4, 5, 6, 6, 5, 7,
		8, 9, 10, 10, 9, 11,
		12, 13, 14, 14, 13, 15,
		16, 17, 18, 18, 17, 19,
		20,21,22,22,21,23,
	};
	mesh.CreateMesh(24);
	mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	mesh.SetIndices(indices, GL_STATIC_DRAW);

	program.CreateProgram();
	program.AttachShader("Default.vert", GL_VERTEX_SHADER);
	program.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	program.SetAttribute(0, "VertexPosition");
	program.SetAttribute(1, "VertexColor");
	program.LinkProgram();

	_camera.SetOrthographic(6.0f, 1.0f);
}

void GameLoop() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_transform.Rotate(0.01f, 0.01f, 0.01f, true);


	program.Activate();
	program.SetUniformMatrix("mvplMatrix", _camera.GetViewProjection()* _transform.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);
	program.Desactivate();


	glutSwapBuffers();
}

void Idle() {
	glutPostRedisplay();
}

void ReshapeWindow(int w, int h) {
	glViewport(0, 0, w, h);

}

int main(int argc, char* argv[]) {
	// Inicializar freeglut
	// Freeglut se encargfa de crear una ventana en donde podemos dibujar Gráficas Computacionales
	glutInit(&argc, argv);
	glutInitContextVersion(4, 2);


	// Iniciar el contexto de OpenGL, se refiere a las capacidades de la aplicación gráfica
	// En este caso se trabaja con el pipeline progamable
	glutInitContextProfile(GLUT_CORE_PROFILE);

	// Freeglut nos permite configurar eventos que ocurren en la ventana
	// Un evento que interesa es cuando alguien cierra la ventana
	// En este caso, se deja de renderear la escena y se termina el programa
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// También configuramos frambuffer, en este caso solicitamos un buffer
	// true color RGBA, un buffer de produndidad y un segundo buffer para renderear
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); // Dos framebuffers

															   // Iniciar las dimensiones de la ventana (en pixeles)
	glutInitWindowSize(400, 400);

	// Creeamos la ventana y le damos un título.
	glutCreateWindow("Hello World OpenGL!");

	glutDisplayFunc(GameLoop);
	//asociamos una función ara el cambio de resolucion de la ventana.
	//freeglut la va a mandar a llamar 
	//cuando alguien cambie el tamaño de la ventana
	glutReshapeFunc(ReshapeWindow);

	//asociamos la función cuando openGL entra en estado de reposos
	glutIdleFunc(Idle);
	// Inicializamos GLEW. Esta librería se encarga de obtener el API de OpenGL de nuestra tarjeta de video
	glewInit();
	glClearColor(1.0f, 1.0f, 3.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	std::cout << glGetString(GL_VERSION) << std::endl;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Configuración inicial de nuestro programa
	Initialize();
	// Iniciar la aplicación. El Main se pausará en esta línea hasta que se cierre la ventana.
	glutMainLoop();

	return 0;
}