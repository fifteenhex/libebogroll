/*
 * libebogroll.h
 */

#ifndef INCLUDE_LIBEBOGROLL_H_
#define INCLUDE_LIBEBOGROLL_H_

#include <stdint.h>

struct epaper_driver {
	int (*reset)(const void *display_data);
	int (*power_up)(const void *display_data);
	int (*send_plane_data)(const void *display_data, unsigned plane, const uint8_t *plane_data);
	int (*refresh)(const void *display_data);
	int (*power_down)(const void *display_data);
};

int ebogroll_reset(const struct epaper_driver *driver, const void *display_data);
int ebogroll_power_up(const struct epaper_driver *driver, const void *display_data);
int ebogroll_send_plane_data(const struct epaper_driver *driver,
		const void *display_data, unsigned plane, const uint8_t *plane_data);
int ebogroll_refresh(const struct epaper_driver *driver, const void *display_data);
int ebogroll_power_down(const struct epaper_driver *driver, const void *display_data);

#endif /* INCLUDE_LIBEBOGROLL_H_ */
