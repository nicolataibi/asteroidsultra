/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "get_text_width.h"
#include "stb_truetype.h"
#include "text_globals.h"

float get_text_width(const char *text, float scale) {
    float width = 0.0f;
    for (const char *p = text; *p; p++) {
        if (*p >= 32 && *p < 128) {
            stbtt_bakedchar *bc = &cdata[*p - 32];
            width += bc->xadvance * scale;
        }
    }
    return width;
}
