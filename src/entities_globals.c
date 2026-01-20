/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "entities_globals.h"

Ship ship;
Asteroid asteroids[MAX_ASTEROIDS];
Bullet bullets[MAX_BULLETS];
EnemyShip enemy_ships[MAX_ENEMY_SHIPS];

unsigned int ship_vao, ship_vbo;
unsigned int bullet_vao, bullet_vbo;
unsigned int enemy_ship_vao, enemy_ship_vbo;
