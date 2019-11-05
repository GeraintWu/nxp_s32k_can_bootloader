/*
 * update.c
 *
 *  Created on: 2019¦~10¤ë28¤é
 *      Author: Jingtai_Wu
 */
#include <stdio.h>
#include <string.h>
#include <update.h>
#include "fsl_flash_driver_c90tfs.h"

extern can_buff_config_t        g_buffCfg;
extern can_message_t            g_recvMsg;
extern can_message_t            g_sendMsg;
extern bool                     g_can_tx_complete;
extern bool                     g_can_rx_complete;
extern const can_msg_commnad_t  g_can_rx_msg_cmd[];
extern const can_msg_commnad_t  g_can_tx_msg_cmd[];
extern rx_cmd_status_t          rx_cmd;

/* Declare a FLASH config struct which initialized by FlashInit, and will be used by all flash operations */
flash_ssd_config_t flashSSDConfig;

/*! @brief Configuration structure flashCfg_0 */
const flash_user_config_t Flash_InitConfig0 = {
		/* for the S32K118 */
		.PFlashBase  = 0x00000000U,
		.PFlashSize  = 0x00040000U,
		.DFlashBase  = 0x10000000U,
		.EERAMBase   = 0x14000000U,
		.CallBack    = NULL_CALLBACK
};


static bool            is_mem_init = false;						/* Variable used to flag is the memory has been initialized */
static bool            can_update_enabled = false;
static bool            update_done = false;
static uint8_t         first_packet;
static uint32_t        packet_num;
static can_message_t   g_rx_buf_tmp;

static uint32_t        i;
static uint32_t        erase_offset;
static uint32_t        erase_addr;
static uint32_t        write_offest;
static uint32_t        write_addr;
static flash_drv_status_t status;
//err_status err_code = 0;

static void comm_send_ack(uint32_t ack_cmd, err_status err_sts);
static void phase1(void);
static void phase2(void);
static void phase3(void);
static void null(void);
void (*execute_phase)(void);

/*FUNCTION**********************************************************************
 *
 * Function Name :
 * Description   :
 * Implements    :
 *END**************************************************************************/
