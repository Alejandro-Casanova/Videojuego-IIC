#pragma once

#include "Pared.h"
#include <vector>
#include <string>
#include "ETSIDI.h"

class Room
{
public:
	Room();
	Room(const char* ruta_de_archivo, const char* ruta_de_textura);
	void mueve();
	void dibuja();

	void inicializa();
	void cargaLayout(const char* ruta_de_archivo);
	void cargaTextura(const char* ruta_de_textura);

private:
	float _ancho = 130;
	float _alto = 70;
	float _bordeText = 10.0f;
	Pared _pared_izq, _pared_sup, _pared_der, _pared_inf;
	//Dimensiones de la habitación 7x13
	std::vector<std::string> _layout;
};

