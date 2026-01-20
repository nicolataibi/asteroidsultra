/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "init_ship.h"
#include "glad/glad.h"
#include "entities_globals.h"
#include <cglm/cglm.h>
#include <stdlib.h>
#include <math.h>

void init_ship() {
    ship.pos[0] = 0.0f;
    ship.pos[1] = 0.0f;
    

    ship.angle = 0.0f;
    ship.velocity[0] = 0.0f;
    ship.velocity[1] = 0.0f;
    ship.acceleration[0] = 0.0f;
    ship.acceleration[1] = 0.0f;
    ship.active = 1;
    ship.explosion_timer = 0.0f;

    float ship_vertices[] = {
        // Fuselage & Nose
        0.0f * 0.5f, 0.08f * 0.5f, 0.0f,    // Point of nose
        0.03f * 0.5f, 0.03f * 0.5f, 0.0f,   // Right side of nose
        0.03f * 0.5f, -0.06f * 0.5f, 0.0f,  // Right side of fuselage

        // Right Tail
        0.05f * 0.5f, -0.09f * 0.5f, 0.0f,  // Outer point of right tail
        0.05f * 0.5f, -0.07f * 0.5f, 0.0f,  // Inner point of right tail
        0.03f * 0.5f, -0.06f * 0.5f, 0.0f,  // Connect to fuselage

        // Left Tail
        -0.03f * 0.5f, -0.06f * 0.5f, 0.0f, // Connect to fuselage
        -0.05f * 0.5f, -0.07f * 0.5f, 0.0f, // Inner point of left tail
        -0.05f * 0.5f, -0.09f * 0.5f, 0.0f, // Outer point of left tail

        // Left side of fuselage
        -0.03f * 0.5f, -0.06f * 0.5f, 0.0f, 
        -0.03f * 0.5f, 0.03f * 0.5f, 0.0f,  // Left side of nose
        0.0f * 0.5f, 0.08f * 0.5f, 0.0f,    // Back to nose point

        // Wings (as separate lines)
        -0.03f * 0.5f, 0.01f * 0.5f, 0.0f,  // Connect to fuselage
        -0.1f * 0.5f, 0.01f * 0.5f, 0.0f,   // Left wing tip
        0.03f * 0.5f, 0.01f * 0.5f, 0.0f,   // Connect to fuselage
        0.1f * 0.5f, 0.01f * 0.5f, 0.0f     // Right wing tip
    };

    glGenVertexArrays(1, &ship_vao);
    glGenBuffers(1, &ship_vbo);
    glBindVertexArray(ship_vao);
    glBindBuffer(GL_ARRAY_BUFFER, ship_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ship_vertices), ship_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Explosion VAO/VBO setup
    glGenVertexArrays(1, &ship.explosion_vao);
    glGenBuffers(1, &ship.explosion_vbo);
    glBindVertexArray(ship.explosion_vao);
    glBindBuffer(GL_ARRAY_BUFFER, ship.explosion_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * 800 * 2, NULL, GL_DYNAMIC_DRAW); // 800 lines, 2 points per line
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
