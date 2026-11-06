/*
 * led_display.h
 *
 *  Created on: Oct 26, 2026
 *      Author: Admin
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "main.h"

#define TRAFFIC_RED     0
#define TRAFFIC_YELLOW  1
#define TRAFFIC_GREEN   2

extern int led_buffer[4];

void display7SEG(int num);
void update7SEG(int index);
void setTraffic(uint8_t color1, uint8_t color2);
void LedBlinking(uint8_t mode);


#endif /* INC_LED_DISPLAY_H_ */
