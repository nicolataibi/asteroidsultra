/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "init_asteroids.h"
#include "entities_globals.h"

void init_asteroids() {
    for (int i = 0; i < MAX_ASTEROIDS; i++) {
        asteroids[i].active = 0;
    }
}
