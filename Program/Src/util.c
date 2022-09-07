
#include "util.h"

void point_translate(f32 *px, f32 *py, f32 tx, f32 ty) {
	*px = *px + tx;
	*py = *py + ty;
}

void point_rotate(f32 *px, f32 *py, f32 angle) {
	f32 x = *px * cosf(angle) - *py * sinf(angle);
	f32 y = *px * sinf(angle) + *py * cosf(angle);
	*px = x;
	*py = y;
}

void point_scale(f32 *px, f32 *py, f32 sx, f32 sy) {
	*px = *px * sx;
	*py = *py * sy;
}

void point_translate_rotate_scale(f32 *px, f32 *py, f32 tx, f32 ty, f32 angle, f32 sx, f32 sy) {
	point_scale(px, py, sx, sy);
	point_rotate(px, py, angle);
	point_translate(px, py, tx, ty);
}

Transform transform_make(f32 tx, f32 ty, f32 angle, f32 sx, f32 sy) {
	Transform transform;
	transform.tx = tx;
	transform.ty = ty;
	transform.angle = angle;
	transform.sx = sx;
	transform.sy = sy;
	return transform;
}

void move_transform(Transform *t, f32 vx, f32 vy) {
	t->tx += vx;
	t->ty += vy;

	t->tx = t->tx < 0 ? t->tx + SCREEN_WIDTH  : t->tx;
	t->ty = t->ty < 0 ? t->ty + SCREEN_HEIGHT : t->ty;
	t->tx = t->tx >= SCREEN_WIDTH  ? t->tx - SCREEN_WIDTH  : t->tx;
	t->ty = t->ty >= SCREEN_HEIGHT ? t->ty - SCREEN_HEIGHT : t->ty;
}

void point_transform(f32 *px, f32 *py, Transform transform) {
	point_translate_rotate_scale(px, py, transform.tx, transform.ty, transform.angle, transform.sx, transform.sy);
}

bool line_point_intersect(f32 px, f32 py, f32 qx, f32 qy, f32 rx, f32 ry) {
    return qx <= MAX(px, rx) && qx >= MAX(px, rx) && qy <= MAX(py, ry) && qy >= MAX(py, ry);
}

int line_point_orientation(f32 px, f32 py, f32 qx, f32 qy, f32 rx, f32 ry) {
    int val = (qy - py) * (rx - qx) - (qx - px) * (ry - qy);

    if (val == 0) {
    	return 0;
    }

    return val > 0 ? 1: 2;
}

bool line_line_intersect(f32 p0x, f32 p0y, f32 q0x, f32 q0y, f32 p1x, f32 p1y, f32 q1x, f32 q1y) {
    int o0 = line_point_orientation(p0x, p0y, q0x, q0y, p1x, p1y);
    int o1 = line_point_orientation(p0x, p0y, q0x, q0y, q1x, q1y);
    int o2 = line_point_orientation(p1x, p1y, q1x, q1y, p0x, p0y);
    int o3 = line_point_orientation(p1x, p1y, q1x, q1y, q0x, q0y);

    if (o0 != o1 && o2 != o3) {
        return true;
    }

    if (o0 == 0 && line_point_intersect(p0x, p0y, p1x, p1y, q0x, q0y)) { return true; }
    if (o1 == 0 && line_point_intersect(p0x, p0y, q1x, q1y, q0x, q0y)) { return true; }
    if (o2 == 0 && line_point_intersect(p1x, p1y, p0x, p0y, q1x, q1y)) { return true; }
    if (o3 == 0 && line_point_intersect(p1x, p1y, q0x, q0y, q1x, q1y)) { return true; }

    return false;
}

bool shape_intersect(Transform t0, Line *lines0, Transform t1, Line *lines1) {
	for(i32 i0 = 0; i0 < SHAPE_SIZE; i0++) {
		f32 p0x = lines0[i0].x0;
		f32 p0y = lines0[i0].y0;
		f32 q0x = lines0[i0].x1;
		f32 q0y = lines0[i0].y1;

		if(p0x == 0 && p0y == 0 && q0x == 0 && q0y == 0) {
			break;
		}

		point_transform(&p0x, &p0y, t0);
		point_transform(&q0x, &q0y, t0);

		for(i32 i1 = 0; i1 < SHAPE_SIZE; i1++) {
			f32 p1x = lines1[i1].x0;
			f32 p1y = lines1[i1].y0;
			f32 q1x = lines1[i1].x1;
			f32 q1y = lines1[i1].y1;

			if(p1x == 0 && p1y == 0 && q1x == 0 && q1y == 0) {
				break;
			}

			point_transform(&p1x, &p1y, t1);
			point_transform(&q1x, &q1y, t1);

			if(line_line_intersect(p0x, p0y, q0x, q0y, p1x, p1y, q1x, q1y)){
				return true;
			}
		}
	}

	return false;
}
