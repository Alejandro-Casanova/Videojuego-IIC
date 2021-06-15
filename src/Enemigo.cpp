#include "Enemigo.h"
#include <iostream>
#include <random>
#include "Interaccion.h"
#include "GestorSprites.h"
#include "Player.h"
#include "ListaProyectil.h"

//CLASE ENEMIGO GENÉRICA (ABSTRACTA) //////////////////////////////////

Enemigo::~Enemigo() {

}

Enemigo::Enemigo(Vector2D posicion, float radio, Player* playerPtr, Room* roomPtr) : Personaje(posicion, radio), _playerPtr(playerPtr) , _roomPtr(roomPtr){
	_posicion = posicion;
}

void Enemigo::inicializa()
{
	intervalo = 100;
}

bool Enemigo::puedeDisparar() 
{
	if (_dispara) return Personaje::puedeDisparar();
	return false;
}

Proyectil* Enemigo::dispara() 
{
	if (puedeDisparar()) {		//Indica si el enemigo está listo para disparar y puede
		// Creacion de un proyectil
		Proyectil* d = new Proyectil();
		//	proyectil.setOrigen(Vector2D.player)
		Vector2D pos = getPos();
		d->setPos(pos.x, pos.y);
		d->setColor(200, 20, 20);
		Vector2D target = _playerPtr->getPos() - pos;
		Vector2D dir = target.unitario();
		d->setVel(_bulletSpeed * dir.x, _bulletSpeed * dir.y);
		return d;
	}
	return nullptr;
}

void Enemigo::follow(Entidad* ptr)
{
	Vector2D dir = ptr->getPos() - _posicion;
	_velocidad = dir.unitario() * _speedStat;
}

void Enemigo::mov_erratico() {
	Vector2D target;	
	if (intervalo != 0) intervalo--;

	if (intervalo == 0){
		std::random_device rd;
		std::mt19937_64 gen(rd());
		std::uniform_int_distribution<> distr1(0, 1), distrx(-50,50), distry(-25,25);
		if (distr1(gen)) {
			target = _playerPtr->getPos() - _posicion;
			_velocidad = target.unitario() * _speedStat;
			//std::cout << "IN " << target.x << " " << target.y << std::endl;
		}
		else {
			target.x = _posicion.x + distrx(gen);
			target.y = _posicion.y + distry(gen);
			_velocidad = target.unitario() * _speedStat;
			//std::cout << "OUT " << target.x << " " << target.y << std::endl;
		}
		intervalo = 100;
	}
}

void Enemigo::flee(Entidad* ptr)
{
	Vector2D dir = _posicion - ptr->getPos();
	_velocidad = dir.unitario() * _speedStat * 2.0f;
}

void Enemigo::stalk(Entidad* ptr, float distance)
{
	Vector2D dir = _posicion - ptr->getPos();
	float dist = dir.modulo();
	if (dist < distance - 1.0f) flee(ptr);
	else if (dist > distance + 1.0f) follow(ptr);
	else _velocidad = 0;

}

void Enemigo::roam(float prob)
{
	if(ETSIDI::lanzaDado() < prob * double(T_CONST)){ //Probabilidad cada segundo
		double angulo = ETSIDI::lanzaDado(360.0); //Ángulo aleatorio entre 0 y 360
		_velocidad.set(_speedStat, angulo); //Dirección aleatoria
	}
	Interaccion::rebote(*this, *_roomPtr, true, vuela());
}


//SUBCLASES DE ENEMIGOS (ABSTRACTAS) Definidas según el tipo de animación

EnemigoA::EnemigoA(Vector2D posicion, float radio, Player* playerPtr, Room* roomPtr, const char* ruta_de_textura) 
	: Enemigo(posicion, radio, playerPtr, roomPtr), _sprite{ ruta_de_textura } {
}

void EnemigoA::dibuja() {
	dibujaHitbox();
	_sprite.setPos(_posicion.x, _posicion.y);
	_sprite.draw();
}

EnemigoB::EnemigoB(Vector2D posicion, float radio, Player* playerPtr, Room* roomPtr, const char* ruta_body, int body_sprite_cols, const char* ruta_head, int head_sprite_cols, int animation_ms_step, int body_sprite_rows)
	: Enemigo(posicion, radio, playerPtr, roomPtr), _body{ ruta_body, body_sprite_cols, body_sprite_rows, animation_ms_step }, _head{ ruta_head, head_sprite_cols, 1, animation_ms_step } {
}

