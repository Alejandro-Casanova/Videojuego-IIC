#include "Player.h"
#include "GestorDeTeclado.h"
#include <iostream>
#include "Macros.h"
#include "GestorSprites.h"
#include "Proyectil.h"
#include <iostream>
#include "Objeto.h"

int sign(float x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

Player::Player()
{

	//inicializa();

	GestorSprites::dimensionaSprite(32, 15, 8.0f, _body);
	_body.setCenter(4, 6);
	GestorSprites::dimensionaSprite(40, 28, 12.0f, _head);
	GestorSprites::dimensionaSprite(40, 36, 12.0f, _especial);
}

Player::~Player()
{
}

void Player::tecla()
{
	if ((_velocidad.x * _velocidad.y) != 0) { //Si el movimiento es diagonal, devuelve ambos componentes de velocidad a su valor máximo
		_velocidad.x = _speedStat * sign(_velocidad.x);
		_velocidad.y = _speedStat * sign(_velocidad.y);
	}

	//Movimiento
	if (GestorDeTeclado::isKeyPressed('a')) {
		_velocidad.x -= _speedStat;
	} 
	if (GestorDeTeclado::isKeyUnPressed('a')) {
		_velocidad.x += _speedStat;
	}
	if (GestorDeTeclado::isKeyPressed('d')) {
		_velocidad.x += _speedStat;
	}
	if (GestorDeTeclado::isKeyUnPressed('d')) {
		_velocidad.x -= _speedStat;
	}
	if (GestorDeTeclado::isKeyPressed('w')) {
		_velocidad.y += _speedStat;
	}
	if (GestorDeTeclado::isKeyUnPressed('w')) {
		_velocidad.y -= _speedStat;
	}
	if (GestorDeTeclado::isKeyPressed('s')) {
		_velocidad.y -= _speedStat;
	}
	if (GestorDeTeclado::isKeyUnPressed('s')) {
		_velocidad.y += _speedStat;
	}
	
	//Para corregir posibles errores, si ninguna tecla direccional está pulsada, se detiene al jugador
	if (!GestorDeTeclado::isKeyDown('a') && !GestorDeTeclado::isKeyDown('d')) _velocidad.x = 0;
	if (!GestorDeTeclado::isKeyDown('w') && !GestorDeTeclado::isKeyDown('s')) _velocidad.y = 0;

	if (_velocidad.modulo() > _speedStat) //Si el módulo de la velocidad es mayor de lo que debe, realiza la corrección
		_velocidad = _velocidad.unitario() * _speedStat;
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
	if (GestorDeTeclado::isSpecialKeyDown(GLUT_KEY_DOWN)) {
		if (_shootCounter > 0.2f) _head.setState(0);
		else _head.setState(1);
	}
	if (GestorDeTeclado::isSpecialKeyDown(GLUT_KEY_RIGHT)) {
		if (_shootCounter > 0.2f) _head.setState(2);
		else _head.setState(3);
	}
	if (GestorDeTeclado::isSpecialKeyDown(GLUT_KEY_UP)) {
		if (_shootCounter > 0.2f) _head.setState(4);
		else _head.setState(5);
	}
	if (GestorDeTeclado::isSpecialKeyDown(GLUT_KEY_LEFT)) {
		if (_shootCounter > 0.2f) _head.setState(6);
		else _head.setState(7);
	}
	if (_shootCounter > 0.2f && (_head.getState() % 2)) _head.setState(_head.getState() - 1); //Evita que se quede con los ojos cerrados

	if (_damageTimer != 0) {
		_especial.setState(1);
		_especial.draw();
	}
	else {
		_head.draw();
		_body.draw();
	}
	//std::cout << _sprite.getState();

	glPopMatrix();
}

void Player::inicializa(){
	setRadio(5.0f);
	setPos(0.0f, 0.0f);
	inicializaStats();
	
}

void Player::inicializaStats()
{
	_llaves = 0;
	_dinero = 0;
	_healthStat = SALUD_JUGADOR;
	_healthCounter = _healthStat;
	_speedStat = VELOCIDAD_JUGADOR;
	_bulletSpeed = VEL_PROYECTIL_JUGADOR;
	_bulletSpeed = VEL_PROYECTIL_JUGADOR;
	_shootSpeed = VEL_DISPARO_JUGADOR;
	_shotDamage = DAMAGE_DISPARO_JUGADOR;
	_damageTimer = 0;
	_shootCounter = 0;
}

void Player::mueve(float t)
{
	Personaje::mueve(t);
	_body.loop();

	//Gestion de la invulnerabilidad
	_damageTimer -= t;
	if (_damageTimer < 0) _damageTimer = 0;
	//std::cout << _damageTimer << "   " << _healthCounter << std::endl;
}

bool Player::recibeHerida(float damage)
{
	if (_damageTimer == 0) {
		_damageTimer = T_INVULNERABLE;
		ETSIDI::play("res/audio/ow.wav");
		return Personaje::recibeHerida(damage);
	}
	return false;
	
}

bool Player::recibeObjeto(const Objeto& obj)
{
	switch (obj.type()) {
	case Objeto::obj_t::CORAZON:
		if (_healthCounter == _healthStat) return false; //Si ya tiene salud máxima
		_healthCounter += obj.getValor();
		if (_healthCounter > _healthStat) _healthCounter = _healthStat;
		break;
	case Objeto::obj_t::LLAVE:
		_llaves += obj.getValor();
		break;
	case Objeto::obj_t::MONEDA:
		_dinero += obj.getValor();
		break;
	default:
		std::cerr << "Se ha recogido un objeto indefinido.\n";
		break;
	}
	return true;
}

Proyectil* Player::dispara()
{
	//DISPARO
	if (GestorDeTeclado::isSpecialKeyDown(GLUT_KEY_LEFT) || GestorDeTeclado::isSpecialKeyDown(GLUT_KEY_DOWN) || GestorDeTeclado::isSpecialKeyDown(GLUT_KEY_RIGHT) || GestorDeTeclado::isSpecialKeyDown(GLUT_KEY_UP)) {
		if (Personaje::puedeDisparar()) { //Indica si el jugador está listo para disparar
			ETSIDI::play("res/audio/agua.wav");
			// Creacion de un proyectil
			Proyectil* d = new Proyectil();
			//	proyectil.setOrigen(Vector2D.player)
			Vector2D pos = getPos();
			d->setPos(pos.x, pos.y);
			Vector2D proyp = d->getPos();

			float vel = getBulletSpeed();
			if (GestorDeTeclado::isSpecialKeyDown(GLUT_KEY_LEFT))
				d->setVel(-vel, 0);
			else if (GestorDeTeclado::isSpecialKeyDown(GLUT_KEY_RIGHT))
				d->setVel(vel, 0);
			else if (GestorDeTeclado::isSpecialKeyDown(GLUT_KEY_UP))
				d->setVel(0, vel);
			else if (GestorDeTeclado::isSpecialKeyDown(GLUT_KEY_DOWN))
				d->setVel(0, -vel);

			return d;

		}
	}
	/*if (Personaje::dispara()) {
		ETSIDI::play("res/audio/agua.wav");
		return true;
	}
	return false;*/
	return nullptr;
}

void Player::flipPos(bool H, bool V)
{
	if (H) _posicion.x *= -1;
	if (V) _posicion.y *= -1;
}


/*
//				INTENTO FALLIDO DE LOGRAR UN MOVIMIENTO DIRECCIONAL

	int a = 0, w = 0, s = 0, d = 0, nteclas = 0;
	float angulo1 = 0, angulo2 = 0, angulo3 = 0, angulo4 = 0, angulot = 0;
	if (GestorDeTeclado::isKeyPressed('a')){
		a = 1;
		angulo1 = PI;
	}
	if (GestorDeTeclado::isKeyUnPressed('a')) {
		a = 0;
		angulo1 = 0;
	}

	if (GestorDeTeclado::isKeyPressed('w')) {
		w = 1;
		angulo2 = PI/2;
	}
	if (GestorDeTeclado::isKeyUnPressed('w')) {
		w = 0;
		angulo2 = 0;
	}

	if (GestorDeTeclado::isKeyPressed('d')) {
		d = 1;
		angulo3 = 2*PI;
	}
	if (GestorDeTeclado::isKeyUnPressed('d')) {
		d = 0;
		angulo3 = 0;
	}

	if (GestorDeTeclado::isKeyPressed('s')) {
		s = 1;
		angulo4 = PI*1.5F;
	}
	if (GestorDeTeclado::isKeyUnPressed('s')) {
		s = 0;
		angulo4 = 0;
	}

	nteclas = a + w + d + s;
	angulot = angulo1 + angulo2 + angulo3 + angulo4;
	if (nteclas != 0) {
		_velocidad.x = _speedStat * cos(angulot/nteclas);
		_velocidad.y = _speedStat * sin(angulot/nteclas);

	}
	else if (nteclas == 0 && angulot == 0) {
		_velocidad = 0, 0;
	}
*/