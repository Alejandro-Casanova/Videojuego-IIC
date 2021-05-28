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
	std::ostream& print(std::ostream& o = std::cout) const override { o << "soy un corazon" << std::endl; return o; }
};

class Moneda : public Objeto {
public:
	Moneda() : Objeto(MONEDA) {}
	void valor() { std::cout << "moneda valor 5G" << std::endl; }
	std::ostream& print(std::ostream& o = std::cout) const override { o << "soy una Moneda" << std::endl; return o; }
};

class Llave : public Objeto {
public:
	Llave() : Objeto(LLAVE) {}
	//void peso() { cout << "arco-peso 3Kg" << endl; }
	std::ostream& print(std::ostream& o = std::cout) const { o << "soy una Moneda" << std::endl; return o; }
};

class Factoria
{
public:
	static Objeto* create(Objeto::obj_t);			//equivalente al constructor normal
	static Objeto* create(const Objeto&);			//equivalente al constructor copia, pero en un ámbito de enlace dinámico
	static void destroy(Objeto* p) { delete p;  p = nullptr; }
};

Objeto* Factoria::create(const Objeto& ob)
{
	if (ob.type() == Objeto::CORAZON) {
		return new Corazon(dynamic_cast<const Corazon&>(ob));			//copia profunda
	}
	else if (ob.type() == Objeto::MONEDA) {
		return new Moneda(dynamic_cast<const Moneda&>(ob));
	}
	else if (ob.type() == Objeto::LLAVE) {
		return new Llave(dynamic_cast<const Llave&>(ob));
	}

	std::cerr << "error al tratar de construir un objeto desconocido- factory::create(...)";
	return NULL;
}

Objeto* Factoria::create(Objeto::obj_t t) {

	switch (t) {
	case Objeto::CORAZON:
		return new Corazon;
	case Objeto::MONEDA:
		return new Moneda;
	case Objeto::LLAVE:
		return new Llave;
	default:
		std::cerr << "incorrect type-factory::create()" << std::endl;
		return nullptr;
	}

	return nullptr;
}