/*
 * can_user_if.h
 *
 *  Created on: 2019¦~10¤ë28¤é
 *      Author: Jingtai_Wu
 */

#ifndef CAN_USER_IF_H_
#define CAN_USER_IF_H_

#include <stdio.h>

#define CAN_RX_CH0       1
#define CAN_RX_CH1       2
#define CAN_RX_CH2       3
#define CAN_RX_CH3       4
#define CAN_RX_CH4       5
#define CAN_RX_CH5       6
#define CAN_RX_CH6       7
#define CAN_RX_CH7       8
#define CAN_RX_CH8       9
#define CAN_RX_CH9      10
#define CAN_RX_CH10     11
#define CAN_RX_CH11     12
#define CAN_RX_CH12     13
#define CAN_RX_CH13     14
#define CAN_RX_CH14     15
#define CAN_TX_CH0       0

//#define CAN_ID_690    0x690 // CH0
//#define CAN_ID_F00    0xF00 // CH1
//#define CAN_ID_301    0x301 // CH11
//#define CAN_ID_302    0x302 // CH12
//#define CAN_ID_303    0x303 // CH13
//#define CAN_ID_180    0x180 // CH14


// ID (command) used for app update
#define CAN_CMD_UPDATE    (0x100)
#define CAN_CMD_ERASE     (0x200)
#define CAN_CMD_ADDR      (0x300)
#define CAN_CMD_DATA      (0x400)
#define CAN_CMD_END       (0x500)
#define CAN_CMD_MASK_ANY  (0)

//messagebox
#define RX_MESSAGE_BOX    CAN_RX_CH0
#define TX_MESSAGE_BOX    CAN_TX_CH0


typedef struct
{
	uint32_t messagebox;
	uint32_t messageid;
}can_msg_commnad_t;

typedef enum
{
	rx_flash_update = CAN_CMD_UPDATE,
	rx_flash_erase = CAN_CMD_ERASE,
	rx_flash_data = CAN_CMD_DATA,
	rx_flash_end  = CAN_CMD_END,
	rx_flash_addr = CAN_CMD_ADDR

}rx_cmd_status_t;

typedef enum
{
	tx_flash_update_ack = CAN_CMD_UPDATE+1,
	tx_flash_erase_ack = CAN_CMD_ERASE+1,
	tx_flash_addr_ack = CAN_CMD_ADDR+1,
	tx_flash_data_ack = CAN_CMD_DATA+1,
	tx_flash_end_ack = CAN_CMD_END+1

}tx_cmd_status_t;


can_buff_config_t    g_buffCfg;
can_message_t        g_recvMsg;
can_message_t        g_sendMsg;
bool                 g_can_tx_complete;
bool                 g_can_rx_complete;
rx_cmd_status_t      rx_cmd;


void init_can(void);


#endif /* CAN_USER_IF_H_ */
