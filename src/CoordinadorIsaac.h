#pragma once

#include "Mundo.h" 

class CoordinadorIsaac { 
public:
	CoordinadorIsaac();
	virtual ~CoordinadorIsaac();
	void dibuja();
	void tecla();
	void mueve();
	void teclaEspecial(); 
	 
	void inicializa();
	
	void cargaPuntuaciones(const char* ruta_de_archivo, const char* ruta_de_archivo_datos);
	void guardaPuntuaciones(const char* ruta_de_archivo_puntos, const char* ruta_de_archivo_datos);
	void ordenaPuntuaciones();
	void nuevaPuntuacion();
	
protected:
	Mundo mundo;
	enum Estado { PREINICIO, INICIO, JUEGO, GAMEOVER, FIN, PAUSA, LEADERBOARD, INSTRUCCIONES };
	Estado estado = PREINICIO;

	ETSIDI::Sprite _sprite = "res/texturas/Pantalla.png";
	ETSIDI::Sprite _spriteInicio = "res/texturas/logo.png";

	std::vector<std::string> _datos;
	std::vector<int> _puntuaciones; //Útil para ordenar la lista

};