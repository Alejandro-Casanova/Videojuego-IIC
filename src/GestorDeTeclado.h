#pragma once

///Basado en el código de Benjamin Arnold: https://github.com/Barnold1953/GraphicsTutorials/blob/master/Bengine/InputManager.h

#include "Vector2D.h"
#include <unordered_map>

class GestorDeTeclado
{
public:
    static void update();

    static void pressKey(int keyID);
    static void releaseKey(int keyID);

    static void setMouseCoords(float x, float y);

    static bool isKeyDown(int keyID);
    static bool isKeyPressed(int keyID);
    static bool isKeyUnPressed(int keyID);

    static Vector2D getMouseCoords(){ return _mouseCoords; }

private:
    static bool wasKeyDown(int keyID);

    static std::unordered_map<int, bool> _keyMap;
    static std::unordered_map<int, bool> _prevKeyMap;
    static Vector2D _mouseCoords;
};

