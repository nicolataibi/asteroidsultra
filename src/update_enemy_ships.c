/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "update_enemy_ships.h"
#include "entities_globals.h"
#include "update_enemy_ship.h"

void update_enemy_ships(double deltaTime) {
    for (int i = 0; i < MAX_ENEMY_SHIPS; i++) {
        update_enemy_ship(&enemy_ships[i], deltaTime);
    }
}
