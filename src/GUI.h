#pragma once
#include <vector>
#include <ETSIDI.h>
#include "Macros.h"
#include "Vector2D.h"

class Player;

class GUI
{
public:
	GUI(Player* playerPtr);
	virtual ~GUI();

	void dibuja();

private:
	Player* _playerPtr;
	std::vector<ETSIDI::Sprite*> _sprites;
	Vector2D _origen{ -ROOM_WIDTH / 2.0f - 30.0f, ROOM_HEIGHT / 2.0f };
};

