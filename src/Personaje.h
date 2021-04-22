#pragma once

#include "Vector2D.h"

class Personaje
{
public:
	Personaje();
	virtual ~Personaje();

	void dibuja();
	void mueve(float t);

	void setColor(unsigned char r, unsigned char g, unsigned char b) { _r = r; _g = g; _b = b; }
	void setRadio(float radio) { _radio = radio; }
	void setPos(float x, float y) { _posicion.x = 0; _posicion.y = y; }

private:
	unsigned char _r = 255;
	unsigned char _g = 255;
	unsigned char _b = 255;
	float _radio = 0.0f;

	Vector2D _posicion;
	Vector2D _velocidad;
	Vector2D _aceleracion;
};
