#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int gpio;
	int mode;
	int value;
} gpio_t;

#define IMX_GPIO_NR(port, index)    ((((port)-1)*32)+((index)&31))

void gpio_init_pin(gpio_t gpio);
void gpio_set_value_pin(int gpio, int value);
int gpio_get_value_pin(int gpio);
#endif /* GPIO_H_ */
