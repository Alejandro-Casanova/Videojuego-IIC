#pragma once

#include "Vector2D.h"
#include "ColorRGB.h"

class Pared
{
public:
	Pared();
	Pared(float limite1x, float limite1y, float limite2x, float limite2y);
	virtual ~Pared();

	void dibuja() const;

	void setColor(ColorRGB nColor) { _color = nColor; }
	void setLimites(float limite1x, float limite1y, float limite2x, float limite2y);

private:
	ColorRGB _color = { 255, 255, 255 };
	Vector2D _limite1;
	Vector2D _limite2;
};

