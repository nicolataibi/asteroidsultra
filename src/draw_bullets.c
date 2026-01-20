/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "draw_bullets.h"
#include "glad/glad.h"
#include "entities_globals.h"
#include <cglm/cglm.h>

void draw_bullets(unsigned int shader_program) {
    glBindVertexArray(bullet_vao);
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            mat4 model = GLM_MAT4_IDENTITY_INIT;
            glm_translate(model, (vec3){bullets[i].pos[0], bullets[i].pos[1], 0.0f});

            glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, (float*)model);
            glUniform3f(glGetUniformLocation(shader_program, "color"), 1.0f, 0.0f, 0.0f);

            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }
}
