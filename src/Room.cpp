#include "Room.h"
#include <iostream>
#include <fstream>
#include "freeglut.h"

Room::Room()
{
	inicializa();
}

Room::Room(const char* ruta_de_archivo)
{
	cargaLayout(ruta_de_archivo);
	inicializa();
}

void Room::mueve()
{

}

void Room::dibuja()
{
	_pared_izq.dibuja();
	_pared_sup.dibuja();
	_pared_der.dibuja();
	_pared_inf.dibuja();
}

void Room::inicializa()
{
	_pared_izq.setLimites(-_ancho / 2.0f, -_alto / 2.0f, -_ancho / 2.0f, _alto / 2.0f);
	_pared_sup.setLimites(-_ancho / 2.0f, _alto / 2.0f, _ancho / 2.0f, _alto / 2.0f);
	_pared_der.setLimites(_ancho / 2.0f, _alto / 2.0f, _ancho / 2.0f, -_alto / 2.0f);
	_pared_inf.setLimites(-_ancho / 2.0f, -_alto / 2.0f, _ancho / 2.0f, -_alto / 2.0f);
}

void Room::cargaLayout(const char* ruta_de_archivo)
{
	std::ifstream file;
	file.open(ruta_de_archivo);

	//Comprobación
	if (file.fail()) {
		std::cout << "No se pudo abrir el archivo: " << ruta_de_archivo << "\n";
		glutLeaveMainLoop();
	}

	//Registra el layout de la habitación desde el archivo
	std::string temp;
	while (std::getline(file, temp)) {
		_layout.emplace_back(temp);
	}

	//Comprobación
	for (auto i : _layout) {
		std::cout << i << std::endl;
	}
}
