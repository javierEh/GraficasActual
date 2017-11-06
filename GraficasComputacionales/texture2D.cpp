#include "texture2D.h"
#include <IL/il.h>

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
	ILuint imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	ilLoadImage(path.c_str());


	glGenTextures(1, &_textureID);
	Bind();

	//texture filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
	
	Unbind();
}

void texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

void texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

