/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "init_text_rendering.h"
#include "glad/glad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stb_truetype.h"
#include "text_globals.h"

void init_text_rendering(const char *font_path, float font_size, int window_width, int window_height) {
    g_window_width = window_width;
    g_window_height = window_height;
    // Compile and link the text shader program
    // vertex shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &text_vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
    }
    // fragment shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &text_fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    // check for shader compile errors
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
    }
    // link shaders
    text_shader_program = glCreateProgram();
    glAttachShader(text_shader_program, vertex_shader);
    glAttachShader(text_shader_program, fragment_shader);
    glLinkProgram(text_shader_program);
    // check for linking errors
    glGetProgramiv(text_shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(text_shader_program, 512, NULL, infoLog);
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Load font
    FILE* font_file = fopen(font_path, "rb");    if (!font_file) {        perror("fopen font");       return;    }
    fseek(font_file, 0, SEEK_END);
    long size = ftell(font_file);
    fseek(font_file, 0, SEEK_SET);
    unsigned char* ttf_buffer = (unsigned char*)malloc(size);
    fread(ttf_buffer, 1, size, font_file);
    fclose(font_file);

    unsigned char temp_bitmap[1024 * 1024];
    stbtt_BakeFontBitmap(ttf_buffer, 0, font_size, temp_bitmap, 1024, 1024, 32, 96, cdata); // no guarantee this fits!
    free(ttf_buffer);

    // Create texture
    glGenTextures(1, &ftex);
    glBindTexture(GL_TEXTURE_2D, ftex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1024, 1024, 0, GL_RED, GL_UNSIGNED_BYTE, temp_bitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // VAO and VBO for text rendering
    glGenVertexArrays(1, &text_vao);
    glGenBuffers(1, &text_vbo);
    glBindVertexArray(text_vao);
    glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
