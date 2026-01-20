/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "update_bullets.h"
#include "entities_globals.h"

void update_bullets(double deltaTime) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].pos[0] += bullets[i].velocity[0] * deltaTime;
            bullets[i].pos[1] += bullets[i].velocity[1] * deltaTime;

            if (bullets[i].pos[0] > 1.0f || bullets[i].pos[0] < -1.0f ||
                bullets[i].pos[1] > 1.0f || bullets[i].pos[1] < -1.0f) {
                bullets[i].active = 0;
                printf("DEBUG: Bullet %d deactivated (off-screen). Pos: (%f, %f)\n", i, bullets[i].pos[0], bullets[i].pos[1]);
            }
        }
    }
}
