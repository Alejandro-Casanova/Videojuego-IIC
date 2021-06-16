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
	enum class obj_t { OBJETO = 0, CORAZON, MONEDA, LLAVE, BONUS};
protected:
	Objeto(const char* ruta_de_textura, Vector2D posicion = { 0.0f, 0.0f }, obj_t t = obj_t::OBJETO);
	obj_t rtt;
	ETSIDI::Sprite _sprite;
	float _valor = 1.0f; //Valor del objeto (cantidad de salud, monedas, llaves....)
public:
	virtual ~Objeto() {};//declaración virtual al dest. OBLIGATORIA!

	void dibuja() override;

	obj_t type() const { return rtt; }
	float getValor() const { return _valor; }
	

	//virtual std::ostream& print(std::ostream& o = std::cout) const = 0;
	//friend std::ostream& operator <<(std::ostream& o, const Objeto& ob) { return ob.print(o); }
};

class Corazon : public Objeto {
public:
	Corazon(Vector2D pos) : Objeto("res/texturas/red_heart.png", pos, obj_t::CORAZON) { GestorSprites::dimensionaSprite(24, 17, TILE_WIDTH / 2.0f, _sprite); }

};

// MONEDA y DERIVADAS //////////////////
class Moneda : public Objeto {
public:
	Moneda(Vector2D pos, const char* ruta_de_textura = "res/texturas/penny.png") : Objeto(ruta_de_textura, pos, obj_t::MONEDA) { GestorSprites::dimensionaSprite(24, 14, TILE_WIDTH / 2.0f, _sprite); }
	
};

class Penny : public Moneda {
public:
	Penny(Vector2D pos) : Moneda(pos, "res/texturas/penny.png") { /*El valor por defecto es 1*/ }
};

class Dime : public Moneda {
public:
	Dime(Vector2D pos) : Moneda(pos, "res/texturas/dime.png") { _valor = 5; }
};

class Nickel : public Moneda {
public:
	Nickel(Vector2D pos) : Moneda(pos, "res/texturas/nickel.png") { _valor = 10; }
};

// LLAVE /////////////////////////////
class Llave : public Objeto {
public:
	Llave(Vector2D pos) : Objeto("res/texturas/key.png", pos, obj_t::LLAVE) { GestorSprites::dimensionaSprite(23, 31, TILE_WIDTH / 2.0f, _sprite); }
	
};

// BONUS ////////////////////////////
class Bonus : public Objeto {
public:
	enum class TIPO {HEALTH, DAMAGE, SPEED, SHOT_SPEED};
	Bonus(Vector2D pos, const char* ruta_de_textura, TIPO tipo, int ancho_de_textura = 26, int alto_de_textura = 29)
		: Objeto(ruta_de_textura, pos, obj_t::BONUS), _tipo(tipo) {
		GestorSprites::dimensionaSprite(ancho_de_textura, alto_de_textura, TILE_WIDTH / 2.0f, _sprite);

		//Ajusta los valores del bonus
		switch (tipo) {
		case TIPO::DAMAGE: _valor = 1.5f; break; //Multiplicador de daño x1.5
		case TIPO::SPEED: _valor = 1.25f; break; //Multiplicador de velocidad x1.25
		case TIPO::SHOT_SPEED: _valor = 0.7f; break; //Multiplicador del tiempo entre disparos x 0.7
		case TIPO::HEALTH: break; //Mantiene el valor en 1, suma 1 de salud
		default: std::cerr << "Tipo de bonus Desconocido\n"; exit(0);
		}
	}
	TIPO bonusType() const { return _tipo; }
protected:
	TIPO _tipo;

};

// FACTORIA /////////////////////////
class Factoria
{
public:
	static Objeto* create(Objeto::obj_t, Vector2D pos);	 //equivalente al constructor normal
	static Objeto* create(const Objeto&);	//equivalente al constructor copia, pero en un ámbito de enlace dinámico
	static void destroy(Objeto* p) { delete p;  p = nullptr; }

	static Objeto* dropRandom(Vector2D pos); //Devuelve un objeto aleatorio

private:
	static Objeto* dropCoin(Vector2D pos); //Devuelve una moneda de valor aleatorio
	static Objeto* dropBonus(Vector2D pos); //Devuelve un bonus aleatorio
	
};

