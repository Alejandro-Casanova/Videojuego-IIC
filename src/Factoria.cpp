#include "Factoria.h"
#include "Objeto.h"

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