#include <ADC.h>

void ADCread(){
			  HAL_ADC_Start(&hadc1);    // starts ADC1 Input 7
			  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
			  raw = HAL_ADC_GetValue(&hadc1);   // raw analogue input measured

}


void CalculateVoltage(){

		voltage = (float)raw /4096 * 5; // since we are using 12 bit ADC, maximum value is 4096, it needs to be scaled down to describe voltage

}


void TransmitData(){

			voltage = (float)raw /4096 * 5; // since we are using 12 bit ADC, maximum value is 4096, it needs to be scaled down to describe voltage

			sprintf(USB_msg, "%2.2f\r\n", voltage);

			HAL_UART_Transmit(&huart2, (uint8_t*)USB_msg, strlen(USB_msg), HAL_MAX_DELAY);  // transmit data to Serial plotter

}

void lcd_initialize()
//initialize the BSP LCD
{
	  BSP_LCD_GLASS_Init();
	  BSP_LCD_GLASS_Clear();
	  BSP_LCD_GLASS_DisplayString("Task3");
}

void ADCTask_initialize()
{
	  HAL_TIM_Base_Start_IT(&htim6);      // initialise global timer interrupt (timer 6) Prescaler 20, 20 MHz / 20 = 1000000. count period 200 (i.e. sampling frequency 5000 Hz)
	  HAL_Delay(1000);
}
