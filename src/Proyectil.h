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
	void inicializa() override;
	void setOrigen(float ox, float oy);
	//void mueve(float t);
	//void setPos1(float ix, float iy);


private:
	
	Vector2D _origen;
	float distancia=0;			// longitud que recorre un disparo desde el origen


};

