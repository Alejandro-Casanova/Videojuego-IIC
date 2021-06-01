#include "Room.h"
#include <iostream>
#include <fstream>
#include "freeglut.h"
#include "Interaccion.h"
#include "ETSIDI.h"
#include "Player.h"
#include "Objeto.h"

Room::Room()
{

}

Room::~Room()
{
	//Libera la memoria
	for (auto i : _enemigos) {
		delete i;
	}

	for (auto i : _objetos) {
		delete i;
	}

	for (auto i : _obstaculos) {
		delete i;
	}
}

void Room::mueve()
{

	//Colision jugador con paredes y obstaculos
	Interaccion::rebote(*_player_ptr, _paredes);
	for (auto& c : _obstaculos) {
		Interaccion::rebote(*_player_ptr, *c);
	}

	//Movimiento enemigos
	for (auto &i : _enemigos) {
		i->mueve(0.025f);
	}

	//Colisiones enemigos con paredes y obstáculos
	for (auto &i : _enemigos) {
		Interaccion::rebote(*i, _paredes);
		for (auto &c : _obstaculos) {
			Interaccion::rebote(*i, *c);
		}
	}
}

void Room::dibujaHitBox() const
{
	//Dibuja las lineas blancas (provisional)
	_paredes.dibuja();
	
}

void Room::dibuja() const
{
	for (auto i : _enemigos) {
		i->dibuja();
	}

	for (auto i : _objetos) {
		i->dibuja();
	}

	for (auto i : _obstaculos) {
		i->dibuja();
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

	_player_ptr = pptr;
	setRoom();
	for (auto i : _enemigos) {
		i->inicializa();
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
	/*for (auto i : _layout) {
		std::cout << i << std::endl;
	}*/
}

void Room::cargaTextura(const char* ruta_de_textura)
{
	_textura = ETSIDI::getTexture(ruta_de_textura);
}

void Room::setRoom()
{
	int i = 0, j = 0;

	//Para facilitar el dibujado se sitúa el origen en la esquina superior izquierda
	Vector2D origen(-_ancho / 2.0f, +_alto / 2.0f - TILE_WIDTH);//10 es el ancho (magic number)
	for (auto str : _layout) {
		for (auto chr : str) {
			//std::cout << chr;
			if (chr == 'R') {
				_obstaculos.emplace_back(new Roca(origen + Vector2D(10.0f * j, -10.0f * i)));
			}
			else if (chr == 'H') {
				_obstaculos.emplace_back(new Hueco(origen + Vector2D(10.0f * j, -10.0f * i)));
			}
			else if (chr == 'F') {
				_enemigos.emplace_back(new Fatty(origen+Vector2D(10.0f * j, -10.0f * i), _player_ptr));
			}
			else if (chr == 'C') {
				_enemigos.emplace_back(new Caca(origen + Vector2D(10.0f * j, -10.0f * i), _player_ptr));
			}
			else if (chr == 'L') {
				_objetos.emplace_back(Factoria::create(Objeto::obj_t::LLAVE, origen + Vector2D(10.0f * j, -10.0f * i)));
			}
			else if (chr == 'S') {
				_objetos.emplace_back(Factoria::create(Objeto::obj_t::CORAZON, origen + Vector2D(10.0f * j, -10.0f * i)));
			}
			else if (chr == 'M') {
				_objetos.emplace_back(Factoria::create(Objeto::obj_t::MONEDA, origen + Vector2D(10.0f * j, -10.0f * i)));
			}
				j++;
			}
			j = 0;
			//std::cout << std::endl;
			i++;
		}
	}


void Room::setParedes(float ancho, float alto)
{
	_paredes.setParedes(Vector2D(-ancho / 2.0f, -alto / 2.0f), Vector2D(ancho / 2.0f, alto / 2.0f));
}

void Room::gestionarDisparos(ListaProyectil& listaP) {

	//PAREDES
	Proyectil* auxc = listaP.colision(_paredes);
	if (auxc != 0) listaP.eliminar(auxc);

	//ENEMIGOS
	for (int j = _enemigos.size() - 1; j >= 0; j--) {
		Proyectil* auxi = listaP.impacto(*_enemigos[j]);
		if (auxi != 0) {
			listaP.eliminar(auxi);
			delete _enemigos[j];
			_enemigos.erase(_enemigos.begin() + j);
		}
	}

	//OBSTACULOS
	for (auto o : _obstaculos) {
		Proyectil* auxi = listaP.impacto(*o);
		if (auxi != 0) {
			listaP.eliminar(auxi);
		}
	}
}