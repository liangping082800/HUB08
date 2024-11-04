#include "hub08.h"

void Hub08_Init(void){
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOC, G1_LED_Pin|G2_LED_Pin, GPIO_PIN_SET);

  HAL_GPIO_WritePin(GPIOD, A_LED_Pin|B_LED_Pin|C_LED_Pin|D_LED_Pin
                          |R1_LED_Pin|R2_LED_Pin|SCK_LED_Pin|STB_LED_Pin, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = G1_LED_Pin|G2_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = A_LED_Pin|B_LED_Pin|C_LED_Pin|D_LED_Pin
                          |R1_LED_Pin|R2_LED_Pin|SCK_LED_Pin|STB_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
//脉冲信号
void Hub08_sck(void)
{
		// 发送一个时钟脉冲
		HAL_GPIO_WritePin(SCK_LED_GPIO_Port, SCK_LED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SCK_LED_GPIO_Port, SCK_LED_Pin, GPIO_PIN_SET);   
		HAL_GPIO_WritePin(SCK_LED_GPIO_Port, SCK_LED_Pin, GPIO_PIN_RESET);
	
}

//颜色
void Hub08_green(uint16_t i)
{	
		HAL_GPIO_WritePin(GPIOD, R1_LED_Pin, GPIO_PIN_SET);

}

void Hub08_en(GPIO_PinState hub08En)
{
		 // 使能信号设为低
    HAL_GPIO_WritePin(GPIOD, EN_LED_Pin, hub08En);	
}

void Hub08_CSan(uint8_t row)
{
    if (row < 1 || row > 19) {
        return;
    }
    GPIO_PinState A = (row & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET; // A: 第0位
    GPIO_PinState B = (row & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET; // B: 第1位
    GPIO_PinState C = (row & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET; // C: 第2位
    GPIO_PinState D = (row & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET; // D: 第3位

    HAL_GPIO_WritePin(GPIOD, A_LED_Pin, A);
    HAL_GPIO_WritePin(GPIOD, B_LED_Pin, B);
    HAL_GPIO_WritePin(GPIOD, C_LED_Pin, C);
    HAL_GPIO_WritePin(GPIOD, D_LED_Pin, D);	
}

//char row=80,col=16;
// 输出列数据
void OutputColumnData(uint8_t columnData) {
    // 在这里输出一列数据到显屏
    for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(GPIOC, (i < 4) ? R1_LED_Pin : G1_LED_Pin, (columnData & (1 << i)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(G2_LED_GPIO_Port, G2_LED_Pin, GPIO_PIN_SET); // 绿色下半部分
}



uint8_t data[5][3] = {
	
0x83,

};

// 向 HUB08 写入数据
void writeToHub08(uint8_t dr1, uint8_t dg1, uint8_t dr2, uint8_t dg2){
	
	for(int i = 0; i <= 19; i++)
	{
		
		Hub08_CSan(i); 
    for (int i = 0; i < 8; i++) {
        SET_PIN(R1_LED_GPIO_Port, R1_LED_Pin, (dr1 & 0x80)? 1 : 0);
        SET_PIN(R2_LED_GPIO_Port, R2_LED_Pin, (dr2 & 0x80)? 1 : 0);
        SET_PIN(G1_LED_GPIO_Port, G1_LED_Pin, (dg1 & 0x80)? 1 : 0);
        SET_PIN(G2_LED_GPIO_Port, G2_LED_Pin, (dg2 & 0x80)? 1 : 0);

        GPIO_SetBits(SCK_LED_GPIO_Port, SCK_LED_Pin);
        GPIO_ResetBits(SCK_LED_GPIO_Port, SCK_LED_Pin);

        dr1 <<= 1;
        dr2 <<= 1;
        dg1 <<= 1;
        dg2 <<= 1;
		}
    }
}
//void Hub08_Display(void){
////		writeToHub08();
//		int col=0,row=0;
//	
//				// 发送数据
//        for (col = 0; col < 32; col++)
//        {
//            // 设置红色数据引脚
//            if (data[row][col] & 0x80)
//            {
//                HAL_GPIO_WritePin(GPIOD, R1_LED_Pin, GPIO_PIN_SET);
//            }
//            else
//            {
//                HAL_GPIO_WritePin(GPIOD, R1_LED_Pin, GPIO_PIN_RESET);
//            }

//            if (data[row][col] & 0x40)
//            {
//                HAL_GPIO_WritePin(GPIOD, G1_LED_Pin, GPIO_PIN_SET);
//            }
//            else
//            {
//                HAL_GPIO_WritePin(GPIOD, G1_LED_Pin, GPIO_PIN_RESET);
//            }

//            // 发送时钟信号
//            HAL_GPIO_WritePin(GPIOD, SCK_LED_Pin, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOD, SCK_LED_Pin, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOD, SCK_LED_Pin, GPIO_PIN_RESET);
//        }

//        // 锁存数据
//        HAL_GPIO_WritePin(GPIOD, STB_LED_Pin, GPIO_PIN_SET);
//        HAL_GPIO_WritePin(GPIOD, STB_LED_Pin, GPIO_PIN_RESET);

//}
void Hub08_View(void){
	        Hub08_en(GPIO_PIN_RESET);
        for(int i = 0; i <= 19; i++){
					
//					OutputColumnData(0x80);
            Hub08_CSan(i); 
            Hub08_green(1);
            Hub08_sck();
					
					
					
    }

}


