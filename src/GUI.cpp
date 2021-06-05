#include "GUI.h"
#include "Player.h"

#include "Vector2D.h"
#include "GestorSprites.h"
#include <sstream>

GUI::GUI(Player* playerPtr) : _playerPtr(playerPtr)
{
	//_origen = Vector2D(-ROOM_WIDTH / 2.0f - 30.0f, ROOM_HEIGHT / 2.0f);

	_sprites.push_back(new ETSIDI::Sprite("res/texturas/container.png"));
	_sprites.push_back(new ETSIDI::Sprite("res/texturas/penny.png"));
	_sprites.push_back(new ETSIDI::Sprite("res/texturas/key.png"));

	float j = -5.5f;
	for (auto i : _sprites) {
		i->setPos(_origen.x, _origen.y + j);
		j -= 5.0f;
	}

	GestorSprites::dimensionaSprite(24, 20, TILE_WIDTH / 2.0f, *_sprites[0]);
	GestorSprites::dimensionaSprite(25, 14, TILE_WIDTH / 2.0f, *_sprites[1]);
	GestorSprites::dimensionaSprite(23, 31, TILE_WIDTH / 2.0f, *_sprites[2]);

	
}

GUI::~GUI()
{
	for (auto i : _sprites) {
		delete i;
	}
}

void GUI::dibuja()
{
	
	ETSIDI::setTextColor(1, 1, 0);
	ETSIDI::setFont("res/font/upheavtt.ttf", 14);
	ETSIDI::printxy("ISAAC", _origen.x, _origen.y);

	//Dibuja iconos
	for (auto i : _sprites) {
		i->draw();
	}

	//Dibuja stats del jugador
	Vector2D health = _playerPtr->getHealth();
	std::stringstream buffer;
	buffer << health.x << "/" << health.y;
	ETSIDI::printxy(buffer.str().c_str(), _origen.x + 5.0f, _origen.y - 6.0f);
	buffer.str("");
	buffer << _playerPtr->getLlaves();
	ETSIDI::printxy(buffer.str().c_str(), _origen.x + 5.0f, _origen.y - 11.0f);
	buffer.str("");
	buffer << _playerPtr->getDinero();
	ETSIDI::printxy(buffer.str().c_str(), _origen.x + 5.0f, _origen.y - 16.0f);

	//Dibuja Modificadores
}
