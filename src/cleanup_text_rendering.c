/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "cleanup_text_rendering.h"
#include "glad/glad.h"
#include "text_globals.h"

void cleanup_text_rendering() {
    glDeleteTextures(1, &ftex);
    glDeleteVertexArrays(1, &text_vao);
    glDeleteBuffers(1, &text_vbo);
    glDeleteProgram(text_shader_program);
}
