#pragma once
#include "Pared.h"

class Mundo
{
public: 
	void tecla(unsigned char key);
	void inicializa();
	void mueve();
	void dibuja();

private:
	float x_ojo = 0;
	float y_ojo = 0;
	float z_ojo = 0;

	Pared pared_izq, pared_sup, pared_der, pared_inf;
};
