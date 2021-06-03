#pragma once
#include "ColorRGB.h"
#include "Vector2D.h"

class Entidad {
public:
	Entidad();
	virtual ~Entidad();

	virtual void dibuja() = 0;
	virtual void mueve(float t);
	virtual void inicializa();

	void setColor(unsigned char r, unsigned char g, unsigned char b) { _color.set(r, g, b); }
	void setRadio(float radio) { _radio = radio; }
	void setPos(float x, float y) { _posicion.set(x, y); }
	void setVel(float vx, float vy) { _velocidad.set(vx, vy); }
	void setAcel(float ax, float ay) { _aceleracion.set(ax, ay); }
	Vector2D getPos() const { return _posicion; }
	float getRadio() const { return _radio; }

	
protected:
	void dibujaHitbox() const;

	ColorRGB _color;
	float _radio = 1.0f; //Para la hitbox

	Vector2D _posicion;
	Vector2D _velocidad;
	Vector2D _aceleracion;

	friend class Interaccion;
};