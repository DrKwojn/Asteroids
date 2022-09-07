
#include "ui.h"

UIState uiState;

bool ui_touch_inside(i32 x, i32 y, i32 w, i32 h) {
	Touch touch = get_touch();
	return touch.down && !(touch.x < x || touch.y < y || touch.x >= x + w || touch.y >= y + h);
}

void ui_init() {
	uiState.color = 15;
}

void ui_start() {

}

void ui_end() {
	Touch touch = get_touch();
	if(!touch.down) {
		uiState.activeItem = 0;
	}
}

bool ui_button(i32 id, i32 x, i32 y, i32 w, i32 h, char *string) {
	if(ui_touch_inside(x, y, w, h) && uiState.activeItem == 0) {
		uiState.activeItem = id;
	}

	draw_rect(x, y, w, h, uiState.color);

	i32 stringLength = strlen(string);
	i32 stringX = x + (w / 2) - (stringLength * (CHAR_WIDTH /2));
	i32 stringY = y + (h / 2) - (CHAR_HEIGHT / 2);
	draw_string(string, stringX, stringY, uiState.color);

	Touch touch = get_touch();

	return !touch.down && uiState.activeItem == id;
}
