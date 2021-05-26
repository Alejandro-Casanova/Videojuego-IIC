#pragma once
//Basado en el código desarrollado en clase por Pablo San Segundo

#include <iostream>
#include <string>
#include <vector>
#include "Entidad.h"

class Objeto : public Entidad
{
public:
	enum obj_t { OBJETO = 0, CORAZON, MONEDA, LLAVE };
protected:
	obj_t rtt;
	Objeto(obj_t t = OBJETO) :rtt(t) {}
public:
	virtual ~Objeto() {};												//declaración virtual al dest. OBLIGATORIA!
	obj_t type() const { return rtt; }
	virtual std::ostream& print(std::ostream& o = std::cout) const = 0;
	friend std::ostream& operator <<(std::ostream& o, const Objeto& ob) { return ob.print(o); }
	void dibuja() override {} //TO DO

};

class Corazon : public Objeto {
public:
	Corazon() : Objeto(CORAZON) {}
	void valor() { std::cout << "corazon valor 10HP" << std::endl; }
	std::ostream& print(std::ostream& o = std::cout) const override{ o << "soy un corazon" << std::endl; return o; }
};

class Moneda : public Objeto {
public:
	Moneda() : Objeto(MONEDA) {}
	void valor() { std::cout << "moneda valor 5G" << std::endl; }
	std::ostream& print(std::ostream& o = std::cout) const override{ o << "soy una Moneda" << std::endl; return o; }
};

class Llave : public Objeto {
public:
	Llave() : Objeto(LLAVE) {}
	//void peso() { cout << "arco-peso 3Kg" << endl; }
	std::ostream& print(std::ostream& o = std::cout) const { o << "soy una Moneda" << std::endl; return o; }
};

