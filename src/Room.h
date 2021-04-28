#pragma once

#include "Pared.h"
#include <vector>
#include <string>
#include "ETSIDI.h"

class Room
{
public:
	Room();
	void mueve();
	void dibuja();

	void inicializa(const char* ruta_de_layout, const char* ruta_de_textura);
	void cargaLayout(const char* ruta_de_archivo);
	void cargaTextura(const char* ruta_de_textura);

	void setParedes(float ancho, float alto);
	void setAncho(float ancho) { _ancho = ancho; }
	void setAlto(float alto) { _alto = alto; }
	void setBordeText(float bordeText) { _bordeText = bordeText; }

private:
	float _ancho = 130;
	float _alto = 70;
	float _bordeText = 10.0f; //Ancho de la textura que queda detrás de la hit-box de la pared
	Pared _pared_izq, _pared_sup, _pared_der, _pared_inf;
	
	std::vector<std::string> _layout; //Dimensiones de la habitación 7x13
	ETSIDI::GLTexture _textura = { 0, 0, 0 };
};

