#pragma once

//Obtenido del juego PANG de las prácticas de laboratorio
class Vector2D {
public:
//MÉTODOS
	Vector2D(float nx = 0.0f, float ny = 0.0f);
	virtual ~Vector2D();
	float modulo(); 
	float argumento();
	Vector2D unitario();

	Vector2D operator - (Vector2D) const; 
	Vector2D operator + (Vector2D) const;
	Vector2D operator += (Vector2D);
	Vector2D operator -= (Vector2D);
	float operator *(Vector2D) const; 
	Vector2D operator *(float) const; 
	Vector2D operator +(float) const;

	void set(float nx, float ny);

//ATRIBUTOS
	float x = 0;
	float y = 0;
};