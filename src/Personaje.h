#pragma once

#include "Vector2D.h"
#include "freeglut.h"

class Personaje
{
public:
	Personaje();
	virtual ~Personaje();

	void dibuja();
	void mueve(float t);
	void inicializa();

	void setColor(unsigned char r, unsigned char g, unsigned char b) { _r = r; _g = g; _b = b; }
	void setRadio(float radio) { _radio = radio; }
	void setPos(float x, float y);
	void setVel(float vx, float vy);

private:
	unsigned char _r;
	unsigned char _g;
	unsigned char _b;
	float _radio = 0.0f;

	Vector2D _posicion;
	Vector2D _velocidad;
	Vector2D _aceleracion;
};

