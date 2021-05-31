#include "Interaccion.h"
#include "Personaje.h"
#include "Caja.h"
#include "Pared.h"
#include "Obstaculo.h"
#include "Proyectil.h"
#include "ListaProyectil.h"
#include "Enemigo.h"
#include "Vector2D.h"

void Interaccion::rebote(Entidad& p, Caja c)
{
	rebote(p, c._dcha);
	rebote(p, c._izq);
	rebote(p, c._sup);
	rebote(p, c._inf);
}

bool Interaccion::rebote(Entidad& e, Pared p)
{
	Vector2D dir;
	float dif = p.distancia(e._posicion, &dir) - e._radio;
	if (dif <= 0.0f){
		//Separa los cuerpos
		e._posicion -= (dir * dif);
		return true;
	}
	return false;
}

void Interaccion::rebote(Entidad& p, Obstaculo o){
	rebote(p, o._hitBox);
}


bool Interaccion::impacto(Proyectil& p, Caja c) {
	if (impacto(p, c._dcha)) return true;
	if (impacto(p, c._izq)) return true;
	if (impacto(p, c._sup)) return true;
	if (impacto(p, c._inf)) return true;
	return false;
}


bool Interaccion::impacto(Proyectil& p, Pared pa) {
	Vector2D dir;
	float dif = pa.distancia(p._posicion, &dir) - p._radio;
	if (dif <= 0.01f) {
		return true;
	}
	return false;
}

bool Interaccion::impacto(Proyectil& pr, Obstaculo obs) {
	if (obs._bulletFlag) {
		return impacto(pr, obs._hitBox);
	}
		return false;
}



bool Interaccion::impacto(Proyectil& p, Enemigo e) {
	Vector2D dif = p._posicion - e._posicion;
	float d = dif.modulo();
	float dentro = d - (p._radio + e._radio);
	if (dentro < 0.0f) return true;
	return false;
}