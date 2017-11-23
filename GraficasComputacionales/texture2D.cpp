#include "texture2D.h"
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <IL/il.h>
#include <string>

using namespace std;
using namespace glm;

texture2D::texture2D()
{
	_textureID = 0;	
}

texture2D::~texture2D()
{
	glDeleteTextures(1, &_textureID);
}

void texture2D::LoadTexture(string path)
{
	//DEVil
	ILuint imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	ilLoadImage(path.c_str());
	//ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);


	glGenTextures(1, &_textureID);
	Bind();

	//texture filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), 
		ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
	
	Unbind();
	ilBindImage(0);
	ilDeleteImages(1, &imageID);
}

//void texture2D::LoadTexture(GLint format, GLsizei width, GLsizei height, const void * pixels) {
//	glGenTextures(1, &_textureID);
//	Bind();

//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

//	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_FLOAT, pixels);
//}

void texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

void texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

