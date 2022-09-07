
#ifndef INC_UI_H_
#define INC_UI_H_

#include "basic.h"
#include "draw.h"

typedef struct  UIState_Def {
	i32 color;

	i32 activeItem;
} UIState;

void ui_init();
void ui_start();
void ui_end();

bool ui_button(i32 id, i32 x, i32 y, i32 w, i32 h, char *string);

#endif /* INC_UI_H_ */
