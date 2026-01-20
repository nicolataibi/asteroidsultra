/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "game_update.h"
#include "input.h"
#include "entities.h"
#include "check_collisions.h"
#include "game_globals.h"
#include <stdlib.h>
#include <cglm/cglm.h>

void game_update(GLFWwindow *window, double deltaTime) {
    process_input(window, deltaTime);
    update_ship(deltaTime);
    update_asteroids(deltaTime);
    update_enemy_ships(deltaTime);
    update_bullets(deltaTime);
    check_collisions();

    // Asteroid spawning logic
    static double asteroid_spawn_timer = 0.0;
    asteroid_spawn_timer += deltaTime;
    if (asteroid_spawn_timer > 2.0 && ship.active) { // Spawn an asteroid every 2 seconds only if ship is active
        asteroid_spawn_timer = 0.0;
        int edge = rand() % 4;
        float x, y;
        if (edge == 0) { // Top
            x = (float)rand() / (float)RAND_MAX * 2.0f - 1.0f;
            y = 1.0f;
        } else if (edge == 1) { // Bottom
            x = (float)rand() / (float)RAND_MAX * 2.0f - 1.0f;
            y = -1.0f;
        } else if (edge == 2) { // Left
            x = -1.0f;
            y = (float)rand() / (float)RAND_MAX * 2.0f - 1.0f;
        } else { // Right
            x = 1.0f;
            y = (float)rand() / (float)RAND_MAX * 2.0f - 1.0f;
        }
        vec2 pos = {x, y};
        spawn_asteroid(pos, 0, 1.0f);
    }

    // Enemy ship spawning logic
    static double enemy_spawn_timer = 0.0;
    enemy_spawn_timer += deltaTime;
    if (enemy_spawn_timer > 10.0) { // Spawn an enemy ship every 10 seconds
        enemy_spawn_timer = 0.0;
        spawn_enemy_ship();
    }
}
