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
#include "DepthBuffer.h"
#include "Mesh.h"
#include "shader.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Camera.h"
#include "texture2D.h"
#include <IL/il.h>

using namespace std;
using namespace glm;

//Palma
Mesh mesh;
Mesh falange;

ShaderProgram program;
ShaderProgram programa;
ShaderProgram programa2;

Transform _transform;
Transform _transform2;

//Falanges
//Pulgar
Transform _falPul1;
Transform _falPul2;

//Indice
Transform _falIn1;
Transform _falIn2;

//Medio
Transform _falMed1;
Transform _falMed2;

//Menique
Transform _falM1;
Transform _falM2;

//Mov
Transform _prueba;
Transform _prueba2;
Transform _prueba3;
Transform _prueba4;
Transform _prueba5;
Transform _prueba6;
Transform _prueba7;
Transform _prueba8;


Camera _camera;
Camera _camaraLuz;

DepthBuffer profundidad;

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
vec3 lightPosition = vec3(0.0f, 5.0f, 10.0f);

mat4 modelMatrix;
mat4 modelMatrix2;
mat3 normalMatrix;
mat3 normalMatrix2;

texture2D piso;
texture2D mario;
texture2D caja;

//Para mover los dedos
float rotarDedos = 0.05f;
float trasladarDedos = 0.004f;
float rotarDedos1 = 0.05f;
float trasladarDedos1 = 0.004f;
float rotarDedos2 = 0.05f;
float trasladarDedos2 = 0.004f;
int delta = 0;

