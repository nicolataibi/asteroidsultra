CC = gcc
CFLAGS = -I./include -I./include/glad -I./vendor/cglm-0.9.2/include -I./vendor -Wall -g
LDFLAGS = -lglfw -lGL -lm -ldl

SRC = src/main.c src/glad.c src/game.c src/entities.c src/input.c src/text.c src/read_shader_file.c src/game_globals.c src/game_init.c src/check_collisions.c src/game_render.c src/game_cleanup.c src/game_reset.c src/entities_globals.c src/init_ship.c src/init_asteroids.c src/init_bullets.c src/init_enemy_ships.c src/update_ship.c src/update_asteroids.c src/update_bullets.c src/update_enemy_ship.c src/update_enemy_ships.c src/draw_ship.c src/draw_asteroids.c src/draw_bullets.c src/draw_enemy_ships.c src/spawn_asteroid.c src/spawn_enemy_ship.c src/cleanup_entities.c src/spawn_initial_asteroids.c src/process_input.c src/screen_globals.c src/text_globals.c src/init_text_rendering.c src/render_text.c src/get_text_width.c src/cleanup_text_rendering.c src/stb_truetype_impl.c src/game_update.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) src/main.o src/glad.o src/game.o src/entities.o src/input.o src/text.o src/read_shader_file.o src/game_globals.o src/game_init.o src/check_collisions.o src/game_render.o src/game_cleanup.o src/game_reset.o src/entities_globals.o src/init_ship.o src/init_asteroids.o src/init_bullets.o src/init_enemy_ships.o src/update_ship.o src/update_asteroids.o src/update_bullets.o src/game_update.o src/update_enemy_ship.o src/update_enemy_ships.o src/draw_ship.o src/draw_asteroids.o src/draw_bullets.o src/draw_enemy_ships.o src/spawn_asteroid.o src/spawn_enemy_ship.o src/cleanup_entities.o src/spawn_initial_asteroids.o src/process_input.o src/screen_globals.o src/text_globals.o src/init_text_rendering.o src/render_text.o src/get_text_width.o src/cleanup_text_rendering.o src/stb_truetype_impl.o -o $(EXECUTABLE) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)