/*
 * input_reading.c
 *
 *  Created on: Oct 26, 2026
 *      Author: Admin
 */
#include "main.h"
#include "timer.h"
#include "input_reading.h"

// We aim to work with more than one buttons
#define NO_OF_BUTTONS                   3

// Timer interrupt duration is 10ms, so to pass 1 second,
// we need to jump to the interrupt service routine 100 time
#define DURATION_FOR_AUTO_INCREASING    (1000/TIMER_CYCLE)
#define DURATION_FOR_CYCLE_AUTO         (500 / TIMER_CYCLE)

#define BUTTON_IS_PRESSED               GPIO_PIN_RESET
#define BUTTON_IS_RELEASED              GPIO_PIN_SET

// The buffer that the final result is stored after debouncing
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];

// We define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];

// We define a flag for a button pressed more than 1 second.
static GPIO_PinState prev_buttonBuffer[NO_OF_BUTTONS];
static uint8_t button_flag[NO_OF_BUTTONS];

static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint16_t counterAutoRepeat[NO_OF_BUTTONS];

// We define counter for automatically increasing the value
// after the button is pressed more than 1 second.
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];

static uint16_t BUTTON_PIN[NO_OF_BUTTONS] = {GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13};

void button_reading(void){
    for(uint8_t i = 0; i < NO_OF_BUTTONS; i++){
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOA, BUTTON_PIN[i]);

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]){
            buttonBuffer[i] = debounceButtonBuffer1[i];

            if (buttonBuffer[i] == BUTTON_IS_PRESSED && prev_buttonBuffer[i] == BUTTON_IS_RELEASED) {
                button_flag[i] = 1;
            }
            prev_buttonBuffer[i] = buttonBuffer[i];

            if (buttonBuffer[i] == BUTTON_IS_PRESSED){
                if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING){
                    counterForButtonPress1s[i]++;
                } else {
                    flagForButtonPress1s[i] = 1;
                    counterAutoRepeat[i]++;
                    if (counterAutoRepeat[i] >= DURATION_FOR_CYCLE_AUTO){
                    	counterAutoRepeat[i] = 0;
                    	button_flag[i] = 1;
                    }
                }
            } else {
                counterForButtonPress1s[i] = 0;
                counterAutoRepeat[i] = 0;
                flagForButtonPress1s[i] = 0;
            }
        }
    }
}

unsigned char is_button_pressed(uint8_t index){
    if (index >= NO_OF_BUTTONS) return 0;
    if (button_flag[index] == 1){
        button_flag[index] = 0;
        return 1;
    }
    return 0;
}

unsigned char is_button_pressed_1s(uint8_t index){
    if (index >= NO_OF_BUTTONS) return 0xff;
    return (flagForButtonPress1s[index] == 1);
}



