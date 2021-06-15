#pragma once
#define TILE_WIDTH 10.0F //Ancho de cada casilla
#define PUERTA_DIST_V 38.0F
#define PUERTA_DIST_H 68.0F
#define ROOM_WIDTH 130.0F
#define ROOM_HEIGHT 70.0F
#define ROOM_BORDE_TEXTURA 18.0F //Ancho de la textura que queda detr�s de la hit-box de la pared
#define T_CONST 0.025F	//Constante de tiempo para movimientos
#define PI 3.14159265358979323846	//pi

//Parámetros del BOSS GUSANO
const float DIST_ENTRE_MODULOS = TILE_WIDTH * 0.85f;
const float MODULO_RAD = 4.0f;
const float BOSS_GUSANO_SALUD_MAX = 18.0f;
const int N_MODULOS = 6;
const float T_ROAR = 8.0f;
const float BOSS_GUSANO_SPEED = 25.0f;
const float BOSS_GUSANO_RAD = 6.0f;

//Parámetros iniciales del jugador
const float SALUD_JUGADOR = 5.0f;
const float VELOCIDAD_JUGADOR = 35.0f;
const float VEL_PROYECTIL_JUGADOR = 45.0f;
const float VEL_DISPARO_JUGADOR = 0.9f;
const float DAMAGE_DISPARO_JUGADOR = 1.5f;
//Otros parámetros del jugador
#define T_INVULNERABLE 0.75F //Tiempo de invulnerabilidad tras recibir daño
const float T_BONUS = 1.5f; //Tiempo que dura la animación de recibir un bonus

//Parámetros de los ENEMIGOS
const float ZOMBIE_RAD = TILE_WIDTH / 2.0f; //Radio de la hit-box
const float ZOMBIE_SALUD = 5.0f;

const float ESQUELETO_RAD = TILE_WIDTH / 2.0f;
const float ESQUELETO_BULLET_SPEED = 40.0f;
const float ESQUELETO_SALUD = 4.0f;

const float WEEPER_RAD = TILE_WIDTH / 2.0f;
const float WEEPER_SPEED = 12.5f;
const float WEEPER_SALUD = 3.5f;

const float FATTY_RAD = 7.0f;
const float FATTY_SPEED = 7.5f;
const float FATTY_SALUD = 9.0f;

const float NARANJA_RAD = 1.0f;
const float NARANJA_SALUD = 1.5f;
const float NARANJA_MULTIPLICADOR = 4.0f; //Relaciona el daño recibido con el tiempo que tarda en regenerarse 

const float MOSCA_RAD = 2.0f;
const float MOSCA_SHOOT_SPEED = 3.0f;
const float MOSCA_SALUD = 2.0f;

const float CACA_RAD = TILE_WIDTH / 2.0f;
const float CACA_SALUD = 3.0f;