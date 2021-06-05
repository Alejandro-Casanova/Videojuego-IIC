#pragma once

#include "Personaje.h"
#include <ETSIDI.h>
#include "Caja.h"
#include <vector>
#include "GestorSprites.h"
#include "Macros.h"
class Player;
class ListaProyectil;

//CLASE ENEMIGO GENÉRICA///////////////////////////////////////////////////

class Enemigo : public Personaje
{
	friend class Interaccion;
public:
	Enemigo(Vector2D posicion, Player* playerPtr); //Almacena posicion y un puntero al jugador
	virtual ~Enemigo();

	virtual void dibuja() override = 0;
	void inicializa() override;
	virtual bool puedeDisparar() override;
	
	float getMeleeDamage() const { return _meleeDamage; }

protected:
	Vector2D _dims{ 13.0f, 13.0f }; //Dimensiones del sprite
	void follow(Entidad* ptr); //Modifica la velocidad del enemigo para seguir a una entidad genérica (a menudo será el jugador)
	void mov_erratico();
	float intervalo;			//valor de apoyo para el intervalo entre movimientos u acciones de un enemigo
	Entidad* _playerPtr = nullptr; //Almacena un puntero al jugador para poder seguirlo
	bool _dispara; //Indica si el enemigo dispara
	float _meleeDamage = 1.0f;
	

};

class EnemigoA : public Enemigo { //Tiene un único sprite
public:
	EnemigoA(Vector2D posicion, Player* playerPtr, const char* ruta_de_textura);
	virtual void dibuja() override = 0;
protected:
	ETSIDI::Sprite _sprite;
};

class EnemigoB : public Enemigo { //Tiene una secuencia de sprites para el cuerpo y una para la cabeza
public:
	EnemigoB(Vector2D posicion, Player* playerPtr, const char* ruta_body, int body_sprite_cols, const char* ruta_head, int head_sprite_cols);
	virtual void dibuja() override = 0;
protected:
	ETSIDI::SpriteSequence _head, _body;
};

class Caca : public EnemigoA {
public:
	Caca(Vector2D pos, Player* const playerPtr);
	virtual ~Caca();

	virtual void dibuja() override;
	virtual void mueve(float t) override;

private:
};

class Fatty : public EnemigoA {
public:
	Fatty(const Vector2D pos, Player* const PlayerPtr);
	virtual ~Fatty();

	virtual void dibuja() override;
	virtual void mueve(float t) override;

private:
};



///BOSS GUSANO////////////////////////////////////////////////////////////////////

class BossGusano : public Enemigo {
	

	//SUBCLASE MÓDULO
	class Modulo : public Entidad{
	public:
		Modulo() { 
			GestorSprites::dimensionaSprite(29, 26, TILE_WIDTH, _sprite); 
			GestorSprites::dimensionaSprite(29, 26, TILE_WIDTH, _spriteRojo);
			_radio = 4.0f;
		}
		void dibuja() override{
			Entidad::dibujaHitbox();
			
			if (_contador > T_INVULNERABLE) {
				_sprite.setPos(_posicion.x, _posicion.y);
				_sprite.draw();
			}
			else {
				_spriteRojo.setPos(_posicion.x, _posicion.y);
				_spriteRojo.draw();
			}
		}
		void mueve(float t) override {
			_contador += t;
			Entidad::mueve(t);
			if (_contador > T_INVULNERABLE)
				_sprite.loop();
			else
				_spriteRojo.loop();
		}
		bool recibeHerida(float damage) { 
			_contador = 0;
			_salud -= damage;
			if (_salud <= 0) return true;
			return false;
		}
		void avanza(Vector2D desplazamiento) { _posicion += desplazamiento; }
		float getSalud() const { return _salud; }
	private:
		float _salud = (SALUD_MAX / N_MODULOS);
		float _contador = T_INVULNERABLE; //Se usa para la animación del daño recibido
		ETSIDI::SpriteSequence _sprite{ "res/texturas/boss/gusano_body.png", 2 , 1, 75};
		ETSIDI::SpriteSequence _spriteRojo{ "res/texturas/boss/gusano_body_r.png", 2 , 1, 75 };
	};
public:
	BossGusano(Player* playerPtr);

	void dibuja() override;
	void mueve(float t, Caja& cajaRoom); //El gusano se desplaza aleatoriamente por la room NOTA: NO SOBREESCRIBE LA FUNCION "MUEVE" DE ENEMIGO
	void mueveCadena(); //Se encarga del movimiento relativo entre los módulos del robot
	bool recibeHerida(float damage) override; //Devuelve true al morir el boss
	bool gestionarDisparos(ListaProyectil& listaP); //Gestiona los disparos con los módulos del boss, devuelve true al destruir alguno
	bool rebote(Player& player); //Gestiona la colision de los módulos con el jugador
private:
	ETSIDI::SpriteSequence _head{ "res/texturas/boss/gusano_cabeza.png", 6 , 1, 75};
	ETSIDI::SpriteSequence _headRoja{ "res/texturas/boss/gusano_cabeza_r.png", 6 , 1, 75 };
	std::vector<Modulo> _modulos;
	float _contador = T_INVULNERABLE; //Se usa para la animación del daño recibido
	float _contadorRoar = T_ROAR; //Controla el rugido del boss


};