/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "init_bullets.h"
#include "glad/glad.h"
#include "entities_globals.h"

void init_bullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = 0;
    }

    float bullet_vertices[] = {
        0.0f, 0.01f, 0.0f,
        -0.01f, -0.01f, 0.0f,
        0.01f, -0.01f, 0.0f
    };

    glGenVertexArrays(1, &bullet_vao);
    glGenBuffers(1, &bullet_vbo);
    glBindVertexArray(bullet_vao);
    glBindBuffer(GL_ARRAY_BUFFER, bullet_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bullet_vertices), bullet_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
