
#include "BMSPA_font.h"
#include "util.h"
#include "draw.h"

u16 rgb_888_to_565(u32 rgb) {
	u16 r = (u16)(rgb >> 16) & 0x00F8;
	u16 g = (u16)(rgb >>  8) & 0x00FC;
	u16 b = (u16)(rgb >>  0) & 0x00F8;
	u16 result = (r << 8) | (g << 3) | (b >> 3);
	return result;
}

u32 rgb_565_to_888(u16 rgb) {
	u32 r = (u32)(rgb & 0xF800) >> 11;
	u32 g = (u32)(rgb & 0x07E0) >> 5;
	u32 b = (u32)(rgb & 0x001F);
	return (r << 16) | (g << 8) | b;
}

DrawState drawState;

i32 xy_to_index(i32 x, i32 y) {
	if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return -1;
	}

	return y * (SCREEN_WIDTH / PIXELS_PER_BYTE) + (x / PIXELS_PER_BYTE);
}

u8 get_pixel_color(u8 pixel, i32 x) {
	u8 offset = (u8)(x % PIXELS_PER_BYTE) * BITS_PER_PALETTE;
	u8 mask = BITS_PER_PALETTE_MASK << offset;
	return (pixel & mask) >> offset;
}

u8 set_pixel_color(u8 pixel, i32 x, i32 color) {
	u8 offset = (u8)(x % PIXELS_PER_BYTE) * BITS_PER_PALETTE;
	u8 mask = ~(BITS_PER_PALETTE_MASK << offset);
	return (pixel & mask) | (color << offset);
}

void set_palette_color(i32 index, u32 color) {
	if(index < 0 || index >= PALETTE_SIZE) {
		return;
	}

	u16 color16 = rgb_888_to_565(color);
	drawState.palette[index] = color16;
}

void draw_pixel(i32 x, i32 y, i32 color) {
	if(color < 0 || color >= PALETTE_SIZE) {
		return;
	}

	i32 index = xy_to_index(x, y);
	if(index > -1) {
		drawState.buffer[index] = set_pixel_color(drawState.buffer[index], x, color);
	}
}

void draw_line(i32 x0, i32 y0, i32 x1, i32 y1, i32 color) {
	if(color < 0 || color >= PALETTE_SIZE) {
		return;
	}

	i32 dx = abs(x1 - x0);
	i32 sx = x0 < x1 ? 1 : -1;
	i32 dy = -abs(y1 - y0);
	i32 sy = y0 < y1 ? 1 : -1;
	i32 error = dx + dy;

	while(true) {
		i32 index = xy_to_index(x0, y0);
		if(index > -1) {
			drawState.buffer[index] = set_pixel_color(drawState.buffer[index], x0, color);
		}

		if(x0 == x1 && y0 == y1) {
			break;
		}
		i32 e2 = 2 * error;
		if(e2 >= dy) {
			if(x0 == x1) {
				break;
			}
			error = error + dy;
			x0 = x0 + sx;
	}
		if(e2 <= dx) {
			if(y0 == y1) {
				break;
			}
			error = error + dx;
			y0 = y0 + sy;
		}
	}
}

void draw_rect(i32 x, i32 y, i32 w, i32 h, i32 color) {
	i32 index;
	for(i32 dx = x; dx < x + w; dx++) {
		index = xy_to_index(dx, y);
		if(index > -1) {
			drawState.buffer[index] = set_pixel_color(drawState.buffer[index], dx, color);
		}

		index = xy_to_index(dx, y + h - 1);
		if(index > -1) {
			drawState.buffer[index] = set_pixel_color(drawState.buffer[index], dx, color);
		}
	}

	for(i32 dy = y; dy < y + h; dy++) {
		index = xy_to_index(x, dy);
		if(index > -1) {
			drawState.buffer[index] = set_pixel_color(drawState.buffer[index], x, color);
		}

		index = xy_to_index(x + w - 1, dy);
		if(index > -1) {
			drawState.buffer[index] = set_pixel_color(drawState.buffer[index], x + w - 1, color);
		}
	}
}

