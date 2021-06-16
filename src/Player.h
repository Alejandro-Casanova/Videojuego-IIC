#pragma once

#include "Personaje.h"
#include "ETSIDI.h"
#include "Objeto.h"
class Proyectil;


class Player : public Personaje
{
public:
	Player();
	virtual ~Player();

	void tecla();
	void teclaEspecial();

	virtual void dibuja() override;
	void inicializa() override;
	void inicializaStats(); //Devuelve las stats a sus valores por defecto
	virtual void mueve(float) override;

	virtual bool recibeHerida(float damage) override;
	void sonidoMuerte() override;
	bool recibeObjeto(Objeto& obj);
	void recibeBonus(const Bonus& bon);
	void dibujaBonus(int x, int y) const; //Dibuja un indicador de qué tipo de bonus se ha recibido, esta función será empleada por la GUI
	virtual Proyectil* dispara();  //Devuelve un proyectil si se produce el disparo, en caso contrario devuelve nullptr

	Vector2D getHealth() const { return Vector2D{ _healthCounter, _healthStat }; }
	int getLlaves() const { return _llaves; }
	int getDinero() const { return _dinero; }
	void flipPos(bool H, bool V);
private:
	float _healthStat = SALUD_JUGADOR; //Salud Máxima
	int _llaves = 0;
	int _dinero = 0;
	float _damageTimer = 0; //Controla el umbral de invulnerabilidad del jugador tras recibir daño
	float _bonusTimer = 0; //Controla la animación de recibir un bonus
	ETSIDI::SpriteSequence _body{ "res/texturas/isaac/body_sequence_full.png", 10, 2 };
	ETSIDI::SpriteSequence _head{ "res/texturas/isaac/head_sequence.png", 8 };
	ETSIDI::SpriteSequence _especial{ "res/texturas/isaac/especial.png", 3 };
	Bonus::TIPO _ultimoBonus = Bonus::TIPO::DAMAGE;
};

