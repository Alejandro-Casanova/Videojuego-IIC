#pragma once
//Basado en el código desarrollado en clase por Pablo San Segundo

#include "Objeto.h"

class Factoria
{
public:
	static Objeto* create(Objeto::obj_t);			//equivalente al constructor normal
	static Objeto* create(const Objeto&);			//equivalente al constructor copia, pero en un ámbito de enlace dinámico
	static void destroy(Objeto* p) { delete p;  p = nullptr; }
};


