#include "CoordinadorIsaac.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include <sstream>
#include "GestorDeTeclado.h"

CoordinadorIsaac::CoordinadorIsaac()
{
	
}

CoordinadorIsaac::~CoordinadorIsaac()
{
}

void CoordinadorIsaac::teclaEspecial() {
	if (estado == Estado::JUEGO) 
		mundo.teclaEspecial(); 
} 

void CoordinadorIsaac::tecla() {
	/*if (estado == Estado::INICIO) {
		if (GestorDeTeclado::isKeyPressed('e')) {
			mundo.inicializa(); 
			estado = Estado::JUEGO;
		} 
		if (GestorDeTeclado::isKeyPressed('s'))
			exit(0);
	}*/
	//if (estado == Estado::JUEGO) { 
	//	if (GestorDeTeclado::isKeyPressed('p')) {
	//		//estado = estado::pausa;
	//	}else
	//		mundo.tecla(); 
	/*}
	else if (estado == Estado::PAUSA) {
		if (GestorDeTeclado::isKeyPressed('c')) {
			estado = Estado::JUEGO;
		}
	}
	else if (estado == Estado::GAMEOVER) { 
		if (GestorDeTeclado::isKeyPressed('c'))
			estado = Estado::INICIO; 
	}
	else if (estado == Estado::FIN) { 
		if (GestorDeTeclado::isKeyPressed('c'))
			estado = Estado::INICIO;
	}*/
	mundo.tecla();
}

void CoordinadorIsaac::inicializa()
{
	mundo.inicializa();
}


void CoordinadorIsaac::mueve() {
	if (estado == Estado::JUEGO) { 
		mundo.mueve(); 
		/*if (mundo.getImpacto()) {
			estado = Estado::GAMEOVER;
			return;
		}
		if (mundo.getNumEsferas() == 0) { 
			if (!mundo.cargarNivel()) 
				estado = Estado::FIN; 
		} */
		
	}
}

void CoordinadorIsaac::dibuja()
{
	if (estado == Estado::INICIO) {//CODIGO PARA PINTAR UNA PANTALLA NEGRA CON LETRAS 
		//gluLookAt(0, 7.5, 30, // posicion del ojo 
		//	0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
		//	0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		//ETSIDI::setTextColor(1, 1, 0);
		//ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
		//ETSIDI::printxy("Pang 1.1", -5, 8);
		//ETSIDI::setTextColor(1, 1, 1);
		//ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
		//ETSIDI::printxy("PULSE LA TECLA -E- PARA EMPEZAR", -5, 7);
		//ETSIDI::printxy("PULSE LA TECLA -S- PARA SALIR", -5, 6);
		//ETSIDI::printxy("Alejandro Casanova Martín", 2, 1);
	}
	else if (estado == Estado::JUEGO) {
		mundo.dibuja();

		//Dibuja Texto
		/*ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 24);
		ETSIDI::printxy("Pang", -10, 9);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
		ETSIDI::printxy("Alejandro Casanova Martín", 4, 9);*/

		//Dibuja contador de disparos
		/*std::stringstream contador;
		contador << "Disparos: " << mundo.getNDisparos();
		ETSIDI::printxy(contador.str().c_str(), -4, 10);
		contador.str("");
		contador << "SUPER Disparos: " << mundo.getNDisparosEspeciales();
		ETSIDI::printxy(contador.str().c_str(), -4, 9);
		ETSIDI::setTextColor(1, 0, 1);
		ETSIDI::printxy("Pulse -Z- para lanzar un SUPER disparo", -5, 8);*/
	}
	else if (estado == Estado::PAUSA) {
		mundo.dibuja();
		/*ETSIDI::setTextColor(1, 0, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 30);
		ETSIDI::printxy("PAUSA", -3, -9);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
		ETSIDI::printxy("Pulse -C- para reanudar", -4, -10);*/
	}
	else if (estado == Estado::GAMEOVER) {
		mundo.dibuja(); 
		/*ETSIDI::setTextColor(1, 0, 0); 
		ETSIDI::setFont("fuentes/Bitwise.ttf", 16); 
		ETSIDI::printxy("GAMEOVER: Has perdido", -5, 10);
		ETSIDI::printxy("Pulsa -C- para continuar", -5, 9);*/
	}
	else if (estado == Estado::FIN) { 
		mundo.dibuja(); 
		/*ETSIDI::setFont("fuentes/Bitwise.ttf", 16); 
		ETSIDI::printxy("ENHORABUENA, ¡Has triunfado!", -5, 10); 
		ETSIDI::printxy("Pulsa -C- para continuar", -5, 9);*/
	}
}

