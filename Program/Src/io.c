
#include "io.h"

void usb_log(char *string, u32 size) {
	CDC_Transmit_FS(string, size);
}

GPIO_TypeDef *convert_index_to_port(int index) {
	if (index >= 0 && index < 4) {
		return GPIOF;
	} else if (index >= 4 && index < 8) {
		return GPIOC;
	} else {
		return 0;
	}
}

u32 convert_index_to_pin(int index) {
	switch(index) {
		case 0: return LL_GPIO_PIN_2;
		case 1: return LL_GPIO_PIN_3;
		case 2: return LL_GPIO_PIN_4;
		case 3: return LL_GPIO_PIN_5;
		case 4: return LL_GPIO_PIN_0;
		case 5: return LL_GPIO_PIN_1;
		case 6: return LL_GPIO_PIN_2;
		case 7: return LL_GPIO_PIN_3;
		default: return 0;
	}
}

bool get_led(int index) {
	GPIO_TypeDef *port = convert_index_to_port(index);
	u32 pin = convert_index_to_pin(index);
	return LL_GPIO_IsOutputPinSet(port, pin) == 1;
}

void set_led(int index, bool value) {
	GPIO_TypeDef *port = convert_index_to_port(index);
	u32 pin = convert_index_to_pin(index);
	if(value) {
		LL_GPIO_SetOutputPin(port, pin);
	} else {
		LL_GPIO_ResetOutputPin(port, pin);
	}
}

void set_all_led(bool value) {
	for(i32 i = 0; i < 8; i++) {
		set_led(i, value);
	}
}

//Button buttons[BUTTON_COUNT];
//Thumb thumb = {};
//Touch touch = {};

IO io = {};

void pull_and_update_inputs() {
	for(i32 index = 0; index < BUTTON_COUNT; index++) {
		io.buttons[index].downPrev = io.buttons[index].down;
	}

	io.buttons[BUTTON_UP    ].down = LL_GPIO_IsInputPinSet(GPIOG, LL_GPIO_PIN_0 ) == 0;
	io.buttons[BUTTON_DOWN  ].down = LL_GPIO_IsInputPinSet(GPIOG, LL_GPIO_PIN_1 ) == 0;
	io.buttons[BUTTON_LEFT  ].down = LL_GPIO_IsInputPinSet(GPIOG, LL_GPIO_PIN_6 ) == 0;
	io.buttons[BUTTON_RIGHT ].down = LL_GPIO_IsInputPinSet(GPIOG, LL_GPIO_PIN_8 ) == 0;
	io.buttons[BUTTON_OK    ].down = LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_15) == 0;
	io.buttons[BUTTON_ESCAPE].down = LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_14) == 0;
	io.buttons[BUTTON_THUMB ].down = LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13) == 0;

	for(i32 index = 0; index < BUTTON_COUNT; index++) {
		io.buttons[index].pressed  =  io.buttons[index].down && !io.buttons[index].downPrev;
		io.buttons[index].released = !io.buttons[index].down &&  io.buttons[index].downPrev;
	}

	HAL_ADC_Start(&hadc4);
	HAL_ADC_PollForConversion(&hadc4, 10);// Waiting for ADC conversion
	io.thumb.x = HAL_ADC_GetValue(&hadc4);

	HAL_ADC_Start(&hadc4);
	HAL_ADC_PollForConversion(&hadc4, 10);// Waiting for ADC conversion
	io.thumb.y = HAL_ADC_GetValue(&hadc4);
	HAL_ADC_Stop(&hadc4);

	i32 max = 3330;
	i32 min = 780;
	f32 range = (f32)(max - min);
	io.thumb.x = ((f32)(io.thumb.x - min) / range) * 2.0f - 1.0f;
	if(io.thumb.x < 0.2f && io.thumb.x > -0.2f) {
		io.thumb.x = 0.0f;
	} else if(io.thumb.x > 0.85f) {
		io.thumb.x = 1.0f;
	} else if(io.thumb.x < -0.85f) {
		io.thumb.x = -1.0f;
	}

	io.thumb.y = ((f32)(io.thumb.y - min) / range) * 2.0f - 1.0f;
	if(io.thumb.y < 0.2f && io.thumb.y > -0.2f) {
		io.thumb.y = 0.0f;
	} else if(io.thumb.y > 0.85f) {
		io.thumb.y = 1.0f;
	} else if(io.thumb.y < -0.85f) {
		io.thumb.y = -1.0f;
	}

	if(XPT2046_TouchPressed() != 0) {
		io.touch.down = true;
		u16 x = 0;
		u16 y = 0;
		XPT2046_TouchGetCoordinates(&x, &y, 0);
		io.touch.x = x;
		io.touch.y = y;
	} else {
		io.touch.down = false;
		io.touch.x = 0;
		io.touch.y = 0;
	}
}

