
#ifndef INC_DRAW_H_
#define INC_DRAW_H_

#include "basic.h"
#include "io.h"
#include "util.h"

u16 rgb_888_to_565(u32 rgb);
u32 rgb_565_to_888(u16 rgb);

#define SCREEN_CHUNKS 6
#define SCREEN_CHUNK_HEIGHT (SCREEN_HEIGHT / SCREEN_CHUNKS)

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8

#define BITS_PER_PALETTE 4
#define BITS_PER_PALETTE_MASK ((1 << BITS_PER_PALETTE) - 1)

#define PALETTE_SIZE (1 << BITS_PER_PALETTE)

#define PIXELS_PER_BYTE (8 / BITS_PER_PALETTE)

typedef struct DrawState_def {
	u8 *buffer;
	u16 palette[PALETTE_SIZE];
	u16 *tempBuffer;
} DrawState;

void set_palette_color(i32 index, u32 color);

void draw_pixel(i32 x, i32 y, i32 color);
void draw_line(i32 x0, i32 y0, i32 x1, i32 y1, i32 color);
void draw_rect(i32 x, i32 y, i32 w, i32 h, i32 color);
void fill_rect(i32 x, i32 y, i32 w, i32 h, i32 color);

void draw_char(char character, i32 x, i32 y, i32 color);
void draw_string(char *string, i32 x, i32 y, i32 color);

void draw_shape(Transform transfrom, Line *lines, i32 color);

void clear_screen(i32 color);

void draw_init();
void draw_push();

#endif /* INC_DRAW_H_ */
