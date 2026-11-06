/*
 * timer.c
 *
 *  Created on: Oct 26, 2026
 *      Author: Admin
 */
#include "main.h"
#include "input_reading.h"
#include "timer.h"

int timer_scan_flag = 0;
int timer_scan_counter = 0;

int timer_blink_flag = 0;
int timer_blink_counter = 0;

int timer_traffic_flag = 0;
int timer_traffic_counter = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2) {
	        button_reading();

	        if (++timer_scan_counter >= (25 / TIMER_CYCLE)) {
	            timer_scan_counter = 0;
	            timer_scan_flag = 1;
	        }

	        if (++timer_blink_counter >= (250 / TIMER_CYCLE)) {
	            timer_blink_counter = 0;
	            timer_blink_flag = 1;
	        }

	        if (++timer_traffic_counter >= (1000 / TIMER_CYCLE)) {
	            timer_traffic_counter = 0;
	            timer_traffic_flag = 1;
	        }
	    }
}



