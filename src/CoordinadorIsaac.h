#pragma once

#include "Mundo.h" 

class CoordinadorIsaac { 
public:
	CoordinadorIsaac();
	virtual ~CoordinadorIsaac();
	void teclaEspecial(); 
	void tecla(); 
	void inicializa();
	void mueve(); 
	void dibuja(); 
protected: 
	enum class Estado { INICIO, JUEGO, GAMEOVER, FIN, PAUSA }; 
	Estado estado = Estado::JUEGO; //TEMPORAL
	Mundo mundo;
};