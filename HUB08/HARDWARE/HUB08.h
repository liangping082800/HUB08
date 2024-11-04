#ifndef HUB08_H_
#define HUB08_H_

#include "main.h"                  // Device header

#define GPIO_SetBits(GPIOx, GPIO_PIN) HAL_GPIO_WritePin(GPIOx, GPIO_PIN, GPIO_PIN_SET)
#define GPIO_ResetBits(GPIOx, GPIO_PIN) HAL_GPIO_WritePin(GPIOx, GPIO_PIN, GPIO_PIN_RESET)

/// 定义宏用于设置引脚状态
#define SET_PIN(GPIOx, GPIO_PIN, GPIO_PinState) ((GPIO_PinState)? GPIO_SetBits(GPIOx, GPIO_PIN) : GPIO_ResetBits(GPIOx, GPIO_PIN))



//#define G1_LED_Pin GPIO_PIN_11
//#define G1_LED_GPIO_Port GPIOC
//#define G2_LED_Pin GPIO_PIN_12
//#define G2_LED_GPIO_Port GPIOC
//#define A_LED_Pin GPIO_PIN_0
//#define A_LED_GPIO_Port GPIOD
//#define B_LED_Pin GPIO_PIN_1
//#define B_LED_GPIO_Port GPIOD
//#define C_LED_Pin GPIO_PIN_2
//#define C_LED_GPIO_Port GPIOD
//#define D_LED_Pin GPIO_PIN_3
//#define D_LED_GPIO_Port GPIOD
//#define R1_LED_Pin GPIO_PIN_4
//#define R1_LED_GPIO_Port GPIOD
//#define R2_LED_Pin GPIO_PIN_5
//#define R2_LED_GPIO_Port GPIOD
//#define SCK_LED_Pin GPIO_PIN_6
//#define SCK_LED_GPIO_Port GPIOD
//#define STB_LED_Pin GPIO_PIN_7
//#define STB_LED_GPIO_Port GPIOD

void Hub08_Init(void);
void Hub08_CSan(uint8_t row);
void Hub08_View(void);
#endif
