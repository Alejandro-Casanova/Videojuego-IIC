#pragma once

#include "Vector2D.h"
#include "freeglut.h"
#include "Entidad.h"

class Personaje : public Entidad
{
	friend class Interaccion;
public:
	Personaje();
	virtual ~Personaje();

	virtual void dibuja() override;

	//Estas funciones están en la clase Entidad (herencia)

	//void mueve(float t);
	void inicializa() override;

	/*void setColor(unsigned char r, unsigned char g, unsigned char b) { _r = r; _g = g; _b = b; }
	void setRadio(float radio) { _radio = radio; }
	void setPos(float x, float y);
	void setVel(float vx, float vy);*/

private:
	/*unsigned char _r;
	unsigned char _g;
	unsigned char _b;
	float _radio = 0.0f;

	Vector2D _posicion;
	Vector2D _velocidad;
	Vector2D _aceleracion;*/
};

