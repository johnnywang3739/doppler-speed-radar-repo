#include <main.h>
#include <comparator.h>

void lcd_initialize(char* taskNumber)
//initialize the BSP LCD
{
	  BSP_LCD_GLASS_Init();

	  BSP_LCD_GLASS_Clear();

	  BSP_LCD_GLASS_DisplayString(taskNumber);
	  BSP_LCD_GLASS_Contrast(LCD_CONTRASTLEVEL_7);  // set the contrast to the highest
}

void comparator_initialize(){

	HAL_COMP_Start(&hcomp1);  // start the comparator 1
}


void timer_initialize(){
	  HAL_TIM_Base_Start_IT(&htim6);      // initialise global timer interrupt (timer 6) Prescaler 20, 20 MHz / 2000 = 10000. Tick 10K for every second
	  HAL_Delay(1000);
}


void compute_speeds(long long unsigned int *squarewave_count, float *frequency, float *speed_kmph, float *speed_mps, float *speed_mph){
	int offset = 0;   // there is some error in counting frequency, this can solve it.
	*frequency = (float)(*squarewave_count)+offset;
	*squarewave_count = 0;
	*speed_kmph = (*frequency) / 19.60;
	*speed_mps = (*frequency) / 70.58;
	*speed_mph = (*frequency) / 31.54;
}


void display_serial_monitor(float frequency, float speed_kmph, float speed_mps, float speed_mph){
	uart_buf_len = sprintf(uart_buf, "%.2f Hz --%.2f Km/h --%.2f mph --%.2fm/s \r\n", frequency, speed_kmph, speed_mph, speed_mps);   // format buffer message
	HAL_UART_Transmit(&huart2, (uint8_t*)uart_buf, uart_buf_len, 100);     // display herz, speeds to arduino monitor via UART2
}

void display_LCD(float speed_Kmph){
    sprintf(LCD_msg, "%2.0f kmh\r\n", speed_Kmph);            // format LCD message
    BSP_LCD_GLASS_DisplayString(LCD_msg);  // display speed in Km/h to LCD
    BSP_LCD_GLASS_Clear();
}
