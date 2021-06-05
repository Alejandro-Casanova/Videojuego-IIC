#include "CoordinadorIsaac.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include <sstream>
#include "GestorDeTeclado.h"
#include "GestorSprites.h"
#include <iostream>



CoordinadorIsaac:: CoordinadorIsaac()
{
	estado = PREINICIO;
} 

CoordinadorIsaac::~CoordinadorIsaac()
{
}

void CoordinadorIsaac::dibuja() {

	switch (estado)
	{
	case(PREINICIO):

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
				
	case(INICIO):

		
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

	case(JUEGO):

		mundo.dibuja();

		/*if (mundo.Getfinal_juego() == 1) {
			estado = FIN;
		}

		else if (mundo.Getfinal_juego() == 2) {
			estado = GAMEOVER;
		}*/

		break;

	case(GAMEOVER):
		
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("res/font/upheavtt.ttf", 30);
		ETSIDI::printxy("GAMEOVER", -5, 9);
		ETSIDI::setFont("res/font/upheavtt.ttf", 15);
		ETSIDI::printxy("Te has quedado sin vidas.", -5, 8);
		ETSIDI::printxy("Pulse R volver al menu de inicio.", -13, 5);
		ETSIDI::printxy("Pulse S para salir del juego.", -13, 4);
					
		break;

	case(FIN):
		
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("res/font/upheavtt.ttf", 30);
		ETSIDI::printxy("FIN DEL JUEGO", -5, 9);
		ETSIDI::setFont("res/font/upheavtt.ttf", 15);
		ETSIDI::printxy("Te has pasado el juego, ENHORABUENA! .", -5, 8);
		ETSIDI::printxy("Pulse R volver al menu de inicio.", -13, 5);
		ETSIDI::printxy("Pulse S para salir del juego.", -13, 4);
		
		break;

	case(PAUSA):

		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		ETSIDI::setFont("res/font/upheavtt.ttf", 30);
		ETSIDI::printxy("JUEGO EN PAUSA", -5, 9);
		ETSIDI::setFont("res/font/upheavtt.ttf", 15);
		ETSIDI::printxy("Pulse C para continuar con el juego", -13, 5);
		ETSIDI::printxy("Pulse R para volver al menu de inicio", -13, 4);
		ETSIDI::printxy("Advertencia: Al volver al menu de inicio se perdera el progeso de la partida", -18, -7);
		
		break;

	case(INSTRUCCIONES):
		
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		ETSIDI::setFont("res/font/upheavtt.ttf", 25);
		ETSIDI::printxy("INSTRUCCIONES:", -5, 10);
		ETSIDI::setFont("res/font/upheavtt.ttf", 15);
		ETSIDI::printxy("1. Utilice W,A,S,D para mover el personaje.", -13, 8);
		ETSIDI::printxy("2. Utilice las flechas para disparar.", -13, 6);
		ETSIDI::printxy("3. Utilice la barra espaciadora cuando se encuentre", -13, 4);
		ETSIDI::printxy("cerca de una puerta para utilizarla.", -13, 3);
		ETSIDI::printxy("4. Si se pulsa P en cualquier momento del juego, se pausara", -13, 1);
		ETSIDI::printxy("El juego consiste en avanzar por las mazmorras a la vez que se va derrotando  ", -18, -2);
		ETSIDI::printxy("a los enemigos que aparecen en las diferentes habitaciones. ", -18, -3);
		ETSIDI::printxy("El objetivo es bajar a la estancia mas profunda, para ello habra que derrotar", -18, -4);
		ETSIDI::printxy("al jefe de cada piso.", -18, -5);
		ETSIDI::printxy("Pulse 'R' para volver al menu de inicio", -13, -8);
		
		break;

	case(LEADERBOARD):
		//gestionar el dibujo del tablero de maximas puntuaciones
		break;

	}
}


void CoordinadorIsaac::tecla() {


	switch (estado)
	{

	case(PREINICIO):

		if (GestorDeTeclado::isKeyPressed('q')) {
			estado = INICIO;
		}
			break;
		
		
	case(INICIO):

		if (GestorDeTeclado::isKeyPressed('j')) {
			mundo.inicializa();
			estado = JUEGO;
		} 

		else if (GestorDeTeclado::isKeyPressed('l')) {
			estado = LEADERBOARD;
		}

		else if (GestorDeTeclado::isKeyPressed('i')) {
			estado = INSTRUCCIONES;
		}

		else if (GestorDeTeclado::isKeyPressed('s')) {
			exit(0);
			//ExitThread(0);
		}
		
		break;

	case(JUEGO):
		if (mundo.JuegoAcabado() == 0) {
			mundo.tecla();

			if (GestorDeTeclado::isKeyPressed('p')) { //Para poner el juego en pausa
				estado = PAUSA;
			}

		}
		else if (mundo.JuegoAcabado() == 1)
			estado =GAMEOVER;
		else if (mundo.JuegoAcabado() == 2)
			estado = FIN;
		

		break;

	case(INSTRUCCIONES):

		if (GestorDeTeclado::isKeyPressed('r')) {//Vuelve al menu inicial

			estado = INICIO;
		}
		break;

	case(PAUSA):
	   
			if (GestorDeTeclado::isKeyPressed('c')) {//Reanuda el juego

				estado = JUEGO;
			}
			else if (GestorDeTeclado::isKeyPressed('r')) { //Vuelve al menu inicial

				estado = INICIO;
			}
		break;
		
	case(GAMEOVER):
	 
		if (GestorDeTeclado::isKeyPressed('r')) {//Vuelve al menu inicial
			
			estado = INICIO;
		}
		if (GestorDeTeclado::isKeyPressed('s')) {//Sale del juego

			exit(0);
		}
		break;

	case(FIN):
	 
		if (GestorDeTeclado::isKeyPressed('r')) {//Vuelve al menu inicial
			
			estado = INICIO;
		}
		if (GestorDeTeclado::isKeyPressed('s')) {//Sale del juego

			exit(0);
		}
		break;

	
    }
}





void CoordinadorIsaac::mueve() {
	if (estado ==JUEGO) { 
		mundo.mueve(); 
		
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