#pragma once

///Basado en el código de Benjamin Arnold: https://github.com/Barnold1953/GraphicsTutorials/blob/master/Bengine/InputManager.h

//Nota: Se discrimina entre teclas normales y especiales, porque tal es el funcionamiento de freeglut. Además, los códigos numéricos
//de algunas de las teclas especiales de freeglut coinciden con los valores ASCII de algunos caracteres. El valor de "GLUT_KEY_LEFT" es 64,
//que coincide con el valor ASCII del caracter 'd'. Esto causaba problemas al disparar con los botones direccionales y moverse  con w,a,s,d

#include "Vector2D.h"
#include <unordered_map>

class GestorDeTeclado
{
public:
    static void update(); //Necesario para la función isKeyPressed

    static void pressKey(int keyID);
    static void releaseKey(int keyID);
    static void pressSpecialKey(int keyID);
    static void releaseSpecialKey(int keyID);

    static void setMouseCoords(float x, float y); //Guarda las coordenadas del cursor

    static bool isKeyDown(int keyID); //Devuelve true si la tecla está presionada
    static bool isKeyPressed(int keyID); //Devuelve true si la tecla JUSTO acaba de ser pulsada
    static bool isKeyUnPressed(int keyID); //Devuelve true si la tecla JUSTO acaba de ser liberada
    static bool isSpecialKeyDown(int keyID); //Devuelve true si la tecla está presionada
    static bool isSpecialKeyPressed(int keyID); //Devuelve true si la tecla JUSTO acaba de ser pulsada
    static bool isSpecialKeyUnPressed(int keyID); //Devuelve true si la tecla JUSTO acaba de ser liberada

    static Vector2D getMouseCoords(){ return _mouseCoords; }

private:
    static bool wasKeyDown(int keyID);
    static bool wasSpecialKeyDown(int keyID);

    static std::unordered_map<int, bool> _keyMap;
    static std::unordered_map<int, bool> _prevKeyMap;
    static std::unordered_map<int, bool> _specialKeyMap;
    static std::unordered_map<int, bool> _prevSpecialKeyMap;
    static Vector2D _mouseCoords;
};

