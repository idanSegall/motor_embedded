#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include "gpio.h"
#include "logger.h"
#include "stepmotor.h"


int main(int argc, char **argv) {

	if (argc < 6)
	{
		LOG_ERROR("Input invalid. Command stepmotor.o <step> <speed> <acceleration> <deacceleration> <dir>\n");
		LOG_ERROR("Notice: \n");
		LOG_ERROR("+ Speed unit is usecond\n");
		LOG_ERROR("+ Acceleration and deacceleration MUST be less than speed\n");
		LOG_ERROR("+ Acceleration and deacceleration can be zero (stable mode)\n");
		LOG_ERROR("+ Acceleration is greater than zero and deacceleration MUST be zero (increase speed mode)\n");
		LOG_ERROR("+ Deacceleration is greater than zero and acceleration MUST be zero (decrease speed mode)\n");
		return 0;
	}
	
	else
	{
			stepmotor_t motor = {
			.step = (int)atoi(argv[1]),
			.speed = (double)strtod(argv[2],NULL),
			.acceleration = (double)strtod(argv[3],NULL),
			.deacceleration = (double)strtod(argv[4],NULL),
			.dir = (int)atoi(argv[5]),
			
			
		};

		if (motor.acceleration > 0 && motor.deacceleration > 0)
		{
			LOG_ERROR("Acceleration and deacceleration can't be greater than zero in same time\n");
			LOG_ERROR("Acceleration is greater than zero and deacceleration MUST be zero (increase speed mode)\n");
			LOG_ERROR("Deacceleration is greater than zero and acceleration MUST be zero (decrease speed mode)\n");
			return 0;
		}

		if (motor.dir != 0 && motor.dir != 1)
		{
			LOG_ERROR("Director only be 0 or 1\n");
			return 0;
		}

		if (motor.step == 0)
		{
			LOG_ERROR("Step is zero\n");
			return 0;
		}
		if (motor.speed <= 0)
		{
			motor.speed=0;
		}
		

		LOG_INFO( "speed - %f\n", motor.speed);
		LOG_INFO("Step motor started");
		step_motor_init(motor);
		
		
		
	}
	
	return 0;
}
