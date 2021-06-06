#pragma once

#include "Personaje.h"
#include <ETSIDI.h>
#include "Caja.h"
#include <vector>
#include "GestorSprites.h"
#include "Macros.h"
class Player;
class ListaProyectil;
class Proyectil;
class Room;

//CLASE ENEMIGO GENÉRICA///////////////////////////////////////////////////

class Enemigo : public Personaje
{
	friend class Interaccion;
public:
	Enemigo(Vector2D posicion, Player* playerPtr, Room* roomPtr); //Almacena posicion y un puntero al jugador
	virtual ~Enemigo();

	virtual void dibuja() override = 0;
	void inicializa() override;
	virtual void mueve(float t) override = 0;
	
	virtual bool puedeDisparar() override;
	float getMeleeDamage() const { return _meleeDamage; }
	virtual Proyectil* dispara();

protected:
	//Funciones de Movimiento
	void follow(Entidad* ptr); //Modifica la velocidad del enemigo para seguir a una entidad genérica (a menudo será el jugador)
	void mov_erratico();
	void flee(Entidad* ptr); //Modifica la velocidad del enemigo para huir de una entidad genérica
	void stalk(Entidad* ptr, float distance); //Se mantiene a una distancia del jugador, y huye si éste se acerca demasiado
	void roam(float prob); //Se mueve aleatoriamente y rebota contra las paredes. Recibe un número entre 0.0f y 1.0f que define la probabilidad que tiene el enemigo de cambiar su trayectoria cada segundo que pasa

	float intervalo;			//valor de apoyo para el intervalo entre movimientos u acciones de un enemigo
	Entidad* _playerPtr = nullptr; //Almacena un puntero al jugador para poder seguirlo
	Room* _roomPtr = nullptr; //Almacena puntero a la room actual para gestionar colisiones y pathfinding
	bool _dispara = false; //Indica si el enemigo dispara
	float _meleeDamage = 1.0f;
	

};

class EnemigoA : public Enemigo { //Tiene un único sprite
public:
	EnemigoA(Vector2D posicion, Player* playerPtr, Room* roomPtr, const char* ruta_de_textura);
	virtual void dibuja() override;
	virtual void mueve(float t) override = 0;
protected:
	ETSIDI::Sprite _sprite;
};

class EnemigoB : public Enemigo { //Tiene una secuencia de sprites para el cuerpo y una para la cabeza
public:
	EnemigoB(Vector2D posicion, Player* playerPtr, Room* roomPtr, const char* ruta_body, int body_sprite_cols, const char* ruta_head, int head_sprite_cols, int animation_ms_step = 50, int body_sprite_rows = 2);
	virtual void dibuja() override;
	virtual void mueve(float t) override = 0;
protected:
	ETSIDI::SpriteSequence _head, _body;
	int _headAnimation = 0; //Indica el tipo de animación de la cabeza
};

class EnemigoC : public Enemigo { //Tiene un único spriteSequence
public:
	EnemigoC(Vector2D posicion, Player* playerPtr, Room* roomPtr, const char* ruta_de_textura, int sprite_cols, int spriteRows = 1, int animation_ms_step = 50);
	virtual void dibuja() override;
	virtual void mueve(float t) override = 0;
protected:
	ETSIDI::SpriteSequence _sprite;
};

// Zombie /////////
class Zombie : public EnemigoB {
public:
	Zombie(Vector2D pos, Player* playerPtr, Room* roomPtr);
	void mueve(float t) override;
private:

};

// Esqueleto ///////////////////////////////////
class Esqueleto : public EnemigoB {
public:
	Esqueleto(Vector2D pos, Player* playerPtr, Room* roomPtr);
	Proyectil* dispara() override;
	void mueve(float t) override;
private:

};

// WEEPER /////////////////////////////

class Weeper : public EnemigoB {
public:
	Weeper(Vector2D pos, Player* playerPtr, Room* roomPtr);
	void mueve(float t) override;
private:

};

// FATTY ////////////////
class Fatty : public EnemigoB {
public:
	Fatty(const Vector2D pos, Player* const PlayerPtr, Room* roomPtr);
	virtual ~Fatty();

	void mueve(float t) override;

private:
};

// NARANJA ////////////////////
class Naranja : public EnemigoC {
public:
	Naranja(Vector2D pos, Player* const playerPtr, Room* roomPtr);
	
	virtual void dibuja() override;
	virtual void mueve(float t) override;
	bool recibeHerida(float damage) override;

private:
	float _contador = 0;
	float _tFase = 1; //Tiempo entre las distintas fases del enemigo
	const int _nFases = 10;
};

// MOSCA /////////////////
class Mosca : public EnemigoC {
public:
	Mosca(Vector2D pos, Player* const playerPtr, Room* roomPtr);

	//virtual void dibuja() override;
	virtual void mueve(float t) override;

private:
};

// CACA //////////

class Caca : public EnemigoA {
public:
	Caca(Vector2D pos, Player* const playerPtr, Room* roomPtr);
	virtual ~Caca();

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
	BossGusano(Player* playerPtr, Room* roomPtr);

	void dibuja() override;
	void mueve(float t) override;
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