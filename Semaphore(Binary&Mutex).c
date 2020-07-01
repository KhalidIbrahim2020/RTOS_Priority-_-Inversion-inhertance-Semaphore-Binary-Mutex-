/*
* interFacing_App
*
* Created: 30-Jun-20 9:01:34 M
*  Author: Khalid
*/

/********************************************************************************/	/*System Change From Binary & Mutex to Check the Inversion & Inher.	  	* For Binary Semaphore --------------->1	********        *****   **********************	* 2sec * 2sec   *.5 *.5 *      7sec on       *	*      **********   *****                    **********************		   vSemaphoreCreateBinary(bsBtnPressed,1);				* For Mutex Semaphore ---------------->2		********        *****        |LOW TASK WILL BE HIGHER PER. Due To Inher.	* 2sec * 2sec   *.5 *.5      |to avoid Medium task to take the role	*      *********    ******** |  			   bsBtnPressed=xSemaphoreCreateMutex();     	*//********************************************************************************/	

/* include OS headers */#include "FreeRTOS.h"#include "task.h"#include "queue.h"#include "semphr.h"#include "avr/delay.h"/* include Our Drivers */#include "board.h"/* Proto. */void T_LOW(void* pvData);void T_MEDIUM(void* pvData);void T_HIGH(void* pvData);void system_init(void);/* OS Services Decl.*/xSemaphoreHandle bsBtnPressed;int main(void){	/* Init Pr. */	system_init();	// For Binary Semaphore --------------->1	   vSemaphoreCreateBinary(bsBtnPressed,1);		// For Mutex Semaphore ---------------->2	  	  // bsBtnPressed=xSemaphoreCreateMutex();   Commented as(  Binary ) Above  		/* Tasks Creat. */	xTaskCreate(T_LOW,"T_LOW",100,NULL,1,NULL);	/* Start OS or Sched. */	vTaskStartScheduler();}void T_LOW(void* pvData){	/* recData is a local or temp message */	while(1)	{		Led_On();		_delay_ms(2000);// OR OS DELAY VTASKDelay(2000);  AS REQUIRED .		Led_Off();		_delay_ms(2000);// OR OS DELAY VTASKDelay(2000);  AS REQUIRED .		xSemaphoreTake(bsBtnPressed,portMAX_DELAY);		xTaskCreate(T_HIGH,"T_HIGH",100,NULL,3,NULL);		xTaskCreate(T_MEDIUM,"T_MEDIUM",100,NULL,2,NULL);		xSemaphoreGive(bsBtnPressed);	}}void T_HIGH(void* pvData){	/* recData is a local or temp message */	while(1)	{		Led_On();		_delay_ms(500);		Led_Off();		_delay_ms(500);		if (xSemaphoreTake(bsBtnPressed,portMAX_DELAY))
		{
			while(1);
		}		vTaskDelay(5);	}}void T_MEDIUM(void* pvData){	/* recData is a local or temp message */	while(1)	{		Led_On();		_delay_ms(7000);		Led_Off();		vTaskDelay(7000);			}}void system_init(void){	Led_Init();}
