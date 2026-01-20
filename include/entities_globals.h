/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#ifndef ENTITIES_GLOBALS_H
#define ENTITIES_GLOBALS_H

#include "entities.h" // For Ship, Asteroid, Bullet, EnemyShip structs

extern Ship ship;
extern Asteroid asteroids[MAX_ASTEROIDS];
extern Bullet bullets[MAX_BULLETS];
extern EnemyShip enemy_ships[MAX_ENEMY_SHIPS];

extern unsigned int ship_vao, ship_vbo;
extern unsigned int bullet_vao, bullet_vbo;
extern unsigned int enemy_ship_vao, enemy_ship_vbo;

#endif // ENTITIES_GLOBALS_H
