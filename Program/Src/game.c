
#include <stdbool.h>
#include "game.h"

Line shapes[SHAPE_COUNT][SHAPE_SIZE] = {
	{
		{ -3, -2, -3,  2},
		{ -3,  2, -5,  4},
		{ -5,  4, 12,  0},
		{ 12,  0, -5, -4},
		{ -5, -4, -3, -2},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0}
	},
	{
		{ -3, -2, -3,  2},
		{ -3,  2, -5,  4},
		{ -5,  4, 12,  0},
		{ 12,  0, -5, -4},
		{ -5, -4, -3, -2},
		{ -3,  2, -7,  0},
		{ -7,  0, -3, -2},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0}
	},
	{
		{ -4,  2, -2,  6 },
		{ -2,  6,  2,  6 },
		{  2,  6,  4,  2 },
		{  4,  2, -4,  2 },
		{  4,  2, 10, -2 },
		{ 10, -2,  4, -6 },
		{  4, -6, -4, -6 },
		{ -4, -6,-10, -2 },
		{-10, -2, -4,  2 },
		{-10, -2, 10, -2 },
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0}
	},
	{
		{  0,  4,  4,  8},
		{  4,  8,  8,  4},
		{  8,  4,  6,  0},
		{  6,  0,  8, -4},
		{  8, -4,  2, -8},
		{  2, -8, -4, -8},
		{ -4, -8, -8, -4},
		{ -8, -4, -8,  4},
		{ -8,  4, -4,  8},
		{ -4,  8,  0,  4},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0}
	},
	{
		{  4,  2,  8,  4},
		{  8,  4,  4,  8},
		{  4,  8,  0,  6},
		{  0,  6, -4,  8},
		{ -4,  8, -8,  4},
		{ -8,  4, -6,  0},
		{ -6,  0, -8, -4},
		{ -8, -4, -4, -8},
		{ -4, -8, -2, -6},
		{ -2, -6,  4, -8},
		{  4, -8,  8, -2},
		{  8, -2,  4,  2},
		{  4,  2,  4,  2}
	},
	{
		{ -4,  0, -8, -2},
		{ -8, -2, -4, -8},
		{ -4, -8,  0, -2},
		{  0, -2,  0, -8},
		{  0, -8,  4, -8},
		{  4, -8,  8, -2},
		{  8, -2,  8,  2},
		{  8,  2,  4,  8},
		{  4,  8, -2,  8},
		{ -2,  8, -8,  2},
		{ -8,  2, -4,  0},
		{ -4,  0, -4,  0},
		{  0,  0,  0,  0}
	},
	{
		{  2,  0,  6,  2},
		{  6,  2,  6,  4},
		{  6,  4,  0,  8},
		{  0,  8, -6,  8},
		{ -6,  8, -4,  4},
		{ -4,  4,-10,  4},
		{-10,  4,-10, -2},
		{-10, -2, -6, -8},
		{ -6, -8,  0, -6},
		{  0, -6,  2, -8},
		{  2, -8,  6, -4},
		{  6, -4,  0,  0},
		{  0,  0,  2,  0}
	},
	{
		{ -1,  0,  1,  0},
		{  0, -1,  0,  1},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0},
		{  0,  0,  0,  0}
	}
};

GameState gameState;

void swap_scene(GameScene scene);

void menu_init() {

}

void menu_tick() {
	//TODO: String size (multiplier like 2x the size)
	//TODO: The font is bad (the letter i is broken)
	//char *title = "Asteroids";
	char *title = "ASTEROIDS";
	i32 titleLength = strlen(title);
	i32 titleX = (SCREEN_WIDTH  / 2) - (titleLength * (CHAR_WIDTH /2));
	i32 titleY = (SCREEN_HEIGHT / 4) - (CHAR_HEIGHT / 2);
	draw_string(title, titleX, titleY, 15);

	i32 buttonW = 120;
	i32 buttonH = 40;

	i32 buttonX = (SCREEN_WIDTH  / 2) - (buttonW / 2);
	i32 buttonY = (SCREEN_HEIGHT / 2) - (buttonH / 2);

	if(ui_button(1, buttonX, buttonY, buttonW, buttonH, "Play")) {
		swap_scene(GAME_SCENE_LEVEL);
	}
}

