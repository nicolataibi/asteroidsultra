/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "game_render.h"
#include "glad/glad.h"
#include "entities.h"
#include "text.h"
#include "game_globals.h"
#include <stdio.h>
#include <cglm/cglm.h>

// Forward declaration for draw_enemy_ships (workaround for linking issue)
void draw_enemy_ships(unsigned int shader_program);

void game_render() {
    

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);

    mat4 projection = GLM_MAT4_IDENTITY_INIT;
    mat4 view = GLM_MAT4_IDENTITY_INIT;

    glm_ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, projection);

    glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, (float*)projection);
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "view"), 1, GL_FALSE, (float*)view);

    draw_ship(shader_program);
    draw_asteroids(shader_program);
    draw_bullets(shader_program);
    draw_enemy_ships(shader_program);

    if (ship.explosion_timer <= 0 && !ship.active) {
        char score_text[50];
        sprintf(score_text, "ASTEROIDI DISTRUTTI: %d", asteroids_destroyed_count);

        float text_scale = 1.0f;

        // "GAME OVER" text
        float game_over_width = get_text_width("GAME OVER", text_scale);
        float game_over_x = (g_window_width - game_over_width) / 2.0f;
        float game_over_y = g_window_height / 2.0f + 50.0f; // Slightly above center
        render_text("GAME OVER", game_over_x, game_over_y, text_scale, (vec3){1.0f, 1.0f, 1.0f});

        // "PREMI SPACEBAR PER RICOMINCIARE" text
        float restart_width = get_text_width("PREMI SPACEBAR PER RICOMINCIARE", text_scale);
        float restart_x = (g_window_width - restart_width) / 2.0f;
        float restart_y = g_window_height / 2.0f; // Center
        render_text("PREMI SPACEBAR PER RICOMINCIARE", restart_x, restart_y, text_scale, (vec3){1.0f, 1.0f, 1.0f});

        // Score text
        float score_width = get_text_width(score_text, text_scale);
        float score_x = (g_window_width - score_width) / 2.0f;
        float score_y = g_window_height / 2.0f - 50.0f; // Slightly below center
        render_text(score_text, score_x, score_y, text_scale, (vec3){1.0f, 1.0f, 1.0f});

        char enemy_ships_destroyed_text_summary[50];
        sprintf(enemy_ships_destroyed_text_summary, "NAVI NEMICHE DISTRUTTE: %d", enemy_ships_destroyed_count);
        float enemy_ships_destroyed_width = get_text_width(enemy_ships_destroyed_text_summary, text_scale);
        float enemy_ships_destroyed_x = (g_window_width - enemy_ships_destroyed_width) / 2.0f;
        float enemy_ships_destroyed_y = g_window_height / 2.0f - 100.0f; // Below score
        render_text(enemy_ships_destroyed_text_summary, enemy_ships_destroyed_x, enemy_ships_destroyed_y, text_scale, (vec3){1.0f, 1.0f, 1.0f});
    }
}
