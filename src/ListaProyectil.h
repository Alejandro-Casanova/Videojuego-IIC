#pragma once
#define MAX_PROYECTILES 100
#include "Proyectil.h"
#include "Caja.h"
#include "Enemigo.h"
class Obstaculo;

class ListaProyectil
{
private: 
	Proyectil* lista_Pro[MAX_PROYECTILES];
	int contador;

public:
	ListaProyectil();
	virtual ~ListaProyectil();
	void destruirContenido();
	friend class Interaccion;

	bool agregar(Proyectil* f);
	void eliminar(int index);
	void eliminar(Proyectil* f);

	void dibuja();
	void mueve(float t);

	void setColor(char r, char g, char b);
	int getNum() { return contador; };

	Proyectil* operator [] (int i);
	Proyectil* colision(Caja c);
	Proyectil* impacto(Enemigo e);
	Proyectil* impacto(Obstaculo& e);

};

