/*
 *
 * site: https://www.e-paper-display.com/products_detail/productId=379.html
 */

#ifndef GDEW042C37_H_
#define GDEW042C37_H_

#include <stdint.h>

#define GDEW042C37_WIDTH				400
#define GDEW042C37_HEIGHT				300
#define GDEW042C37_PLANESIZE				((GDEW042C37_WIDTH * GDEW042C37_HEIGHT) / 8)

#define GDEW042C37_CMD_PANEL_SETTING			0x00
#define GDEW042C37_CMD_POWER_SETTING			0x01
#define GDEW042C37_CMD_POWER_OFF			0x02
#define GDEW042C37_CMD_POWER_OFF_SEQUENCE_SETTING	0x03
#define GDEW042C37_CMD_POWER_ON				0x04
#define GDEW042C37_CMD_POWER_ON_MEASURE			0x05
#define GDEW042C37_CMD_BOOSTER_SOFT_START		0x06
#define GDEW042C37_CMD_DEEP_SLEEP			0x07
#define GDEW042C37_CMD_DATA_START_TRANSMISSION1		0x10
#define GDEW042C37_CMD_DATA_STOP			0x11
#define GDEW042C37_CMD_DISPLAY_REFRESH			0x12
#define GDEW042C37_CMD_DATA_START_TRANSMISSION2		0x13
#define GDEW042C37_CMD_VCOM_AND_DATA_INTERVAL_SETTING	0x50
#define GDEW042C37_CMD_RESOLUTION_SETTING		0x61

extern const struct epaper_driver gdew042c37;

struct gdew042c37_data {
	int reset_gpio;
	int busy_gpio;
	int dc_gpio;

	const struct gpio_controller *gpio_controller;
	const struct spi_controller *spi_controller;
};

int gdew042c37_new(struct gdew042c37_data *display_data,
	const struct gpio_controller *gpio_controller,
	const struct spi_controller *spi_controller,
	int reset_gpio, int busy_gpio, int dc_gpio);

#endif
