#include "Room.h"
#include <iostream>
#include <fstream>
#include "freeglut.h"
#include "Interaccion.h"
#include "ETSIDI.h"
#include "Player.h"
#include "Objeto.h"
#include "GestorDeTeclado.h"
#include "Macros.h"
#include "Enemigo.h"

Room::Room(float indice, const char* ruta_de_textura, Player* playerPtr, ROOM_TYPE tipo) 
	: _indice(indice), _sprite{ruta_de_textura}, _playerPtr(playerPtr), _tipo(tipo)
{
	_sprite.setPos(0, 0);
	GestorSprites::dimensionaSprite(468, 285, _ancho + 2.0f * ROOM_BORDE_TEXTURA, _sprite); //Se ha estrechado un poco la textura para adaptarla a l hitbox de la habitacion
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

	for (auto i : _puertas) {
		delete i;
	}
}

void Room::mueve()
{
	if (_puertasAbiertas && !_enemigos.empty()) {
		for (auto& i : _puertas) i->close();
		_puertasAbiertas = false;
		ETSIDI::play("res/audio/door_close.wav");
	}
	if (_enemigos.empty() && !_puertasAbiertas) { //Se abren las puertas al morir todos los enemigos
		for (auto& i : _puertas) i->open();
		_puertasAbiertas = true;
		ETSIDI::play("res/audio/door_open.wav");
	}

	//Colision jugador con paredes y obstaculos
	Interaccion::rebote(*_playerPtr, _paredes);
	for (auto& c : _obstaculos) {
		Interaccion::rebote(*_playerPtr, *c);
	}

	//Movimiento enemigos
	for (auto &i : _enemigos) {
		i->mueve(T_CONST);
	}

	//Colisiones enemigos con paredes y obstáculos
	for (auto &i : _enemigos) {
		Interaccion::rebote(*i, _paredes);
		for (auto &c : _obstaculos) {
			Interaccion::rebote(*i, *c);
		}
	}

	//Colisiones entre los enemigos
	if (!_enemigos.empty()) {
		for (int i = 0; i < _enemigos.size() - 1; i++) {
			for (int j = i + 1; j < _enemigos.size(); j++) {
				Interaccion::rebote(*_enemigos[i], *_enemigos[j]);
			}
		}
	}

	//Colisiones del jugador con los enemigos y DAÑO melee
	for (auto& i : _enemigos) {
		if (Interaccion::rebote(*_playerPtr, *i))
			if (_playerPtr->recibeHerida(i->getMeleeDamage()))
				muerte();
	}

	Room::disparos();
	disparosEnemigos.mueve(T_CONST);
	Room::gestionarDisparos(disparosEnemigos);
}

void Room::dibujaHitBox() const
{
	//Dibuja las lineas blancas (provisional)
	_paredes.dibuja();
	
}

void Room::dibuja()
{

	disparosEnemigos.dibuja();


	for (auto i : _enemigos) {
		i->dibuja();
	}

	for (auto i : _objetos) {
		i->dibuja();
	}

	for (auto i : _obstaculos) {
		i->dibuja();
	}


	for (auto i : _puertas) {
		i->dibuja();
	}
  
	_sprite.draw();


}

void Room::inicializa(const char* ruta_de_layout)
{
	setParedes(_ancho, _alto);
	cargaLayout(ruta_de_layout);

	setRoom();
	for (auto i : _enemigos) {
		i->inicializa();
	}
	disparosEnemigos.setFriendly(false);
}