void EnemigoB::dibuja() {
	dibujaHitbox();

	glPushMatrix();
	glTranslatef(_posicion.x, _posicion.y, 0);
	glColor3f(1.0f, 0.0f, 0.0f);

	//Gestion de direccion y animacion
	if (_velocidad.x > 0.01) {//DERECHA
		_body.flip(false, false);
		_head.flip(false, false);
	}
	else if (_velocidad.x < -0.01) {//IZQUIERDA
		_body.flip(true, false);
		_head.flip(true, false);
	}
	if (_headAnimation == 0) { //Animación de la cabeza, cuando hay sprites diferentes según el movimiento vertical
		_head.setState(1);
		if (_velocidad.y > 0.01 && _velocidad.y > abs(_velocidad.x)) {//ARRIBA
			_head.setState(2);
		}
		else if (_velocidad.y < -0.01 && abs(_velocidad.y) > abs(_velocidad.x)) {//ABAJO
			_head.setState(0);
		}
	}
	//QUIETO
	if ((_velocidad.x < 0.01) && (_velocidad.x > -0.01) && (_velocidad.y < 0.01) && (_velocidad.y > -0.01))
		_body.setState(10);
	else if (_body.getState() == 10)
		_body.setState(10, false);

	//GESTION DE MOVIMIENTO VERTICAL/HORIZONTAL
	if (abs(_velocidad.x) > 0.01f && (abs(_velocidad.x) > abs(_velocidad.y)))  {
		if (_body.getState() > 9) {
			_body.setState(0, false);
		}
	}
	else if (abs(_velocidad.y) > 0.01f){
		if (_body.getState() < 10) {
			_body.setState(10, false);
		}
	}

	_head.draw();
	_body.draw();

	glPopMatrix();
}

EnemigoC::EnemigoC(Vector2D posicion, float radio, Player* playerPtr, Room* roomPtr, const char* ruta_de_textura, int sprite_cols, int spriteRows, int animation_ms_step)
	: Enemigo(posicion, radio, playerPtr, roomPtr), _sprite{ ruta_de_textura, sprite_cols, spriteRows, animation_ms_step }
{
}

void EnemigoC::dibuja()
{
	//Gestion de direccion y animacion
	if (_velocidad.x > 0.01) //DERECHA
		_sprite.flip(false, false);
	else if (_velocidad.x < -0.01) //IZQUIERDA
		_sprite.flip(true, false);
	

	dibujaHitbox();

	glPushMatrix();
	glTranslatef(_posicion.x, _posicion.y, 0);
	glColor3f(1.0f, 0.0f, 0.0f);

	_sprite.draw();

	glPopMatrix();
}

//// ZOMBIE /////////////////////////
Zombie::Zombie(Vector2D pos, Player* playerPtr, Room* roomPtr) : EnemigoB(pos, ZOMBIE_RAD, playerPtr, roomPtr, "res/texturas/enemigos/zombie_body_full.png", 10, "res/texturas/enemigos/zombie_head.png", 1){
	GestorSprites::dimensionaSprite(38, 35, TILE_WIDTH * 1.25f, _head);
	GestorSprites::dimensionaSprite(26, 22, TILE_WIDTH, _body, 4);
	_dispara = false;
	_healthCounter = ZOMBIE_SALUD;
}

void Zombie::mueve(float t) {
	Personaje::mueve(t);
	follow(_playerPtr);
	_body.loop();
}

//// ESQUELETO /////////////////////////
Esqueleto::Esqueleto(Vector2D pos, Player* playerPtr, Room* roomPtr) :EnemigoB(pos, ESQUELETO_RAD, playerPtr, roomPtr, "res/texturas/enemigos/skelly_full_body.png", 10, "res/texturas/enemigos/skelly_head.png", 3) {
	GestorSprites::dimensionaSprite(32, 33, TILE_WIDTH * 1.2f, _head);
	GestorSprites::dimensionaSprite(26, 22, TILE_WIDTH, _body, 5);
	_dispara = true;
	_bulletSpeed = ESQUELETO_BULLET_SPEED;
	_healthCounter = ESQUELETO_SALUD;
}