void Initialize() {

	vector<vec3> colors, normals, positions, positionsFalange;
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

	//Posiciones por cara para la Palma
	//trasera
	positions.push_back(vec3(3.0f, -5.0f, -1.0f));
	positions.push_back(vec3(3.0f, 5.0f, -1.0f));
	positions.push_back(vec3(-3.0f, -5.0f, -1.0f));
	positions.push_back(vec3(-3.0f, 5.0f, -1.0f));
	//derecha
	positions.push_back(vec3(3.0f, -5.0f, -1.0f));
	positions.push_back(vec3(3.0f, 5.0f, -1.0f));
	positions.push_back(vec3(3.0f, -5.0f, 1.0f));
	positions.push_back(vec3(3.0f, 5.0f, 1.0f));
	//abajo
	positions.push_back(vec3(3.0f, -5.0f, 1.0f));
	positions.push_back(vec3(3.0f, -5.0f, -1.0f));
	positions.push_back(vec3(-3.0f, -5.0f, 1.0f));
	positions.push_back(vec3(-3.0f, -5.0f, -1.0f));
	//frontal
	positions.push_back(vec3(3.0f, -5.0f, 1.0f));
	positions.push_back(vec3(3.0f, 5.0f, 1.0f));
	positions.push_back(vec3(-3.0f, -5.0f, 1.0f));
	positions.push_back(vec3(-3.0f, 5.0f, 1.0f));
	//izquierda
	positions.push_back(vec3(-3.0f, -5.0f, -1.0f));
	positions.push_back(vec3(-3.0f, 5.0f, -1.0f));
	positions.push_back(vec3(-3.0f, -5.0f, 1.0f));
	positions.push_back(vec3(-3.0f, 5.0f, 1.0f));
	//arriba
	positions.push_back(vec3(3.0f, 5.0f, 1.0f));
	positions.push_back(vec3(3.0f, 5.0f, -1.0f));
	positions.push_back(vec3(-3.0f, 5.0f, 1.0f));
	positions.push_back(vec3(-3.0f, 5.0f, -1.0f));

	//Posiciones para las falanges
	//Posiciones por cara
	//trasera
	positionsFalange.push_back(vec3(4.0f * 0.2f, -3.0f * 0.6f, -1.0f));
	positionsFalange.push_back(vec3(4.0f * 0.2f, 3.0f * 0.6f, -1.0f));
	positionsFalange.push_back(vec3(-4.0f * 0.2f, -3.0f* 0.6f, -1.0f));
	positionsFalange.push_back(vec3(-4.0f * 0.2f, 3.0f* 0.6f, -1.0f));
	//derecha
	positionsFalange.push_back(vec3(4.0f * 0.2f, -3.0f* 0.6f, -1.0f));
	positionsFalange.push_back(vec3(4.0f * 0.2f, 3.0f* 0.6f, -1.0f));
	positionsFalange.push_back(vec3(4.0f * 0.2f, -3.0f* 0.6f, 1.0f));
	positionsFalange.push_back(vec3(4.0f * 0.2f, 3.0f* 0.6f, 1.0f));
	//abajo
	positionsFalange.push_back(vec3(4.0f * 0.2f, -3.0f* 0.6f, 1.0f));
	positionsFalange.push_back(vec3(4.0f* 0.2f, -3.0f* 0.6f, -1.0f));
	positionsFalange.push_back(vec3(-4.0f* 0.2f, -3.0f* 0.6f, 1.0f));
	positionsFalange.push_back(vec3(-4.0f* 0.2f, -3.0f* 0.6f, -1.0f));
	//frontal
	positionsFalange.push_back(vec3(4.0f* 0.2f, -3.0f* 0.6f, 1.0f));
	positionsFalange.push_back(vec3(4.0f* 0.2f, 3.0f* 0.6f, 1.0f));
	positionsFalange.push_back(vec3(-4.0f* 0.2f, -3.0f* 0.6f, 1.0f));
	positionsFalange.push_back(vec3(-4.0f* 0.2f, 3.0f* 0.6f, 1.0f));
	//izquierda
	positionsFalange.push_back(vec3(-4.0f* 0.2f, -3.0f* 0.6f, -1.0f));
	positionsFalange.push_back(vec3(-4.0f* 0.2f, 3.0f* 0.6f, -1.0f));
	positionsFalange.push_back(vec3(-4.0f* 0.2f, -3.0f* 0.6f, 1.0f));
	positionsFalange.push_back(vec3(-4.0f* 0.2f, 3.0f* 0.6f, 1.0f));
	//arriba
	positionsFalange.push_back(vec3(4.0f* 0.2f, 3.0f* 0.6f, 1.0f));
	positionsFalange.push_back(vec3(4.0f* 0.2f, 3.0f* 0.6f, -1.0f));
	positionsFalange.push_back(vec3(-4.0f* 0.2f, 3.0f* 0.6f, 1.0f));
	positionsFalange.push_back(vec3(-4.0f* 0.2f, 3.0f* 0.6f, -1.0f));

	//Normales
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
		20,21,22,22,21,23
	};

	caja.LoadTexture("caja.jpg");
	piso.LoadTexture("piso.jpg");
	mario.LoadTexture("mario.png");

	//Palma
	//Manager
	mesh.CreateMesh(positions.size());
	mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	mesh.SetNormalAttribute(normals, GL_STATIC_DRAW, 2);
	mesh.SetTexCoordAttribute(textures, GL_STATIC_DRAW, 3);
	mesh.SetIndices(indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	//Falanges
	//Manager
	falange.CreateMesh(positionsFalange.size());
	falange.SetPositionAttribute(positionsFalange, GL_STATIC_DRAW, 0);
	falange.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	falange.SetNormalAttribute(normals, GL_STATIC_DRAW, 2);
	falange.SetTexCoordAttribute(textures, GL_STATIC_DRAW, 3);
	falange.SetIndices(indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	//Shader Program para profundidad
	programa.CreateProgram();
	programa.AttachShader("Depth.vert", GL_VERTEX_SHADER);
	programa.AttachShader("Depth.frag", GL_FRAGMENT_SHADER);
	programa.SetAttribute(0, "VertexPosition");
	programa.LinkProgram();
	glBindVertexArray(0);
	

	program.CreateProgram();
	program.AttachShader("Shadow.vert", GL_VERTEX_SHADER);
	program.AttachShader("Shadow.frag", GL_FRAGMENT_SHADER);
	program.SetAttribute(0, "VertexPosition");
	program.SetAttribute(1, "VertexColor");
	program.SetAttribute(2, "VertexNormal");
	program.SetAttribute(3, "VertexTexCoord");
	program.LinkProgram();

	program.Activate();
	
	//program.Activate();
	program.SetUniformf("lightColor", 1.0f, 1.0f, 1.0f);
	program.SetUniformf("lightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
	program.SetUniformf("cameraPosition", _camera.GetPosition().x, _camera.GetPosition().y, _camera.GetPosition().z);
	program.SetUniformi("diffuseTexture", 0);
	program.SetUniformi("diffuseTexture2", 1);
	program.SetUniformi("shadowMap", 2);
	program.Deactivate();

	programa2.CreateProgram();
	programa2.AttachShader("Shadow.vert", GL_VERTEX_SHADER);
	programa2.AttachShader("Shadow.frag", GL_FRAGMENT_SHADER);
	programa2.SetAttribute(0, "VertexPosition");
	programa2.SetAttribute(1, "VertexColor");
	programa2.SetAttribute(2, "VertexNormal");
	programa2.SetAttribute(3, "VertexTexCoord");
	programa2.LinkProgram();

	programa2.Activate();

	programa2.SetUniformf("cameraPosition", _camera.GetPosition().x, _camera.GetPosition().y, _camera.GetPosition().z);
	programa2.SetUniformi("diffuseTexture", 0);
	programa2.SetUniformi("diffuseTexture2", 1);
	programa2.SetUniformi("shadowMap", 2);
	programa2.SetUniformf("lightColor", 1.0f, 1.0f, 1.0f);
	programa2.SetUniformf("lightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
	
	programa2.Deactivate();

	_camera.SetPosition(0.0f, 0.0f, 30.0f);
	_camaraLuz.SetPosition(lightPosition.x, lightPosition.y, lightPosition.z);
	_camaraLuz.Pitch(-45);
	_camaraLuz.SetOrthographic(30.0f, 1);

	//_transform.SetScale(0.1f, 0.1f, 0.1f);
	_transform.SetRotation(-45.0f, 0.0f, 0.0f);
	_transform.SetPosition(0.0f, -2.0f, 0.0f);
	_transform2.SetScale(8.0f, 0.01f, 15.0f);
	_transform2.SetPosition(0.0f, -10.0f, 0.0f);

	
	
	
	//Dedos
	//Pulgar
	//_falPul1.SetScale(0.04f, 0.02f, 0.08f);
	//_falPul2.SetScale(0.04f, 0.02f, 0.08f);
	_falPul1.SetPosition(0.0f, 2.5f, 0.0f);
	_falPul2.SetPosition(0.0f, 2.5f, 0.0f);

	//Indice
	//_falIn1.SetScale(0.025f, 0.03f, 0.2f);
	//_falIn2.SetScale(0.025f, 0.03f, 0.2f);
	_falIn1.SetPosition(0.0f, 2.5f, 0.0f);
	_falIn2.SetPosition(0.0f, 2.5f, 0.0f);

	//Medio
	//_falMed1.SetScale(0.025f, 0.03f, 0.2f);
	//_falMed2.SetScale(0.025f, 0.03f, 0.2f);
	_falMed1.SetPosition(0.0f, 2.5f, 0.0f);
	_falMed2.SetPosition(0.0f, 2.5f, 0.0f);

	//Menique
	//_falM1.SetScale(0.025f, 0.03f, 0.2f);
	//_falM2.SetScale(0.025f, 0.03f, 0.2f);
	_falM1.SetPosition(1.8f,0.0f, 0.0f);
	_falM1.Rotate(0.0f, 0.0f, -90.0f, false);
	_falM2.SetPosition(  0.0f, 1.8f, 0.0f);
	//_falM2.Rotate(0.0f, 0.0f, 90.0f, false);

	_prueba.SetPosition(-2.2f, 5.0f, 0.0f);
	_prueba2.SetPosition(0.0f, 0.8f, 0.0f);

	_prueba3.SetPosition(-0.2f,5.0f,0.0f);
	_prueba4.SetPosition(0.0f, 0.8f, 0.0f);

	_prueba5.SetPosition(1.8f, 5.0f, 0.0f);
	_prueba6.SetPosition(0.0f, 0.8f, 0.0f);

	_prueba7.SetPosition(3.0f,-4.2f,0.0f);
	_prueba8.SetPosition( 0.0f, 1.8f, 0.0f);

	//Recibe resolucion
	profundidad.Create(2048);
	
	


	
}

void GameLoop() {
	_transform.Rotate(0.00f, 0.00f, 0.01f, false);
	
	//Mover dedos
	//_falPul1.Rotate(rotarDedos, 0.0f, 0.0f, false);
	_prueba.Rotate(rotarDedos, 0.0f, 0.0f, false);
	_prueba2.Rotate(rotarDedos, 0.0f, 0.0f, false);
	//_falPul2.Translate(0.0f, trasladarDedos, 0.0f, false);

	_prueba3.Rotate(rotarDedos, 0.0f, 0.0f, false);
	//_falIn1.Translate(0.0f, trasladarDedos, 0.0f, false);
	_prueba4.Rotate(rotarDedos, 0.0f, 0.0f, false);
	//_falIn2.Translate(0.0f, trasladarDedos, 0.0f, false);

	_prueba5.Rotate(rotarDedos, 0.0f, 0.0f, false);
	//_falMed1.Translate(0.0f, trasladarDedos, 0.0f, false);
	_prueba6.Rotate(rotarDedos, 0.0f, 0.0f, false);
	//_falMed2.Translate(0.0f, trasladarDedos, 0.0f, false);

	_prueba7.Rotate(0.0f, -rotarDedos, 0.0f, false);
	//_falM1.Translate(0.0f, -trasladarDedos, 0.0f, false);
	_prueba8.Rotate(rotarDedos, 0.0f, 0.0f, false);
	//_falM2.Translate(0.0f, -trasladarDedos, 0.0f, false);

	delta += 1;
	//cout << delta << endl;
	if (delta % 2000 == 0) {
		rotarDedos = rotarDedos*-1.0;
		trasladarDedos = trasladarDedos*-1.0;
	}
	


	/////////////////////////////////////////////////////////////////////////////
	//Primer Render
	/////////////////////////////////////////////////////////////////////////////
	
	//Usaremos Depth.vert y frag para regresar la distancia entre un punto y la camara
	profundidad.Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	programa2.Activate();

	//Palma
	programa.SetUniformMatrix("mvpMatrix", _camaraLuz.GetViewProjection() * _transform.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);

	//Piso
	mat4 mm2 = _transform2.GetModelMatrix();
	programa.SetUniformMatrix("mvpMatrix", _camaraLuz.GetViewProjection() * _transform2.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);

	//programa.Deactivate();

	//programa2.Activate();
	//Menique
	programa2.SetUniformMatrix("mvpMatrix", _camaraLuz.GetViewProjection() *  _transform.GetModelMatrix() * _prueba.GetModelMatrix() * _falPul1.GetModelMatrix());
	falange.Draw(GL_TRIANGLES);
	programa2.SetUniformMatrix("mvpMatrix", _camaraLuz.GetViewProjection() *  _transform.GetModelMatrix() * _prueba.GetModelMatrix() * _falPul1.GetModelMatrix() * _prueba2.GetModelMatrix() * _falPul2.GetModelMatrix());
	falange.Draw(GL_TRIANGLES);

	//Indice
	programa2.SetUniformMatrix("mvpMatrix", _camaraLuz.GetViewProjection() *  _transform.GetModelMatrix() * _prueba3.GetModelMatrix() * _falIn1.GetModelMatrix());
	falange.Draw(GL_TRIANGLES);
	programa2.SetUniformMatrix("mvpMatrix", _camaraLuz.GetViewProjection() *  _transform.GetModelMatrix() * _prueba3.GetModelMatrix() *  _falIn1.GetModelMatrix() *_prueba4.GetModelMatrix() *_falIn2.GetModelMatrix());
	falange.Draw(GL_TRIANGLES);

	//Medio
	programa2.SetUniformMatrix("mvpMatrix", _camaraLuz.GetViewProjection() *  _transform.GetModelMatrix() * _prueba5.GetModelMatrix() * _falMed1.GetModelMatrix());
	falange.Draw(GL_TRIANGLES);
	programa2.SetUniformMatrix("mvpMatrix", _camaraLuz.GetViewProjection() *  _transform.GetModelMatrix() * _prueba5.GetModelMatrix() * _falMed1.GetModelMatrix() * _prueba6.GetModelMatrix() *_falMed2.GetModelMatrix());
	falange.Draw(GL_TRIANGLES);

	//Menique
	programa2.SetUniformMatrix("mvpMatrix", _camaraLuz.GetViewProjection() *  _transform.GetModelMatrix() * _prueba7.GetModelMatrix() * _falM1.GetModelMatrix());
	falange.Draw(GL_TRIANGLES);
	programa2.SetUniformMatrix("mvpMatrix", _camaraLuz.GetViewProjection() *  _transform.GetModelMatrix() * _prueba7.GetModelMatrix() * _falM1.GetModelMatrix() * _prueba8.GetModelMatrix() * _falM2.GetModelMatrix());
	falange.Draw(GL_TRIANGLES);



	programa2.Deactivate();

	

	profundidad.Unbind();
	glViewport(0, 0, 400, 400);

	///////////////////////////////////////////////////////////////////////////
	//Segundo Render
	///////////////////////////////////////////////////////////////////////////
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program.Activate();

	glActiveTexture(GL_TEXTURE0);
	caja.Bind();

	glActiveTexture(GL_TEXTURE1);
	mario.Bind();

	glActiveTexture(GL_TEXTURE2);
	profundidad.BindDepthMap();

	program.SetUniformf("lightColor", lightColor.x, lightColor.y, lightColor.z);
	program.SetUniformf("lightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
	program.SetUniformf("cameraPosition", _camera.GetPosition().x, _camera.GetPosition().y, _camera.GetPosition().z);
	program.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix());
	program.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transform.GetModelMatrix()))));
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()* _transform.GetModelMatrix());
	program.SetUniformMatrix("LightVPMatrix", _camaraLuz.GetViewProjection());
	program.SetUniformi("shadowMap", 2);
	mesh.Draw(GL_TRIANGLES);
	
	glActiveTexture(GL_TEXTURE0);
	caja.Unbind();
	glActiveTexture(GL_TEXTURE1);
	mario.Unbind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.UnbindDepthMap();

	//Piso
	glActiveTexture(GL_TEXTURE0);
	piso.Bind();
	modelMatrix2 = _transform2.GetModelMatrix();
	normalMatrix2 = transpose(inverse(mat3(_transform2.GetModelMatrix())));
	program.SetUniformMatrix("modelMatrix", modelMatrix2);
	program.SetUniformMatrix3("normalMatrix", normalMatrix2);
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()* _transform2.GetModelMatrix());
	program.SetUniformMatrix("LightVPMatrix", _camaraLuz.GetViewProjection());
	program.SetUniformi("shadowMap", 2);

	glActiveTexture(GL_TEXTURE2);
	profundidad.BindDepthMap();
	mesh.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE2);
	profundidad.UnbindDepthMap();
	glActiveTexture(GL_TEXTURE0);
	piso.Unbind();
	
	program.Deactivate();

	//Menique
	program.Activate();
	glActiveTexture(GL_TEXTURE0);
	caja.Bind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.BindDepthMap();
	program.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix() * _prueba.GetModelMatrix() * _falPul1.GetModelMatrix());
	program.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transform.GetModelMatrix() * _prueba.GetModelMatrix() * _falPul1.GetModelMatrix()))));
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix() * _prueba.GetModelMatrix() * _falPul1.GetModelMatrix() );
	program.SetUniformMatrix("LightVPMatrix", _camaraLuz.GetViewProjection());
	falange.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	caja.Unbind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.UnbindDepthMap();
	program.Deactivate();

	program.Activate();
	glActiveTexture(GL_TEXTURE0);
	caja.Bind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.BindDepthMap();
	program.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix() * _prueba.GetModelMatrix() * _falPul1.GetModelMatrix() * _prueba2.GetModelMatrix() * _falPul2.GetModelMatrix());
	program.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transform.GetModelMatrix() * _prueba.GetModelMatrix() * _falPul1.GetModelMatrix() * _prueba2.GetModelMatrix() * _falPul2.GetModelMatrix()))));
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() *_transform.GetModelMatrix() * _prueba.GetModelMatrix() * _falPul1.GetModelMatrix() * _prueba2.GetModelMatrix() * _falPul2.GetModelMatrix());
	program.SetUniformMatrix("LightVPMatrix", _camaraLuz.GetViewProjection());
	falange.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	caja.Unbind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.UnbindDepthMap();
	program.Deactivate();

	//(medio)
	program.Activate();
	glActiveTexture(GL_TEXTURE0);
	caja.Bind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.BindDepthMap();
	program.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix() * _prueba3.GetModelMatrix() * _falIn1.GetModelMatrix());
	program.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transform.GetModelMatrix() * _prueba3.GetModelMatrix() * _falIn1.GetModelMatrix()))));
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() *  _transform.GetModelMatrix() * _prueba3.GetModelMatrix() * _falIn1.GetModelMatrix());
	program.SetUniformMatrix("LightVPMatrix", _camaraLuz.GetViewProjection());
	falange.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	caja.Unbind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.UnbindDepthMap();
	program.Deactivate();

	program.Activate();
	glActiveTexture(GL_TEXTURE0);
	caja.Bind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.BindDepthMap();
	program.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix() * _prueba3.GetModelMatrix() *  _falIn1.GetModelMatrix() *_prueba4.GetModelMatrix() *_falIn2.GetModelMatrix());
	program.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transform.GetModelMatrix() * _prueba3.GetModelMatrix() *  _falIn1.GetModelMatrix() *_prueba4.GetModelMatrix() *_falIn2.GetModelMatrix()))));
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() *   _transform.GetModelMatrix() * _prueba3.GetModelMatrix() *  _falIn1.GetModelMatrix() *_prueba4.GetModelMatrix() *_falIn2.GetModelMatrix());
	program.SetUniformMatrix("LightVPMatrix", _camaraLuz.GetViewProjection());
	falange.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	caja.Unbind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.UnbindDepthMap();
	program.Deactivate();

	//Indice
	program.Activate();
	glActiveTexture(GL_TEXTURE0);
	caja.Bind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.BindDepthMap();
	program.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix() * _prueba5.GetModelMatrix() * _falMed1.GetModelMatrix());
	program.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transform.GetModelMatrix() * _prueba5.GetModelMatrix() * _falMed1.GetModelMatrix()))));
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix() * _prueba5.GetModelMatrix() * _falMed1.GetModelMatrix());
	program.SetUniformMatrix("LightVPMatrix", _camaraLuz.GetViewProjection());
	falange.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	caja.Unbind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.UnbindDepthMap();
	program.Deactivate();

	program.Activate();
	glActiveTexture(GL_TEXTURE0);
	caja.Bind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.BindDepthMap();
	program.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix() * _prueba5.GetModelMatrix() * _falMed1.GetModelMatrix() * _prueba6.GetModelMatrix() *_falMed2.GetModelMatrix());
	program.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transform.GetModelMatrix() * _prueba5.GetModelMatrix() * _falMed1.GetModelMatrix() * _prueba6.GetModelMatrix() *_falMed2.GetModelMatrix()))));
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix() * _prueba5.GetModelMatrix() * _falMed1.GetModelMatrix() * _prueba6.GetModelMatrix() *_falMed2.GetModelMatrix());
	program.SetUniformMatrix("LightVPMatrix", _camaraLuz.GetViewProjection());
	falange.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	caja.Unbind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.UnbindDepthMap();
	program.Deactivate();

	//Menique no
	program.Activate();
	glActiveTexture(GL_TEXTURE0);
	caja.Bind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.BindDepthMap();
	program.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix() * _prueba7.GetModelMatrix() * _falM1.GetModelMatrix());
	program.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transform.GetModelMatrix() * _prueba7.GetModelMatrix() * _falM1.GetModelMatrix()))));
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix() * _prueba7.GetModelMatrix() * _falM1.GetModelMatrix());
	program.SetUniformMatrix("LightVPMatrix", _camaraLuz.GetViewProjection());
	falange.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	caja.Unbind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.UnbindDepthMap();
	program.Deactivate();

	program.Activate();
	glActiveTexture(GL_TEXTURE0);
	caja.Bind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.BindDepthMap();
	program.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix() * _prueba7.GetModelMatrix() * _falM1.GetModelMatrix() * _prueba8.GetModelMatrix() * _falM2.GetModelMatrix());
	program.SetUniformMatrix3("normalMatrix", transpose(inverse(mat3(_transform.GetModelMatrix() * _prueba7.GetModelMatrix() * _falM1.GetModelMatrix() * _prueba8.GetModelMatrix() * _falM2.GetModelMatrix()))));
	program.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix() * _prueba7.GetModelMatrix() * _falM1.GetModelMatrix() * _prueba8.GetModelMatrix() * _falM2.GetModelMatrix());
	program.SetUniformMatrix("LightVPMatrix", _camaraLuz.GetViewProjection());
	falange.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	caja.Unbind();
	glActiveTexture(GL_TEXTURE2);
	profundidad.UnbindDepthMap();
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
