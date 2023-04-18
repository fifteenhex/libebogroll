/*
 * bogroll.c
 *
 *  Created on: 18 Apr 2023
 *      Author: daniel
 */

#include "libebogroll.h"

int ebogroll_reset(const struct epaper_driver *driver, const void *display_data)
{
	if (!driver->reset)
		return -1;

	return driver->reset(display_data);
}

int ebogroll_power_up(const struct epaper_driver *driver, const void *display_data)
{
	if (!driver->power_up)
		return -1;

	return driver->power_up(display_data);
}

int ebogroll_send_plane_data(const struct epaper_driver *driver,
		const void *display_data, unsigned plane, const uint8_t *plane_data)
{
	if (!driver->send_plane_data)
		return -1;

	return driver->send_plane_data(display_data, plane, plane_data);
}

int ebogroll_refresh(const struct epaper_driver *driver, const void *display_data)
{
	if (!driver->refresh)
		return -1;

	return driver->refresh(display_data);
}

int ebogroll_power_down(const struct epaper_driver *driver, const void *display_data)
{
	if (!driver->power_down)
		return -1;

	return driver->power_down(display_data);
}

