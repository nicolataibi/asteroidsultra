/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "game_reset.h"
#include "entities.h"
#include "game_globals.h"

void game_reset() {
    cleanup_entities();
    init_ship();
    init_asteroids();
    init_bullets();
    init_enemy_ships();
    spawn_initial_asteroids();
    asteroids_destroyed_count = 0;
    enemy_ships_destroyed_count = 0;
}
