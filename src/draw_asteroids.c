/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "draw_asteroids.h"
#include "glad/glad.h"
#include "entities_globals.h"
#include <cglm/cglm.h>

void draw_asteroids(unsigned int shader_program) {
    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        if (asteroids[i].active) {
            glBindVertexArray(asteroids[i].vao);
            mat4 model = GLM_MAT4_IDENTITY_INIT;
            glm_translate(model, (vec3){asteroids[i].pos[0], asteroids[i].pos[1], 0.0f});
            glm_scale(model, (vec3){asteroids[i].scale, asteroids[i].scale, 1.0f});

            glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, (float*)model);
            glUniform3f(glGetUniformLocation(shader_program, "color"), 0.5f, 0.5f, 0.5f);

            glDrawArrays(GL_LINE_LOOP, 0, 8);
        }
    }
}
