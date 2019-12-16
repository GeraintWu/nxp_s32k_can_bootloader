/*
 * update.h
 *
 *  Created on: Oct 31, xxxx
 *      Author: xxx
 */

#ifndef SOURCES_DRIVERS_INC_UPDATE_H_
#define SOURCES_DRIVERS_INC_UPDATE_H_

#include "can_pal.h"
#include "can_pal1.h"
#include "can_user_if.h"
#include "callbacks.h"

#define DEBUG_CONSOLE       (0)

/* Little Endian to Big Endian macro */
#define LE2BE_32(c)	        (((c & 0xFF) << 24) | ((c & 0xFF00) << 8) | ((c & 0xFF0000) >> 8) | ((c & 0xFF000000) >> 24))

#define MEM_APP_START		(0x0A000)			/* Application starts at 40 kB */
#define MEM_APP_END         (0x3FFFF)



typedef enum
{
	err_flash_init = 0x00E0,
	//err_flash_erase = 0x00E1,
	//err_flash_write = 0x00E2,
	err_flash_addr = 0x00E3,
	err_flash_ok = 0x0000,
	err_unknown  = 0xEEEE
}err_status_t;


/* Prototypes */
uint8_t wait_update_cmd(void);
void download_app(void);

#endif /* SOURCES_DRIVERS_INC_UPDATE_H_ */
