#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#pragma once
#include "glew\glew.h"
#include "glfw\glfw3.h"

#include <string>

using std::string;

class Texture
{
public:
	static void active(GLuint index);

	Texture();
	virtual ~Texture();

	void setTextureID(GLuint id);
	GLuint getTextureID();
	string getTextureType();
	string getPath();
	void setTextureType(string type);
	void setPath(const string &path);

	void bind();
	void unbind();

	void setDefaultParameters();
	void textureParameteri(GLenum pname, GLint value);
	void setWrap(GLint value);
	void setWrapS(GLint value);
	void setWrapT(GLint value);
	void setMagFilter(GLint value);
	void setMinFilter(GLint value);

	void generateMipmap();
	void loadImage(const char *path, bool flipVertically = true);

private:
	GLuint textureID;
	string type;
	string path;
	int width;
	int height;
};

#endif //__TEXTURE_H__