void score_init() {

}

void score_tick() {
	char *title = "ASTEROIDS";
	i32 titleLength = strlen(title);
	i32 titleX = (SCREEN_WIDTH  / 2) - (titleLength * (CHAR_WIDTH /2));
	i32 titleY = (SCREEN_HEIGHT / 4) - (CHAR_HEIGHT / 2);
	draw_string(title, titleX, titleY, 15);

	char score[64];
	sprintf(&score, "SCORE %06d", gameState.score);
	i32 scoreLength = strlen(score);
	i32 scoreX = (SCREEN_WIDTH  / 2) - (scoreLength * (CHAR_WIDTH /2));
	i32 scoreY = (SCREEN_HEIGHT / 4) + 5 * (CHAR_HEIGHT / 2);
	draw_string(score, scoreX, scoreY, 15);

	i32 buttonW = 120;
	i32 buttonH = 40;

	i32 buttonX = (SCREEN_WIDTH  / 2) - (buttonW / 2);
	i32 buttonY = (SCREEN_HEIGHT / 2) - (buttonH / 2);

	if(ui_button(1, buttonX, buttonY, buttonW, buttonH, "Play again")) {
		swap_scene(GAME_SCENE_LEVEL);
	}
}

void spawn_ship() {
	gameState.ship.transform = transform_make(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, M_PI / 2 * 3, 1, 1);
	gameState.ship.thrust = false;
	gameState.ship.thrustCooldown = 0.0f;
	gameState.ship.velocityX = 0.0f;
	gameState.ship.velocityY = 0.0f;
}

void spawn_asteroid(f32 px, f32 py, i32 size) {
	for(i32 i = 0; i < ASTEROID_COUNT; i++) {
		if(!gameState.asteroids[i].alive) {
			gameState.asteroids[i].alive = true;
			gameState.asteroids[i].shape = SHAPE_ASTEROIDS_0 + rand() % 4;
			f32 scale = size == 3 ? 2.0f : (size == 2 ? 1.0f : 0.5f);
			gameState.asteroids[i].transform = transform_make(px, py, 0, scale, scale);
			gameState.asteroids[i].size = size;

			f32 angle = (f32)rand()/(f32)(RAND_MAX/(2 * M_PI));
			gameState.asteroids[i].velocityX = cos(angle) * 100;
			gameState.asteroids[i].velocityY = sin(angle) * 100;
			return;
		}
	}
}

void level_setup() {
	spawn_ship();

	for(i32 i = 0; i < ASTEROID_COUNT; i++) {
		gameState.asteroids[i].alive = false;
	}

	gameState.level++;

	for(i32 i = 0; i < gameState.level + ASTEROID_START_COUNT; i++) {
		f32 x = 0.0f;
		f32 y = 0.0f;
		while(true) {
			//TODO: Check if the asteroid is generated near the ship and try again
			x = rand() % SCREEN_WIDTH;
			y = rand() % SCREEN_HEIGHT;
			if((x < (SCREEN_WIDTH / 2) - 20 || x > (SCREEN_WIDTH / 2) + 20) && (y < (SCREEN_HEIGHT / 2) - 20 || y > (SCREEN_HEIGHT / 2) + 20)) {
				break;
			}
		}
		spawn_asteroid(x, y, 3);
	}
}

void level_init() {
	//Level info
	gameState.score = 0;
	gameState.level = 0;
	gameState.lives = 3;

	gameState.blinkState = false;
	gameState.blink = 0.0f;

	level_setup();
}

