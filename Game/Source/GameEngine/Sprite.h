#pragma once
#include <GL/glew.h>
#include "Graphics\GLTexture.h"

/*
	Sprite is a class that can draw a rectangle of a texture to a render target. It can also transform that texture in 2d space (translate, rotate, scale). 
*/

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(int16 screenCoordinateX, int16 screenCoordinateY, uint16 imageWidth, uint16 imageHeight, Blz::string imageFilePath);

	void Draw();

private:
	float x = 0.0f;
	float y = 0.0f;
	float width = 0.0f;
	float height = 0.0f;

	GLuint vboID = 0;

	Blz::Graphics::GLTexture texture;
};

