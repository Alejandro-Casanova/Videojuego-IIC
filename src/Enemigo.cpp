#include "Enemigo.h"
#include <iostream>
#include "Interaccion.h"
#include "GestorSprites.h"
#include "Player.h"
#include "ListaProyectil.h"

Enemigo::~Enemigo() {

}

Enemigo::Enemigo(Vector2D posicion, Player* playerPtr) :  _playerPtr(playerPtr) {
	_posicion = posicion;
}

void Enemigo::inicializa()
{

}

bool Enemigo::dispara()
{
	if (_dispara)return Personaje::dispara();
	return false;
}

void Enemigo::dibuja(){

}

void Enemigo::follow(Entidad* ptr)
{
	Vector2D dir = ptr->getPos() - _posicion;
	_velocidad = dir.unitario() * _speedStat;
}

EnemigoA::EnemigoA(Vector2D posicion, Player* playerPtr, const char* ruta_de_textura) 
	: Enemigo(posicion, playerPtr), _sprite{ ruta_de_textura } {
}
EnemigoB::EnemigoB(Vector2D posicion, Player* playerPtr, const char* ruta_body, int body_sprite_cols, const char* ruta_head, int head_sprite_cols)
	: Enemigo(posicion, playerPtr), _body{ ruta_body, body_sprite_cols }, _head{ ruta_head, head_sprite_cols } {
}

/// FATTY

Fatty::~Fatty(){

}

Fatty::Fatty(Vector2D pos, Player* playerPtr) : EnemigoA(pos, playerPtr, "res/texturas/fatty.png") {

	_sprite.setSize(_dims.x, _dims.y);
	_sprite.setCenter(_dims.x / 2.0f, _dims.y / 2.0f);
	_radio = 5.0f;
}

void Fatty::dibuja()
{
	dibujaHitbox();
	_sprite.setPos(_posicion.x, _posicion.y);
	_sprite.draw();
}

void Fatty::mueve(float t) {
	Enemigo::mueve(t);
	follow(_playerPtr);
	//_spriteFatty.loop();

}

///////////// caca
Caca::Caca(Vector2D pos, Player* const playerPtr) : EnemigoA(pos, playerPtr, "res/texturas/caca.png")
{
	_sprite.setSize(_dims.x, _dims.y);
	_sprite.setCenter(_dims.x / 2.0f, _dims.y / 2.0f);
	_radio = 5.0f;
}

void Caca::dibuja()
{
	dibujaHitbox();
	_sprite.setPos(_posicion.x, _posicion.y);
	_sprite.draw();
}

void Caca::mueve(float t) 
{
	Enemigo::mueve(t);
	follow(_playerPtr);
	//_spriteCaca.loop();
}

Caca::~Caca()
{
}

/// BOSS GUSANO

BossGusano::BossGusano(Player* playerPtr) : Enemigo(Vector2D{ 0.0f, 0.0f }, playerPtr)
{
	_speedStat = 25.0f;
	_dispara = false;
	_velocidad.y = _speedStat;
	_velocidad.x = 0.0f;
	_radio = 6.0f;
	GestorSprites::dimensionaSprite(39, 36, TILE_WIDTH * 1.5f, _head);
	GestorSprites::dimensionaSprite(39, 36, TILE_WIDTH * 1.5f, _headRoja);
	_modulos.resize(N_MODULOS);
	_healthCounter = SALUD_MAX;
}

