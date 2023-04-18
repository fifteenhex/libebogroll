/*
 *
 */

#include <errno.h>
#include <stddef.h>

#include "libebogroll.h"
#include "gdew042c37.h"

static int gdew042c37_wait_not_busy(struct gdew042c37_data *display_data)
{
	while(gpio_controller_get_value(display_data->gpio_controller, display_data->busy_gpio) == 0){
	}

	return 0;
}

static int gdew042c37_send_command(struct gdew042c37_data *display_data, uint8_t *command, size_t len)
{
	struct spi_controller *spi_controller = display_data->spi_controller;

	gpio_controller_set_value(display_data->gpio_controller, display_data->dc_gpio, 0);
	spi_controller_cs_assert(spi_controller);
	int ret = spi_controller_write(spi_controller, command, len, 0);
	spi_controller_cs_release(spi_controller);

	return ret;
}

static int gdew042c37_send_data(struct gdew042c37_data *display_data, uint8_t *data, size_t len)
{
	struct spi_controller *spi_controller = display_data->spi_controller;

	gpio_controller_set_value(display_data->gpio_controller, display_data->dc_gpio, 1);
	spi_controller_cs_assert(spi_controller);
	int ret = spi_controller_write(spi_controller, data, len, 0);
	spi_controller_cs_release(spi_controller);

	return ret;
}

static int gdew042c37_send_plane_data(const void *display_data, unsigned plane, const uint8_t *plane_data)
{
	struct gdew042c37_data *gdew042c37_display_data = display_data;

	switch (plane) {
	case 0:
	{
		const uint8_t start_bw_data[] = { GDEW042C37_CMD_DATA_START_TRANSMISSION1 };
		gdew042c37_send_command(gdew042c37_display_data, start_bw_data, sizeof(start_bw_data));
	};
		break;
	case 1:
	{
		const uint8_t start_yellow_data[] = { GDEW042C37_CMD_DATA_START_TRANSMISSION2 };
		gdew042c37_send_command(gdew042c37_display_data, start_yellow_data, sizeof(start_yellow_data));
	}
		break;
	default:
		return -EINVAL;
	}

	gdew042c37_send_data(gdew042c37_display_data, plane_data, GDEW042C37_PLANESIZE);

	return 0;
}

static int gdew042c37_refresh(const void *display_data)
{
	struct gdew042c37_data *gdew042c37_display_data = display_data;
	const uint8_t display_refresh[] = { GDEW042C37_CMD_DISPLAY_REFRESH };

	gdew042c37_send_command(gdew042c37_display_data, display_refresh, sizeof(display_refresh));
	gdew042c37_wait_not_busy(gdew042c37_display_data);

	return 0;
}


const struct epaper_driver gdew042c37 = {
	.send_plane_data = gdew042c37_send_plane_data,
	.refresh = gdew042c37_refresh,
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
