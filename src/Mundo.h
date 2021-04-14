#pragma once

class Mundo
{
public: 
	void tecla(unsigned char key);
	void inicializa();
	void mueve();
	void dibuja();

	float x_ojo = 0;
	float y_ojo = 0;
	float z_ojo = 0;
};
