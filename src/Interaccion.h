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
	static void rebote(Entidad& p, Obstaculo& o);
	static bool rebote(Entidad& a, Entidad& b);

	//Las funciones impacto tan solo devuelven true si ocurre colisi�n
	//NOTA: Gracias a la herencia podr�an definirse para recibir una referencia a entidad, siendo as� m�s gen�ricas
	static bool colision(const Entidad& p, const Pared& pa);
	static bool colision(const Entidad& p, const Caja& c);
	static bool colision(const Entidad& p, const Obstaculo& o);
	static bool colision(const Entidad& p, const Entidad& e);
};

