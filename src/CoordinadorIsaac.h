#pragma once

#include "Mundo.h" 

class CoordinadorIsaac { 
protected:
	Mundo mundo;
	enum  Estado { INICIO, JUEGO, GAMEOVER, FIN, PAUSA, LEADERBOARD };
	Estado estado;
	//ETSIDI::GLTexture _texturaInicial = { 0, 0, 0 };
	ETSIDI::Sprite _sprite = "res/texturas/logo.png";

	
public:
	CoordinadorIsaac();
	virtual ~CoordinadorIsaac();
	void dibuja();
	void tecla();
	void mueve();
	void teclaEspecial(); 
	 
	void inicializa() { mundo.inicializa(); }
	
	

};