uint8_t wait_update_cmd(void)
{
	uint8_t status = 0;

	if(!can_update_enabled) {

       memset((void *)&g_recvMsg, 0, sizeof(can_message_t));
	   g_can_rx_complete = true;  // the flag will be set in ISR when rx completed
	   CAN_Receive(&can_pal1_instance, g_can_rx_msg_cmd[0].messagebox,  &g_recvMsg);
	   can_update_enabled = 1;
	}

	if((g_can_rx_complete == true) && (g_recvMsg.id == rx_flash_update))
	{
		comm_send_ack(tx_flash_update_ack, err_flash_ok);
		status = 1;
	}

	return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : phase1
 * Description   : initialize and erase memory
 * Implements    :
 *END**************************************************************************/
static void phase1(void)
{
	update_done = false;

	/* Check if memory is initialized */
	if(is_mem_init == false) {					/* Initialize memory */

		status = FlashInit(&Flash_InitConfig0, &flashSSDConfig);
		if(status != FTFx_OK)
			comm_send_ack(tx_flash_erase_ack, err_flash_init);
		else
		    is_mem_init = true;
	}

	if(is_mem_init)
	{
		/* Check if block has been erased aligned addresses (first address is assumed to be 0x2000) */
		if((MEM_APP_START % FEATURE_FLS_PF_BLOCK_SECTOR_SIZE) == 0) {

			/* Erase sector */
			for(erase_offset = 0; erase_offset < (MEM_APP_END-MEM_APP_START)/FEATURE_FLS_DF_BLOCK_SECTOR_SIZE  ; erase_offset++)
			{
			  erase_addr = MEM_APP_START + (erase_offset*FEATURE_FLS_DF_BLOCK_SECTOR_SIZE);
			  status = FlashEraseSector(&flashSSDConfig, erase_addr, FEATURE_FLS_DF_BLOCK_SECTOR_SIZE, FlashCommandSequence);
			  if(status != FTFx_OK) {
				  comm_send_ack(tx_flash_erase_ack, err_flash_erase);
				  return;
			  }
			}

			//packet_num = 0;
			first_packet = 0; // set 0: ready to receive 1st data packet
			comm_send_ack(tx_flash_erase_ack, err_flash_ok);

		} else {
			comm_send_ack(tx_flash_erase_ack, err_flash_addr);
		}
	}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : phase2
 * Description   : write new app to flash sector (8bytes per write)
 * Implements    :
 *END**************************************************************************/
static void phase2(void)
{

	if(rx_cmd == rx_flash_addr)
	{
		write_offest = 0;
		write_offest = (uint32_t)(write_offest +
				                  (uint32_t)(g_recvMsg.data[4]<<24) +
				                  (uint32_t)(g_recvMsg.data[5]<<16) +
								  (uint32_t)(g_recvMsg.data[6]<<8) +
								  (uint32_t)g_recvMsg.data[7]);
		comm_send_ack(tx_flash_addr_ack, err_flash_ok);
		packet_num = 0;
	}

	if(rx_cmd == rx_flash_data)
	{
		if(first_packet == 0) {

		   first_packet = 1;
		   packet_num++;
		   memcpy(&g_rx_buf_tmp, &g_recvMsg, sizeof(can_message_t));
		   comm_send_ack(tx_flash_data_ack, err_flash_ok);

		} else {

		   write_addr = write_offest + (packet_num * 8);
		   status = FlashProgram(&flashSSDConfig, write_addr, g_recvMsg.length,  g_recvMsg.data, FlashCommandSequence);

		   if(status != FTFx_OK)
		       comm_send_ack(tx_flash_data_ack, err_flash_write);
		   else {
			   comm_send_ack(tx_flash_data_ack, err_flash_ok);
		       packet_num++;
		   }
		}
	}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : phase3
 * Description   : write first packet to the start address of app
 * Implements    :
 *END**************************************************************************/
static void phase3(void)
{
	status = FlashProgram(&flashSSDConfig, MEM_APP_START, g_rx_buf_tmp.length,  g_rx_buf_tmp.data, FlashCommandSequence);
	if(status != FTFx_OK) {

		//comm_send_ack(tx_flash_data_ack, err_flash_write);
		comm_send_ack(tx_flash_end_ack, err_flash_write);

	} else {

		g_can_tx_complete = false;
		comm_send_ack(tx_flash_end_ack, err_flash_ok);
		while(g_can_tx_complete == false);
		update_done = true;
	}
}

static void null(void){ __asm__ ("NOP");}

/*FUNCTION**********************************************************************
 *
 * Function Name :
 * Description   :
 * Implements    :
 *END**************************************************************************/
static void comm_send_ack(uint32_t ack_cmd, err_status err_sts)
{
#if 1
	g_sendMsg.id = ack_cmd;
	g_sendMsg.length = 1;
	g_sendMsg.data[0] = (uint8_t)err_sts;
#else
	if(err_sts == err_flash_ok) {
		//memcpy(g_sendMsg, g_recvMsg, sizeof(can_message_t));
		g_sendMsg = g_recvMsg;
		g_sendMsg.id = ack_cmd;
	} else {
		g_sendMsg.id = ack_cmd;
		g_sendMsg.length = 1;
		g_sendMsg.data[0] = (uint8_t)err_sts;
	}
#endif
	//g_can_rx_complete = 0;
	if(ack_cmd != tx_flash_end_ack)
	{
		CAN_Receive(&can_pal1_instance, g_can_rx_msg_cmd[0].messagebox,  &g_recvMsg);
	}

	CAN_Send(&can_pal1_instance, g_can_tx_msg_cmd[0].messagebox, &g_sendMsg);
	//while(!g_can_rx_complete);

}


/*FUNCTION**********************************************************************
 *
 * Function Name :
 * Description   :
 * Implements    :
 *END**************************************************************************/
void download_app(void)
{

    while(1)
    {
    	if(g_can_rx_complete == true)
    	{
    		g_can_rx_complete = false;

    		switch(rx_cmd)
    		{
    		  case rx_flash_erase:
    			  execute_phase = phase1;
    			  break;
    		  case rx_flash_data:
    		  case rx_flash_addr:
    			  execute_phase = phase2;
    			  break;
    		  case rx_flash_end:
    			  execute_phase = phase3;
    			  break;
    		  default:
    			  execute_phase = null;
    			  break;
    		}
    		(*execute_phase)();

#if(DEBUG_CONSOLE)
    		printf("<DEBUG MSG> Received ID#:%04XH\n", rx_cmd);
#endif
    		if(update_done)
    			break;
    	}

    	PINS_DRV_TogglePins(PTE, (1 << 8));
        for(i=0;i<800000;i++)
        	if(g_can_rx_complete == true) break;
    }

}

/*END OF FILE*/
