/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "game_cleanup.h"
#include "entities.h"
#include "game_globals.h"
#include "glad/glad.h"

void game_cleanup() {
    cleanup_entities();
    glDeleteProgram(shader_program);
}
