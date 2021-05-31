#pragma once

///Basado en el código de Benjamin Arnold: https://github.com/Barnold1953/GraphicsTutorials/blob/master/Bengine/InputManager.h

#include "Vector2D.h"
#include <unordered_map>

class GestorDeTeclado
{
public:
    static void update(); //Necesario para la función isKeyPressed

    static void pressKey(int keyID);
    static void releaseKey(int keyID);

    static void setMouseCoords(float x, float y); //Guarda las coordenadas del cursor

    static bool isKeyDown(int keyID); //Devuelve true si la tecla está presionada
    static bool isKeyPressed(int keyID); //Devuelve true si la tecla JUSTO acaba de ser pulsada
    static bool isKeyUnPressed(int keyID); //Devuelve true si la tecla JUSTO acaba de ser liberada

    static Vector2D getMouseCoords(){ return _mouseCoords; }

private:
    static bool wasKeyDown(int keyID);

    static std::unordered_map<int, bool> _keyMap;
    static std::unordered_map<int, bool> _prevKeyMap;
    static Vector2D _mouseCoords;
};

