/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "process_input.h"
#include "entities.h"
#include "game.h"
#include <cglm/cglm.h>
#include <cglm/vec2.h> // Added for glm_vec2_len
#include <math.h>
#include "entities_globals.h"
#include "game_reset.h"

void process_input(GLFWwindow *window, double deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    float rotation_speed = 3.0f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        ship.angle += rotation_speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        ship.angle -= rotation_speed * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        // Apply acceleration in the direction the ship is facing
        ship.acceleration[0] = -sin(ship.angle) * 3.0f;
        ship.acceleration[1] = cos(ship.angle) * 3.0f;
    } else {
        // No acceleration if W is not pressed
        ship.acceleration[0] = 0.0f;
        ship.acceleration[1] = 0.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        // Apply braking force
        ship.velocity[0] *= (1.0f - 2.0f * deltaTime);
        ship.velocity[1] *= (1.0f - 2.0f * deltaTime);
    }

    static int space_pressed = 0;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !space_pressed) {
        space_pressed = 1;
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!bullets[i].active) {
                bullets[i].active = 1;
                bullets[i].owner = PLAYER;

                // Calculate bullet starting position from the ship's nose
                float nose_offset_x = 0.0f;
                float nose_offset_y = 0.04f;
                bullets[i].pos[0] = ship.pos[0] + (nose_offset_x * cos(ship.angle) - nose_offset_y * sin(ship.angle));
                bullets[i].pos[1] = ship.pos[1] + (nose_offset_x * sin(ship.angle) + nose_offset_y * cos(ship.angle));

                bullets[i].velocity[0] = -sin(ship.angle) * 5.0f;
                bullets[i].velocity[1] = cos(ship.angle) * 5.0f;
                printf("DEBUG: Player bullet %d spawned. Ship Pos: (%f, %f), Ship Angle: %f, Bullet Pos: (%f, %f), Bullet Vel: (%f, %f), Owner: %d\n", i, ship.pos[0], ship.pos[1], ship.angle, bullets[i].pos[0], bullets[i].pos[1], bullets[i].velocity[0], bullets[i].velocity[1], bullets[i].owner);
                break;
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        space_pressed = 0;
    }

    if (!ship.active && ship.explosion_timer <= 0) {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            game_reset();
        }
    }
}
