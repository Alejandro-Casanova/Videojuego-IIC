#include "Piso.h"
#include <iostream>
#include "Player.h"
#include <fstream>
#include "ETSIDI.h"
#include <sstream>

Piso::Piso(Player* playerPtr, const char* ruta_de_layout) : _playerPtr(playerPtr)
{
	cargaLayout(ruta_de_layout);
	//inicializa();
}

Piso::~Piso() {

	//Libera la memoria
	for (auto &i : _rooms) {
		delete i;
	}

}

void Piso::mueve()
{
	_rooms[_roomActual]->mueve();
}

void Piso::dibuja()
{
	//_rooms[_roomActual]->dibujaHitBox();
	_rooms[_roomActual]->dibuja();

}

bool Piso::cambiaRoom()
{
	auto* puerta = roomActual()->puertaActual();
	if (puerta != nullptr && puerta->isOpen()) {
		roomActual()->disparosEnemigos.destruirContenido();
		setRoomActual(puerta->getNextRoom()->getIndice());

		//Reproduce música de BOSS
		if ((roomActual()->tipo() == Room::ROOM_TYPE::BOSS) && roomActual()->hayEnemigos())
			ETSIDI::playMusica("res/audio/boss_fight.mp3", true);
		

		//Invierte la posicion del jugador para que aparezca al otro lado de la puerta
		switch (puerta->getOrientacion()) {
		case PuertaRoom::ORIENTACION::DOWN:
		case PuertaRoom::ORIENTACION::UP:
			_playerPtr->flipPos(false, true);
			break;
		case PuertaRoom::ORIENTACION::LEFT:
		case PuertaRoom::ORIENTACION::RIGHT:
			_playerPtr->flipPos(true, false);
			break;
		default:
			break;	
		}
		return true;
	}
	return false;
}


void Piso::inicializa()
{
	for (auto& i : _rooms) {
		if (i != nullptr) {
			delete i;
			i = nullptr;
		}
	}
	if(!_rooms.empty()) _rooms.clear();
	//_layout.clear();
	if(!_roomLayout.empty()) _roomLayout.clear();

	setPiso();
}

void Piso::cargaLayout(const char* ruta_de_archivo)
{
	std::ifstream file;
	file.open(ruta_de_archivo);

	//Comprobación (ruta de archivo válida)
	if (file.fail()) {
		std::cerr << "No se pudo abrir el archivo: " << ruta_de_archivo << "\n";
		exit(0);
	}

	//Registra el layout de la habitación desde el archivo y comprueba el formato
	std::string temp;
	int Scounter = 0; //Contador de rooms iniciales, sólo debe haber una
	while (std::getline(file, temp)) {
		_layout.emplace_back(temp);
		for (auto i : temp) { 
			if (i == 'S') Scounter++;
		}
	}
	if (Scounter != 1) {//Comprueba que sólo hay una única room inicial
		std::cerr << "El formato del archivo " << ruta_de_archivo << " es incorrecto, solo debe haber una room inicial (S).";
		exit(0);
	}
	auto sizeCheck = _layout[0].size();
	for (auto i : _layout) {//Comprueba que el layout del piso es rectangular
		if (sizeCheck != i.size()) {
			std::cout << "El layout del piso debe ser rectangular. Archivo: " << ruta_de_archivo;
			exit(0);
		}
	}

	//Comprobación por terminal
	/*for (auto i : _layout) {
		std::cout << i << std::endl;
	}*/
}

