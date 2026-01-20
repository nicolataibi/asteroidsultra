/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "update_ship.h"
#include "entities_globals.h"
#include "glad/glad.h"
#include <cglm/cglm.h>
#include <math.h>

void update_ship(double deltaTime) {
    if (ship.active) {
        // Update velocity based on acceleration
        ship.velocity[0] += ship.acceleration[0] * deltaTime;
        ship.velocity[1] += ship.acceleration[1] * deltaTime;

        // Apply friction
        ship.velocity[0] *= (1.0f - 0.3f * deltaTime);
        ship.velocity[1] *= (1.0f - 0.3f * deltaTime);

        // Clamp velocity to max speed
        float speed = glm_vec2_norm(ship.velocity);
        if (speed > MAX_SHIP_SPEED) {
            glm_vec2_scale(ship.velocity, MAX_SHIP_SPEED / speed, ship.velocity);
        }

        // Update position based on velocity
        ship.pos[0] += ship.velocity[0] * deltaTime;
        ship.pos[1] += ship.velocity[1] * deltaTime;

        // Screen wrapping
        if (ship.pos[0] > 1.05f) ship.pos[0] = -1.05f;
        if (ship.pos[0] < -1.05f) ship.pos[0] = 1.05f;
        if (ship.pos[1] > 1.05f) ship.pos[1] = -1.05f;
        if (ship.pos[1] < -1.05f) ship.pos[1] = 1.05f;
    } else { // Ship is exploding
        ship.explosion_timer -= deltaTime;
        if (ship.explosion_timer > 0) {
            float explosion_data[800 * 4]; // 800 lines, each with 2 points (x,y) = 4 floats
            for (int i = 0; i < 800; i++) {
                ship.explosion_fragments[i][0] += ship.explosion_velocities[i][0] * deltaTime;
                ship.explosion_fragments[i][1] += ship.explosion_velocities[i][1] * deltaTime;

                explosion_data[i * 4] = ship.explosion_fragments[i][0];
                explosion_data[i * 4 + 1] = ship.explosion_fragments[i][1];
                explosion_data[i * 4 + 2] = ship.explosion_fragments[i][0] + ship.explosion_velocities[i][0] * 0.01f;
                explosion_data[i * 4 + 3] = ship.explosion_fragments[i][1] + ship.explosion_velocities[i][1] * 0.01f;
            }
            glBindBuffer(GL_ARRAY_BUFFER, ship.explosion_vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(explosion_data), explosion_data);
        }
    }
}
