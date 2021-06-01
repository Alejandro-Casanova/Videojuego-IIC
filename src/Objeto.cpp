#include "Objeto.h"
#include "Macros.h"

Objeto::Objeto(const char* ruta_de_textura, Vector2D posicion, obj_t t) : rtt(t), _sprite{ ruta_de_textura }
{
	_radio = TILE_WIDTH / 4.0f;
	_posicion = posicion + Vector2D{TILE_WIDTH / 2.0f, TILE_WIDTH / 2.0f};
	
}

void Objeto::dibuja()
{
	Entidad::dibujaHitbox();
	_sprite.setPos(_posicion.x, _posicion.y);
	_sprite.draw();
}

void Objeto::dimensionaSprite(int pxWidth, int pxHeight)
{
	float width, height;
	if (pxWidth >= pxHeight) {
		width = TILE_WIDTH / 2.0f;
		height = TILE_WIDTH * pxHeight / 2.0f / pxWidth;
		_sprite.setSize(width, height);
		
	}
	else {
		width = TILE_WIDTH * pxWidth / pxHeight / 2.0f;
		height = TILE_WIDTH / 2.0f;
		_sprite.setSize(width, height);
	}
	_sprite.setCenter(width / 2.0f, height / 2.0f);
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
		return new Moneda(pos);
	case Objeto::obj_t::LLAVE:
		return new Llave(pos);
	default:
		std::cerr << "incorrect type-factory::create()" << std::endl;
		return nullptr;
	}

	return nullptr;
}