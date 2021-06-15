#include "Objeto.h"
#include "Macros.h"
#include "GestorSprites.h"
#include <sstream>

Objeto::Objeto(const char* ruta_de_textura, Vector2D posicion, obj_t t) : Entidad(posicion, TILE_WIDTH / 4.0f), rtt(t), _sprite{ ruta_de_textura }
{
	
}

void Objeto::dibuja()
{
	Entidad::dibujaHitbox();
	_sprite.setPos(_posicion.x, _posicion.y);
	_sprite.draw();
	
}

Objeto* Factoria::create(const Objeto& ob)
{
	if (ob.type() == Objeto::obj_t::CORAZON) {
		return new Corazon(dynamic_cast<const Corazon&>(ob));			//copia profunda
	}
	else if (ob.type() == Objeto::obj_t::MONEDA) {
		return new Moneda(dynamic_cast<const Moneda&>(ob));
	}
	else if (ob.type() == Objeto::obj_t::LLAVE) {
		return new Llave(dynamic_cast<const Llave&>(ob));
	}

	std::cerr << "error al tratar de construir un objeto desconocido- factory::create(...)";
	return nullptr;
}

Objeto* Factoria::create(Objeto::obj_t t, Vector2D pos) {

	switch (t) {
	case Objeto::obj_t::CORAZON:
		return new Corazon(pos);
	case Objeto::obj_t::MONEDA:
		return dropCoin(pos);
	case Objeto::obj_t::LLAVE:
		return new Llave(pos);
	case Objeto::obj_t::BONUS:
		return dropBonus(pos);
	default:
		std::cerr << "incorrect type-factory::create()" << std::endl;
		return nullptr;
	}

	return nullptr;
}

Objeto* Factoria::dropCoin(Vector2D pos)
{
	double valor = ETSIDI::lanzaDado();
	if (valor < 0.1) return new Nickel(pos);
	else if (valor < 0.4) return new Dime(pos);
	else return new Penny(pos);
}

Objeto* Factoria::dropBonus(Vector2D pos)
{
	//Elige textura y tipo de bonus aleatorios
	std::stringstream ruta;
	int valor = ETSIDI::lanzaDado(10);
	ruta << "res/texturas/pills/" << valor << ".png";
	Bonus::TIPO tipo = Bonus::TIPO::HEALTH;

	switch (ETSIDI::lanzaDado(5)) {
	case 1: tipo = Bonus::TIPO::HEALTH; break;
	case 2: tipo = Bonus::TIPO::DAMAGE; break;
	case 3: tipo = Bonus::TIPO::SHOT_SPEED; break;
	case 4: tipo = Bonus::TIPO::SPEED; break;
	case 5: //lanzaDado nunca devuelve el valor max
		std::cerr << "ERROR en Factoria::dropBonus" << std::endl;
		exit(0);
		break;
	}

	if (valor > 6) return new Bonus(pos, ruta.str().c_str(), tipo, 23, 32);
	else return new Bonus(pos, ruta.str().c_str(), tipo);
}

Objeto* Factoria::dropRandom(Vector2D pos)
{
	double valor = ETSIDI::lanzaDado();
	if (valor >= 0.5) return nullptr; //50% NADA
	else if (valor < 0.2) return create(Objeto::obj_t::CORAZON, pos); //20% Corazón
	else if (valor < 0.35) return dropCoin(pos); //15% Moneda
	else if (valor < 0.45) return dropBonus(pos); //10% Bonus
	else if (valor < 0.5) return create(Objeto::obj_t::LLAVE, pos); //5% Llave
}
