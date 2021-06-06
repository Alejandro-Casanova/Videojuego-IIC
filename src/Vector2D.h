#pragma once
#include "Macros.h"

//Obtenido del juego PANG de las pr�cticas de laboratorio
class Vector2D {
public:
//M�TODOS
	Vector2D(float nx = 0.0f, float ny = 0.0f);
	virtual ~Vector2D();
	float modulo(); 
	float argumento();
	Vector2D unitario();

	Vector2D operator - (Vector2D) const; 
	Vector2D operator + (Vector2D) const;
	Vector2D operator += (Vector2D);
	Vector2D operator -= (Vector2D);
	Vector2D operator *=(float f);
	float operator *(Vector2D) const; 
	Vector2D operator *(float) const; 
	Vector2D operator +(float) const;

	void setXY(float nx, float ny);
	void set(float modulo, float angulo); //�ngulo en grados

//ATRIBUTOS
	float x = 0;
	float y = 0;
};