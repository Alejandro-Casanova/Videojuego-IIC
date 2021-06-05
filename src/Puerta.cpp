#include "Puerta.h"
#include "GestorSprites.h"
#include "Macros.h"
#include <iostream>

Puerta::Puerta(Room* room, TIPO t, const char* ruta, int pxW, int pxH, float maxDim, float offset) : _roomPtr(room), _tipo(t), _sprite{ ruta, 2 }
{
	//Gira y posiciona el sprite
	switch (t) {
	case TIPO::DOWN:
		_sprite.flip(false, true);
		_posicion.set(0.0f, -(PUERTA_DIST_V + offset));
		GestorSprites::dimensionaHitBox(pxW, pxH, maxDim, _posicion, _hitBox);
		break;
	case TIPO::LEFT:
		_sprite.setAngle(+90.0);
		_posicion.set(-(PUERTA_DIST_H + offset), 0.0f);
		GestorSprites::dimensionaHitBox(pxW, pxH, maxDim, _posicion, _hitBox, true);
		break;
	case TIPO::RIGHT:
		_sprite.setAngle(-90.0);
		_posicion.set(PUERTA_DIST_H + offset, 0.0f);
		GestorSprites::dimensionaHitBox(pxW, pxH, maxDim, _posicion, _hitBox, true);
		break;
	case TIPO::UP:
		_posicion.set(0.0f, PUERTA_DIST_V + offset);
		GestorSprites::dimensionaHitBox(pxW, pxH, maxDim, _posicion, _hitBox);
		break;
	default: std::cerr << "Tipo de puerta no previsto. \n";
	}

	GestorSprites::dimensionaSprite(pxW, pxH, maxDim, _sprite);

	open();
	
}

Puerta::~Puerta()
{
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

PuertaBoss::PuertaBoss(Room* room, TIPO t) : Puerta(room, t, "res/texturas/puerta_boss.png", 61, 77, TILE_WIDTH * 2.0f, -3.0f) {

}