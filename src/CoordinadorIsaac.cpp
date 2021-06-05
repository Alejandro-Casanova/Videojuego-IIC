#include "CoordinadorIsaac.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include <sstream>
#include "GestorDeTeclado.h"
#include "GestorSprites.h"
#include <iostream>



CoordinadorIsaac:: CoordinadorIsaac()
{
	estado = INICIO;
} 

CoordinadorIsaac::~CoordinadorIsaac()
{
}

void CoordinadorIsaac::dibuja() {
	if (estado == INICIO) {

		////Borrado de la pantalla	
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//////Para definir el punto de vista
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		glEnable(GL_LIGHTING);
		//GestorSprites::dimensionaSprite(362, 103, TILE_WIDTH / 2.0f, _sprite);
		ETSIDI::setTextColor(0, 0, 0);
		ETSIDI::setFont("bin/fuentes/Bitwise.ttf", 50);
		ETSIDI::printxy("The Binding of Isaac", -10, 2);
		ETSIDI::setTextColor(0.5, 0.5, 0.5);
		ETSIDI::setFont("bin/fuentes/Bitwise.ttf", 12);
		ETSIDI::printxy("Pulse 'Q' para empezar a jugar", -10, -3);
		ETSIDI::printxy("Pulse 'R' para ver las maximas puntuaciones", -10, -4);
		ETSIDI::printxy("Pulse 'L' para leer el leaderboard", -10, -5);
		ETSIDI::printxy("Pulse 'S' para salir", -10, -6);

	}
	else if (estado == JUEGO) {

		//mundo.inicializa();
		mundo.dibuja();

		if (mundo.Getfinal_juego() == 1) {
			estado = FIN;
		}

		else if (mundo.Getfinal_juego() == 2) {
			estado = GAMEOVER;
		}
	}

	else if (estado == GAMEOVER) {
		//mundo.dibuja();
	}

	else if (estado == FIN) {
		//mundo.dibuja();
	}

	else if (estado == PAUSA) {
		//mundo.dibuja();

	}

	else if (estado==LEADERBOARD){}

}


void CoordinadorIsaac::tecla() {
	
	if (estado == INICIO) {
		if (GestorDeTeclado::isKeyPressed('q')) {
			mundo.inicializa();
			//mundo.tecla();
			estado = JUEGO;
		    
		} 
		else if (GestorDeTeclado::isKeyPressed('s')) {
			exit(0);
			//mundo.tecla();
			//ExitThread(0);
		}
		else if (GestorDeTeclado::isKeyPressed('l')) {

			//mundo.tecla();
			estado = LEADERBOARD;
		}
		}
	
	else if (estado == JUEGO) {
		mundo.tecla();
		if (GestorDeTeclado::isKeyPressed('p')) { //Para poner el juego en pausa
			//mundo.tecla();
			estado = PAUSA;

		}
	}
	else if (estado == PAUSA) {
			if (GestorDeTeclado::isKeyPressed('r')) {//Reanuda el juego
				//mundo.tecla();
				estado = JUEGO;
			}
		
	}
	else if (estado ==GAMEOVER) { 
		if (GestorDeTeclado::isKeyPressed('r')) {//Vuelve al menu inicial
			//mundo.tecla();
			estado = INICIO;
		}
	}
	else if (estado ==FIN) { 
		if (GestorDeTeclado::isKeyPressed('r')) {//Vuelve al menu inicial
			//mundo.tecla();
			estado = INICIO;
		}
	}
	
}


