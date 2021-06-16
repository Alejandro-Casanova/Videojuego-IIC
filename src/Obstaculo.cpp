#include "Obstaculo.h"
#include "Macros.h"

Obstaculo::Obstaculo(Vector2D posicion, const char* ruta_de_textura) : _sprite{ ruta_de_textura }
{
	_hitBox.setParedes(posicion, posicion + Vector2D(_ancho, _alto));
	_posicion = posicion;

	
	
	
	
	_sprite.setSize(TILE_WIDTH, TILE_WIDTH);
	_sprite.setCenter(0.0f, 0.0f);

}

void Obstaculo::dibuja()
{
	//_hitBox.dibuja();
	_sprite.setPos(_posicion.x, _posicion.y);
	_sprite.draw();
}

Roca::Roca(Vector2D posicion) : Obstaculo(posicion, "res/texturas/rocas.png"){
	
}

Hueco::Hueco(Vector2D posicion) : Obstaculo(posicion, "res/texturas/hole.png") { 
	_bulletFlag = false;
	
}
