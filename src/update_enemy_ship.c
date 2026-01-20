/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "update_enemy_ship.h"
#include "entities_globals.h"
#include <stdio.h>
#include <cglm/cglm.h>
#include "glad/glad.h" // Added for GL_ARRAY_BUFFER, glBindBuffer, glBufferSubData

void update_enemy_ship(EnemyShip *enemy_ship, double deltaTime) {
    if (enemy_ship->active) {
        printf("Enemy ship active at pos: (%f, %f) with velocity: (%f, %f)\n", enemy_ship->pos[0], enemy_ship->pos[1], enemy_ship->velocity[0], enemy_ship->velocity[1]);

        // Update position based on velocity
        enemy_ship->pos[0] += enemy_ship->velocity[0] * deltaTime;
        enemy_ship->pos[1] += enemy_ship->velocity[1] * deltaTime;

        // Deactivate if it goes off-screen
        if (enemy_ship->pos[0] < -1.1f || enemy_ship->pos[0] > 1.1f || enemy_ship->pos[1] < -1.1f || enemy_ship->pos[1] > 1.1f) {
            enemy_ship->active = 0;
            printf("DEBUG: Enemy ship deactivated (off-screen). Pos: (%f, %f)\n", enemy_ship->pos[0], enemy_ship->pos[1]);
            enemy_ship->explosion_timer = 0.0f; // Ensure explosion timer is reset
        }

        // Shooting logic
        enemy_ship->shoot_timer += deltaTime;
        static vec2 shoot_directions[4];
        shoot_directions[0][0] = 0.0f; shoot_directions[0][1] = 0.5f;   // Up
        shoot_directions[1][0] = 0.0f; shoot_directions[1][1] = -0.5f;  // Down
        shoot_directions[2][0] = 0.5f; shoot_directions[2][1] = 0.0f;   // Right
        shoot_directions[3][0] = -0.5f; shoot_directions[3][1] = 0.0f;   // Left
        static const int NUM_DIRECTIONS = 4;

        if (enemy_ship->shoot_timer >= 1.0) { // Shoot every 1 second
            enemy_ship->shoot_timer = 0.0;

            // Find an inactive bullet
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) {
                    bullets[i].active = 1;
                    glm_vec2_copy(enemy_ship->pos, bullets[i].pos);

                    bullets[i].velocity[0] = shoot_directions[enemy_ship->current_shoot_direction_idx][0];
                    bullets[i].velocity[1] = shoot_directions[enemy_ship->current_shoot_direction_idx][1];
                    bullets[i].owner = ENEMY;

                    // Adjust bullet spawn position based on direction
                    if (enemy_ship->current_shoot_direction_idx == 0) { // Up
                        bullets[i].pos[1] += 0.06f;
                    } else if (enemy_ship->current_shoot_direction_idx == 1) { // Down
                        bullets[i].pos[1] -= 0.06f;
                    } else if (enemy_ship->current_shoot_direction_idx == 2) { // Right
                        bullets[i].pos[0] += 0.06f;
                    } else { // Left
                        bullets[i].pos[0] -= 0.06f;
                    }

                    enemy_ship->current_shoot_direction_idx = (enemy_ship->current_shoot_direction_idx + 1) % NUM_DIRECTIONS;
                    break; // Exit after firing one bullet
                }
            }
        }
    } else if (enemy_ship->explosion_timer > 0.0f) {
        enemy_ship->explosion_timer -= deltaTime;
        if (enemy_ship->explosion_timer < 0.0f) {
            enemy_ship->explosion_timer = 0.0f;
        }

        // Update explosion fragments
        for (int i = 0; i < 800; i++) {
            enemy_ship->explosion_fragments[i][0] += enemy_ship->explosion_velocities[i][0] * deltaTime;
            enemy_ship->explosion_fragments[i][1] += enemy_ship->explosion_velocities[i][1] * deltaTime;
        }

        // Update VBO data
        glBindBuffer(GL_ARRAY_BUFFER, enemy_ship->explosion_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec2) * 800, enemy_ship->explosion_fragments);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}