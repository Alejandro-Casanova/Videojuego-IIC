#include "GestorDeTeclado.h"

void GestorDeTeclado::update() {

    //Copia el mapa actual en el anterior
    for (auto& it : _keyMap) {
        _prevKeyMap[it.first] = it.second;
    }
}

void GestorDeTeclado::pressKey(int keyID) {
    _keyMap[keyID] = true;
}

void GestorDeTeclado::releaseKey(int keyID) {
    _keyMap[keyID] = false;
}

void GestorDeTeclado::setMouseCoords(float x, float y) {
    _mouseCoords.x = x;
    _mouseCoords.y = y;
}

bool GestorDeTeclado::isKeyDown(int keyID) {
    //Comprueba si ya existe
    auto it = _keyMap.find(keyID);
    if (it != _keyMap.end()) {
        //Encuentra la llave
        return it->second;
    }
    //No encuentra la llave
    return false;
}

bool GestorDeTeclado::isKeyPressed(int keyID) {
    //Comprueba si justo acaba de ser pulsada
    if (isKeyDown(keyID) && (!(wasKeyDown(keyID)))) {
        return true;
    }
    return false;
}

bool GestorDeTeclado::isKeyUnPressed(int keyID) {
    //Comprueba si justo acaba de ser soltada
    if ((!isKeyDown(keyID)) && ((wasKeyDown(keyID)))) {
        return true;
    }
    return false;
}

bool GestorDeTeclado::wasKeyDown(int keyID) {

    //Comprueba si ya existe
    auto it = _prevKeyMap.find(keyID);
    if (it != _prevKeyMap.end()) {
        //Encuentra la llave
        return it->second;
    }
    //No encuentra la llave
    return false;
}

//Evita error de enlazado
std::unordered_map<int, bool> GestorDeTeclado::_keyMap;
std::unordered_map<int, bool> GestorDeTeclado::_prevKeyMap;
Vector2D GestorDeTeclado::_mouseCoords;

