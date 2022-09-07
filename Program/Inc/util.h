
#ifndef INC_UTIL_H_
#define INC_UTIL_H_

#include "basic.h"

#define SHAPE_SIZE 13

void point_translate(f32 *px, f32 *py, f32 tx, f32 ty);
void point_rotate(f32 *px, f32 *py, f32 angle);
void point_scale(f32 *px, f32 *py, f32 sx, f32 sy);
void point_translate_rotate_scale(f32 *px, f32 *py, f32 tx, f32 ty, f32 angle, f32 sx, f32 sy);

typedef struct Line_Def {
	i32 x0;
	i32 y0;
	i32 x1;
	i32 y1;
} Line;

typedef struct Transform_Def {
	f32 tx;
	f32 ty;
	f32 angle;
	f32 sx;
	f32 sy;
} Transform;

Transform transform_make(f32 tx, f32 ty, f32 angle, f32 sx, f32 sy);

void move_transform(Transform *t, f32 vx, f32 vy);

void point_transform(f32 *px, f32 *py, Transform transform);

bool shape_intersect(Transform t0, Line *lines0, Transform t1, Line *lines1);

#endif /* INC_UTIL_H_ */
