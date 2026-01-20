/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "spawn_initial_asteroids.h"
#include "entities_globals.h"
#include "spawn_asteroid.h"
#include <stdlib.h>

void spawn_initial_asteroids() {
    for (int i = 0; i < 10; i++) {
        float x = (float)rand() / (float)RAND_MAX * 2.0f - 1.0f;
        float y = (float)rand() / (float)RAND_MAX * 2.0f - 1.0f;
        vec2 pos = {x, y};
        spawn_asteroid(pos, 0, 1.0f);
    }
}
