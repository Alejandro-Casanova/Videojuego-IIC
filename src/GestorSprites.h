#pragma once
#include "Macros.h"
#include "ETSIDI.h"
#include "Caja.h"

class GestorSprites {
public:
	//Evita la deformación de los sprites, recibe las dimensiones de los sprites en pixeles, y la dimensión máxima en el mundo
	static void dimensionaSprite(int pxWidth, int pxHeight, float maxDim, ETSIDI::Sprite& sprite, float centerOffsetY = 0)
	{
		float width, height;
		if (pxWidth >= pxHeight) {
			width = maxDim;
			height = maxDim * pxHeight / pxWidth;
			sprite.setSize(width, height);

		}
		else {
			width = maxDim * pxWidth / pxHeight;
			height = maxDim;
			sprite.setSize(width, height);
		}
		sprite.setCenter(width / 2.0f, height / 2.0f + centerOffsetY);
	}
	static void dimensionaHitBox(float pxWidth, float pxHeight, float maxDim, Vector2D centerPos, Caja& caja, bool rotate90 = false)
	{
		if (rotate90) {
			swap(pxWidth, pxHeight);
		}
		float width, height;
		if (pxWidth >= pxHeight) {
			width = maxDim;
			height = maxDim * pxHeight / pxWidth;
		}
		else {
			width = maxDim * pxWidth / pxHeight;
			height = maxDim;
		}
		caja.setParedes(centerPos - Vector2D(width / 2.0f, height / 2.0f), centerPos + Vector2D(width / 2.0f, height / 2.0f));
	}
private:
	static void swap (float& a, float& b) {
		float aux = a;
		a = b;
		b = aux;
	}
};