Proyectil* Esqueleto::dispara() {
	if (puedeDisparar()) {		//Indica si el enemigo está listo para disparar y puede
			// Creacion de un proyectil
		Proyectil* d = new Hueso();
		//	proyectil.setOrigen(Vector2D.player)
		Vector2D pos = getPos();
		d->setPos(pos.x, pos.y);
		d->setColor(200, 20, 20);
		Vector2D target = _playerPtr->getPos() - pos;
		Vector2D dir = target.unitario();
		d->setVel(_bulletSpeed * dir.x, _bulletSpeed * dir.y);
		return d;
	}
	return nullptr;
}

void Esqueleto::mueve(float t) {
	Personaje::mueve(t);
	follow(_playerPtr);
	_body.loop();
}

// WEEPER ///////////////

Weeper::Weeper(Vector2D pos, Player* playerPtr, Room* roomPtr)
	: EnemigoB(pos, WEEPER_RAD, playerPtr, roomPtr, "res/texturas/enemigos/weeper_body_full.png", 10, "res/texturas/enemigos/weeper_head.png", 6) {

	GestorSprites::dimensionaSprite(44, 42, TILE_WIDTH * 1.2f, _head);
	GestorSprites::dimensionaSprite(66, 39, TILE_WIDTH, _body, 5.0f);
	_speedStat = WEEPER_SPEED;
	_headAnimation = 1;
	_dispara = true;
	_healthCounter = WEEPER_SALUD;

}

void Weeper::mueve(float t) {
	Personaje::mueve(t);
	stalk(_playerPtr, 50.0f);
	_body.loop();
	_head.loop();
}

/// FATTY ///////////////////////

Fatty::~Fatty(){

}

bool Fatty::recibeHerida(float damage)
{
	if (!_hostil) _hostil = true;
	return Personaje::recibeHerida(damage);
}

Fatty::Fatty(Vector2D pos, Player* playerPtr, Room* roomPtr)
	: EnemigoB(pos, FATTY_RAD, playerPtr, roomPtr, "res/texturas/enemigos/fatty_body_full.png", 12, "res/texturas/enemigos/fatty_head.png", 6, 200) {
	
	_velocidad.set(_speedStat, ETSIDI::lanzaDado(360));
	GestorSprites::dimensionaSprite(34, 30, TILE_WIDTH * 1.2f, _head, -4.0f);
	GestorSprites::dimensionaSprite(66, 39, TILE_WIDTH * 2.0f, _body, 2.5f);
	_speedStat = FATTY_SPEED;
	_headAnimation = 1;
	_hostil = false;
	_healthCounter = FATTY_SALUD;
}

void Fatty::mueve(float t) {
	Personaje::mueve(t);

	if (_hostil) follow(_playerPtr);
	else roam(0.3f); //30% de probabilidad de cambiar su trayectoria cada segundo

	_body.loop();
	_head.loop();

}

/// NARANJA ///////////////////
Naranja::Naranja(Vector2D pos, Player* const playerPtr, Room* roomPtr)
	: EnemigoC(pos, NARANJA_RAD, playerPtr, roomPtr, "res/texturas/enemigos/orange.png", 4, 3)
{
	GestorSprites::dimensionaSprite(32, 32, TILE_WIDTH, _sprite, -1.0f);
}

void Naranja::dibuja()
{
	int fase = (int)floor(_contador / _tFase);

	if (_contador <= 0)_sprite.setState(9);
	else if (fase < _nFases - 1) {
		_sprite.setState(_nFases -1 - fase);
	}
	dibujaHitbox();

	glPushMatrix();
	glTranslatef(_posicion.x, _posicion.y, 0);
	glColor3f(1.0f, 0.0f, 0.0f);

	_sprite.draw();

	glPopMatrix();
}

void Naranja::mueve(float t)
{
	//Ajuste del radio de la hitbox
	_radio = 1 + 2.5f * _contador / 10.0f;
	if (_radio < 1) _radio = 1;

	if (_contador < _nFases * _tFase) { //La naranja va creciendo
		_contador += t;
		_dispara = false;
	}
	else { //Al alcanzar tamaño máximo, dispara
		_contador = _nFases * _tFase;
		_dispara = true;
	}
	//std::cout << _contador << std::endl;
	Personaje::mueve(t);
	_sprite.loop();
}

bool Naranja::recibeHerida(float damage)
{
	if (_contador < _tFase) return Personaje::recibeHerida(damage);
	_contador -= (damage * NARANJA_MULTIPLICADOR / _tFase / NARANJA_SALUD);
	return false;
}

