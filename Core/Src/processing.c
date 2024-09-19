#include <processing.h>


void lcd_initialize()
//initialize the BSP LCD
{
	  BSP_LCD_GLASS_Init();

	  BSP_LCD_GLASS_Clear();

	  BSP_LCD_GLASS_DisplayString("Task6");
	  BSP_LCD_GLASS_Contrast(LCD_CONTRASTLEVEL_7);  // set the contrast to the highest
}

void processing_initialize()
//initialize variables, timer and fft instance
{
    flag=0;
    maxIndex=0;

	HAL_TIM_Base_Start_IT(&htim6);      // initialise global timer interrupt (timer 6) Prescaler 20, 20 MHz / 20 = 1000000. count period 200 (i.e. sampling frequency 5000 Hz)

	  //Initialise the fft instance with a length of 1024
	  status = arm_rfft_fast_init_f32(&S, 1024);
	  //check if successful
	  if ( status != ARM_MATH_SUCCESS)
	    {
		  sprintf(USB_msg, "error");
		  HAL_UART_Transmit(&huart2, (uint8_t*)USB_msg, strlen(USB_msg), HAL_MAX_DELAY);
	      while(1);
	    }
}

void doFFT()
//finding the speed of the object
{
	    	arm_rfft_fast_f32(&S, inputBuffer, output, 0); //do fft

	    	//calculate the amplitude of each frequency component
	    	for (int j=1; j<512; j++)
	    	{
	    		amplitude[j]=output[2*j]*output[2*j]+output[2*j+1]*output[2*j+1]; //use the squared amplitude
	    	}

	    	//find the index of the frequency component with the largest amplitude
	    	arm_max_f32(amplitude, 512, &maxValue, &maxIndex);

	    	//calculate the frequency using its index and transmit to serial port
	    	frequency = maxIndex*5000/1024; //sample rate of adc is 5000Hz
	        sprintf(USB_msg, "%f\r\n", frequency);
	    	HAL_UART_Transmit(&huart2, (uint8_t*)USB_msg, strlen(USB_msg), HAL_MAX_DELAY);

	    	//calculate the speed and display on LCD
	    	speed = frequency*300000000/(2*10587000000); //v=f*c/2fdoppler

	    	//set flag back to zero and start storing adc data again
	    	flag = 0;
}

void lcd_displaySpeed(float speedInMeterPerSecond)
//display speed on lcd in m/s
{
	BSP_LCD_GLASS_Clear();
    sprintf(LCD_msg, "%2.0f M/S\r\n", speedInMeterPerSecond);  // format LCD message
    BSP_LCD_GLASS_DisplayString(LCD_msg);  // display speed in m/s to LCD
}

void adcRead()
//get the value of adc
{
	  HAL_ADC_Start(&hadc1);    // starts ADC1 Input 7
	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	  raw = HAL_ADC_GetValue(&hadc1);   // raw analogue input measured
}

void bufferStoring()
//store the adc values in the buffer
{
	  //if the inputBuffer is full
	  if (indexNumber > 1023)
	  	  {
	  		 indexNumber = 0; //store values from the beginning
	  		 flag = 1; //do fft
	  	  }

	  //flag indicating storing adc data
	  if(flag == 0)
	  {
		  inputBuffer[indexNumber]=(float)raw; //store raw adc data in the inputBuffer
		  indexNumber++;
	  }
}
