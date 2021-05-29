#pragma once

class Entidad;
class Caja;
class Pared;
class Obstaculo;
class Proyectil;
class Enemigo;

class Interaccion
{
public:
	static void rebote(Entidad& p, Caja c);
	static bool rebote(Entidad& e, Pared p);
	static void rebote(Entidad& p, Obstaculo o);

	static bool impacto(Proyectil& p, Pared pa);
	static bool impacto(Proyectil& p, Caja c);
	static bool impacto(Proyectil& p, Obstaculo o);
	static bool impacto(Proyectil& p, Enemigo e);
};

