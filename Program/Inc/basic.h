
#ifndef INC_BASIC_H_
#define INC_BASIC_H_

#include <stdbool.h>
#include <stdint.h>

typedef   int8_t i8 ;
typedef  int16_t i16;
typedef  int32_t i32;
typedef  int64_t i64;
typedef  uint8_t u8 ;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef    float f32;
typedef   double f64;

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX(v0, v1) (v0 > v1 ? v0 : v1)
#define MIN(v0, v1) (v0 < v1 ? v0 : v1)
#define CLAMP(v, min, max) (MAX(MIN(v, max), min))

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

#endif /* INC_BASIC_H_ */
