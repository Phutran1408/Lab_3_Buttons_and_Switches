/*
 * led_display.c
 *
 *  Created on: Oct 26, 2026
 *      Author: Admin
 */

#include "led_display.h"

int led_buffer[4]={0,0,0,0};

void display7SEG(int num){
	if ( num < 0 || num > 9 ) return;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_SET);

	    switch (num)
	    {
	        case 0: // a,b,c,d,e,f
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);
	            break;
	        case 1: // b,c
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);
	            break;
	        case 2: // a,b,d,e,g
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        case 3: // a,b,c,d,g
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        case 4: // b,c,f,g
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        case 5: // a,c,d,f,g
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        case 6: // a,c,d,e,f,g
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        case 7: // a,b,c
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);
	            break;
	        case 8: // a,b,c,d,e,f,g
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        case 9: // a,b,c,d,f,g
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        default:
	            break;
	    }
}


void update7SEG(int index){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_SET);

	display7SEG(led_buffer[index]);

	switch (index){
	case 0:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3,GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}

void setTraffic(uint8_t color1, uint8_t color2) {

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (color1 == TRAFFIC_RED)    ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (color1 == TRAFFIC_YELLOW) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (color1 == TRAFFIC_GREEN)  ? GPIO_PIN_RESET : GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  (color2 == TRAFFIC_RED)    ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,  (color2 == TRAFFIC_YELLOW) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, (color2 == TRAFFIC_GREEN)  ? GPIO_PIN_RESET : GPIO_PIN_SET);
}
void LedBlinking(uint8_t mode) {
    switch (mode) {
        case 2:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10, GPIO_PIN_SET);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_8);
            break;

        case 3:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_10, GPIO_PIN_SET);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6 | GPIO_PIN_9);
            break;

        case 4:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_SET);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7 | GPIO_PIN_10);
            break;
        default:
            break;
    }
}
