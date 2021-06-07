#pragma once

#include "Vector2D.h"
#include "Entidad.h"
#include <ETSIDI.h>

class Proyectil : public Entidad
{
	friend class Interaccion;
public:
	Proyectil();
	virtual ~Proyectil();

	virtual void dibuja() override;
	void inicializa() override;
	void setOrigen(float ox, float oy);
	int getDamage() const { return _damage; }
protected:
	int _damage = 1;
	Vector2D _origen;
	float distancia = 0.0f;			// longitud que recorre un disparo desde el origen
};

class Hueso : public Proyectil {
public:
	Hueso();
	void dibuja() override;
	void mueve(float t) override;
private:
	ETSIDI::Sprite _sprite{ "res/texturas/enemigos/bone.png" };

};

