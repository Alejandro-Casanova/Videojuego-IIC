#pragma once

#include "Mundo.h" 

class CoordinadorIsaac { 
protected:
	Mundo mundo;
	enum Estado {PREINICIO, INICIO, JUEGO, GAMEOVER, FIN, PAUSA, LEADERBOARD, INSTRUCCIONES };
	Estado estado = PREINICIO;

	ETSIDI::Sprite _sprite = "res/texturas/Pantalla.png";
	ETSIDI::Sprite _spriteInicio = "res/texturas/logo.png";

public:
	CoordinadorIsaac();
	virtual ~CoordinadorIsaac();
	void dibuja();
	void tecla();
	void mueve();
	void teclaEspecial(); 
	 
	void inicializa() { mundo.inicializa(); }
	
	

};