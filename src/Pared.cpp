#include "Pared.h"
#include "freeglut.h"

Pared::Pared() {

}

Pared::Pared(float limite1x, float limite1y, float limite2x, float limite2y) :
	_limite1(limite1x, limite1y), _limite2(limite2x, limite2y)
{

}

Pared::~Pared() {

}

void Pared::dibuja() const{
	_color.ponColor();
	glBegin(GL_LINES);
	glVertex3f(_limite1.x, _limite1.y, 0.0f);
	glVertex3f(_limite2.x, _limite2.y, 0.0f);
	glEnd();
}

void Pared::setLimites(float limite1x, float limite1y, float limite2x, float limite2y)
{
	_limite1.x = limite1x;
	_limite1.y = limite1y;
	_limite2.x = limite2x;
	_limite2.y = limite2y;
}
