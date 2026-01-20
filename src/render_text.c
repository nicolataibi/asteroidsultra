/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "render_text.h"
#include "glad/glad.h"
#include "stb_truetype.h"
#include "text_globals.h"
#include <cglm/cglm.h>

void render_text(const char *text, float x, float y, float scale, vec3 color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mat4 projection = GLM_MAT4_IDENTITY_INIT;
    glm_ortho(0.0f, (float)g_window_width, 0.0f, (float)g_window_height, -1.0f, 1.0f, projection);

    glUseProgram(text_shader_program);
    glUniformMatrix4fv(glGetUniformLocation(text_shader_program, "projection"), 1, GL_FALSE, (float*)projection);
    glUniform3f(glGetUniformLocation(text_shader_program, "textColor"), color[0], color[1], color[2]);
    glUniform1f(glGetUniformLocation(text_shader_program, "textScale"), scale);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ftex);
    glBindVertexArray(text_vao);

    // iterate through all characters
    float current_x = x;
    float current_y = y;
    const char *p;
    for (p = text; *p; p++) {
        if (*p >= 32 && *p < 128) {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(cdata, 1024, 1024, *p - 32, &current_x, &current_y, &q, 1); //1=opengl & d3d10+,0=d3d9

            float xpos = q.x0;
            float ypos = q.y0;
            float w = (q.x1 - q.x0);
            float h = (q.y1 - q.y0);

            float vertices[6][4] = {
                { xpos,     ypos + h,   q.s0, q.t0 },
                { xpos,     ypos,       q.s0, q.t1 },
                { xpos + w, ypos,       q.s1, q.t1 },

                { xpos,     ypos + h,   q.s0, q.t0 },
                { xpos + w, ypos,       q.s1, q.t1 },
                { xpos + w, ypos + h,   q.s1, q.t0 }
            };

            // render glyph texture over quad
            glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}
