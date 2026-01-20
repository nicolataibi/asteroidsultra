/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "update_asteroids.h"
#include "entities_globals.h"

void update_asteroids(double deltaTime) {
    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        if (asteroids[i].active) {
            asteroids[i].pos[0] += asteroids[i].velocity[0] * deltaTime;
            asteroids[i].pos[1] += asteroids[i].velocity[1] * deltaTime;

            if (asteroids[i].pos[0] > 1.0f || asteroids[i].pos[0] < -1.0f ||
                asteroids[i].pos[1] > 1.0f || asteroids[i].pos[1] < -1.0f) {
                asteroids[i].active = 0;
            }
        }
    }
}
