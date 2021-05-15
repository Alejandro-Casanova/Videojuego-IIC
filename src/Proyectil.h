#include "Vector2D.h"
#include "Entidad.h"
#pragma once


class Proyectil : public Entidad
{
	friend class Interaccion;
public:
	Proyectil(void);
	~Proyectil(void);

	void dibuja() override;
	/*void mueve(float t);*/
	void inicializa() override;

	void setOrigen(float ox, float oy);

	/*void setPos(float x, float y);
	void setVel(float vx, float vy);
	void setAcel(float ax, float ay);*/
	


private:
	/*float radio;
	Vector2D posicion;
	Vector2D velocidad;
	Vector2D aceleracion;*/
	Vector2D _origen;
	float distancia;			// longitud que recorre un disparo desde el origen

	float GetPosX(Vector2D);
	float GetPosY(Vector2D);
};

