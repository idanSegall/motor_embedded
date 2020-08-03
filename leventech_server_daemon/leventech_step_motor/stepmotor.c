#include <pthread.h>
#include "logger.h"
#include "stepmotor.h"
#include "unistd.h"

static bool flag_step_is_running;

static gpio_t gpio_ena = {
	.gpio = STEPMOTOR_PIN_ENA,
	.value = 0,
	.mode = 0,
};

static gpio_t gpio_dir = {
	.gpio = STEPMOTOR_PIN_DIR,
	.value = 0,
	.mode = 0,
};

static gpio_t gpio_pul = {
	.gpio = STEPMOTOR_PIN_PUL,
	.value = 0,
	.mode = 0
};

static void* stepmotor_drive_trigger_thread(void *vargp)
{
	LOG_ERROR("stepmotor_drive_trigger_thread(\n:");
	stepmotor_t *trigger = (stepmotor_t *)vargp;
	int step_count = 0;
	double speed = (double)trigger->speed ;
	double accel_speed = (double)trigger->acceleration;
	double deaccel_speed = (double)trigger->deacceleration;
	
	
	flag_step_is_running = true;

	gpio_set_value_pin(STEPMOTOR_PIN_ENA, 1U);
	usleep(5);

	gpio_set_value_pin(STEPMOTOR_PIN_DIR, trigger->dir);
	usleep(5);

	while(trigger->step > step_count)
	
	{
	
		if (trigger->acceleration > 0 && trigger->deacceleration == 0)
		{
		
			LOG_INFO( "speed - %f\n", speed);
			gpio_set_value_pin(STEPMOTOR_PIN_PUL, 1U);
			usleep(speed / 2);
			gpio_set_value_pin(STEPMOTOR_PIN_PUL, 0U);
			usleep(speed / 2);
			step_count += 1;
			
			if (speed > 0)
			{
				speed = speed - accel_speed;
			}
			else {
				speed=0; 
			}
		}

		if (trigger->deacceleration > 0 && trigger->acceleration == 0)
		{
		        LOG_INFO( "speed - %f\n", speed);
			gpio_set_value_pin(STEPMOTOR_PIN_PUL, 1U);
			usleep(speed / 2);
			gpio_set_value_pin(STEPMOTOR_PIN_PUL, 0U);
			usleep(speed / 2);
			step_count += 1;
			speed = speed + deaccel_speed;
			if (speed == 100000)
			{
				break;
			}
			
			
		}

		if (trigger->acceleration == 0 && trigger->deacceleration == 0)
		{
			LOG_INFO( "speed - %f\n", speed);
			gpio_set_value_pin(STEPMOTOR_PIN_PUL, 1U);
			usleep(speed / 0.2);
			gpio_set_value_pin(STEPMOTOR_PIN_PUL, 0U);
			usleep(speed / 0.2);
			step_count += 1;
		}
		
		
	}

	/* Disable ENA to stop sending PULSE */
	gpio_set_value_pin(STEPMOTOR_PIN_ENA, 0U);
	usleep(5);

	LOG_INFO("Done!!!\n");
	flag_step_is_running = false;
	return NULL;
}

void step_motor_init(stepmotor_t info)
{

	LOG_INFO( "step - %d\n", info.step);
	LOG_INFO( "speed - %f\n", info.speed);
	LOG_INFO( "acceleration - %f\n", info.acceleration);
	LOG_INFO( "deacceleration - %f\n", info.deacceleration);
	LOG_INFO( "dir - %d\n", info.dir);
	pthread_t tid;
	flag_step_is_running = false;

	gpio_init_pin(gpio_pul);
	gpio_init_pin(gpio_dir);
	gpio_init_pin(gpio_ena);
	pthread_create(&tid, NULL, &stepmotor_drive_trigger_thread, (void *)&info);
	pthread_join(tid,NULL);
		
	
		
}
