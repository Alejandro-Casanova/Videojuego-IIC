#include "Room.h"
#include <iostream>
#include <fstream>
#include "freeglut.h"
#include "Interaccion.h"
#include "ETSIDI.h"

Room::Room()
{

}

Room::~Room()
{
}

void Room::mueve()
{
	Interaccion::rebote(*_personaje_ptr, _paredes);
	for (auto& c : _obstaculos) {
		Interaccion::rebote(*_personaje_ptr, c);
	}
}

void Room::dibujaHitBox() const
{
	//Dibuja las lineas blancas (provisional)
	_paredes.dibuja();
	for (auto i : _obstaculos) {
		i.dibuja();
	}
}

void Room::dibuja() const
{
	for (auto i : _enemigos) {
		i.dibuja();
	}

	glEnable(GL_TEXTURE_2D);
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

void Room::inicializa(const char* ruta_de_layout, const char* ruta_de_textura, Entidad* pptr)
{
	setParedes(_ancho, _alto);
	cargaLayout(ruta_de_layout);
	cargaTextura(ruta_de_textura);
	_personaje_ptr = pptr;
	setObstaculos();
	for (auto i : _enemigos) {
		i.inicializa();
	}
}

void Room::cargaLayout(const char* ruta_de_archivo)
{
	std::ifstream file;
	file.open(ruta_de_archivo);

	//Comprobación (ruta de archivo válida)
	if (file.fail()) {
		std::cout << "No se pudo abrir el archivo: " << ruta_de_archivo << "\n";
		exit(0);
	}

	//Registra el layout de la habitación desde el archivo
	std::string temp;
	while (std::getline(file, temp)) {
		_layout.emplace_back(temp);
	}

	//Comprobación por terminal
	for (auto i : _layout) {
		std::cout << i << std::endl;
	}
}

void Room::cargaTextura(const char* ruta_de_textura)
{
	_textura = ETSIDI::getTexture(ruta_de_textura);
}

void Room::setObstaculos()
{
	int i = 0, j = 0;

	//Para facilitar el dibujado se sitúa el origen en la esquina superior izquierda
	Vector2D origen(-_ancho / 2.0f, +_alto / 2.0f - 10.0f);//10 es el ancho (magic number)
	for (auto str : _layout) {
		for (auto chr : str) {
			std::cout << chr;
			if (chr == 'R') {
		
			
				_obstaculos.emplace_back(Obstaculo(origen + Vector2D(10.0f * j, -10.0f * i), "res/texturas/rocas.png"));
				
			}
			else if (chr == 'H') {
				_obstaculos.emplace_back(Obstaculo(origen + Vector2D(10.0f * j, -10.0f * i), "res/texturas/hole.png"));
			}

			else if (chr == 'E') {
				_enemigos.emplace_back(Enemigo(origen+Vector2D(10.0f * j, -10.0f * i)));
			}


				j++;
			}
			j = 0;
			std::cout << std::endl;
			i++;
		}
	}


void Room::setParedes(float ancho, float alto)
{
	_paredes.setParedes(Vector2D(-ancho / 2.0f, -alto / 2.0f), Vector2D(ancho / 2.0f, alto / 2.0f));
}