Button get_button(ButtonType type) {
	return io.buttons[type];
}

Thumb get_thumb() {
	return io.thumb;
}

Touch get_touch() {
	return io.touch;
}

#define LCD_RESET_GPIO_PORT GPIOD
#define LCD_RESET_GPIO_PIN  GPIO_PIN_3

#define LCD_BACKLIGHT_GPIO_PORT GPIOB
#define LCD_BACKLIGHT_GPIO_PIN  GPIO_PIN_6

//DMA_HandleTypeDef hLCDDMA = {};

void lcd_reset_low() {
	WRITE_REG(LCD_RESET_GPIO_PORT->BRR, LCD_RESET_GPIO_PIN);
}

void lcd_reset_high() {
	WRITE_REG(LCD_RESET_GPIO_PORT->BSRR, LCD_RESET_GPIO_PIN);
}

void lcd_set_backlight(bool value) {
	if(value) {
		WRITE_REG(LCD_BACKLIGHT_GPIO_PORT->BSRR, LCD_BACKLIGHT_GPIO_PIN);
	} else {
		WRITE_REG(LCD_BACKLIGHT_GPIO_PORT->BRR, LCD_BACKLIGHT_GPIO_PIN);
	}
}

void lcd_set_pixel(u32 x, u32 y, u16 color) {
	ILI9341_SetDisplayWindow(x, y, 1, 1);
	ILI9341_SendData((u16*)&color, 1);
}

void lcd_fill(u32 x, u32 y, u32 w, u32 h, u16 *data) {
	ILI9341_SetDisplayWindow(x, y, w, h);
	ILI9341_SendData(data, w * h);
	//ILI9341_SendDataDMA(data, w * h);
}


void lcd_clear() {
	u32 pixel_count = ILI9341_GetParam(LCD_AREA);
	ILI9341_SetDisplayWindow(0, 0, LCD_WIDTH, LCD_HEIGHT);
	ILI9341_SendRepeatedData(0, pixel_count);
}

void lcd_init() {
	lcd_reset_low();
	HAL_Delay(120);
	lcd_reset_high();
	HAL_Delay(120);

	ILI9341_Init(ILI9341_COLORSPACE_RBG565, ILI9341_MISKO_ROTATE_0);
	ILI9341_DisplayOn();

	//NOTE: DMA Init
//	hLCDDMA.Instance = DMA1_Channel1;
//	hLCDDMA.Init.Direction = DMA_MEMORY_TO_MEMORY;
//	hLCDDMA.Init.PeriphInc = DMA_PINC_ENABLE;
//	hLCDDMA.Init.MemInc = DMA_MINC_ENABLE;
//	hLCDDMA.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
//	hLCDDMA.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
//	hLCDDMA.Init.Mode = DMA_NORMAL;
//	hLCDDMA.Init.Priority = DMA_PRIORITY_VERY_HIGH;
//	hLCDDMA.Init.Request = DMA_REQUEST_MEM2MEM;
//
//	__DMA1_CLK_ENABLE();
//
//	HAL_DMA_Init(&hLCDDMA);

	lcd_clear();
	ILI9341_WaitTransfer();
	lcd_set_backlight(true);
}
