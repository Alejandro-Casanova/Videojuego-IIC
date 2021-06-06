#include "Puerta.h"
#include "GestorSprites.h"
#include "Macros.h"
#include <iostream>

Puerta::Puerta(Vector2D posicion) : _posicion(posicion)
{

}


PuertaRoom::PuertaRoom(Room* room, ORIENTACION t, const char* ruta, int pxW, int pxH, float maxDim, float offset) 
	: _roomPtr(room), _orientacion(t), _sprite{ ruta, 2 }
{
	//Gira y posiciona el sprite
	switch (t) {
	case ORIENTACION::DOWN:
		_sprite.flip(false, true);
		_posicion.setXY(0.0f, -(PUERTA_DIST_V + offset));
		GestorSprites::dimensionaHitBox(pxW, pxH, maxDim, _posicion, _hitBox);
		break;
	case ORIENTACION::LEFT:
		_sprite.setAngle(+90.0);
		_posicion.setXY(-(PUERTA_DIST_H + offset), 0.0f);
		GestorSprites::dimensionaHitBox(pxW, pxH, maxDim, _posicion, _hitBox, true);
		break;
	case ORIENTACION::RIGHT:
		_sprite.setAngle(-90.0);
		_posicion.setXY(PUERTA_DIST_H + offset, 0.0f);
		GestorSprites::dimensionaHitBox(pxW, pxH, maxDim, _posicion, _hitBox, true);
		break;
	case ORIENTACION::UP:
		_posicion.setXY(0.0f, PUERTA_DIST_V + offset);
		GestorSprites::dimensionaHitBox(pxW, pxH, maxDim, _posicion, _hitBox);
		break;
	default: std::cerr << "Tipo de puerta no previsto. \n";
	}

	GestorSprites::dimensionaSprite(pxW, pxH, maxDim, _sprite);

	open();
	
}

PuertaRoom::~PuertaRoom()
{
}

void PuertaRoom::dibuja()
{
	_hitBox.dibuja();

	glPushMatrix();
	glTranslatef(_posicion.x, _posicion.y, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	_sprite.draw();

	glPopMatrix();

	
}

PuertaBoss::PuertaBoss(Room* room, ORIENTACION t) : PuertaRoom(room, t, "res/texturas/puerta_boss.png", 61, 77, TILE_WIDTH * 2.0f, -3.0f) {
	
}

Trampilla::Trampilla(Vector2D pos, const char* ruta_de_sprite, int pxW, int pxH, float maxDim)
	: Puerta(pos), _sprite{ ruta_de_sprite }
{
	GestorSprites::dimensionaHitBox(pxW, pxH, maxDim, _posicion, _hitBox);
	GestorSprites::dimensionaSprite(pxW, pxH, maxDim, _sprite);
}

void Trampilla::dibuja()
{
	_hitBox.dibuja();

	glPushMatrix();
	glTranslatef(_posicion.x, _posicion.y, 0);
	glColor3f(1.0f, 1.0f, 1.0f);

	_sprite.draw();

	glPopMatrix();
}