void BossGusano::dibuja()
{
	//Orientaci�n de la cabeza
	if (_velocidad.x < -0.01) {//IZQUIERDA
		_head.flip(true, false);
		_headRoja.flip(true, false);
	}
	else if (_velocidad.x > 0.01) {
		_head.flip(false, false);
		_headRoja.flip(false, false);
	}

	//GESTION DE MOVIMIENTO VERTICAL/HORIZONTAL
	if (_contador > T_INVULNERABLE) {
		if ((_velocidad.x > 0.01) || (_velocidad.x < -0.01)) {
			if (_head.getState() > 3 || _head.getState() < 2)
				_head.setState(2, false);
		}
		else if (_velocidad.y > 0.01) {
			if (_head.getState() < 4)
				_head.setState(4, false);
		}
		else if (_velocidad.y < -0.01) {
			if (_head.getState() > 1)
				_head.setState(0, false);
		}
	}
	else {
		if ((_velocidad.x > 0.01) || (_velocidad.x < -0.01)) {
			if (_headRoja.getState() > 3 || _head.getState() < 2)
				_headRoja.setState(2, false);
		}
		else if (_velocidad.y > 0.01) {
			if (_headRoja.getState() < 4)
				_headRoja.setState(4, false);
		}
		else if (_velocidad.y < -0.01) {
			if (_headRoja.getState() > 1)
				_headRoja.setState(0, false);
		}
	}

	Entidad::dibujaHitbox(); //De la cabeza

	if (_contador > T_INVULNERABLE) {
		_head.setPos(_posicion.x, _posicion.y);
		_head.draw();
	}
	else {
		_headRoja.setPos(_posicion.x, _posicion.y);
		_headRoja.draw();
	}

	for (auto& i : _modulos) {
		i.dibuja();
	}
}

void BossGusano::mueve(float t, Caja& cajaRoom)
{
	mueveCadena();
	
	//Si s�lo queda la cabeza, sigue al jugador
	if (_modulos.empty()) {
		follow(_playerPtr);
		//Rugido
		if (_contadorRoar >= T_ROAR) {
			ETSIDI::play("res/audio/roar.wav");
			_contadorRoar = 0.0f;
		}
		_contadorRoar += t;
	}
	//Si quedan m�dulos, se mueve aleatoriamente
	else if (ETSIDI::lanzaDado() < (0.1 / 15.0)) {//MEJORABLE
		float aux = _velocidad.x;
		_velocidad.x = _velocidad.y;
		_velocidad.y = aux;
		if (ETSIDI::lanzaMoneda) _velocidad *= -1;
	}

	Interaccion::rebote(*this, cajaRoom, true);  //Invierte la velocidad al chocar con la pared

	//Enemigo::mueve(t); //Ya se llama en Room normal

	_contador += t;

	if (_contador > T_INVULNERABLE)
		_head.loop();
	else
		_headRoja.loop();
	
	for (auto& i : _modulos) {
		i.mueve(t);
	}
}

void BossGusano::mueveCadena()
{
	if (_modulos.empty()) return;
	Vector2D aux = _modulos[0].getPos() - getPos();
	float dif = aux.modulo() - DIST_ENTRE_MODULOS;

	if (dif > 0) {
		_modulos[0].avanza(aux.unitario() * -1.0f * dif);
		if (abs(aux.x) > abs(aux.y)) {

		}
	}
	else {
	}
	for (size_t i = 1; i < _modulos.size(); i++) {
		aux = _modulos[i].getPos() - _modulos[i - 1].getPos();
		dif = aux.modulo() - DIST_ENTRE_MODULOS;
		if (dif > 0) {
			_modulos[i].avanza(aux.unitario() * -1.0f * dif);
			if (abs(aux.x) > abs(aux.y)) {

			}
		}
	}

}

bool BossGusano::recibeHerida(float damage)
{
	_contador = 0;
	_healthCounter -= damage;
	
	if (!_modulos.empty()) {//Impacto a la cabeza causa da�o a todos los m�dulos
		for (int i = _modulos.size() - 1; i >= 0; i--) {
			if (_modulos[i].recibeHerida(damage / 4.0f))
				_modulos.erase(_modulos.begin() + i);
		}

	}
	if (_healthCounter <= 0 && _modulos.empty()) return true;
	return false;
}

bool BossGusano::gestionarDisparos(ListaProyectil& listaP)
{
	bool hit = false;
	//Impactos en los modulos
	for (int i = _modulos.size() - 1; i >= 0; i--) {
		Proyectil* aux = listaP.impacto(_modulos[i]);
		if (aux != nullptr) {
			if (_modulos[i].recibeHerida(aux->getDamage()))
				_modulos.erase(_modulos.begin() + i);
			listaP.eliminar(aux);
			hit = true;
		}
	}
	return hit;
}

bool BossGusano::rebote(Player& player)
{
	//if (Interaccion::rebote(player, *this)) return true;
	for (auto& i : _modulos) {
		if (Interaccion::rebote(player, i)) return true;
	}
	return false;

}