void level_tick() {
	if(gameState.blinkState) {
		gameState.blink += gameState.deltaTime;
		if(gameState.blink > BLINK_MAX) {
			set_all_led(false);
			gameState.blink = 0.0f;
			gameState.blinkState = false;
		}
	}

	if(get_button(BUTTON_ESCAPE).down) {
		swap_scene(GAME_SCENE_START);
		return;
	} else if(get_button(BUTTON_OK).down) {
		gameState.pause = true;
	} else if(get_button(BUTTON_DOWN).pressed) {
		gameState.pause = false;
	}

	if(!gameState.pause) {
		bool shoot = get_button(BUTTON_DOWN).pressed;

		i32 numberOfUpdates = 4;
		f32 deltaTime = gameState.deltaTime / numberOfUpdates;
		for(i32 i = 0; i < numberOfUpdates; i++) {
			//Ship(Player)
			f32 accelerationX = 0.0f;
			f32 accelerationY = 0.0f;

			Thumb thumb = get_thumb();
			if(thumb.x != 0 || thumb.y != 0) {
				gameState.ship.transform.angle = atan2f(thumb.y * -1, thumb.x);

				accelerationX = cos(gameState.ship.transform.angle) * SHIP_ACCELERATION;
				accelerationY = sin(gameState.ship.transform.angle) * SHIP_ACCELERATION;

				gameState.ship.thrustCooldown += deltaTime;
				if(gameState.ship.thrustCooldown > SHIP_THRUST_COOLDOWN) {
					gameState.ship.thrust = !gameState.ship.thrust;
					gameState.ship.thrustCooldown -= SHIP_THRUST_COOLDOWN;
				}
			} else {
				gameState.ship.thrust = false;
			}

			accelerationX += gameState.ship.velocityX * -SHIP_FRICTION;
			accelerationY += gameState.ship.velocityY * -SHIP_FRICTION;

			gameState.ship.velocityX = CLAMP(gameState.ship.velocityX + accelerationX * deltaTime, -SHIP_MAX_VELOCITY, SHIP_MAX_VELOCITY);
			gameState.ship.velocityY = CLAMP(gameState.ship.velocityY + accelerationY * deltaTime, -SHIP_MAX_VELOCITY, SHIP_MAX_VELOCITY);

			move_transform(&gameState.ship.transform, gameState.ship.velocityX * deltaTime, gameState.ship.velocityY * deltaTime);

		//	char velString[64];
		//	sprintf(velString, "Vel X:%5d, Y:%5d\r\n", (i32)(gameState.ship.velocityX * 1000), (i32)(gameState.ship.velocityY * 1000));
		//	usb_log(velString, strlen(velString));

			//Bullets
			for(i32 i = 0; i < BULLET_COUNT; i++) {
				Bullet *bullet = gameState.bullets + i;
				if(bullet->alive) {
					for(i32 i = 0; i < ASTEROID_COUNT; i++) {
						Asteroid *asteroid = gameState.asteroids + i;
						if(asteroid->alive && shape_intersect(bullet->transform, shapes[SHAPE_BULLET], asteroid->transform, shapes[asteroid->shape])) {
							asteroid->alive = false;
							set_all_led(true);
							gameState.blinkState = true;
							gameState.blink = 0.0f;

							switch(asteroid->size) {
								case 3: gameState.score += 250; break;
								case 2: gameState.score += 100; break;
								case 1: gameState.score +=  25; break;
							}

							if(asteroid->size > 1) {
								i32 size = asteroid->size - 1;
								spawn_asteroid(asteroid->transform.tx, asteroid->transform.ty, size);
								spawn_asteroid(asteroid->transform.tx, asteroid->transform.ty, size);
							}
							bullet->alive = false;
							break;
						}
					}

					bullet->time += deltaTime;
					if(bullet->time > BULLET_ALIVE_TIME) {
						bullet->alive = false;
						continue;
					}

					move_transform(&bullet->transform, bullet->velocityX * deltaTime, bullet->velocityY * deltaTime);
				}
			}

			if(shoot) {
				for(i32 i = 0; i < BULLET_COUNT; i++) {
					if(!gameState.bullets[i].alive) {
						gameState.bullets[i].alive = true;
						gameState.bullets[i].time = 0.0f;
						f32 bx = gameState.ship.transform.tx + cos(gameState.ship.transform.angle) * 10;
						f32 by = gameState.ship.transform.ty + sin(gameState.ship.transform.angle) * 10;
						gameState.bullets[i].transform = transform_make(bx, by, gameState.ship.transform.angle, 1, 1);
						gameState.bullets[i].velocityX = cos(gameState.ship.transform.angle) * BULLET_SPEED + gameState.ship.velocityX;
						gameState.bullets[i].velocityY = sin(gameState.ship.transform.angle) * BULLET_SPEED + gameState.ship.velocityY;
						break;
					}
				}
			}

			//Asteroids
			for(i32 i = 0; i < ASTEROID_COUNT; i++) {
				Asteroid *asteroid = gameState.asteroids + i;
				if(asteroid->alive) {
					if(shape_intersect(gameState.ship.transform, shapes[SHAPE_SHIP], asteroid->transform, shapes[asteroid->shape])) {
						gameState.lives--;
						if(gameState.lives <= 0) {
							swap_scene(GAME_SCENE_SCORE);
							return;
						}

						spawn_ship();
						gameState.pause = true;
						return;
					}

					move_transform(&asteroid->transform, asteroid->velocityX * deltaTime, asteroid->velocityY * deltaTime);
				}
			}


			bool nextLevel = true;
			for(i32 i = 0; i < ASTEROID_COUNT; i++) {
				if(gameState.asteroids[i].alive) {
					nextLevel = false;
				}
			}

			if(nextLevel) {
				level_setup();
			}

			shoot = false;
		}
	}

	//NOTE: DRAW
	if(gameState.ship.thrust) {
		draw_shape(gameState.ship.transform, shapes[SHAPE_SHIP_THRUST], 1);
	} else {
		draw_shape(gameState.ship.transform, shapes[SHAPE_SHIP], 1);
	}

	for(i32 i = 0; i < ASTEROID_COUNT; i++) {
		if(gameState.asteroids[i].alive) {
			draw_shape(gameState.asteroids[i].transform, shapes[gameState.asteroids[i].shape], 1);
		}
	}

	for(i32 i = 0; i < BULLET_COUNT; i++) {
		if(gameState.bullets[i].alive) {
			draw_shape(gameState.bullets[i].transform, shapes[SHAPE_BULLET], 1);
		}
	}

	char score[16];
	sprintf(&score, "%06d", gameState.score);
	i32 scoreLength = strlen(score);
	draw_string(score, 0, 0, 15);

	for(i32 i = 0; i < gameState.lives; i++) {
		Transform t = transform_make(16 + 8 * i, CHAR_HEIGHT * 2, M_PI / 2 * 3, 0.5f, 0.5f);
		draw_shape(t, shapes[SHAPE_SHIP], 1);
	}
}

