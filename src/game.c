/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "glad/glad.h"
#include "game.h"
#include "entities.h"
#include "input.h"
#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cglm/cglm.h>

#include "read_shader_file.h"
#include "game_globals.h"
#include "game_init.h"
#include "check_collisions.h"
#include "game_update.h"
#include "game_render.h"
#include "game_cleanup.h"
#include "game_reset.h"