void Room::cargaLayout(const char* ruta_de_archivo)
{
	std::ifstream file;
	file.open(ruta_de_archivo);

	//Comprobación (ruta de archivo válida)
	if (file.fail()) {
		std::cerr << "No se pudo abrir el archivo: " << ruta_de_archivo << "\n";
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
				_enemigos.emplace_back(new Fatty(origen+Vector2D(10.0f * j, -10.0f * i), _playerPtr, this));
			}
			else if (chr == 'A') {
				_enemigos.emplace_back(new Mosca(origen + Vector2D(10.0f * j, -10.0f * i), _playerPtr, this));
			}
			else if (chr == 'N') {
				_enemigos.emplace_back(new Naranja(origen + Vector2D(10.0f * j, -10.0f * i), _playerPtr, this));
			}
			else if (chr == 'E') {
				_enemigos.emplace_back(new Esqueleto(origen + Vector2D(10.0f * j, -10.0f * i), _playerPtr, this));
			}
			else if (chr == 'W') {
				_enemigos.emplace_back(new Weeper(origen + Vector2D(10.0f * j, -10.0f * i), _playerPtr, this));
			}
			else if (chr == 'C') {
				_enemigos.emplace_back(new Caca(origen + Vector2D(10.0f * j, -10.0f * i), _playerPtr, this));
			}
			else if (chr == 'Z') {
				_enemigos.emplace_back(new Zombie(origen + Vector2D(10.0f * j, -10.0f * i), _playerPtr, this));
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

void Room::disparos() {
	for (auto i : _enemigos){
		//if (i->puedeDisparar()) {		//Indica si el enemigo está listo para disparar
		//// Creacion de un proyectil
		//	Proyectil* d = new Proyectil();
		//	//	proyectil.setOrigen(Vector2D.player)
		//	Vector2D pos = i->getPos();
		//	d->setPos(pos.x, pos.y);
		//	d->setColor(200, 20, 20);
		//	disparosEnemigos.agregar(d);
		//	Vector2D target = _playerPtr->getPos() - pos;
		//	Vector2D dir = target.unitario();
		//	d->setVel(15*dir.x , 15*dir.y);
		//}
		auto aux = i->dispara();
		if (aux != nullptr) disparosEnemigos.agregar(aux);
	}
}

void Room::addPuerta(PuertaRoom* newPuerta)
{
	_puertas.push_back(newPuerta);
}


void Room::setParedes(float ancho, float alto)
{
	_paredes.setParedes(Vector2D(-ancho / 2.0f, -alto / 2.0f), Vector2D(ancho / 2.0f, alto / 2.0f));
}

void Room::muerte()
{
	
	std::cout << "\n\n\nMORISTEEEEEEEEEEEEEEEEEEEEEEE\n\n\n"; //PROVISIONAL
	
	//exit(0);
}

void Room::gestionarDisparos(ListaProyectil& listaP) {


	if (listaP.isFriend()) {	//Interacciones de Proyectiles del Player
		//ENEMIGOS
		for (int j = _enemigos.size() - 1; j >= 0; j--) {
			Proyectil* auxi = listaP.impacto(*_enemigos[j]);
			if (auxi != 0) {
				listaP.eliminar(auxi);
				if (_enemigos[j]->recibeHerida(_playerPtr->getShotDamage())) {
					delete _enemigos[j];
					_enemigos.erase(_enemigos.begin() + j);
				}
			}
		}
	}
	else{	//Interacciones de los Proyectiles de los Enemigos
		Proyectil* auxi = listaP.impacto(*_playerPtr);
		if (auxi != 0) {
			if (_playerPtr->recibeHerida(auxi->getDamage())) {
				muerte();
			}
			listaP.eliminar(auxi);
		}
	}

	//PAREDES
	Proyectil* auxc = listaP.colision(_paredes);
	if (auxc != 0) listaP.eliminar(auxc);


	//OBSTACULOS
	for (auto o : _obstaculos) {
		Proyectil* auxi = listaP.impacto(*o);
		if (auxi != 0) {
			listaP.eliminar(auxi);
		}
	}
}

PuertaRoom* Room::puertaActual()
{
	for (auto& c : _puertas) {
		if (Interaccion::colision(*_playerPtr, c->getHitBox()))
			return c;
	}
	return nullptr;
}

BossRoom::BossRoom(float indice, const char* ruta_de_textura, Player* playerPtr) 
	: Room(indice, ruta_de_textura, playerPtr, ROOM_TYPE::BOSS), _gusano{ new BossGusano(playerPtr, this) }, _trampilla(Vector2D(0.0f, 0.0f))
{
	_enemigos.emplace_back(_gusano);
}
BossRoom::~BossRoom() {
	//if (_gusano != nullptr) delete _gusano;
}

void BossRoom::dibuja()
{
	//if (_gusano != nullptr) _gusano->dibuja();
	if (_trampilla.isOpen()) _trampilla.dibuja();
	Room::dibuja();
	
	
}

void BossRoom::mueve()
{
	if (_enemigos.empty() && _gusano != nullptr) {
		_gusano = nullptr;
		ETSIDI::play("res/audio/victory.wav");
		_trampilla.open();
	}

	else if (_gusano != nullptr) {
		_gusano->mueve(T_CONST, _paredes); // Movimiento del gusano
		if (_gusano->rebote(*_playerPtr)){ //Gusano tiene una funcion interna para gestionar la colision con todos sus módulos
			if (_playerPtr->recibeHerida(_gusano->getMeleeDamage())) { //Daño al jugador
				muerte();
			}
		}
	}
	Room::mueve();
	
}

void BossRoom::gestionarDisparos(ListaProyectil& listaP)
{
	Room::gestionarDisparos(listaP);
	if (_gusano != nullptr) { //Si el gusano sigue vivo
		_gusano->gestionarDisparos(listaP);
	}
}

bool BossRoom::juntoTrampilla()
{
	
	if (Interaccion::colision(*_playerPtr, _trampilla.getHitBox()) && _trampilla.isOpen())
		return true;
	
	return false;
}

