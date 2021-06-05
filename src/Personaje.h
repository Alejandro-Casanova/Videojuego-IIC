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

	virtual bool dispara();
	virtual bool recibeHerida(float daño); //Devuelve true si se ha producido la muerte

	
	float getShotDamage() const { return _shotDamage; }
	float getShootSpeed() const { return _shootSpeed; }
	float getBulletSpeed() const { return _bulletSpeed; }
	float getHealthCounter() const { return _healthCounter; }

protected:
	
	float _healthCounter = 2.0f; //Contador de salud
	float _speedStat = 10.0f; //Velocidad de desplazamiento
	float _shootSpeed = 1.0f; //Segundos entre disparos
	float _shootCounter = 0.0f; //Contador para controlar la frecuencia de disparo
	float _shotDamage = 1.0f;
	float _bulletSpeed = 15.0f;
};

