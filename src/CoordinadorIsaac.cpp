#include "CoordinadorIsaac.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include <sstream>
#include "GestorDeTeclado.h"
#include "GestorSprites.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>



CoordinadorIsaac:: CoordinadorIsaac()
{
} 

CoordinadorIsaac::~CoordinadorIsaac()
{
	
}

void CoordinadorIsaac::dibuja() {

	switch (estado)
	{
	case(Estado::PREINICIO):

		//////Para definir el punto de vista
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		//glEnable(GL_LIGHTING);
		GestorSprites::dimensionaSprite(1920, 1080, 33, _sprite);
		_sprite.draw();
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("res/font/upheavtt.ttf", 14);
		ETSIDI::printxy("Pulse 'Q' para continuar", -5, -10);

		break;
				
	case(Estado::INICIO):

		
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		//glEnable(GL_LIGHTING);
		GestorSprites::dimensionaSprite(362, 103, 25, _spriteInicio);
		_spriteInicio.draw();
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("res/font/upheavtt.ttf", 13);
		ETSIDI::printxy("Pulse J para empezar a jugar.", 0, -6);
		ETSIDI::printxy("Pulse L para ver el leaderboard.", 0, -7);
		ETSIDI::printxy("Pulse I para leer las instrucciones.", 0, -8);
		ETSIDI::printxy("Pulse S para salir del juego.", 0, -9);

		break;

	case(Estado::JUEGO):

		mundo.dibuja();

		/*if (mundo.Getfinal_juego() == 1) {
			estado = FIN;
		}

		else if (mundo.Getfinal_juego() == 2) {
			estado = GAMEOVER;
		}*/

		break;

	case(Estado::GAMEOVER):
		
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("res/font/upheavtt.ttf", 30);
		ETSIDI::printxy("GAMEOVER", -5, 9);
		ETSIDI::setFont("res/font/upheavtt.ttf", 15);
		ETSIDI::printxy("Te has quedado sin vidas.", -5, 8);
		ETSIDI::printxy("Pulse R volver al menu de inicio.", -13, 5);
		ETSIDI::printxy("Pulse Q para salir del juego.", -13, 4);
					
		break;

	case(Estado::FIN):
		
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("res/font/upheavtt.ttf", 30);
		ETSIDI::printxy("FIN DEL JUEGO", -5, 9);
		ETSIDI::setFont("res/font/upheavtt.ttf", 15);
		ETSIDI::printxy("Te has pasado el juego, ENHORABUENA! .", -5, 8);
		ETSIDI::printxy("Pulse R volver al menu de inicio.", -13, 5);
		ETSIDI::printxy("Pulse S para salir del juego.", -13, 4);
		
		break;

	case(Estado::PAUSA):

		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		ETSIDI::setFont("res/font/upheavtt.ttf", 30);
		ETSIDI::printxy("JUEGO EN PAUSA", -5, 9);
		ETSIDI::setFont("res/font/upheavtt.ttf", 15);
		ETSIDI::printxy("Pulse C para continuar con el juego", -13, 5);
		ETSIDI::printxy("Pulse R para volver al menu de inicio", -13, 4);
		ETSIDI::printxy("Advertencia: Al volver al menu de inicio se perdera el progeso de la partida", -18, -7);
		
		break;

	case(Estado::INSTRUCCIONES):
		
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		ETSIDI::setFont("res/font/upheavtt.ttf", 25);
		ETSIDI::printxy("INSTRUCCIONES:", -5, 10);
		ETSIDI::setFont("res/font/upheavtt.ttf", 15);
		ETSIDI::printxy("1. Utilice W,A,S,D para mover el personaje.", -13, 8);
		ETSIDI::printxy("2. Utilice las flechas para disparar.", -13, 6);
		ETSIDI::printxy("3. Utilice la barra espaciadora cuando se encuentre", -13, 4);
		ETSIDI::printxy("cerca de una puerta para utilizarla.", -13, 3);
		ETSIDI::printxy("4. Pulse P en cualquier momento para pausar el juego", -13, 1);
		ETSIDI::printxy("El objetivo del juego es avanzar por las mazmorras a la vez que se va derrotando  ", -18, -2);
		ETSIDI::printxy("a los enemigos que aparecen en las diferentes habitaciones. ", -18, -3);
		ETSIDI::printxy("La meta es bajar a la estancia mas profunda, para ello debe derrotarse", -18, -4);
		ETSIDI::printxy("al jefe de cada piso.", -18, -5);
		ETSIDI::printxy("Pulse 'R' para volver al menu de inicio", -13, -8);
		
		break;

	case(Estado::LEADERBOARD):
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("res/font/upheavtt.ttf", 25);
		ETSIDI::printxy("MAYORES PUNTUACIONES:", -7, 9);
		ETSIDI::setFont("res/font/upheavtt.ttf", 15);
		ETSIDI::printxy("Puntos  |  Pisos Superados  |  Fecha de la Partida", -10, 7);
		ETSIDI::setTextColor(1, 1, 1);
		for (size_t i = 0; (i < _puntuaciones.size()) && (i < 13); i++) {
			ETSIDI::printxy(std::to_string(_puntuaciones[i]).c_str(), -9, 5 - int(i));
			char pisos[] = { _datos[i][0] , '\0'};
			ETSIDI::printxy(pisos, -3, 5 - int(i));
			ETSIDI::printxy(&_datos[i][2], 2, 5 - int(i));
		}
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::printxy("Pulse 'R' para volver al menu de inicio", -8, -9);
		ETSIDI::setTextColor(1, 1, 1);
		break;

	}
}


