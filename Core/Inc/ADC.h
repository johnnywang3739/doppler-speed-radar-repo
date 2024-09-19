#ifndef __ADC_H__
#define __ADC_H__

#include <string.h>
#include <stdio.h>
#include <main.h>
ADC_HandleTypeDef hadc1;
COMP_HandleTypeDef hcomp1;
DAC_HandleTypeDef hdac1;
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
LCD_HandleTypeDef hlcd;
QSPI_HandleTypeDef hqspi;
SAI_HandleTypeDef hsai_BlockA1;
SAI_HandleTypeDef hsai_BlockB1;
SPI_HandleTypeDef hspi2;
TIM_HandleTypeDef htim6;
UART_HandleTypeDef huart2;


//


uint16_t raw;
float voltage;
char uart_buf[50];  // create a buffer to store uart message
int uart_buf_len;   // related to buffer character length
char LCD_msg[10];   // create a buffer to store message to be displayed on LCD
char USB_msg[10];   // create a usb buffer to store message to be displayed on Serial monitor

// user defined functions -- see ADC.c file
void ADCread();
void CalculateVoltage();
void TransmitData();
void lcd_initialize();
void ADCTask_initialize();

#endif