// MOSCA /////////////////////
Mosca::Mosca(Vector2D pos, Player* const playerPtr, Room* roomPtr)
	: EnemigoC(pos, MOSCA_RAD, playerPtr, roomPtr, "res/texturas/enemigos/fly.png", 2)
{
	_velocidad.set(_speedStat, ETSIDI::lanzaDado(360));
	_shootSpeed = MOSCA_SHOOT_SPEED;
	_dispara = true;
	GestorSprites::dimensionaSprite(32, 32, TILE_WIDTH, _sprite);
	_vuela = true;
	_healthCounter = MOSCA_SALUD;
}

void Mosca::mueve(float t)
{
	Personaje::mueve(t);
	_sprite.loop();
	roam(0.3f); //30% de probabilidad de cambiar su trayectoria cada segundo
}

///////////// CACA ////////////////////////
Caca::Caca(Vector2D pos, Player* const playerPtr, Room* roomPtr) : EnemigoA(pos, CACA_RAD, playerPtr, roomPtr, "res/texturas/enemigos/caca.png")
{
	_sprite.setSize(13, 13);
	_sprite.setCenter(13 / 2.0f, 13 / 2.0f);
	_dispara = false;
	_healthCounter = CACA_SALUD;
}

void Caca::mueve(float t) 
{
	Personaje::mueve(t);
	roam(0.3f);
	//follow(_playerPtr);
	//_spriteCaca.loop();
}

Caca::~Caca()
{
}

/// BOSS GUSANO /////////////////////////////////////

BossGusano::BossGusano(Player* playerPtr, Room* roomPtr) : Enemigo(Vector2D{ 0.0f, 0.0f }, BOSS_GUSANO_RAD, playerPtr, roomPtr)
{
	_speedStat = BOSS_GUSANO_SPEED;
	_dispara = false;
	_velocidad.setXY(0.0f, _speedStat);
	GestorSprites::dimensionaSprite(39, 36, TILE_WIDTH * 1.5f, _head);
	GestorSprites::dimensionaSprite(39, 36, TILE_WIDTH * 1.5f, _headRoja);
	_modulos.resize(N_MODULOS);
	_healthCounter = BOSS_GUSANO_SALUD_MAX;
}

void BossGusano::dibuja()
{
	//Orientación de la cabeza
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
	
	//Si sólo queda la cabeza, sigue al jugador
	if (_modulos.empty()) {
		follow(_playerPtr);
		//Rugido
		if (_contadorRoar >= T_ROAR) {
			ETSIDI::play("res/audio/roar.wav");
			_contadorRoar = 0.0f;
		}
		_contadorRoar += t;
	}
	//Si quedan módulos, se mueve aleatoriamente
	else if (ETSIDI::lanzaDado() < (0.1 / 15.0)) {//MEJORABLE
		float aux = _velocidad.x;
		_velocidad.x = _velocidad.y;
		_velocidad.y = aux;
		if (ETSIDI::lanzaMoneda()) _velocidad *= -1;
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
	
	if (!_modulos.empty()) {//Impacto a la cabeza causa daño a todos los módulos
		for (int i = (int)_modulos.size() - 1; i >= 0; i--) {
			_modulos[i].recibeHerida(damage / N_MODULOS); //Nunca se eliminan módulos por impactos a la cabeza
				//_modulos.erase(_modulos.begin() + i);
		}

	}
	if (_healthCounter <= 0 && _modulos.empty()) {
		return true;
		sonidoMuerte();
	}
	return false;
}

Objeto* BossGusano::gestionarDisparos(ListaProyectil& listaP)
{
	bool hit = false;
	Objeto* nObj = nullptr;
	//Impactos en los modulos
	for (int i = (int)_modulos.size() - 1; i >= 0; i--) {
		Proyectil* aux = listaP.impacto(_modulos[i]);
		if (aux != nullptr) {
			if (_modulos[i].recibeHerida((float)aux->getDamage())) {
				nObj = Factoria::dropRandom(_modulos[i].getPos());
				_modulos.erase(_modulos.begin() + i);
			}
			listaP.eliminar(aux);
			hit = true;
		}
	}
	if (hit) return nObj;
	return nullptr;
}

bool BossGusano::rebote(Player& player)
{
	//if (Interaccion::rebote(player, *this)) return true;
	for (auto& i : _modulos) {
		if (Interaccion::rebote(player, i)) return true;
	}
	return false;

}

void BossGusano::mueve(float t)
{
	Personaje::mueve(t);
}


