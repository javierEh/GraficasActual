/*********************************************************
Materia: Gráficas Computacionales
Fecha: 30 de Noviembre de 2017
Autor: A01370699 Abraham Soto
Autor: A01374645 Javier Esponda Hernandez
*********************************************************/
#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h>

#include <vector>
#include <glm/glm.hpp>
#include <iostream>

#include "inputFile.h"
#include "Mesh.h"
#include "shader.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Camera.h"
#include "texture2D.h"
#include <IL/il.h>

using namespace std;
using namespace glm;

Mesh mesh;
ShaderProgram program;
Transform _transform;
Transform _transform2;
Transform _transform3;
Camera _camera;
//float deg = 0.0f;
//float scala = 0.5f;
//int creciendo = 1;
vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
vec3 lightPosition = vec3(0.0f, 5.0f, 10.0f);

mat4 modelMatrix;
mat4 modelMatrix2;
mat3 normalMatrix;
mat3 normalMatrix2;

texture2D piso;
texture2D mario;
texture2D caja;

void Initialize() {

	vector<vec3> colors, normals, positions;
	vector<vec2> textures;

	//Colores por cara
	colors.push_back(vec3(1.0f, 1.0f, 0));
	colors.push_back(vec3(1.0f, 1.0f, 0));
	colors.push_back(vec3(1.0f, 1.0f, 0));
	colors.push_back(vec3(1.0f, 1.0f, 0));

	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));

	colors.push_back(vec3(0.0f, 0.749f, 1.0f));
	colors.push_back(vec3(0.0f, 0.749f, 1.0f));
	colors.push_back(vec3(0.0f, 0.749f, 1.0f));
	colors.push_back(vec3(0.0f, 0.749f, 1.0f));

	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));

	colors.push_back(vec3(1.0f, 1.0f, 0.00f));
	colors.push_back(vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(vec3(1.0f, 1.0f, 0.0f));

	colors.push_back(vec3(1.0f, 0.549f, 0.0f));
	colors.push_back(vec3(1.0f, 0.549f, 0.0f));
	colors.push_back(vec3(1.0f, 0.549f, 0.0f));
	colors.push_back(vec3(1.0f, 0.549f, 0.0f));

	//Posiciones por cara
	//trasera
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));
	//derecha
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	//abajo
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	//frontal
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	//izquierda
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	//arriba
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));

	//trasera
	normals.push_back(vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(vec3(0.0f, 0.0f, -1.0f));
	//derecha
	normals.push_back(vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(vec3(1.0f, 0.0f, 0.0f));
	//abajo
	normals.push_back(vec3(0.0f, -1.0f, .0f));
	normals.push_back(vec3(0.0f, -1.0f, .0f));
	normals.push_back(vec3(0.0f, -1.0f, .0f));
	normals.push_back(vec3(0.0f, -1.0f, .0f));
	//frontal
	normals.push_back(vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(vec3(0.0f, 0.0f, 1.0f));
	//izquierda
	normals.push_back(vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(vec3(-1.0f, 0.0f, 0.0f));
	//arriba
	normals.push_back(vec3(0.0f, 1.0f, .0f));
	normals.push_back(vec3(0.0f, 1.0f, .0f));
	normals.push_back(vec3(0.0f, 1.0f, .0f));
	normals.push_back(vec3(0.0f, 1.0f, .0f));

	textures.push_back(vec2(1.0f, 0.0f));
	textures.push_back(vec2(1.0f, 1.0f));
	textures.push_back(vec2(0.0f, 0.0f));
	textures.push_back(vec2(0.0f, 1.0f));

	textures.push_back(vec2(1.0f, 0.0f));
	textures.push_back(vec2(1.0f, 1.0f));
	textures.push_back(vec2(0.0f, 0.0f));
	textures.push_back(vec2(0.0f, 1.0f));

	textures.push_back(vec2(1.0f, 0.0f));
	textures.push_back(vec2(1.0f, 1.0f));
	textures.push_back(vec2(0.0f, 0.0f));
	textures.push_back(vec2(0.0f, 1.0f));

	textures.push_back(vec2(1.0f, 0.0f));
	textures.push_back(vec2(1.0f, 1.0f));
	textures.push_back(vec2(0.0f, 0.0f));
	textures.push_back(vec2(0.0f, 1.0f));

	textures.push_back(vec2(1.0f, 0.0f));
	textures.push_back(vec2(1.0f, 1.0f));
	textures.push_back(vec2(0.0f, 0.0f));
	textures.push_back(vec2(0.0f, 1.0f));

	textures.push_back(vec2(1.0f, 0.0f));
	textures.push_back(vec2(1.0f, 1.0f));
	textures.push_back(vec2(0.0f, 0.0f));
	textures.push_back(vec2(0.0f, 1.0f));

	vector<unsigned int> indices = {
		0, 1, 2, 2, 1, 3,
		4, 5, 6, 6, 5, 7,
		8, 9, 10, 10, 9, 11,
		12, 13, 14, 14, 13, 15,
		16, 17, 18, 18, 17, 19,
		20,21,22,22,21,23,
	};

	caja.LoadTexture("caja.jpg");
	piso.LoadTexture("piso.jpg");
	mario.LoadTexture("mario.png");

	mesh.CreateMesh(positions.size());
	mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	mesh.SetNormalAttribute(normals, GL_STATIC_DRAW, 2);
	mesh.SetTexCoordAttribute(textures, GL_STATIC_DRAW, 3);
	mesh.SetIndices(indices, GL_STATIC_DRAW);

	program.CreateProgram();
	//program.SetAttribute(0, "VertexPosition");
	//program.SetAttribute(1, "VertexColor");
	//program.SetAttribute(2, "VertexNormal");
	//program.AttachShader("Light.vert", GL_VERTEX_SHADER);
	//program.AttachShader("Light.frag", GL_FRAGMENT_SHADER);
	//program.LinkProgram();
	program.AttachShader("Shadow.vert", GL_VERTEX_SHADER);
	program.AttachShader("Shadow.frag", GL_FRAGMENT_SHADER);
	program.SetAttribute(0, "VertexPosition");
	program.SetAttribute(1, "VertexColor");
	program.SetAttribute(2, "VertexNormal");
	program.SetAttribute(3, "VertexTextCoord");
	program.LinkProgram();
	
	program.Activate();
	program.SetUniformf("lightColor", 1.0f, 1.0f, 1.0f);
	program.SetUniformf("lightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
	program.SetUniformf("cameraPosition", _camera.GetPosition().x, _camera.GetPosition().y, _camera.GetPosition().z);
	program.SetUniformi("diffuseTexture", 0);
	program.SetUniformi("diffuseTexture2", 1);
	program.Deactivate();

	_transform.SetScale(0.3f, 0.3f, 0.3f);
	_transform2.SetScale(8.0f, 0.01f, 8.0f);

	_transform.SetPosition(0.0f, 0.0f, 0.0f);
	_transform2.SetPosition(0.0f, -2.0f, 0.0f);

	_camera.SetPosition(0.0f, 0.0f, 10.0f);
}

void GameLoop() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_transform.Rotate(0.01f, 0.01f, 0.01f, false);

	program.Activate();

	glActiveTexture(GL_TEXTURE0);
	caja.Bind();

	glActiveTexture(GL_TEXTURE1);
	mario.Bind();

	/*
	program.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix());
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	program.SetUniformVector("LightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	program.SetUniformVector("LightPosition", glm::vec3(0, 0, 5.0f));
	program.SetUniformVector("CamaraPosition", _camera.GetPosition());
	mesh.Draw(GL_TRIANGLES);

	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform2.GetModelMatrix());
	program.SetUniformMatrix("modelMatrix", _transform2.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);
	program.Deactivate();
	*/

	program.SetUniformf("lightColor", lightColor.x, lightColor.y, lightColor.z);
	program.SetUniformf("lightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
	program.SetUniformf("cameraPosition", _camera.GetPosition().x, _camera.GetPosition().y, _camera.GetPosition().z);
	modelMatrix = _transform.GetModelMatrix();
	normalMatrix = transpose(inverse(mat3(_transform.GetModelMatrix())));
	program.SetUniformMatrix("modelMatrix", modelMatrix);
	program.SetUniformMatrix3("normalMatrix", normalMatrix);
	program.SetUniformMatrix("mvplMatrix", _camera.GetViewProjection()* _transform.GetModelMatrix());
	//program.SetUniformMatrix("LightVPMatrix", );
	mesh.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	caja.Unbind();
	glActiveTexture(GL_TEXTURE1);
	mario.Unbind();

	glActiveTexture(GL_TEXTURE0);
	piso.Bind();
	modelMatrix2 = _transform2.GetModelMatrix();
	normalMatrix2 = transpose(inverse(mat3(_transform2.GetModelMatrix())));
	program.SetUniformMatrix("modelMatrix", modelMatrix2);
	program.SetUniformMatrix3("normalMatrix", normalMatrix2);
	program.SetUniformMatrix("mvplMatrix", _camera.GetViewProjection()* _transform2.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	piso.Unbind();


	program.Deactivate();

	//Cuando terminamos de renderear, cambiamos los buffers.
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

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

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