void CoordinadorIsaac::mueve() {
	if (estado ==JUEGO) { 
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

void CoordinadorIsaac::teclaEspecial() {
	if (estado == JUEGO)
		mundo.teclaEspecial();
}

//void CoordinadorIsaac::dibuja()
//{
//	if (estado == Estado::INICIO) {//CODIGO PARA PINTAR UNA PANTALLA NEGRA CON LETRAS 
//		//gluLookAt(0, 7.5, 30, // posicion del ojo 
//		//	0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
//		//	0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
//		//ETSIDI::setTextColor(1, 1, 0);
//		//ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
//		//ETSIDI::printxy("Pang 1.1", -5, 8);
//		//ETSIDI::setTextColor(1, 1, 1);
//		//ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
//		//ETSIDI::printxy("PULSE LA TECLA -E- PARA EMPEZAR", -5, 7);
//		//ETSIDI::printxy("PULSE LA TECLA -S- PARA SALIR", -5, 6);
//		//ETSIDI::printxy("Alejandro Casanova Martín", 2, 1);
//	}
//	else if (estado == Estado::JUEGO) {
//		mundo.dibuja();
//
//		//Dibuja Texto
//		/*ETSIDI::setTextColor(1, 1, 0);
//		ETSIDI::setFont("fuentes/Bitwise.ttf", 24);
//		ETSIDI::printxy("Pang", -10, 9);
//		ETSIDI::setTextColor(1, 1, 1);
//		ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
//		ETSIDI::printxy("Alejandro Casanova Martín", 4, 9);*/
//
//		//Dibuja contador de disparos
//		/*std::stringstream contador;
//		contador << "Disparos: " << mundo.getNDisparos();
//		ETSIDI::printxy(contador.str().c_str(), -4, 10);
//		contador.str("");
//		contador << "SUPER Disparos: " << mundo.getNDisparosEspeciales();
//		ETSIDI::printxy(contador.str().c_str(), -4, 9);
//		ETSIDI::setTextColor(1, 0, 1);
//		ETSIDI::printxy("Pulse -Z- para lanzar un SUPER disparo", -5, 8);*/
//	}
//	else if (estado == Estado::PAUSA) {
//		mundo.dibuja();
//		/*ETSIDI::setTextColor(1, 0, 0);
//		ETSIDI::setFont("fuentes/Bitwise.ttf", 30);
//		ETSIDI::printxy("PAUSA", -3, -9);
//		ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
//		ETSIDI::printxy("Pulse -C- para reanudar", -4, -10);*/
//	}
//	else if (estado == Estado::GAMEOVER) {
//		mundo.dibuja(); 
//		/*ETSIDI::setTextColor(1, 0, 0); 
//		ETSIDI::setFont("fuentes/Bitwise.ttf", 16); 
//		ETSIDI::printxy("GAMEOVER: Has perdido", -5, 10);
//		ETSIDI::printxy("Pulsa -C- para continuar", -5, 9);*/
//	}
//	else if (estado == Estado::FIN) { 
//		mundo.dibuja(); 
//		/*ETSIDI::setFont("fuentes/Bitwise.ttf", 16); 
//		ETSIDI::printxy("ENHORABUENA, ¡Has triunfado!", -5, 10); 
//		ETSIDI::printxy("Pulsa -C- para continuar", -5, 9);*/
//	}
//}

//void CoordinadorIsaac::tecla() {
//	/*if (estado == Estado::INICIO) {
//		if (GestorDeTeclado::isKeyPressed('e')) {
//			mundo.inicializa();
//			estado = Estado::JUEGO;
//		}
//		if (GestorDeTeclado::isKeyPressed('s'))
//			exit(0);
//	}*/
//	//if (estado == Estado::JUEGO) { 
//	//	if (GestorDeTeclado::isKeyPressed('p')) {
//	//		//estado = estado::pausa;
//	//	}else
//	//		mundo.tecla(); 
//	/*}
//	else if (estado == Estado::PAUSA) {
//		if (GestorDeTeclado::isKeyPressed('c')) {
//			estado = Estado::JUEGO;
//		}
//	}
//	else if (estado == Estado::GAMEOVER) {
//		if (GestorDeTeclado::isKeyPressed('c'))
//			estado = Estado::INICIO;
//	}
//	else if (estado == Estado::FIN) {
//		if (GestorDeTeclado::isKeyPressed('c'))
//			estado = Estado::INICIO;
//	}*/
//	mundo.tecla();
//}