void CoordinadorIsaac::tecla() {


	switch (estado)
	{

	case(Estado::PREINICIO):

		if (GestorDeTeclado::isKeyPressed('q')) {
			estado = Estado::INICIO;
			ETSIDI::playMusica("res/audio/ambience.mp3", true);
		}
		break;
		
		
	case(Estado::INICIO):

		if (GestorDeTeclado::isKeyPressed('j')) {
			//mundo.inicializa();  //El mundo ya se inicializa con el constructor
			estado = Estado::JUEGO;
		} 

		else if (GestorDeTeclado::isKeyPressed('l')) {
			estado = Estado::LEADERBOARD;
		}

		else if (GestorDeTeclado::isKeyPressed('i')) {
			estado = Estado::INSTRUCCIONES;
		}

		else if (GestorDeTeclado::isKeyPressed('s')) {
			exit(0);
			//ExitThread(0);
		}
		
		break;

	case(Estado::JUEGO):
		if (mundo.JuegoAcabado() == 0) {
			mundo.tecla();

			if (GestorDeTeclado::isKeyPressed('p')) { //Para poner el juego en pausa
				estado = Estado::PAUSA;
			}

		}
		else if (mundo.JuegoAcabado() == 1) {
			estado = Estado::GAMEOVER;
			//ETSIDI::play("res/audio/death.wav");
			nuevaPuntuacion(); //Guarda la puntuacion
		}
		else if (mundo.JuegoAcabado() == 2)
			estado = Estado::FIN;
		

		break;

	case(Estado::INSTRUCCIONES):

		if (GestorDeTeclado::isKeyPressed('r')) {//Vuelve al menu inicial

			estado = Estado::INICIO;
		}
		break;

	case(Estado::PAUSA):
	   
			if (GestorDeTeclado::isKeyPressed('c')) {//Reanuda el juego

				estado = Estado::JUEGO;
			}
			else if (GestorDeTeclado::isKeyPressed('r')) { //Vuelve al menu inicial

				estado = Estado::INICIO;
				mundo.inicializa(); //Reestablece el mundo
			}
		break;
		
	case(Estado::GAMEOVER):
	 
		if (GestorDeTeclado::isKeyPressed('r')) {//Vuelve al menu inicial
			
			estado = Estado::INICIO;
			guardaPuntuaciones("res/leaderboards/puntos.txt", "res/leaderboards/datos.txt");
			mundo.inicializa(); //Reestablece el mundo
		}
		if (GestorDeTeclado::isKeyPressed('q')) {//Sale del juego
			guardaPuntuaciones("res/leaderboards/puntos.txt", "res/leaderboards/datos.txt");
			exit(0);
		}
		break;

	case(Estado::FIN):
	 
		if (GestorDeTeclado::isKeyPressed('r')) {//Vuelve al menu inicial
			
			estado = Estado::INICIO;
			mundo.inicializa(); //Reestablece el mundo
		}
		if (GestorDeTeclado::isKeyPressed('s')) {//Sale del juego

			exit(0);
		}
		break;
	case(Estado::LEADERBOARD):
		if (GestorDeTeclado::isKeyPressed('r')) {//Vuelve al menu inicial

			estado = Estado::INICIO;
		}
		break;

	
    }
}

