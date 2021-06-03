#pragma once
//Basado en el código desarrollado en clase por Pablo San Segundo

#include <iostream>
#include <string>
#include <vector>
#include "Entidad.h"
#include <ETSIDI.h>
#include "Vector2D.h"
#include "GestorSprites.h"

class Objeto : public Entidad
{	
public:
	enum class obj_t { OBJETO = 0, CORAZON, MONEDA, LLAVE };
protected:
	Objeto(const char* ruta_de_textura, Vector2D posicion = { 0.0f, 0.0f }, obj_t t = obj_t::OBJETO);
	//void dimensionaSprite(int pxWidth, int pxHeight); //Ajusta las proporciones del sprite para que no se deforme la textura
	obj_t rtt;
	ETSIDI::Sprite _sprite;
	int _valor = 1; //Valor del objeto (cantidad de salud, monedas, llaves....)
public:
	virtual ~Objeto() {};//declaración virtual al dest. OBLIGATORIA!

	void dibuja() override;

	obj_t type() const { return rtt; }
	int getValor() { return _valor; }

	virtual std::ostream& print(std::ostream& o = std::cout) const = 0;
	friend std::ostream& operator <<(std::ostream& o, const Objeto& ob) { return ob.print(o); }
};

class Corazon : public Objeto {
public:
	Corazon(Vector2D pos) : Objeto("res/texturas/container.png", pos, obj_t::CORAZON) { GestorSprites::dimensionaSprite(24, 20, TILE_WIDTH / 2.0f, _sprite); }

	std::ostream& print(std::ostream& o = std::cout) const override { o << "soy un corazon" << std::endl; return o; }
};

class Moneda : public Objeto {
public:
	Moneda(Vector2D pos) : Objeto("res/texturas/dime.png", pos, obj_t::MONEDA) { GestorSprites::dimensionaSprite(24, 14, TILE_WIDTH / 2.0f, _sprite); }
	
	std::ostream& print(std::ostream& o = std::cout) const override { o << "soy una Moneda" << std::endl; return o; }
};

class Llave : public Objeto {
public:
	Llave(Vector2D pos) : Objeto("res/texturas/key.png", pos, obj_t::LLAVE) { GestorSprites::dimensionaSprite(23, 31, TILE_WIDTH / 2.0f, _sprite); }
	
	std::ostream& print(std::ostream& o = std::cout) const { o << "soy una Moneda" << std::endl; return o; }
};

class Factoria
{
public:
	static Objeto* create(Objeto::obj_t, Vector2D pos);			//equivalente al constructor normal
	static Objeto* create(const Objeto&);			//equivalente al constructor copia, pero en un ámbito de enlace dinámico
	static void destroy(Objeto* p) { delete p;  p = nullptr; }
};

