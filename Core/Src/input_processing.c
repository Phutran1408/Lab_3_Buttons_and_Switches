/*
 * input_processing.c
 *
 *  Created on: Oct 26, 2026
 *      Author: Admin
 */
#include "main.h"
#include "input_reading.h"
#include "led_display.h"
#include "timer.h"

uint8_t mode = 1;

int time_red = 5;
int time_yellow = 2;
int time_green = 3;

int temp_red = 5;
int temp_yellow = 2;
int temp_green = 3;

enum TrafficState {
    AUTO_RED_GREEN,
    AUTO_RED_YELLOW,
    AUTO_GREEN_RED,
    AUTO_YELLOW_RED
};
enum TrafficState traffic_state = AUTO_RED_GREEN;

int count_way1 = 0;
int count_way2 = 0;

void resetTrafficMode1(void) {
    traffic_state = AUTO_RED_GREEN;
    count_way1 = time_red;
    count_way2 = time_green;
}

void fsm_traffic_normal(void) {
    switch (traffic_state) {
        case AUTO_RED_GREEN:
            setTraffic(TRAFFIC_RED, TRAFFIC_GREEN);
            if (timer_traffic_flag == 1) {
                count_way1--;
                count_way2--;
                if (count_way2 <= 0) {
                    traffic_state = AUTO_RED_YELLOW;
                    count_way2 = time_yellow;
                }
            }
            break;

        case AUTO_RED_YELLOW:
            setTraffic(TRAFFIC_RED, TRAFFIC_YELLOW);
            if (timer_traffic_flag == 1) {
                count_way1--;
                count_way2--;
                if (count_way2 <= 0 || count_way1 <= 0) {
                    traffic_state = AUTO_GREEN_RED;
                    count_way1 = time_green;
                    count_way2 = time_red;
                }
            }
            break;

        case AUTO_GREEN_RED:
            setTraffic(TRAFFIC_GREEN, TRAFFIC_RED);
            if (timer_traffic_flag == 1) {
                count_way1--;
                count_way2--;
                if (count_way1 <= 0) {
                    traffic_state = AUTO_YELLOW_RED;
                    count_way1 = time_yellow;
                }
            }
            break;

        case AUTO_YELLOW_RED:
            setTraffic(TRAFFIC_YELLOW, TRAFFIC_RED);
            if (timer_traffic_flag == 1) {
                count_way1--;
                count_way2--;
                if (count_way1 <= 0 || count_way2 <= 0) {
                    traffic_state = AUTO_RED_GREEN;
                    count_way1 = time_red;
                    count_way2 = time_green;
                }
            }
            break;
    }

    if (timer_traffic_flag == 1) {
        timer_traffic_flag = 0;
    }

    int disp1 = (count_way1 >= 0) ? count_way1 : 0;
    int disp2 = (count_way2 >= 0) ? count_way2 : 0;

    led_buffer[0] = disp1 / 10;
    led_buffer[1] = disp1 % 10;
    led_buffer[2] = disp2 / 10;
    led_buffer[3] = disp2 % 10;
}

void fsm_for_input_processing(void) {
    if (is_button_pressed(0)) {
        mode++;
        if (mode > 4) {
            mode = 1;
            temp_red = time_red;
            temp_yellow = time_yellow;
            temp_green = time_green;
            resetTrafficMode1();
        } else {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 |
                                     GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10, GPIO_PIN_SET);
            if (mode == 2) {
                temp_red = time_red;
                temp_yellow = time_yellow;
                temp_green = time_green;
            }
        }
    }
    if (mode >= 2 && mode <= 4) {
        if (timer_blink_flag == 1) {
            timer_blink_flag = 0;
            LedBlinking(mode);
        }
    }

    switch (mode) {
        case 1:
            fsm_traffic_normal();
            break;

        case 2:
            if (is_button_pressed(1)) {
                temp_red++;
                if (temp_red > 99) temp_red = 1;
            }
            if (is_button_pressed(2)) {
                time_red = temp_red;
                time_yellow = temp_yellow;
                time_green = temp_green;
            }
            led_buffer[0] = mode / 10;
            led_buffer[1] = mode % 10;
            led_buffer[2] = temp_red / 10;
            led_buffer[3] = temp_red % 10;
            break;

        case 3:
            if (is_button_pressed(1)) {
                temp_yellow++;
                if (temp_yellow > 99) temp_yellow = 1;
            }
            if (is_button_pressed(2)) {
                time_red = temp_red;
                time_yellow = temp_yellow;
                time_green = temp_green;
            }
            led_buffer[0] = mode / 10;
            led_buffer[1] = mode % 10;
            led_buffer[2] = temp_yellow / 10;
            led_buffer[3] = temp_yellow % 10;
            break;

        case 4:
            if (is_button_pressed(1)) {
                temp_green++;
                if (temp_green > 99) temp_green = 1;
            }
            if (is_button_pressed(2)) {
                time_red = temp_red;
                time_yellow = temp_yellow;
                time_green = temp_green;
            }
            led_buffer[0] = mode / 10;
            led_buffer[1] = mode % 10;
            led_buffer[2] = temp_green / 10;
            led_buffer[3] = temp_green % 10;
            break;
    }
}
