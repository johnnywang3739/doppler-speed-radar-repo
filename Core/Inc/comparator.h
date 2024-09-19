/*
 * comparator.h
 *
 *  Created on: Jan 2, 2021
 *      Author: ASUS
 */

#ifndef	_COMPARATOR_H_
#define _COMPARATOR_H_


#include <main.h>
#include <stdio.h>


ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
COMP_HandleTypeDef hcomp1;
DAC_HandleTypeDef hdac1;
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
LCD_HandleTypeDef hlcd;
QSPI_HandleTypeDef hqspi;
SAI_HandleTypeDef hsai_BlockA1;
SAI_HandleTypeDef hsai_BlockB1;
SPI_HandleTypeDef hspi2;
TIM_HandleTypeDef htim6;   // we are using htim6 as timer to count waves and calculate frequency
TIM_HandleTypeDef htim7;
UART_HandleTypeDef huart2;

// user defined global variable
char uart_buf[50];  // create a buffer to store uart message
int uart_buf_len;   // related to buffer character length
char LCD_msg[10];   // create a buffer to store message to be displayed on LCD


void lcd_initialize(char* taskNumber);
void comparator_initialize();  // initialise the comparator
void timer_initialize(); // initialise the timer

void compute_speeds(long long unsigned int *squarewave_count, float *frequency, float *speed_kmph, float *speed_mps, float *speed_mph);   // compute speeds in unit of  m/s, km/h, mph
void display_LCD(float speed_Kmph); // display on LCD
void display_serial_monitor(float frequency, float speed_kmph, float speed_mps, float speed_mph);// display on serial monitor

#endif /* INC_COMPARATOR_H_ */
