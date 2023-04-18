/*
 * libebogroll.h
 */

#ifndef INCLUDE_LIBEBOGROLL_H_
#define INCLUDE_LIBEBOGROLL_H_

#include <stdint.h>

struct epaper_driver {
	int (*power_up)(void *display_data);
	int (*send_plane_data)(const void *display_data, unsigned plane, const uint8_t *plane_data);
	int (*refresh)(const void *display_data);
	int (*power_down)(void *display_data);
};

int ebogroll_send_plane_data(const struct epaper_driver *driver,
		const void *display_data, unsigned plane, const uint8_t *plane_data);
int ebogroll_refresh(const struct epaper_driver *driver, const void *display_data);

#endif /* INCLUDE_LIBEBOGROLL_H_ */
