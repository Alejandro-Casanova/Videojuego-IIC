#include "Enemigo.h"
#include <iostream>

Enemigo::Enemigo() {

}

Enemigo::~Enemigo() {

}

Enemigo::Enemigo(Vector2D posicion) {
	//_hitBox.setParedes(posicion, posicion + Vector2D(_ancho, _alto));
	_posicion = posicion;


}


void Enemigo::inicializa()
{
	_sprite.setSize(13, 13);

}
void Enemigo::dibuja()
{
	_sprite.setPos(_posicion.x, _posicion.y);
	_sprite.setSize(13, 13);
	_sprite.draw();
}




void Enemigo::mueve(float t) {
	Entidad::mueve(t);
	_velocidad = (10, 10);
	_sprite.loop();

}
