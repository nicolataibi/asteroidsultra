/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "draw_enemy_ships.h"
#include "glad/glad.h"
#include "entities_globals.h"
#include <cglm/cglm.h>

void draw_enemy_ships(unsigned int shader_program) {
    for (int i = 0; i < MAX_ENEMY_SHIPS; i++) {
        if (enemy_ships[i].active) {
            mat4 model = GLM_MAT4_IDENTITY_INIT;
            glm_translate(model, (vec3){enemy_ships[i].pos[0], enemy_ships[i].pos[1], 0.0f});
            glm_rotate(model, enemy_ships[i].angle, (vec3){0.0f, 0.0f, 1.0f});

            glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, (float*)model);
            glUniform3f(glGetUniformLocation(shader_program, "color"), 1.0f, 0.0f, 0.0f); // Red color

            glBindVertexArray(enemy_ship_vao);
            glDrawArrays(GL_LINE_LOOP, 0, 12);
            glDrawArrays(GL_LINES, 12, 4);
        } else if (enemy_ships[i].explosion_timer > 0.0f) {
            printf("Drawing enemy ship explosion. Timer: %f, VAO: %u\n", enemy_ships[i].explosion_timer, enemy_ships[i].explosion_vao); fflush(stdout);
            mat4 model = GLM_MAT4_IDENTITY_INIT;
            glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, (float*)model);
            glUniform3f(glGetUniformLocation(shader_program, "color"), 1.0f, 0.5f, 0.0f); // Orange color for explosion

            glBindVertexArray(enemy_ships[i].explosion_vao);
            glDrawArrays(GL_POINTS, 0, 800);
        }
    }
}
