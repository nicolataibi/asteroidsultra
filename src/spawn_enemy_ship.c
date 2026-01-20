/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "spawn_enemy_ship.h"
#include "entities_globals.h"
#include <stdlib.h>

void spawn_enemy_ship() {
    for (int i = 0; i < MAX_ENEMY_SHIPS; i++) {
        if (!enemy_ships[i].active) {
            enemy_ships[i].active = 1;
            enemy_ships[i].pos[0] = 1.0f; // Start just off screen to the right
            enemy_ships[i].pos[1] = (float)rand() / (float)RAND_MAX * 1.8f - 0.9f; // Random Y position
            enemy_ships[i].velocity[0] = -0.2f; // Move left
            enemy_ships[i].velocity[1] = 0.0f;
            enemy_ships[i].shoot_timer = 0.0;
            return; // Spawn one at a time
        }
    }
}
