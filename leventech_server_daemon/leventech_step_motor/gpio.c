#include <stdbool.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "gpio.h"
#include "logger.h"

#define GPIO_MAX_LEN 128
#define GPIO_PATTERN "/sys/class/gpio/gpio%d"

static bool is_gpio_register(int pin)
{
	char path[GPIO_MAX_LEN] = {0};
	int len = sprintf(path, GPIO_PATTERN, pin);
	path[len] = '\0';

	DIR* dir = opendir(path);
	if (dir) {
		closedir(dir);
		return true;
	}

	return false;
}

static void gpio_register(int pin)
{
	int fd;
	char buf[GPIO_MAX_LEN];
	fd = open("/sys/class/gpio/export", O_WRONLY);

	sprintf(buf, "%d", pin);

	write(fd, buf, strlen(buf));
	close(fd);
}

static void gpio_set_mode(int gpio, int mode)
{
	int fd;
	char buf[GPIO_MAX_LEN];
	sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
	fd = open(buf, O_WRONLY);
	if (mode == 1)
	{
		/* Set in direction */
		write(fd, "in", 2);
	}
	else
	{
		/* Set out direction */
		write(fd, "out", 3);
	}

	close(fd);
}

static void gpio_set_value(int gpio, int value)
{
        
	int fd;
	char buf[GPIO_MAX_LEN];
	sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
	fd = open(buf, O_WRONLY);
	if (value == 1)
	{
		/* Set GPIO high status */
		write(fd, "1", 1);
	}
	else
	{
		/* Set GPIO low status */
		write(fd, "0", 1);
	}
	close(fd);
}

static int gpio_get_value(int gpio)
{
	char value;
	int fd;
	char buf[GPIO_MAX_LEN];
	sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
	fd = open(buf, O_RDONLY);
	read(fd, &value, 1);
	close(fd);
	return (int)atoi((const char *)&value);
}

void gpio_init_pin(gpio_t gpio)
{
	if (!is_gpio_register(gpio.gpio))
	{
		LOG_WARNING("Register the GPIO number %d\n", gpio.gpio);
		gpio_register(gpio.gpio);
	}

	LOG_WARNING("Registered the GPIO number %d\n", gpio.gpio);
	gpio_set_mode(gpio.gpio, gpio.mode);
	gpio_set_value(gpio.gpio, gpio.value);
}

void gpio_set_value_pin(int gpio, int value)
{
	if (!is_gpio_register(gpio))
	{
		LOG_ERROR("Please initialize this PIN first\n");
		return;
	}

	gpio_set_value(gpio, value);
}

int gpio_get_value_pin(int gpio)
{
	if (!is_gpio_register(gpio))
	{
		LOG_ERROR("Please initialize this PIN first\n");
		return -1;
	}

	return gpio_get_value(gpio);
}