void Piso::setPiso()
{
	//CONFIGURA EL MAPA 2D Y GENERA LAS ROOMS
	//Primero se configura la room inicial
	_roomLayout.resize(_layout.size()); //Dimensiona las filas del vector
	for (int i = 0; i < _layout.size(); i++) {
		_roomLayout[i].resize(_layout[i].size()); //Dimensiona las columnas del vector
		for (int j = 0; j < _layout[i].size(); j++) {
			if(_layout[i][j] == 'S') {
				_roomLayout[i][j] = new Room(0, "res/texturas/rooms/tutorial_room.png", _playerPtr);
				_roomLayout[i][j]->inicializa("res/rooms/0.txt");
				_rooms.push_back(_roomLayout[i][j]);//Será la room inicial
				break;
			}
		}
	}
	//A continuación se configuran el resto de las rooms
	for (int i = 0; i < _layout.size(); i++) {
		for (int j = 0; j < _layout[i].size(); j++) {
			switch (_layout[i][j]) {
			case 'R': {
				std::stringstream buffer;
				buffer << "res/texturas/rooms/";

				//Carga textura aleatoria
				switch (ETSIDI::lanzaDado(5)) { //Nunca devuelve 5 (máximo)
				case 1: buffer << "Basement1.png"; break;
				case 2: buffer << "Catacombs1.png"; break;
				case 3: buffer << "Necropolis1.png"; break;
				case 4: buffer << "Caves1.png"; break;
				default: std::cerr << "Valor inesperado en setPiso\n"; exit(0); break;
				}
				_roomLayout[i][j] = new Room(_rooms.size(), buffer.str().c_str(), _playerPtr);

				//Carga layout aleatorio
				buffer.str(""); //Reinicia el buffer
				buffer << "res/rooms/" << ETSIDI::lanzaDado(15) << ".txt"; //Nunca devuelve 15 (máximo)
				_roomLayout[i][j]->inicializa(buffer.str().c_str());
				_rooms.push_back(_roomLayout[i][j]);
				break; }
			case 'B':
				_roomLayout[i][j] = new BossRoom(int(_rooms.size()), "res/texturas/rooms/Basement1.png", _playerPtr);
				_roomLayout[i][j]->inicializa("res/rooms/B1.txt");
				_rooms.push_back(_roomLayout[i][j]);
				break;
			case '.':
				_roomLayout[i][j] = nullptr;
				break;
			}
		}
	}

	///CONFIGURA LAS PUERTAS
	//Barrido por filas de izquierda a derecha (puertas izquierdas)
	for (size_t row = 0; row < _roomLayout.size(); row++) {
		Room* aux = nullptr;
		for (size_t col = 0; col < _roomLayout[row].size(); col++) {
			auto& roomPtr = _roomLayout[row][col];
			if (roomPtr != nullptr) { //Encuentra room
				if (aux != nullptr) { //Hay room anterior
					if(_layout[row][col] == 'B' || _layout[row][col-1] == 'B') //Comprueba si se trata de la puerta del boss
						roomPtr->addPuerta(new PuertaBoss(aux, PuertaRoom::ORIENTACION::LEFT));
					else
						roomPtr->addPuerta(new PuertaRoom(aux, PuertaRoom::ORIENTACION::LEFT));
				}
				aux = roomPtr;
			}
			else {
				aux = nullptr; //No encuentra room
			}
		}
	}
	//Barrido por filas de derecha a izquierda (puertas derechas)
	for (size_t row = 0; row < _roomLayout.size(); row++) {
		Room* aux = nullptr;
		for (int col = int(_roomLayout[row].size()) - 1; col >= 0; col--) {
			auto& roomPtr = _roomLayout[row][col];
			if (roomPtr != nullptr) { //Encuentra room
				if (aux != nullptr) { //Hay room anterior
					if (_layout[row][col] == 'B' || _layout[row][col + size_t(1)] == 'B') //Comprueba si se trata de la puerta del boss
						roomPtr->addPuerta(new PuertaBoss(aux, PuertaRoom::ORIENTACION::RIGHT));
					else
						roomPtr->addPuerta(new PuertaRoom(aux, PuertaRoom::ORIENTACION::RIGHT));
				}
				aux = roomPtr;
			}
			else {
				aux = nullptr; //No encuentra room
			}
		}
	}
	//Barrido por columnas de arriba a abajo (puertas superiores)
	for (size_t col = 0; col < _roomLayout[0].size(); col++) { //La matriz debe ser rectangular para que funcione
		Room* aux = nullptr;
		for (size_t row = 0; row < _roomLayout.size(); row++) {
			auto& roomPtr = _roomLayout[row][col];
			if (roomPtr != nullptr) { //Encuentra room
				if (aux != nullptr) { //Hay room anterior
					if (_layout[row][col] == 'B' || _layout[row - 1][col] == 'B') //Comprueba si se trata de la puerta del boss
						roomPtr->addPuerta(new PuertaBoss(aux, PuertaRoom::ORIENTACION::UP));
					else
						roomPtr->addPuerta(new PuertaRoom(aux, PuertaRoom::ORIENTACION::UP));
				}
				aux = roomPtr;
			}
			else {
				aux = nullptr; //No encuentra room
			}
		}
	}
	//Barrido por columnas de abajo a arriba (puertas inferiores)
	for (size_t col = 0; col < _roomLayout[0].size(); col++) { //La matriz debe ser rectangular para que funcione
		Room* aux = nullptr;
		for (int row = int(_roomLayout.size()) - 1; row >= 0; row--) {
			auto& roomPtr = _roomLayout[row][col];
			if (roomPtr != nullptr) { //Encuentra room
				if (aux != nullptr) { //Hay room anterior
					if (_layout[row][col] == 'B' || _layout[row + size_t(1)][col] == 'B') //Comprueba si se trata de la puerta del boss
						roomPtr->addPuerta(new PuertaBoss(aux, PuertaRoom::ORIENTACION::DOWN));
					else
						roomPtr->addPuerta(new PuertaRoom(aux, PuertaRoom::ORIENTACION::DOWN));
				}
				aux = roomPtr;
			}
			else {
				aux = nullptr; //No encuentra room
			}
		}
	}

}
