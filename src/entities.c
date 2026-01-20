/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "entities.h"
#include "glad/glad.h"
#include <cglm/cglm.h>
#include <stdlib.h>
#include <math.h> // For M_PI and random numbers
#include <stdio.h> // For printf

#include "entities_globals.h"
#include "init_ship.h"
#include "init_asteroids.h"
#include "init_bullets.h"
#include "init_enemy_ships.h"
#include "update_ship.h"
#include "update_asteroids.h"
#include "update_bullets.h"
#include "update_enemy_ship.h"
#include "update_enemy_ships.h"
#include "draw_ship.h"
#include "draw_asteroids.h"
#include "draw_bullets.h"
#include "draw_enemy_ships.h"
#include "spawn_asteroid.h"
#include "spawn_enemy_ship.h"
#include "cleanup_entities.h"
#include "spawn_initial_asteroids.h"