void swap_scene(GameScene scene) {
	if(scene == gameState.scene) {
		return;
	}

	gameState.scene = scene;
	switch(gameState.scene) {
		case GAME_SCENE_START:  menu_init(); break;
		case GAME_SCENE_SCORE: score_init(); break;
		case GAME_SCENE_LEVEL: level_init(); break;
	}
}

void game_init() {
	set_led(0, true);

	draw_init();

	ui_init();

	set_palette_color( 0, 0x00000000); //Background
	set_palette_color( 1, 0x0000FF00); //Foreground
	set_palette_color(14, 0x00FF0000); //FPS COUNTER
	set_palette_color(15, 0x00FFFFFF); //UI

	sprintf(gameState.fpsCountString, "FPS   0");
}

void game_tick() {
	pull_and_update_inputs();

	clear_screen(0);

	ui_start();

	switch(gameState.scene) {
		case GAME_SCENE_START:  menu_tick(); break;
		case GAME_SCENE_SCORE: score_tick(); break;
		case GAME_SCENE_LEVEL: level_tick(); break;
	}

	ui_end();

	{ // FPS Counter
//		gameState.fpsCounter += gameState.deltaTime;
//		gameState.fpsCount++;
//
//		if(gameState.fpsCounter >= 1.0f) {
//			sprintf(gameState.fpsCountString, "FPS %3ld", gameState.fpsCount);
//			gameState.fpsCounter -= 1.0f;
//			gameState.fpsCount = 0;
//		}
//
//		draw_string(gameState.fpsCountString, 10, 10, 14);
	}

	draw_push();
}
