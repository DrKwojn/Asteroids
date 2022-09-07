
#ifndef INC_GAME_H_
#define INC_GAME_H_

#include "basic.h"
#include "io.h"
#include "draw.h"
#include "ui.h"
#include "util.h"

#define SHAPE_SIZE 13

typedef enum Shape_Def {
	SHAPE_SHIP,
	SHAPE_SHIP_THRUST,
	SHAPE_UFO,
	SHAPE_ASTEROIDS_0,
	SHAPE_ASTEROIDS_1,
	SHAPE_ASTEROIDS_2,
	SHAPE_ASTEROIDS_3,
	SHAPE_BULLET,
	SHAPE_COUNT
} Shape;

#define SHIP_ACCELERATION 200
#define SHIP_FRICTION 0.7
#define SHIP_MAX_VELOCITY 200
#define SHIP_THRUST_COOLDOWN 0.05f

typedef struct Ship_Def {
	Transform transform;
	bool thrust;
	f32 thrustCooldown;
	f32 velocityX;
	f32 velocityY;
} Ship;

#define BULLET_SPEED 200
#define BULLET_ALIVE_TIME 0.75f
#define BULLET_COUNT 8

typedef struct Bullet_Def {
	bool alive;
	f32 time;

	Transform transform;
	f32 velocityX;
	f32 velocityY;
} Bullet;

#define ASTEROID_COUNT 256
#define ASTEROID_START_COUNT 3

typedef struct Asteroid_Def {
	bool alive;
	i32 size;

	Shape shape;
	i32 shapeLineCount;

	Transform transform;
	f32 velocityX;
	f32 velocityY;
} Asteroid;

typedef enum GameScene_Def {
	GAME_SCENE_START,
	GAME_SCENE_SCORE,
	GAME_SCENE_LEVEL
} GameScene;

#define BLINK_MAX 0.3f

typedef struct GameState_Def {
	u32 ticks;      // Milliseconds
	u32 deltaTicks; // Milliseconds

	f32 time;       // Seconds
	f32 deltaTime;  // Seconds

	char fpsCountString[16];
	f32 fpsCounter;
	i32 fpsCount;

	GameScene scene;

	bool pause;

	bool blinkState;
	f32 blink;

	i32 score;
	i32 level;
	i32 lives;

	Ship ship;
	Bullet bullets[BULLET_COUNT];
	Asteroid asteroids[ASTEROID_COUNT];
} GameState;

extern GameState gameState;

void game_init();
void game_tick();

#endif /* INC_GAME_H_ */
