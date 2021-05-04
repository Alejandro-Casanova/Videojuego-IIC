#pragma once

#include "Pared.h"
#include <vector>
#include <string>
#include "ETSIDI.h"
#include <Caja.h>
#include "Obstaculo.h"

class Room
{
public:
	Room();
	~Room();
	void mueve();
	void dibuja() const;
	void dibujaHitBox() const;

	void inicializa(const char* ruta_de_layout, const char* ruta_de_textura);
	void cargaLayout(const char* ruta_de_archivo);
	void cargaTextura(const char* ruta_de_textura);
	
	void setObstaculos();

	void setParedes(float ancho, float alto);
	void setAncho(float ancho) { _ancho = ancho; }
	void setAlto(float alto) { _alto = alto; }
	void setBordeText(float bordeText) { _bordeText = bordeText; }

private:
	float _ancho = 130;
	float _alto = 70;
	float _bordeText = 12.0f; //Ancho de la textura que queda detrás de la hit-box de la pared
	Caja _paredes; //Hit-box de las paredes
	
	std::vector<std::string> _layout; //Dimensiones de la habitación 7x13
	std::vector<Obstaculo> _obstaculos;
	ETSIDI::GLTexture _textura = { 0, 0, 0 };
};

