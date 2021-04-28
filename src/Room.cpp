#include "Room.h"
#include <iostream>
#include <fstream>
#include "freeglut.h"
#include "ETSIDI.h"

Room::Room()
{

}

void Room::mueve()
{

}

void Room::dibuja()
{
	//Dibuja las lineas blancas (provisional)
	_pared_izq.dibuja();
	_pared_sup.dibuja();
	_pared_der.dibuja();
	_pared_inf.dibuja();
	
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("res/texturas/Basement1.png").id);
	glBindTexture(GL_TEXTURE_2D, _textura.id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex3f(-_ancho / 2.0f - _bordeText, _alto/2.0f + _bordeText, 0.0f);
	glTexCoord2d(1, 1); glVertex3f(_ancho / 2.0f + _bordeText, _alto / 2.0f + _bordeText, 0.0f);
	glTexCoord2d(1, 0); glVertex3f(_ancho / 2.0f + _bordeText, -_alto / 2.0f - _bordeText, 0.0f);
	glTexCoord2d(0, 0); glVertex3f(-_ancho / 2.0f - _bordeText, -_alto / 2.0f - _bordeText, 0.0f);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void Room::inicializa(const char* ruta_de_layout, const char* ruta_de_textura)
{
	setParedes(_ancho, _alto);
	cargaLayout(ruta_de_layout);
	cargaTextura(ruta_de_textura);
}

void Room::cargaLayout(const char* ruta_de_archivo)
{
	std::ifstream file;
	file.open(ruta_de_archivo);

	//Comprobación
	if (file.fail()) {
		std::cout << "No se pudo abrir el archivo: " << ruta_de_archivo << "\n";
		exit(0);
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

void Room::cargaTextura(const char* ruta_de_textura)
{
	_textura = ETSIDI::getTexture(ruta_de_textura);
}

void Room::setParedes(float ancho, float alto)
{
	_pared_izq.setLimites(-ancho / 2.0f, -alto / 2.0f, -ancho / 2.0f, alto / 2.0f);
	_pared_sup.setLimites(-ancho / 2.0f, alto / 2.0f, ancho / 2.0f, alto / 2.0f);
	_pared_der.setLimites(ancho / 2.0f, alto / 2.0f, ancho / 2.0f, -alto / 2.0f);
	_pared_inf.setLimites(-ancho / 2.0f, -alto / 2.0f, ancho / 2.0f, -alto / 2.0f);
}
