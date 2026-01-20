/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "draw_ship.h"
#include "glad/glad.h"
#include "entities_globals.h"
#include <cglm/cglm.h>
#include <stdlib.h>

void draw_ship(unsigned int shader_program) {
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model, (vec3){ship.pos[0], ship.pos[1], 0.0f});
    glm_rotate(model, ship.angle, (vec3){0.0f, 0.0f, 1.0f});

    glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, (float*)model);

    if (ship.active) {
        glUniform3f(glGetUniformLocation(shader_program, "color"), 1.0f, 1.0f, 1.0f);
        glBindVertexArray(ship_vao);
        glDrawArrays(GL_LINE_LOOP, 0, 12);
        glDrawArrays(GL_LINES, 12, 4);
    } else if (ship.explosion_timer > 0) {
        mat4 identity_model = GLM_MAT4_IDENTITY_INIT; // Create an identity matrix
        glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, (float*)identity_model); // Set model matrix to identity

        glBindVertexArray(ship.explosion_vao);
        for (int i = 0; i < 800; i++) {
            // Choose a random color for each fragment
            int color_index = rand() % 5; // 0:Red, 1:Yellow, 2:Orange, 3:Purple, 4:Blue
            if (color_index == 0) glUniform3f(glGetUniformLocation(shader_program, "color"), 1.0f, 0.0f, 0.0f); // Red
            else if (color_index == 1) glUniform3f(glGetUniformLocation(shader_program, "color"), 1.0f, 1.0f, 0.0f); // Yellow
            else if (color_index == 2) glUniform3f(glGetUniformLocation(shader_program, "color"), 1.0f, 0.6f, 0.0f); // Orange
            else if (color_index == 3) glUniform3f(glGetUniformLocation(shader_program, "color"), 0.5f, 0.0f, 0.5f); // Purple
            else if (color_index == 4) glUniform3f(glGetUniformLocation(shader_program, "color"), 0.0f, 0.0f, 1.0f); // Blue

            glDrawArrays(GL_LINES, i * 2, 2); // Draw each fragment as a line
        }
    }
}
