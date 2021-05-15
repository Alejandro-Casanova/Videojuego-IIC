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
	static void impacto(Proyectil& p, Obstaculo);
	static void impacto(Proyectil& p, Enemigo);
	static void impacto(Proyectil& p, Pared);
};

