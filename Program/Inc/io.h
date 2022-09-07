
#ifndef INC_IO_H_
#define INC_IO_H_

#include "adc.h"
#include "stm32g4xx_ll_gpio.h"
#include "lcd_ili9341.h"
#include "XPT2046_touch.h"

#include "basic.h"

void usb_log(char *string, u32 size);

bool get_led(int index);
void set_led(int index, bool value);
void set_all_led(bool value);

typedef enum ButtonType_Def {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_OK,
	BUTTON_ESCAPE,
	BUTTON_THUMB,

	BUTTON_COUNT
} ButtonType;

typedef struct Button_Def {
	bool down;
	bool downPrev;

	bool pressed;
	bool released;
} Button;

typedef struct Thumb_Def {
	f32 x;
	f32 y;
} Thumb;

typedef struct Touch_Def {
	bool down;
	i32 x;
	i32 y;
} Touch;

typedef struct IO_Def {
	Button buttons[BUTTON_COUNT];
	 Thumb thumb;
	 Touch touch;
} IO;

void pull_and_update_inputs();

Button get_button(ButtonType type);
Thumb get_thumb();
Touch get_touch();

#define LCD_WIDTH  320U
#define LCD_HEIGHT 240U

void lcd_reset_low();
void lcd_reset_high();

void lcd_set_backlight(bool value);

void lcd_set_pixel(u32 x, u32 y, u16 color);
void lcd_fill(u32 x, u32 y, u32 w, u32 h, u16 *data);
void lcd_clear();

void lcd_init();

#endif /* INC_IO_H_ */
