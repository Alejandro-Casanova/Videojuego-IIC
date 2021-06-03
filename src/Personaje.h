#pragma once

#include "Vector2D.h"
#include "freeglut.h"
#include "Entidad.h"

class Personaje : public Entidad
{
public:
	Personaje();
	virtual ~Personaje();

	virtual void dibuja() override = 0; //Personaje es una clase abstracta
	void inicializa() override;
	virtual void mueve(float) override;

	bool dispara();
	virtual bool recibeHerida(int daño); //Devuelve true si se ha producido la muerte

	Vector2D getHealth () const { return Vector2D{ _healthCounter, _healthStat }; }
	float getShotDamage() const { return _shotDamage; }
	float getMeleeDamage() const { return _meleeDamage; }

protected:
	float _healthStat = 2.0f; //Salud Máxima
	float _healthCounter = 2.0f; //Contador de salud
	float _speedStat = 10.0f; //Velocidad de desplazamiento
	float _shootSpeed = 1.0f; //Segundos entre disparos
	float _shootCounter = 0.0f; //Contador para controlar la frecuencia de disparo
	float _meleeDamage = 1.0f;
	float _shotDamage = 1.0f;
};

