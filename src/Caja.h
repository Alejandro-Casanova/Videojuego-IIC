#pragma once

#include "Pared.h"

class Vector2D;

class Caja{ //Útil para las hit-box
	friend class Interaccion;
public:
	Caja();
	Caja(Vector2D vert1, Vector2D vert2); //Construye la caja a partir de los dos vértices opuestos
	virtual ~Caja();

	void dibuja() const;
	void setParedes(Vector2D vert1, Vector2D vert2); //(Vértices opuestos)
	void setColor(ColorRGB cInf, ColorRGB cSup, ColorRGB cIzq, ColorRGB cDcha);

private:
	Pared _inf;
	Pared _sup;
	Pared _izq;
	Pared _dcha;

	Vector2D _lim1 = 0, _lim2 = 0;
};