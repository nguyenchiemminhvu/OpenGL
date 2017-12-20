#include "Texture.h"
#include "SOIL\SOIL.h"

void Texture::active(GLuint index)
{
	glActiveTexture(GL_TEXTURE0 + index);
}


Texture::Texture()
{
	glGenTextures(1, &textureID);
}


Texture::~Texture()
{
}


void Texture::setTextureID(GLuint id)
{
	this->textureID = id;
}


GLuint Texture::getTextureID()
{
	return this->textureID;
}


string Texture::getTextureType()
{
	return this->type;
}


string Texture::getPath()
{
	return this->path;
}


void Texture::setTextureType(string type)
{
	this->type = type;
}


void Texture::setPath(const string &path)
{
	this->path = path;
}


void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}


void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::setDefaultParameters()
{
	setWrap(GL_REPEAT);
	setMinFilter(GL_LINEAR);
	setMagFilter(GL_LINEAR);
}


void Texture::textureParameteri(GLenum pname, GLint value)
{
	glTexParameteri(GL_TEXTURE_2D, pname, value);
}


void Texture::setWrap(GLint value)
{
	setWrapS(value);
	setWrapT(value);
}


void Texture::setWrapS(GLint value)
{
	textureParameteri(GL_TEXTURE_WRAP_S, value);
}


void Texture::setWrapT(GLint value)
{
	textureParameteri(GL_TEXTURE_WRAP_T, value);
}


void Texture::setMagFilter(GLint value)
{
	textureParameteri(GL_TEXTURE_MAG_FILTER, value);
}


void Texture::setMinFilter(GLint value)
{
	textureParameteri(GL_TEXTURE_MIN_FILTER, value);
}


void Texture::generateMipmap()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}


void Texture::loadImage(const char *path, bool flipVertically)
{
	int channel;

	unsigned char *image = SOIL_load_image(path, &width, &height, &channel, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	generateMipmap();
	setPath(path);

	SOIL_free_image_data(image);
}
