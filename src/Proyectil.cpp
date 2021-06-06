#include "Proyectil.h"
#include "freeglut.h"
#include "iostream"
#include "Macros.h"
#include "GestorSprites.h"


Proyectil::Proyectil()
{
	_radio = 1.0f;
}

Proyectil::~Proyectil() 
{

}

void Proyectil::dibuja(){
	glTranslatef(_posicion.x, _posicion.y, 0);
	_color.ponColor();
	glutSolidSphere(_radio, 20, 20);
	glTranslatef(-_posicion.x, -_posicion.y, 0);
}

//SETS DE DIFERENTES VALORES

void Proyectil::setOrigen(float ox, float oy) {
	_origen.x = ox;
	_origen.y = oy;
}

void Proyectil::inicializa()
{

}

Hueso::Hueso()
{
	_radio = TILE_WIDTH / 3.0f;
	GestorSprites::dimensionaSprite(320, 190, TILE_WIDTH, _sprite);

}

void Hueso::dibuja()
{
	dibujaHitbox();
	glTranslatef(_posicion.x, _posicion.y, 0);
	_color.ponColor();
	_sprite.draw();
	glTranslatef(-_posicion.x, -_posicion.y, 0);
}

void Hueso::mueve(float t)
{
	Entidad::mueve(t);
	_sprite.setAngle(_sprite.getAngle() + double(t) * 360.0f);
}
