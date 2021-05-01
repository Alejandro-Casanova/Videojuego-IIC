#include "Vector2D.h"
#pragma once


class Proyectil
{
public:
	Proyectil(void);
	~Proyectil(void);
	void dibuja(void);
	void setOrigen(float ox, float oy);
	void setPos(float x, float y);
	void setVel(float vx, float vy);
	void setAcel(float ax, float ay);
	void mueve(float t);
	void inicializa(void);


private:
	float radio;
	Vector2D posicion;
	Vector2D velocidad;
	Vector2D aceleracion;
	Vector2D origen;

	float GetPosX(Vector2D);
	float GetPosY(Vector2D);
};

