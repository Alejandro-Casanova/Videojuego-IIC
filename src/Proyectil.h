#include "Vector2D.h"
#include "Entidad.h"
#pragma once


class Proyectil : public Entidad
{
	friend class Interaccion;
public:
	Proyectil();
	~Proyectil();

	void dibuja() override;
	void inicializa() override;
	void setOrigen(float ox, float oy);

private:
	
	Vector2D _origen;
	float distancia = 0.0f;			// longitud que recorre un disparo desde el origen
};

