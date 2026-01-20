/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#ifndef ENTITIES_H
#define ENTITIES_H

#include <cglm/cglm.h>

#define MAX_ASTEROIDS 50
#define MAX_BULLETS 500
#define MAX_ENEMY_SHIPS 1

#define MAX_SHIP_SPEED 2.0f

// Ship
typedef struct {
    vec2 pos;
    float angle;
    vec2 velocity;
    vec2 acceleration;
    int active;
    float explosion_timer;
    vec2 explosion_fragments[800]; // Max 800 fragments
    vec2 explosion_velocities[800];
    unsigned int explosion_vao;
    unsigned int explosion_vbo;
} Ship;

// Asteroid
typedef struct {
    vec2 pos;
    vec2 velocity;
    float scale;
    int active;
    int generation;
    unsigned int vao;
    unsigned int vbo;
} Asteroid;

// Bullet
typedef enum {
    PLAYER,
    ENEMY
} BulletOwner;

typedef struct {
    vec2 pos;
    vec2 velocity;
    int active;
    BulletOwner owner;
} Bullet;

// Enemy Ship
typedef struct {
    vec2 pos;
    float angle;
    vec2 velocity;
    int active;
    double shoot_timer;
    int current_shoot_direction_idx;
    unsigned int vao;
    unsigned int vbo;
    float explosion_timer;
    vec2 explosion_fragments[800]; // Max 800 fragments
    vec2 explosion_velocities[800];
    unsigned int explosion_vao;
    unsigned int explosion_vbo;
} EnemyShip;

extern Ship ship;
extern Asteroid asteroids[MAX_ASTEROIDS];
extern Bullet bullets[MAX_BULLETS];
extern EnemyShip enemy_ships[MAX_ENEMY_SHIPS];

void init_ship();
void init_asteroids();
void init_bullets();
void init_enemy_ships();
void spawn_initial_asteroids();
void spawn_asteroid(vec2 pos, int generation, float scale);
void spawn_enemy_ship();

void update_ship(double deltaTime);
void update_asteroids(double deltaTime);
void update_bullets(double deltaTime);
void update_enemy_ships(double deltaTime);

void draw_ship(unsigned int shader_program);
void draw_asteroids(unsigned int shader_program);
void draw_bullets(unsigned int shader_program);
void draw_enemy_ships(unsigned int shader_program);

void cleanup_entities();

#endif