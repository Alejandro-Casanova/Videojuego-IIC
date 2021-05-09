#pragma once

class Personaje;
class Caja;
class Pared;
class Obstaculo;

class Interaccion
{
public:
	static void rebote(Personaje& p, Caja c);
	static bool rebote(Personaje& e, Pared p);
	static void rebote(Personaje& p, Obstaculo o);
};

