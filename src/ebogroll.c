/*
 * bogroll.c
 *
 *  Created on: 18 Apr 2023
 *      Author: daniel
 */

#include "libebogroll.h"

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

