#include "Obstaculo.h"

Obstaculo::Obstaculo()
{
}

Obstaculo::Obstaculo(const char* ruta_de_textura, Caja hitBox)
{
}

void Obstaculo::dibuja() const
{
	//TO DO:

	/*glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textura.id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex3f(-_ancho / 2.0f - _bordeText, _alto / 2.0f + _bordeText, 0.0f);
	glTexCoord2d(1, 1); glVertex3f(_ancho / 2.0f + _bordeText, _alto / 2.0f + _bordeText, 0.0f);
	glTexCoord2d(1, 0); glVertex3f(_ancho / 2.0f + _bordeText, -_alto / 2.0f - _bordeText, 0.0f);
	glTexCoord2d(0, 0); glVertex3f(-_ancho / 2.0f - _bordeText, -_alto / 2.0f - _bordeText, 0.0f);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);*/
}

void Obstaculo::cargaTextura(const char* ruta_de_textura)
{
	_textura = ETSIDI::getTexture(ruta_de_textura);
}