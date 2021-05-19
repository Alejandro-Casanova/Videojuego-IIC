#pragma once

class Personaje;
class Caja;
class Pared;
class Obstaculo;
class Proyectil;
class Enemigo;

class Interaccion
{
public:
	static void rebote(Personaje& p, Caja c);
	static bool rebote(Personaje& e, Pared p);
	static void rebote(Personaje& p, Obstaculo o);
	static bool impacto(Proyectil& p, Pared pa);
	static bool impacto(Proyectil& p, Obstaculo o);
	static bool impacto(Proyectil& p, Personaje per);
};