void CoordinadorIsaac::mueve() {
	if (estado == Estado::JUEGO) {
		mundo.mueve(); 
		
	}
}

void CoordinadorIsaac::teclaEspecial() {
	if (estado == Estado::JUEGO)
		mundo.teclaEspecial();
}

void CoordinadorIsaac::inicializa()
{
	mundo.inicializa(); cargaPuntuaciones("res/leaderboards/puntos.txt", "res/leaderboards/datos.txt");
}

void CoordinadorIsaac::cargaPuntuaciones(const char* ruta_de_archivo_puntos, const char* ruta_de_archivo_datos)
{
	std::ifstream puntos, datos;
	puntos.open(ruta_de_archivo_puntos);
	datos.open(ruta_de_archivo_datos);

	//Comprobación (ruta de archivo válida)
	if (puntos.fail()) {
		std::cerr << "No se pudo abrir el archivo: " << ruta_de_archivo_puntos << "\n";
		exit(0);
	}
	if (datos.fail()) {
		std::cerr << "No se pudo abrir el archivo: " << ruta_de_archivo_datos << "\n";
		exit(0);
	}

	//Registra la lista de datos
	std::string temp;
	while (std::getline(datos, temp)) {
		_datos.emplace_back(temp);
		//std::cout << temp << std::endl;
	}

	//Registra sólo las puntuaciones 
	temp.clear();
	while (std::getline(puntos, temp)) {
		_puntuaciones.emplace_back(std::stoi(temp));
		//std::cout << temp << std::endl;
	}

	//Comprobación
	if (_puntuaciones.size() != _datos.size()) {
		std::cerr << "Archivos corruptos: " << ruta_de_archivo_puntos << ", " << ruta_de_archivo_datos << std::endl;
		exit(0);
	}

	ordenaPuntuaciones();

	//for (auto& i : _puntuaciones) { std::cout << i << std::endl; }
	//for (auto& i : _datos) { std::cout << i << std::endl; }

	//Comprobación por terminal
	/*for (auto i : _layout) {
		std::cout << i << std::endl;
	}*/
}

void CoordinadorIsaac::guardaPuntuaciones(const char* ruta_de_archivo_puntos, const char* ruta_de_archivo_datos)
{
	std::ofstream puntos, datos;
	puntos.open(ruta_de_archivo_puntos);
	datos.open(ruta_de_archivo_datos);

	//Comprobación (ruta de archivo válida)
	if (puntos.fail()) {
		std::cerr << "No se pudo abrir el archivo: " << ruta_de_archivo_puntos << "\n";
		exit(0);
	}
	if (datos.fail()) {
		std::cerr << "No se pudo abrir el archivo: " << ruta_de_archivo_datos << "\n";
		exit(0);
	}

	ordenaPuntuaciones();

	//Guarda los puntos y los datos
	for (auto& i : _puntuaciones) {
		puntos << i << std::endl;
	}
	for (auto& i : _datos) {
		datos << i << std::endl;
	}
}

void CoordinadorIsaac::ordenaPuntuaciones()
{
	//Ordena las puntuaciones
	bool move;
	do {
		move = false;
		for (size_t i = 1; i < _puntuaciones.size(); i++) {
			if (_puntuaciones[i] > _puntuaciones[i - 1]) {
				std::iter_swap(_puntuaciones.begin() + i - 1, _puntuaciones.begin() + i);
				std::iter_swap(_datos.begin() + i - 1, _datos.begin() + i);
				move = true;
			}
		}
	} while (move == true);
}

void CoordinadorIsaac::nuevaPuntuacion()
{
	int nPuntuacion = 0;
	nPuntuacion += mundo.getContadorPisos() * 100;
	nPuntuacion += mundo.getPlayer().getDinero() * 10;

	_puntuaciones.push_back(nPuntuacion);

	time_t now = time(0);
	char dt[26];
	ctime_s(dt, sizeof dt, &now);
	std::string time = std::string(dt);
	time.pop_back(); //Elimina el "\n" sobrante
	_datos.push_back(std::to_string(mundo.getContadorPisos()) + " " + time);

}