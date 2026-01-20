/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "cleanup_entities.h"
#include "glad/glad.h"
#include "entities_globals.h"

void cleanup_entities() {
    glDeleteVertexArrays(1, &ship_vao);
    glDeleteBuffers(1, &ship_vbo);
    glDeleteVertexArrays(1, &ship.explosion_vao);
    glDeleteBuffers(1, &ship.explosion_vbo);
    glDeleteVertexArrays(1, &enemy_ship_vao);
    glDeleteBuffers(1, &enemy_ship_vbo);
    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        if (asteroids[i].active) {
            glDeleteVertexArrays(1, &asteroids[i].vao);
            glDeleteBuffers(1, &asteroids[i].vbo);
        }
    }
    for (int i = 0; i < MAX_ENEMY_SHIPS; i++) {
        glDeleteVertexArrays(1, &enemy_ships[i].explosion_vao);
        glDeleteBuffers(1, &enemy_ships[i].explosion_vbo);
    }
    glDeleteVertexArrays(1, &bullet_vao);
    glDeleteBuffers(1, &bullet_vbo);
}
