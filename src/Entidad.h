#pragma once
#include "ColorRGB.h"
#include "Vector2D.h"

class Entidad {
public:
	Entidad();
	virtual ~Entidad();

	virtual void dibuja() = 0;
	void mueve(float t);
	virtual void inicializa();

	void setColor(unsigned char r, unsigned char g, unsigned char b) { _color.set(r, g, b); }
	void setRadio(float radio) { _radio = radio; }
	void setPos(float x, float y);
	void setVel(float vx, float vy);
	void setAcel(float ax, float ay);
	Vector2D getPos();

protected:
	ColorRGB _color;
	float _radio = 0.0f;

	Vector2D _posicion;
	Vector2D _velocidad;
	Vector2D _aceleracion;

};