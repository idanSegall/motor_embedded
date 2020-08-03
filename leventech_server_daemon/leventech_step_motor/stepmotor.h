#ifndef STEPMOTOR_H_
#define STEPMOTOR_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "gpio.h"
#include "logger.h"

typedef struct {
	int step;
	double speed;
	double acceleration;
	double deacceleration;
	int dir;
} stepmotor_t;

#define STEPMOTOR_PIN_ENA 	IMX_GPIO_NR(1,15)
#define STEPMOTOR_PIN_DIR 	IMX_GPIO_NR(1, 141)
#define STEPMOTOR_PIN_PUL 	IMX_GPIO_NR(1, 11)

void step_motor_init(stepmotor_t info);

#endif /* STEPMOTOR_H_ */
