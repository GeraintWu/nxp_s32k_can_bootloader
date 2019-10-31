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


/* Little Endian to Big Endian macro */
#define LE2BE_32(c)	(((c & 0xFF) << 24) | ((c & 0xFF00) << 8) | ((c & 0xFF0000) >> 8) | ((c & 0xFF000000) >> 24))

#define MEM_APP_START		0x10000			/* Application starts at 64 kB */
#define MEM_APP_END         0x3FFFF

/* Timeout in ms for blocking operations */
#define TIMEOUT     100U

typedef enum
{
	err_flash_init = 0xE0,
	err_flash_erase = 0xE1,
	err_flash_write = 0xE2,
	err_flash_addr = 0xE3,
	err_flash_ok = 0x00,
	err_unknow  = 0xE0
}err_status;


/* Prototypes */
uint8_t wait_update_cmd(void);
void download_app(void);

#endif /* SOURCES_DRIVERS_INC_UPDATE_H_ */