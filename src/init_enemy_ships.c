/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "init_enemy_ships.h"
#include "glad/glad.h"
#include "entities_globals.h"

void init_enemy_ships() {
    int i; // Declare i before the loop
    for (i = 0; i < MAX_ENEMY_SHIPS; i++) {
        enemy_ships[i].active = 0;
        enemy_ships[i].shoot_timer = 0.0;
        enemy_ships[i].current_shoot_direction_idx = 0;
        enemy_ships[i].explosion_timer = 0.0f;

        glGenVertexArrays(1, &enemy_ships[i].explosion_vao);
        glGenBuffers(1, &enemy_ships[i].explosion_vbo);

        glBindVertexArray(enemy_ships[i].explosion_vao);
        glBindBuffer(GL_ARRAY_BUFFER, enemy_ships[i].explosion_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * 800, NULL, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    // Define vertices for the enemy ship (half the size of the player ship)
    float enemy_ship_vertices[] = {
        // Fuselage & Nose
        0.0f * 0.25f, 0.08f * 0.25f, 0.0f,    // Point of nose
        0.03f * 0.25f, 0.03f * 0.25f, 0.0f,   // Right side of nose
        0.03f * 0.25f, -0.06f * 0.25f, 0.0f,  // Right side of fuselage

        // Right Tail
        0.05f * 0.25f, -0.09f * 0.25f, 0.0f,  // Outer point of right tail
        0.05f * 0.25f, -0.07f * 0.25f, 0.0f,  // Inner point of right tail
        0.03f * 0.25f, -0.06f * 0.25f, 0.0f,  // Connect to fuselage

        // Left Tail
        -0.03f * 0.25f, -0.06f * 0.25f, 0.0f, // Connect to fuselage
        -0.05f * 0.25f, -0.07f * 0.25f, 0.0f, // Inner point of left tail
        -0.05f * 0.25f, -0.09f * 0.25f, 0.0f, // Outer point of left tail

        // Left side of fuselage
        -0.03f * 0.25f, -0.06f * 0.25f, 0.0f, 
        -0.03f * 0.25f, 0.03f * 0.25f, 0.0f,  // Left side of nose
        0.0f * 0.25f, 0.08f * 0.25f, 0.0f,    // Back to nose point

        // Wings (as separate lines)
        -0.03f * 0.25f, 0.01f * 0.25f, 0.0f,  // Connect to fuselage
        -0.1f * 0.25f, 0.01f * 0.25f, 0.0f,   // Left wing tip
        0.03f * 0.25f, 0.01f * 0.25f, 0.0f,   // Connect to fuselage
        0.1f * 0.25f, 0.01f * 0.25f, 0.0f     // Right wing tip
    };

    glGenVertexArrays(1, &enemy_ship_vao);
    glGenBuffers(1, &enemy_ship_vbo);
    glBindVertexArray(enemy_ship_vao);
    glBindBuffer(GL_ARRAY_BUFFER, enemy_ship_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(enemy_ship_vertices), enemy_ship_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}