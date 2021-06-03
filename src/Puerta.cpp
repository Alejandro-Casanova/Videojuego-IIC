#include "Puerta.h"
#include "GestorSprites.h"
#include "Macros.h"
#include <iostream>

Puerta::Puerta(Room* room, TIPO t) : _roomPtr(room), _tipo(t)
{
	//Gira y posiciona el sprite
	switch (t) {
	case TIPO::DOWN:
		_sprite.flip(false, true);
		_posicion.set(0.0f, -PUERTA_DIST_V);
		GestorSprites::dimensionaHitBox(49, 33, TILE_WIDTH * 1.5f, _posicion, _hitBox);
		break;
	case TIPO::LEFT:
		_sprite.setAngle(+90.0);
		_posicion.set(-PUERTA_DIST_H, 0.0f);
		GestorSprites::dimensionaHitBox(49, 33, TILE_WIDTH * 1.5f, _posicion, _hitBox, true);
		break;
	case TIPO::RIGHT:
		_sprite.setAngle(-90.0);
		_posicion.set(PUERTA_DIST_H, 0.0f);
		GestorSprites::dimensionaHitBox(49, 33, TILE_WIDTH * 1.5f, _posicion, _hitBox, true);
		break;
	case TIPO::UP:
		_posicion.set(0.0f, PUERTA_DIST_V);
		GestorSprites::dimensionaHitBox(49, 33, TILE_WIDTH * 1.5f, _posicion, _hitBox);
		break;
	default: std::cerr << "Tipo de puerta no previsto. \n";
	}

	GestorSprites::dimensionaSprite(49, 33, TILE_WIDTH * 1.5f, _sprite);
	
}

void Puerta::dibuja()
{
	_hitBox.dibuja();

	glPushMatrix();
	glTranslatef(_posicion.x, _posicion.y, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	_sprite.draw();

	glPopMatrix();

	
}