void fill_rect(i32 x, i32 y, i32 w, i32 h, i32 color) {
	if(color < 0 || color >= PALETTE_SIZE) {
		return;
	}

	if (x >= SCREEN_WIDTH || x + w < 0 || y >= SCREEN_HEIGHT || y + h < 0) {
		return;
	}

	x = x > 0 ? x : 0;
	y = y > 0 ? y : 0;

	w = x + w <= SCREEN_WIDTH  ? w : SCREEN_WIDTH  - x;
	h = y + h <= SCREEN_HEIGHT ? h : SCREEN_HEIGHT - y;

	for(i32 dy = y; dy < y + h; dy++) {
		for(i32 dx = x; dx < x + w; dx++) {
			i32 index = xy_to_index(dx, dy);
			if(index > -1) {
				drawState.buffer[index] = set_pixel_color(drawState.buffer[index], dx, color);
			}
		}
	}
}

void draw_char(char character, i32 x, i32 y, i32 color) {
	if(color < 0 || color >= PALETTE_SIZE) {
		return;
	}

	character &= 0x7F;
	if(character < ' ') {
		character = 0;
	} else {
		character -= ' ';
	}

	u8 *c = (u8*)font[character];
	for(i32 dx = 0; dx < CHAR_WIDTH; dx++) {
		for(i32 dy = 0; dy < CHAR_HEIGHT; dy++) {
			if(c[dx] & (1 << dy)) {
				i32 index = xy_to_index(x + dx, y + dy);
				if(index > -1) {
					drawState.buffer[index] = set_pixel_color(drawState.buffer[index], x + dx, color);
				}
			}
		}
	}
}

void draw_string(char *string, i32 x, i32 y, i32 color) {
	for(i32 index = 0; string[index] != '\0'; index++) {
		draw_char(string[index], x, y, color);
		x += CHAR_WIDTH;
	}
}

void draw_shape(Transform transfrom, Line *lines, i32 color) {
	for(i32 i = 0; i < SHAPE_SIZE; i++) {
		if(lines[i].x0 != lines[i].x1 || lines[i].y0 != lines[i].y1) {
			f32 x0 = lines[i].x0;
			f32 y0 = lines[i].y0;
			point_transform(&x0, &y0, transfrom);

			f32 x1 = lines[i].x1;
			f32 y1 = lines[i].y1;
			point_transform(&x1, &y1, transfrom);

			//draw_line(x0, (SCREEN_HEIGHT - 1) - y0, x1, (SCREEN_HEIGHT - 1) - y1, color);
			draw_line(x0, y0, x1, y1, color);

			if(x0 < 0 || x1 < 0) {
				draw_line(x0 + SCREEN_WIDTH, y0, x1 + SCREEN_WIDTH, y1, color);
			} else if(x0 >= SCREEN_WIDTH || x1 >= SCREEN_WIDTH){
				draw_line(x0 - SCREEN_WIDTH, y0, x1 - SCREEN_WIDTH, y1, color);
			}

			if(y0 < 0 || y1 < 0) {
				draw_line(x0, y0 + SCREEN_HEIGHT, x1, y1 + SCREEN_HEIGHT, color);
			} else if(y0 >= SCREEN_HEIGHT || y1 >= SCREEN_HEIGHT){
				draw_line(x0, y0 - SCREEN_HEIGHT, x1, y1 - SCREEN_HEIGHT, color);
			}
		}
	}
}

void clear_screen(i32 color) {
	fill_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
}

void draw_init() {
	lcd_init();

	drawState.buffer = (u8*)malloc((SCREEN_WIDTH / PIXELS_PER_BYTE) * SCREEN_HEIGHT);
	drawState.tempBuffer = (u16*)malloc(SCREEN_WIDTH * SCREEN_CHUNK_HEIGHT * sizeof(u16));

	clear_screen(0);
}

void draw_push() {
	i32 yOffset = 0;
	for(i32 chunk = 0; chunk < SCREEN_CHUNKS; chunk++) {
		for(i32 y = 0; y < SCREEN_CHUNK_HEIGHT; y++) {
			for(i32 x = 0; x < SCREEN_WIDTH; x++) {
				i32 index = xy_to_index(x, y + yOffset);
				i32 colorIndex = get_pixel_color(drawState.buffer[index], x);
				i32 color = drawState.palette[colorIndex];
				drawState.tempBuffer[y * SCREEN_WIDTH + x] = color;
				//lcd_set_pixel(x, y + yOffset, color);
			}
		}

		lcd_fill(0, yOffset, SCREEN_WIDTH, SCREEN_CHUNK_HEIGHT, drawState.tempBuffer);

		yOffset += SCREEN_CHUNK_HEIGHT;
	}
}
