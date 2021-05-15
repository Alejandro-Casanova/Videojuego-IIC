#include "ListaProyectil.h"

ListaProyectil::ListaProyectil()
{
	contador = 0;
	for (int i = 0; i < MAX_PROYECTILES; i++)
	{
		lista_Pro[i] = 0; //Por ahora los 100 valores del puntero no apuntan a nada
	}
}

ListaProyectil::~ListaProyectil()
{
}

void ListaProyectil::destruirContenido()
{
	for (int i = 0; i < contador; i++)
	{
		delete lista_Pro[i];
	}
	contador = 0;
}

///AGREGAR - DESTRUIR///
bool ListaProyectil::agregar(Proyectil* f)
{
	if (contador < MAX_PROYECTILES)
		lista_Pro[contador++] = f;
	else
		return false;

	return true;
}

void ListaProyectil::eliminar(Proyectil* f)
{
	for (int i = 0; i < contador; i++)
		if (lista_Pro[i] == f)
		{
			eliminar(lista_Pro[i]);
			return;
		}
}
void ListaProyectil::dibuja()
{
	for (int i = 0; i < contador; i++)
		lista_Pro[i]->dibuja();
}

void ListaProyectil::mueve(float t)
{
	for (int i = 0; i < contador; i++)
		lista_Pro[i]->mueve(t);
}


void ListaProyectil::setColor(char r, char g, char b) {
	for (int i = 0; i < contador; i++) {

		lista_Pro[i]->setColor(r, g, b);
	}
}

Proyectil* ListaProyectil::operator[](int i)
{
	if (i >= contador) //si me paso devuelvo la ultima
		i = contador - 1;
	if (i < 0) //si el indice es negativo, devuelvo la primera
		i = 0;
	return lista_Pro[i];
}