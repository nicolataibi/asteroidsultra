/* 
 * ASTEROIDS 
 * Authors: Nicola Taibi 
 * Supported by Google Gemini
 * Copyright (C) 2026 Nicola Taibi
 * License: GNU General Public License v3.0
 */

#include "text_globals.h"

stbtt_bakedchar cdata[96];
GLuint ftex;
GLuint text_vao, text_vbo;
GLuint text_shader_program;

const char* text_vertex_shader_source = "#version 330 core\n"
    "layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>\n"
    "out vec2 TexCoords;\n"
    "uniform mat4 projection;\n"
    "uniform float textScale;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = projection * vec4(vertex.xy * textScale, 0.0, 1.0);\n"
    "    TexCoords = vertex.zw;\n"
    "}";

const char* text_fragment_shader_source = "#version 330 core\n"
    "in vec2 TexCoords;\n"
    "out vec4 color;\n"
    "uniform sampler2D text;\n"
    "uniform vec3 textColor;\n"
    "void main()\n"
    "{\n"
    "    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
    "    color = vec4(textColor, 1.0) * sampled;\n"
    "}";


