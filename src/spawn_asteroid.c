/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "spawn_asteroid.h"
#include "entities_globals.h"
#include "glad/glad.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void spawn_asteroid(vec2 pos, int generation, float scale) {
    printf("spawn_asteroid called with pos: (%f, %f), generation: %d, scale: %f)\n", pos[0], pos[1], generation, scale);
    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        if (!asteroids[i].active) {
            asteroids[i].active = 1;
            asteroids[i].pos[0] = pos[0];
            asteroids[i].pos[1] = pos[1];
            asteroids[i].generation = generation;

            float angle = (float)rand() / (float)RAND_MAX * 2.0f * M_PI;
            float speed = (float)rand() / (float)RAND_MAX * 0.2f + 0.1f;
            asteroids[i].velocity[0] = cos(angle) * speed;
            asteroids[i].velocity[1] = sin(angle) * speed;
            asteroids[i].scale = scale;

            // Generate unique asteroid shape
            float vertices[8 * 3];
            for (int j = 0; j < 8; j++) {
                float angle_vert = (float)j / 8.0f * 2.0f * M_PI;
                float radius = ((float)rand() / (float)RAND_MAX * 0.1f + 0.05f) * scale;
                vertices[j * 3] = cos(angle_vert) * radius;
                vertices[j * 3 + 1] = sin(angle_vert) * radius;
                vertices[j * 3 + 2] = 0.0f;
            }

            glGenVertexArrays(1, &asteroids[i].vao);
            glGenBuffers(1, &asteroids[i].vbo);
            glBindVertexArray(asteroids[i].vao);
            glBindBuffer(GL_ARRAY_BUFFER, asteroids[i].vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            return;
        }
    }
}