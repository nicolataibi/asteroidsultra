/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "game.h"
#include "text.h"
#include "screen_globals.h"
#include "game_init.h"
#include "game_update.h"
#include "game_render.h"
#include "game_cleanup.h"

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    printf("Game started and writing to game.txt"); fflush(stdout);
    

    if (!glfwInit())
    {
        printf("Failed to initialize GLFW");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Asteroids", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    game_init(SCR_WIDTH, SCR_HEIGHT);

    double lastTime = glfwGetTime();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        // Cap deltaTime to prevent large jumps, especially at startup or after a long pause.
        // This prevents entities from moving too far in a single frame and disappearing off-screen.
        if (deltaTime > 0.05) {
            deltaTime = 0.05;
        }

        game_update(window, deltaTime);
        game_render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    game_cleanup();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
