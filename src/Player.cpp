#include "Player.h"
#include "GestorDeTeclado.h"
#include <iostream>

Player::Player()
{
}

Player::~Player()
{
}

void Player::tecla()
{
	//Movimiento
	if (GestorDeTeclado::isKeyPressed('a')) {
		_velocidad.x -= 20.0f;
	} 
	if (GestorDeTeclado::isKeyUnPressed('a')) {
		_velocidad.x += 20.0f;
	}
	if (GestorDeTeclado::isKeyPressed('d')) {
		_velocidad.x += 20.0f;
	}
	if (GestorDeTeclado::isKeyUnPressed('d')) {
		_velocidad.x -= 20.0f;
	}
	if (GestorDeTeclado::isKeyPressed('w')) {
		_velocidad.y += 20.0f;
	}
	if (GestorDeTeclado::isKeyUnPressed('w')) {
		_velocidad.y -= 20.0f;
	}
	if (GestorDeTeclado::isKeyPressed('s')) {
		_velocidad.y -= 20.0f;
	}
	if (GestorDeTeclado::isKeyUnPressed('s')) {
		_velocidad.y += 20.0f;
	}

	//Disparo
	//ObjetoMovil::mueve(t);
	//sprite.loop();
}

void Player::teclaEspecial()
{
}

void Player::dibuja()
{
	dibujaHitbox();

	glPushMatrix();
	glTranslatef(_posicion.x, _posicion.y, 0);
	glColor3f(1.0f, 0.0f, 0.0f);

	//glutSolidSphere(1.8, 20, 20);

	//gestion de direccion y animacion
	if (_velocidad.x > 0.01) {//DERECHA
		_body.flip(false, false);
		_head.setState(2);
	}
	else if (_velocidad.x < -0.01) {//IZQUIERDA
		_body.flip(true, false);
		_head.setState(6);
	}
	if (_velocidad.y > 0.01) {//ARRIBA
		_head.setState(4);
	}
	else if (_velocidad.y < -0.01) {//ABAJO
		_head.setState(0);
	}
	//QUIETO
	if ((_velocidad.x < 0.01) && (_velocidad.x > -0.01) && (_velocidad.y < 0.01) && (_velocidad.y > -0.01))
		_body.setState(10);
	else if (_body.getState() == 10)
		_body.setState(10, false);

	//GESTION DE MOVIMIENTO VERTICAL/HORIZONTAL
	if ((_velocidad.x > 0.01) || (_velocidad.x < -0.01)) {
		if (_body.getState() > 9) {
			_body.setState(1, false);
		}
	}
	else if((_velocidad.y > 0.01) || (_velocidad.y < -0.01)){
		if (_body.getState() < 10) {
			_body.setState(10, false);
		}
	}

	//GUIÑO Y ORIENTACION CABEZA
	if (GestorDeTeclado::isKeyDown('k')) {
		if (_shootCounter > 0.2f) _head.setState(0);
		else _head.setState(1);
	}
	if (GestorDeTeclado::isKeyDown('l')) {
		if (_shootCounter > 0.2f) _head.setState(2);
		else _head.setState(3);
	}
	if (GestorDeTeclado::isKeyDown('i')) {
		if (_shootCounter > 0.2f) _head.setState(4);
		else _head.setState(5);
	}
	if (GestorDeTeclado::isKeyDown('j')) {
		if (_shootCounter > 0.2f) _head.setState(6);
		else _head.setState(7);
	}
	if (_shootCounter > 0.2f && (_head.getState() % 2)) _head.setState(_head.getState() - 1); //Evita que se quede con los ojos cerrados

	_head.draw();
	_body.draw();
	//std::cout << _sprite.getState();

	glPopMatrix();
}

void Player::inicializa(){

	_body.setCenter(4, 6);
	_body.setSize(8, 3.75);
	_head.setCenter(6, 4);
	_head.setSize(12, 8.4);
	setRadio(5.0f);
	//_setPos(0.0f, -7.5f);
}

void Player::mueve(float t)
{
	Personaje::mueve(t);
	_body.loop();
}