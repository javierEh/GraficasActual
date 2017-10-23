/*********************************************************
Materia: Gráficas Computacionales
Fecha: 23 de Octubre del 2017
Autor: A01374645 Javier Esponda Hernandez


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <vector> 
#include <glm/glm.hpp>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

using namespace std;
using namespace glm;

#pragma region Global Scope vars

//manager al que le vamos a asociar todos los VBOs
GLuint vao;

//declaro shader program y mesh
ShaderProgram program;
Mesh mesh;

Transform _transform;
Transform _transform2;
Transform _transform3;
Transform _transform4;
Transform _transform5;

Camera _camera;

int cont = 0;

void Initialize()
{
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
}

void GameLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cont = cont + 1;

	float x, y, z;

	if (cont % 2000 == 0) {
		x = glm::sin(glm::radians(float(cont)));
		y = glm::cos(glm::radians(float(cont)));
		z = glm::cos(glm::radians(float(cont)))*glm::sin(glm::radians(float(cont)));
		glClearColor(x, y, z, 0.0f);
	}

	_camera.Rotate(0.0f, 0.005f, 0.0f, true);

	//Primer cubo
	_transform.Rotate(0.0f, 0.0f, 0.052f, true);//

												//Segundo cubo
	_transform2.SetPosition(20.0f, 0.0f, 0.0f);
	_transform2.Rotate(0.005f, 0.0f, 0.0f, true);

	//Cubo piso
	_transform3.SetScale(12.0f, 0.2f, 12.0f);
	_transform3.SetPosition(0.0f, -5.0f, 0.0f);

	//Cubos en la misma posicion pero uno encima de otro
	//Cubo de abajo
	_transform4.SetPosition(-15.0f, 0.0f, 0.0f);
	_transform4.Rotate(0.0f, 0.005f, 0.0f, true);

	//Cubo de arriba
	_transform5.SetPosition(-15.0f, 7.0f, 0.0f);
	_transform5.Rotate(0.0f, -0.005f, 0.0f, true);

	program.Activate();

	program.SetUniformMatrix("mvplMatrix", _camera.GetViewProjection()* _transform.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);
	program.SetUniformMatrix("mvplMatrix", _camera.GetViewProjection()* _transform2.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);
	program.SetUniformMatrix("mvplMatrix", _camera.GetViewProjection()* _transform3.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);
	program.SetUniformMatrix("mvplMatrix", _camera.GetViewProjection()* _transform4.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);
	program.SetUniformMatrix("mvplMatrix", _camera.GetViewProjection()* _transform5.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);
	program.Deactivate();
	glutSwapBuffers();
}

void ReshapeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
}

void Idle()
{
	//Cuando opengl entra ne modo de reposo 
	//le decimos que vuelva a llamar el gameloop 
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	//inicializa freglut
	//este crea ventana
	//en donde se dibuja
	glutInit(&argc, argv);
	//INICIA EL CONTEXTO DE OPENGL; ESTO SON SUS CAPACIDADES GRAFICAS
	//En este caso se usa pipeline Programable
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//SOLICITANDO VERSION 4.4 DE GL 
	glutInitContextVersion(4, 4);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//freeglut nos permite configurar eventos que ocurren en la ventana
	//nos interesa cuando alguien cierra la ventana, en ese caso se deja de renderear la escena.

	//configuramos el framebuffer, true color RGBA profundidad y un segundo buffer para rendereo
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	//la ventana 
	glutInitWindowSize(400, 400);

	//su titulo e inicialización
	glutCreateWindow("HELLO WORLD GL ");

	glutDisplayFunc(GameLoop);

	//asociamos una funicon para el cambio de resolucion de la ventana
	//se va amandar a llamar cuando alguioen cambie el tamaño
	glutReshapeFunc(ReshapeWindow);
	glutIdleFunc(Idle);
	//inicializa glew y se encarga de obtener el api de opengl de nuestra video card
	glewInit();

	//Config OpenGL
	//este es el color por default en el buffer del color
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	//borrado de caras traseras, todos los triangulos CCW
	//glEnable(GL_CULL_FACE);
	//No dibujar las caras de atras
	//glEnable(GL_BACK);
	//std::cout << glGetString(GL_VERSION) << std::endl;

	//config inicial del programa.
	Initialize();

	//Inicia la aplicación, el main se pausa en esta linea hasta que se cierre la ventana
	glutMainLoop();

	return 0;
}
*********************************************************/