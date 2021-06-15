#pragma once

class Entidad;
class Caja;
class Pared;
class Obstaculo;
class Proyectil;
class Enemigo;

class Objeto;

class Room;


class Interaccion
{
public:
	//Las funciones rebote detienen el cuerpo ante la colision
	static bool rebote(Entidad& p, Caja c, bool velMod = false); //Si el booleano es true, modifica la velocidad de la entidad para que rebote
	static bool rebote(Entidad& e, Pared p, bool velMod = false); //Si el booleano es true, modifica la velocidad de la entidad para que rebote
	static bool rebote(Entidad& p, Obstaculo& o);
	static bool rebote(Entidad& a, Entidad& b);

	static bool rebote(Entidad& a, Room& b, bool velMod = false, bool skipObstaculos = false); //Combina varias llamadas a las anteriores

	//Las funciones impacto tan solo devuelven true si ocurre colisión
	static bool colision(const Entidad& p, const Pared& pa);
	static bool colision(const Entidad& p, const Caja& c);
	static bool colision(const Entidad& p, const Obstaculo& o);
	static bool colision(const Entidad& p, const Entidad& e);

	static bool insideBox(Entidad& p, const Caja& c, bool corrige = false); //Comprueba si una entidad se encuentra dentro de la caja
	static bool outsideBox(Entidad& p, const Caja& c, bool corrige = false); //Comprueba si una entidad se encuentra fuera de la caja
};

