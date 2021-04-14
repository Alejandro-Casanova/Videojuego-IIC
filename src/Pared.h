#pragma once

#include "Vector2D.h"

class Pared
{
public:
	Pared();
	virtual ~Pared();

	unsigned char r;
	unsigned char g;
	unsigned char b;

	Vector2D limite1;
	Vector2D limite2;
};

