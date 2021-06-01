#pragma once

#include "Pared.h"
#include <vector>
#include <string>
#include "ETSIDI.h"
#include <Caja.h>
#include "Obstaculo.h"
#include "Enemigo.h"
#include "Interaccion.h"
#include "ListaProyectil.h"
#include "Macros.h"



class Entidad;
class Enemigo;
class Objeto;
class Player;

class Room
{
	friend class ListaProyectil;

public:
	Room();
	~Room();
	void mueve();
	void dibuja() const;
	void dibujaHitBox() const;

	void inicializa(const char* ruta_de_layout, const char* ruta_de_textura, Entidad* pptr);
	void cargaLayout(const char* ruta_de_archivo);
	void cargaTextura(const char* ruta_de_textura);
	
	void setRoom(); //Inicializa Obstáculos, Enemigos, etc...

	void setParedes(float ancho, float alto);
	void setAncho(float ancho) { _ancho = ancho; }
	void setAlto(float alto) { _alto = alto; }
	void setBordeText(float bordeText) { _bordeText = bordeText; }

	void gestionarDisparos(ListaProyectil& listaP); //Colisiones de los proyectiles con diferentes elementos de la room

private:
	float _ancho = 130;
	float _alto = 70;
	float _bordeText = 15.0f; //Ancho de la textura que queda detrás de la hit-box de la pared

	Caja _paredes; //Hit-box de las paredes
	Vector2D origen=(-_ancho / 2.0f, +_alto / 2.0f - 10.0f);

	Entidad* _player_ptr = nullptr;
	std::vector<std::string> _layout; //Dimensiones de la habitación 7x13
	std::vector<Obstaculo*> _obstaculos;
	std::vector<Enemigo*> _enemigos;
	std::vector<Objeto*> _objetos;
	ETSIDI::GLTexture _textura = { 0, 0, 0 };
	
};

