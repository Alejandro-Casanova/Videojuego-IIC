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
	//Las funciones rebote detienen el cuerpo ante la colision
	static void rebote(Entidad& p, Caja c);
	static bool rebote(Entidad& e, Pared p);
	static void rebote(Entidad& p, Obstaculo o);

	//Las funciones impacto tan solo devuelven true si ocurre colisi�n
	//NOTA: Gracias a la herencia podr�an definirse para recibir una referencia a entidad, siendo as� m�s gen�ricas
	static bool impacto(Proyectil& p, Pared pa);
	static bool impacto(Proyectil& p, Caja c);
	static bool impacto(Proyectil& p, Obstaculo o);
	static bool impacto(Proyectil& p, Enemigo e);
};

