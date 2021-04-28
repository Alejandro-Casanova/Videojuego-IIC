#include "Caja.h"

Caja::Caja()
{

}

Caja::Caja(Vector2D vert1, Vector2D vert2)
{
	setParedes(vert1, vert2);
}

Caja::~Caja()
{
}

void Caja::dibuja() const{
	_dcha.dibuja();
	_izq.dibuja();
	_sup.dibuja();
	_inf.dibuja();
}

void Caja::setParedes(Vector2D vert1, Vector2D vert2)
{
	_izq.setLimites(vert1.x, vert1.y, vert1.x, vert2.y);
	_dcha.setLimites(vert2.x, vert1.y, vert2.x, vert2.y);
	_sup.setLimites(vert1.x, vert2.y, vert2.x, vert2.y);
	_inf.setLimites(vert1.x, vert1.y, vert2.x, vert1.y);
}

void Caja::setColor(ColorRGB c1, ColorRGB c2, ColorRGB c3, ColorRGB c4)
{
	_inf.setColor(c1);
	_sup.setColor(c2);
	_izq.setColor(c3);
	_dcha.setColor(c4);
	
}
