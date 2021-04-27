#pragma once

#include "Pared.h"
#include <vector>
#include <string>
#include "ETSIDI.h"
#include "freeglut.h"

class Room
{
public:
	Room();
	Room(const char* ruta_de_archivo);
	void mueve();
	void dibuja();

	void inicializa();
	void cargaLayout(const char* ruta_de_archivo);

private:
	float _ancho = 130;
	float _alto = 70;
	Pared _pared_izq, _pared_sup, _pared_der, _pared_inf;
	//Dimensiones de la habitación 7x13
	std::vector<std::string> _layout;
	//GLtextura _textura;
};

