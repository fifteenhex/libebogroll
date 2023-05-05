/*
 *
 */

#include <errno.h>
#include <stddef.h>

#include "libebogroll.h"
#include "gdew042c37.h"

static int gdew042c37_wait_not_busy(const struct gdew042c37_data *display_data)
{
	while(gpio_controller_get_value(display_data->gpio_controller, display_data->busy_gpio) == 0){
	}

	return 0;
}

static int gdew042c37_send_command(const struct gdew042c37_data *display_data, const uint8_t *command, size_t len)
{
	const struct spi_controller *spi_controller = display_data->spi_controller;

	gpio_controller_set_value(display_data->gpio_controller, display_data->dc_gpio, 0);
	spi_controller_cs_assert(spi_controller);
	int ret = spi_controller_write(spi_controller, command, len, 0);
	spi_controller_cs_release(spi_controller);

	return ret;
}

static int gdew042c37_send_data(const struct gdew042c37_data *display_data, const uint8_t *data, size_t len)
{
	const struct spi_controller *spi_controller = display_data->spi_controller;

	gpio_controller_set_value(display_data->gpio_controller, display_data->dc_gpio, 1);
	spi_controller_cs_assert(spi_controller);
	int ret = spi_controller_write(spi_controller, data, len, 0);
	spi_controller_cs_release(spi_controller);

	return ret;
}

static int gdew042c37_reset(const void *display_data)
{
	const struct gdew042c37_data *gdew042c37_display_data = display_data;
	const struct gpio_controller *gpio_controller = gdew042c37_display_data->gpio_controller;
	int reset_gpio = gdew042c37_display_data->reset_gpio;

	for (int i = 0; i < 3; i++) {
		/* apply reset and set default value for DC */
		gpio_controller_set_value(gpio_controller, reset_gpio, 0);
		usleep(100);
		/* release reset */
		gpio_controller_set_value(gpio_controller, reset_gpio, 1);
	}

	return 0;
}

static int gdew042c37_power_up(const void *display_data)
{
	const struct gdew042c37_data *gdew042c37_display_data = display_data;
	int ret;

	{
		const uint8_t booster_soft_start[] = { GDEW042C37_CMD_BOOSTER_SOFT_START, 0x17, 0x17, 0x17 };
		ret = gdew042c37_send_command(gdew042c37_display_data, booster_soft_start, sizeof(booster_soft_start));
		if (ret)
			return ret;
	}

	{
		const uint8_t power_setting[] = { GDEW042C37_CMD_POWER_SETTING, 0x03, 0x00, 0x2b, 0x2b, 0x09 };
		ret = gdew042c37_send_command(gdew042c37_display_data, power_setting, sizeof(power_setting));
		if (ret)
			return ret;
	};

	{
		const uint8_t power_on[] = { GDEW042C37_CMD_POWER_ON };
		ret = gdew042c37_send_command(gdew042c37_display_data, power_on, sizeof(power_on));
		if (ret)
			return ret;
	};

	/* wait for ready */
	ret = gdew042c37_wait_not_busy(gdew042c37_display_data);
	if (ret)
		return ret;

	{
		const uint8_t panel_setting[] = { GDEW042C37_CMD_PANEL_SETTING, 0x0f};
		ret = gdew042c37_send_command(gdew042c37_display_data, panel_setting, sizeof(panel_setting));
		if (ret)
			return ret;
	};

	{
		const uint8_t resolution_setting[] = { GDEW042C37_CMD_RESOLUTION_SETTING, 0x01, 0x90, 0x01, 0x2c };
		ret = gdew042c37_send_command(gdew042c37_display_data, resolution_setting, sizeof(resolution_setting));
		if (ret)
			return ret;
	};

	{
		const uint8_t vcom_datainterval[] = { GDEW042C37_CMD_VCOM_AND_DATA_INTERVAL_SETTING, 0x77 };
		ret = gdew042c37_send_command(gdew042c37_display_data, vcom_datainterval, sizeof(vcom_datainterval));
		if (ret)
			return ret;
	};

	return 0;
}

static int gdew042c37_send_plane_data(const void *display_data, unsigned plane, const uint8_t *plane_data)
{
	const struct gdew042c37_data *gdew042c37_display_data = display_data;
	int ret;

	switch (plane) {
	case 0:
	{
		const uint8_t start_bw_data[] = { GDEW042C37_CMD_DATA_START_TRANSMISSION1 };
		ret =gdew042c37_send_command(gdew042c37_display_data, start_bw_data, sizeof(start_bw_data));
		if (ret)
			return ret;
	};
		break;
	case 1:
	{
		const uint8_t start_yellow_data[] = { GDEW042C37_CMD_DATA_START_TRANSMISSION2 };
		ret = gdew042c37_send_command(gdew042c37_display_data, start_yellow_data, sizeof(start_yellow_data));
		if (ret)
			return ret;
	}
		break;
	default:
		return -EINVAL;
	}

	ret = gdew042c37_send_data(gdew042c37_display_data, plane_data, GDEW042C37_PLANESIZE);
	if (ret)
		return ret;

	return 0;
}

static int gdew042c37_refresh(const void *display_data)
{
	const struct gdew042c37_data *gdew042c37_display_data = display_data;
	const uint8_t display_refresh[] = { GDEW042C37_CMD_DISPLAY_REFRESH };
	int ret;

	ret = gdew042c37_send_command(gdew042c37_display_data, display_refresh, sizeof(display_refresh));
	if (ret)
		return ret;

	ret = gdew042c37_wait_not_busy(gdew042c37_display_data);
	if (ret)
		return ret;

	return 0;
}

static int gdew042c37_power_down(const void *display_data)
{
	const struct gdew042c37_data *gdew042c37_display_data = display_data;
	int ret;

	{
		const uint8_t power_off[] = { GDEW042C37_CMD_POWER_OFF };
		ret = gdew042c37_send_command(gdew042c37_display_data, power_off, sizeof(power_off));
		if (ret)
			return ret;
	}
	// vcom and interval setting?

	{
		const uint8_t deep_sleep[] = { GDEW042C37_CMD_DEEP_SLEEP, 0xa5 };
		ret = gdew042c37_send_command(gdew042c37_display_data, deep_sleep, sizeof(deep_sleep));
		if (ret)
			return ret;
	}

	return 0;
}


const struct epaper_driver gdew042c37 = {
	.reset = gdew042c37_reset,
	.power_up = gdew042c37_power_up,
	.send_plane_data = gdew042c37_send_plane_data,
	.refresh = gdew042c37_refresh,
	.power_down = gdew042c37_power_down,
};

int gdew042c37_new(struct gdew042c37_data *display_data,
	const struct gpio_controller *gpio_controller,
	const struct spi_controller *spi_controller,
	int reset_gpio, int busy_gpio, int dc_gpio)
{
	display_data->gpio_controller = gpio_controller;
	display_data->spi_controller = spi_controller;
	display_data->reset_gpio = reset_gpio;
	display_data->busy_gpio = busy_gpio;
	display_data->dc_gpio = dc_gpio;

	return 0;
}
