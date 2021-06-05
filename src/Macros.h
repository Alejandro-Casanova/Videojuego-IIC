#pragma once
#define TILE_WIDTH 10.0F //Ancho de cada casilla
#define PUERTA_DIST_V 38.0F
#define PUERTA_DIST_H 68.0F
#define ROOM_WIDTH 130.0F
#define ROOM_HEIGHT 70.0F
#define ROOM_BORDE_TEXTURA 18.0F //Ancho de la textura que queda detr�s de la hit-box de la pared
#define T_CONST 0.025F	//Constante de tiempo para movimientos
#define T_INVULNERABLE 0.75F //Tiempo de invulnerabilidad tras recibir daño

//Parámetros del BOSS GUSANO
const float DIST_ENTRE_MODULOS = TILE_WIDTH * 0.85f;
const float SALUD_MAX = 18.0f;
const int N_MODULOS = 6;
const float T_ROAR = 8.0f;