#ifndef __PROCESSING_H__
#define __PROCESSING_H__

#include <string.h>
#include <stdio.h>
#include <arm_math.h>
#include <arm_const_structs.h>
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

uint16_t raw;
char LCD_msg[10];   // create a buffer to store message to be displayed on LCD
char USB_msg[50];   // create a usb buffer to store message to be displayed on Serial monitor

float32_t inputBuffer[1024]; //store the adc read input
float32_t output[1024]; //store the output from the output
uint16_t indexNumber;
float32_t amplitude[512]; //store the square of the amplitude of each frequency component
float32_t maxValue; //store the maximum amplitude square
uint32_t maxIndex; //the index of the frequency with maximum amplitude

arm_rfft_fast_instance_f32 S; //create fft instance
arm_status status; //create fft instance status

float frequency; //the frequency with maximum amplitude
float speed; //the speed of the frequency with maximum amplitude
int flag; //indicate either to store data in the inputBuffer (flag=0) or to do fft (flag=1)

void lcd_initialize();
void processing_initialize();
void doFFT();
void lcd_displaySpeed(float speedInMeterPerSecond);
void adcRead();
void bufferStoring();

#endif
