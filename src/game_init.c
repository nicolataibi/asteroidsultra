/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "game_init.h"
#include "glad/glad.h"
#include "game.h"
#include "entities.h"
#include "input.h"
#include "text.h"
#include "read_shader_file.h"
#include "game_globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cglm/cglm.h>

void game_init(int window_width, int window_height) {
    g_window_width = window_width;
    g_window_height = window_height;
    // Build and compile our shader program
    // ------------------------------------
    // vertex shader
    const char* vertex_shader_source = read_shader_file("shaders/shader.vs");
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }
    // fragment shader
    const char* fragment_shader_source = read_shader_file("shaders/shader.fs");
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    // check for shader compile errors
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }
    // link shaders
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    // check for linking errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    free((void*)vertex_shader_source);
    free((void*)fragment_shader_source);

    // Initialize game entities
    init_ship();
    init_bullets();
    init_asteroids();
    init_enemy_ships();
    init_text_rendering("vendor/PressStart2P-Regular.ttf", 48.0f, window_width, window_height);
    spawn_initial_asteroids();
}