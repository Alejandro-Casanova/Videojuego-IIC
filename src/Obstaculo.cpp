#include "Obstaculo.h"

Obstaculo::Obstaculo()
{
	
}

Obstaculo::Obstaculo(Vector2D posicion, const char* ruta_de_textura) {
	_hitBox.setParedes(posicion, posicion + Vector2D(_ancho, _alto));
	_posicion = posicion;
	cargaTextura(ruta_de_textura);
	
}

Obstaculo::Obstaculo(const char* ruta_de_textura, Caja hitBox)
{
	_hitBox = hitBox;
	cargaTextura(ruta_de_textura);


}

Obstaculo::Obstaculo(Caja hitBox)
{
	_hitBox = hitBox;
}

void Obstaculo::dibuja() const
{

	_hitBox.dibuja();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textura.id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex3f(_posicion.x, _posicion.y,0.0f);
	glTexCoord2d(1, 1); glVertex3f(_posicion.x + _ancho, _posicion.y , 0.0f);
	glTexCoord2d(1, 0); glVertex3f(_posicion.x +_ancho, _posicion.y + _alto, 0.0f);
	glTexCoord2d(0, 0); glVertex3f(_posicion.x , _posicion.y + _alto, 0.0f);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	
}

void Obstaculo::cargaTextura(const char* ruta_de_textura)
{
	_textura = ETSIDI::getTexture(ruta_de_textura);
}