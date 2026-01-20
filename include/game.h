/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#ifndef GAME_H
#define GAME_H


#include <GLFW/glfw3.h>

extern int asteroids_destroyed_count;

void game_init(int window_width, int window_height);
void game_update(GLFWwindow *window, double deltaTime);
void game_render();
void game_cleanup();
void game_reset();

#endif
