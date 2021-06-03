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

Room::Room(float indice, const char* ruta_de_textura) : _indice(indice), _sprite{ruta_de_textura}
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
		if (Interaccion::rebote(*_player_ptr, *i))
			if (_player_ptr->recibeHerida(i->getMeleeDamage()))
				muerte();
	}

	Room::disparos();
	disparosEnemigos.mueve(T_CONST);
}

void Room::dibujaHitBox() const
{
	//Dibuja las lineas blancas (provisional)
	_paredes.dibuja();
	
}

void Room::dibuja()
{
	//_puerta.dibuja();
	for (auto i : _puertas) {
		i->dibuja();
	}

	for (auto i : _enemigos) {
		i->dibuja();
	}

	for (auto i : _objetos) {
		i->dibuja();
	}

	for (auto i : _obstaculos) {
		i->dibuja();
	}
  
	_sprite.draw();

	disparosEnemigos.dibuja();
	Room::gestionarDisparos(disparosEnemigos);
}

void Room::inicializa(const char* ruta_de_layout, Player* pptr)
{
	setParedes(_ancho, _alto);
	cargaLayout(ruta_de_layout);

	_player_ptr = pptr;
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

void Room::disparos() {
	for (auto i : _enemigos){
		if (i->dispara()) {		//Indica si el enemigo está listo para disparar
		// Creacion de un proyectil
			Proyectil* d = new Proyectil();
			//	proyectil.setOrigen(Vector2D.player)
			Vector2D pos = i->getPos();
			d->setPos(pos.x, pos.y);
			d->setColor(200, 20, 20);
			disparosEnemigos.agregar(d);
			Vector2D target = _player_ptr->getPos() - pos;
			Vector2D dir = target.unitario();
			d->setVel(15*dir.x , 15*dir.y);
		}
	}
}

void Room::addPuerta(Puerta* newPuerta)
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
	exit(0);
}

void Room::gestionarDisparos(ListaProyectil& listaP) {


	if (listaP.isFriend()) {	//Interacciones de Proyectiles del Player
		//ENEMIGOS
		for (int j = _enemigos.size() - 1; j >= 0; j--) {
			Proyectil* auxi = listaP.impacto(*_enemigos[j]);
			if (auxi != 0) {
				listaP.eliminar(auxi);
				if (_enemigos[j]->recibeHerida(_player_ptr->getShotDamage())) {
					delete _enemigos[j];
					_enemigos.erase(_enemigos.begin() + j);
				}
			}
		}
	}
	else{	//Interacciones de los Proyectiles de los Enemigos
		Proyectil* auxi = listaP.impacto(*_player_ptr);
		if (auxi != 0) {
			listaP.eliminar(auxi);
			if (_player_ptr->recibeHerida(1)) { //VALOR PROVISIONAL, incluir informacion de daño en los disparos???
				muerte();
			}
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

Puerta* Room::puertaActual()
{
	for (auto& c : _puertas) {
		if (Interaccion::colision(*_player_ptr, c->getHitBox()))
			return c;
	}
	return nullptr;
}
