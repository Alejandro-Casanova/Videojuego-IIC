#pragma once
//Basado en el c�digo desarrollado en clase por Pablo San Segundo

#include "Objeto.h"

class Factoria
{
public:
	static Objeto* create(Objeto::obj_t);			//equivalente al constructor normal
	static Objeto* create(const Objeto&);			//equivalente al constructor copia, pero en un �mbito de enlace din�mico
	static void destroy(Objeto* p) { delete p;  p = nullptr; }
};


