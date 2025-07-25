/*
 * Copyright (c) 2023 Juan Manuel Cruz <jcruz@fi.uba.ar>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @file   : task_led.c
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version	v1.0.0
 */

/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"
#include "cmsis_os.h"

/* Demo includes. */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes. */
#include "board.h"
#include "led.h"
#include "app.h"

/********************** macros and definitions *******************************/
#define G_TASK_LED_CNT_INI	0ul

#define LED_TICK_DEL_MAX	(pdMS_TO_TICKS(250ul))

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_task_led 			= "Task LED - Demo Code";

const char *p_task_led_t_on		= "LDX turn On ";
const char *p_task_led_t_off	= "LDX turn Off";

led_config_t led_config[]	= {{LED_A_PORT,	LED_A_PIN, \
							LED_OFF,	NOT_BLINKING,\
							NULL},
						   {LED_B_PORT,	LED_B_PIN, \
							LED_OFF,	NOT_BLINKING,\
							NULL},
						   {LED_C_PORT,	LED_C_PIN, \
							LED_OFF,	NOT_BLINKING,\
							NULL}};

/********************** external data declaration *****************************/
uint32_t g_task_led_cnt;
extern SemaphoreHandle_t h_mutex;
extern led_flag_t led_blinking_flag;

/********************** external functions definition ************************/
/* Task A, B and C thread */
/*
 * This task uses a mutex (h_mutex) to protect access to the shared global
 * variable 'led_blinking_flag'. The variable is updated by task_button and
 * read by task_led. Mutex ensures data consistency and avoids race conditions.
 */

void task_led(void *parameters)
{
	#if (TEST_X == TEST_0)
	g_task_led_cnt = G_TASK_LED_CNT_INI;

	/*  Declare & Initialize Task Function variables for argument, led, button and task */
	led_config_t *p_led_config = (led_config_t *)parameters;

	TickType_t last_wake_time;

	/* The xLastWakeTime variable needs to be initialized with the current tick count. */
	last_wake_time = xTaskGetTickCount();

	char *p_task_name = (char *)pcTaskGetName(NULL);

	/* Print out: Application Update */
	LOGGER_LOG("  %s is running - %s\r\n", p_task_name, p_task_led);

	#endif

	#if (TEST_X == TEST_1)

	/* Here another code option */

	#endif

	#if (TEST_X == TEST_2)

	/* Here Chatbot Artificial Intelligence generated code */

	#endif

	/* As per most tasks, this task is implemented in an infinite loop. */
	for (;;)
	{
		#if (TEST_X == TEST_0)

		/* Update Task Led Counter */
		g_task_led_cnt++;

		//Take the mutex
		if (xSemaphoreTake(h_mutex, portMAX_DELAY) == pdTRUE)
		{
			if (BLINKING == led_blinking_flag)
			{
				//Toggle the led
				if (GPIO_PIN_RESET == (p_led_config->led_state))
				{
					p_led_config->led_state = GPIO_PIN_SET;
					//LOGGER_LOG("  %s - %s\r\n", p_task_name, p_task_led_t_on);
				}
				else
				{
					p_led_config->led_state = GPIO_PIN_RESET;
					//LOGGER_LOG("  %s - %s\r\n", p_task_name, p_task_led_t_off);
				}

				/* Update HW Led State */
				HAL_GPIO_WritePin(p_led_config->led_gpio_port, p_led_config->led_pin, p_led_config->led_state);
			}
			//Release the mutex
			xSemaphoreGive(h_mutex);
		}

		/* We want this task to execute exactly every 250 milliseconds. */
		vTaskDelayUntil(&last_wake_time, LED_TICK_DEL_MAX);

		#endif

		#if (TEST_X == TEST_1)

		/* Here another code option */

		#endif

		#if (TEST_X == TEST_2)

		/* Here Chatbot Artificial Intelligence generated code */

		#endif
	}
}

/********************** end of file ******************************************/
