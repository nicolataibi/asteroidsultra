/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "check_collisions.h"
#include "entities.h"
#include "game_globals.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "glad/glad.h"

void check_collisions() {
    printf("Before collision check: Asteroid 0 active: %d, pos: (%f, %f)\n", asteroids[0].active, asteroids[0].pos[0], asteroids[0].pos[1]);
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            for (int j = 0; j < MAX_ASTEROIDS; j++) {
                if (asteroids[j].active) {
                    float dx = bullets[i].pos[0] - asteroids[j].pos[0];
                    float dy = bullets[i].pos[1] - asteroids[j].pos[1];
                    float distance = sqrt(dx * dx + dy * dy);

                    if (distance < 0.15f * asteroids[j].scale) { // Collision
                        bullets[i].active = 0;
                        asteroids[j].active = 0;
                        asteroids_destroyed_count++;
                        glDeleteVertexArrays(1, &asteroids[j].vao);
                        glDeleteBuffers(1, &asteroids[j].vbo);

                        

                        if (asteroids[j].generation < 2) {
                            spawn_asteroid(asteroids[j].pos, asteroids[j].generation + 1, asteroids[j].scale * 0.7f);
                            spawn_asteroid(asteroids[j].pos, asteroids[j].generation + 1, asteroids[j].scale * 0.7f);
                        }
                    }
                }
            }
        }
    }

    // Ship-asteroid collision
    if (ship.active) {
        for (int i = 0; i < MAX_ASTEROIDS; i++) {
            if (asteroids[i].active) {
                float dx = ship.pos[0] - asteroids[i].pos[0];
                float dy = ship.pos[1] - asteroids[i].pos[1];
                float distance = sqrt(dx * dx + dy * dy);

                if (distance < 0.05f + (0.1f * asteroids[i].scale)) { // Collision
                    ship.active = 0;
                    ship.explosion_timer = 1.0f; // Explosion lasts 1 second
                    for (int k = 0; k < 800; k++) {
                        ship.explosion_fragments[k][0] = ship.pos[0];
                        ship.explosion_fragments[k][1] = ship.pos[1];
                        float angle = (float)rand() / (float)RAND_MAX * 2.0f * M_PI;
                        float speed = (float)rand() / (float)RAND_MAX * 0.5f + 0.1f;
                        ship.explosion_velocities[k][0] = cos(angle) * speed;
                        ship.explosion_velocities[k][1] = sin(angle) * speed;
                    }
                    asteroids[i].active = 0;
                    glDeleteVertexArrays(1, &asteroids[i].vao);
                    glDeleteBuffers(1, &asteroids[i].vbo);
                }
            }
        }
    }

    // Bullet-enemy ship collision
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            for (int j = 0; j < MAX_ENEMY_SHIPS; j++) {
                if (enemy_ships[j].active) {
                    float dx = bullets[i].pos[0] - enemy_ships[j].pos[0];
                    float dy = bullets[i].pos[1] - enemy_ships[j].pos[1];
                    float distance = sqrt(dx * dx + dy * dy);

                    // Assuming enemy ship has a collision radius similar to player ship (0.05f)
                    if (distance < 0.05f && bullets[i].owner == PLAYER) { 
                        bullets[i].active = 0;
                        enemy_ships[j].active = 0;
                        enemy_ships[j].explosion_timer = 1.0f; // Explosion lasts 1 second
                        enemy_ships_destroyed_count++;
                        for (int k = 0; k < 800; k++) {
                            enemy_ships[j].explosion_fragments[k][0] = enemy_ships[j].pos[0];
                            enemy_ships[j].explosion_fragments[k][1] = enemy_ships[j].pos[1];
                            float angle = (float)rand() / (float)RAND_MAX * 2.0f * M_PI;
                            float speed = (float)rand() / (float)RAND_MAX * 0.5f + 0.1f;
                            enemy_ships[j].explosion_velocities[k][0] = cos(angle) * speed;
                            enemy_ships[j].explosion_velocities[k][1] = sin(angle) * speed;
                        }
                    }
                }
            }
        }
    }

    // Bullet-ship collision (enemy bullets)
    if (ship.active) {
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active && bullets[i].owner == ENEMY) {
                float dx = bullets[i].pos[0] - ship.pos[0];
                float dy = bullets[i].pos[1] - ship.pos[1];
                float distance = sqrt(dx * dx + dy * dy);

                if (distance < 0.05f) { // Assuming ship collision radius is 0.05f
                    ship.active = 0;
                    ship.explosion_timer = 1.0f; // Explosion lasts 1 second
                    for (int k = 0; k < 800; k++) {
                        ship.explosion_fragments[k][0] = ship.pos[0];
                        ship.explosion_fragments[k][1] = ship.pos[1];
                        float angle = (float)rand() / (float)RAND_MAX * 2.0f * M_PI;
                        float speed = (float)rand() / (float)RAND_MAX * 0.5f + 0.1f;
                        ship.explosion_velocities[k][0] = cos(angle) * speed;
                        ship.explosion_velocities[k][1] = sin(angle) * speed;
                    }
                    bullets[i].active = 0; // Deactivate enemy bullet
                }
            }
        }
    }

    // Ship-enemy ship collision
    if (ship.active) {
        for (int i = 0; i < MAX_ENEMY_SHIPS; i++) {
            if (enemy_ships[i].active) {
                float dx = ship.pos[0] - enemy_ships[i].pos[0];
                float dy = ship.pos[1] - enemy_ships[i].pos[1];
                float distance = sqrt(dx * dx + dy * dy);

                if (distance < 0.05f + 0.05f) { // Sum of radii
                    printf("DEBUG: Player ship collided with enemy ship %d.\n", i);
                    ship.active = 0;
                    ship.explosion_timer = 1.0f; // Explosion lasts 1 second
                    for (int k = 0; k < 800; k++) {
                        ship.explosion_fragments[k][0] = ship.pos[0];
                        ship.explosion_fragments[k][1] = ship.pos[1];
                        float angle = (float)rand() / (float)RAND_MAX * 2.0f * M_PI;
                        float speed = (float)rand() / (float)RAND_MAX * 0.5f + 0.1f;
                        ship.explosion_velocities[k][0] = cos(angle) * speed;
                        ship.explosion_velocities[k][1] = sin(angle) * speed;
                    }
                    enemy_ships[i].active = 0;
                    enemy_ships[i].explosion_timer = 1.0f; // Explosion lasts 1 second
                    for (int k = 0; k < 800; k++) {
                        enemy_ships[i].explosion_fragments[k][0] = enemy_ships[i].pos[0];
                        enemy_ships[i].explosion_fragments[k][1] = enemy_ships[i].pos[1];
                        float angle = (float)rand() / (float)RAND_MAX * 2.0f * M_PI;
                        float speed = (float)rand() / (float)RAND_MAX * 0.5f + 0.1f;
                        enemy_ships[i].explosion_velocities[k][0] = cos(angle) * speed;
                        enemy_ships[i].explosion_velocities[k][1] = sin(angle) * speed;
                    }
                }
            }
        }
    }
}