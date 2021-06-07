#include "Interaccion.h"
#include "Personaje.h"
#include "Caja.h"
#include "Pared.h"
#include "Obstaculo.h"
#include "Proyectil.h"
#include "ListaProyectil.h"
#include "Enemigo.h"
#include "Vector2D.h"
#include "Room.h"

bool Interaccion::rebote(Entidad& p, Caja c, bool velMod)
{	
	bool t = rebote(p, c._dcha, velMod) + rebote(p, c._izq, velMod) + rebote(p, c._sup, velMod) + rebote(p, c._inf, velMod);
	return t;
}

bool Interaccion::rebote(Entidad& e, Pared p, bool velMod)
{
	Vector2D dir;
	float dif = p.distancia(e._posicion, &dir) - e._radio;
	if (dif <= 0.01f){ 
		//Separa los cuerpos
		e._posicion -= (dir * dif);
		if (velMod) {
			Vector2D v_inicial = e._velocidad;
			e._velocidad = v_inicial - dir * 2.0 * (v_inicial * dir);
		}
		return true;
	}
	return false;
}

bool Interaccion::rebote(Entidad& p, Obstaculo& o){
	return rebote(p, o._hitBox);
}

bool Interaccion::rebote(Entidad& a, Entidad& b)
{
	Vector2D dir = a.getPos() - b.getPos();
	if (dir.modulo() < a._radio + b._radio) {
		float dist = (a._radio + b._radio - dir.modulo()) / 2.0f;
		Vector2D separar = dir.unitario();
		a._posicion += separar * dist;
		b._posicion -= separar * dist;
		return true;
	}
	return false;

}

bool Interaccion::rebote(Entidad& a, Room& b, bool velMod)
{
	bool hayRebote = false;
	for (auto& i : b._obstaculos) {
		if (Interaccion::rebote(a, i->getHitBox(), velMod)) hayRebote = true;
	}
	if (Interaccion::rebote(a, b._paredes, velMod)) hayRebote = true;
	return hayRebote;
}


bool Interaccion::colision(const Entidad& p, const Caja& c) {
	if (colision(p, c._dcha)) return true;
	if (colision(p, c._izq)) return true;
	if (colision(p, c._sup)) return true;
	if (colision(p, c._inf)) return true;
	return false;
}


bool Interaccion::colision(const Entidad& p, const Pared& pa) {
	Vector2D dir;
	float dif = pa.distancia(p._posicion, &dir) - p._radio;
	if (dif <= 0.01f) {
		return true;
	}
	return false;
}

bool Interaccion::colision(const Entidad& pr, const Obstaculo& obs) {
	if (obs._bulletFlag) {
		return colision(pr, obs._hitBox);
	}
		return false;
}



bool Interaccion::colision(const Entidad& p, const Entidad& e) {
	Vector2D dif = p._posicion - e._posicion;
	float d = dif.modulo();
	float dentro = d - (p._radio + e._radio);
	if (dentro < 0.0f) return true;
	return false;
}