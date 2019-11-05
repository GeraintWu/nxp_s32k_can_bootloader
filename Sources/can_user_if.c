/*
 * can_user_if.c
 *
 *  Created on: 2019¦~10¤ë28¤é
 *      Author: Jingtai_Wu
 */

#include <string.h>

#include "can_pal.h"
#include "can_pal1.h"
#include "can_user_if.h"
#include "callbacks.h"


const can_msg_commnad_t g_can_rx_msg_cmd[] =
{
		{
				.messagebox = 	RX_MESSAGE_BOX,
				.messageid  =   CAN_CMD_MASK_ANY
		},
};

const can_msg_commnad_t g_can_tx_msg_cmd[] =
{
		{
				.messagebox = 	TX_MESSAGE_BOX,
				.messageid  =   0
		},
};


//can_msg_commnad_t *p_can_msg_cmd;

static void callbackCan(uint8_t instance,
		                can_event_t eventType,
						uint32_t objIdx,
						void *driverState);

/*FUNCTION**********************************************************************
 *
 * Function Name :
 * Description   :
 * Implements    :
 *END**************************************************************************/
void init_can(void)
{
	CAN_Init(&can_pal1_instance, &can_pal1_Config0);

	//RX
    g_buffCfg.enableFD = false;
    g_buffCfg.enableBRS = true;
    g_buffCfg.fdPadding = 0U;
    g_buffCfg.idType = CAN_MSG_ID_EXT;
    g_buffCfg.isRemote = false;

    CAN_ConfigRxBuff(&can_pal1_instance, g_can_rx_msg_cmd[0].messagebox, &g_buffCfg, g_can_rx_msg_cmd[0].messageid);
    CAN_SetRxFilter(&can_pal1_instance,CAN_MSG_ID_EXT,g_can_rx_msg_cmd[0].messagebox, CAN_CMD_MASK_ANY); //mask = 0 => Don't care the ID#

    // TX
    g_buffCfg.enableFD = false;
    g_buffCfg.enableBRS = true;
    g_buffCfg.fdPadding = 0U;
    g_buffCfg.idType = CAN_MSG_ID_EXT;
    g_buffCfg.isRemote = false;
    CAN_ConfigTxBuff(&can_pal1_instance, g_can_tx_msg_cmd[0].messagebox, &g_buffCfg);

    CAN_InstallEventCallback(&can_pal1_instance, (void *)&callbackCan, NULL);

}

/*FUNCTION**********************************************************************
 *
 * Function Name :
 * Description   :
 * Implements    :
 *END**************************************************************************/
static void callbackCan(uint8_t instance,
		                can_event_t eventType,
						uint32_t objIdx,
						void *driverState)
{
	 switch(eventType)
	 {
		 case CAN_EVENT_TX_COMPLETE:
			 g_can_tx_complete = true;
		 break;

		 case CAN_EVENT_RX_COMPLETE:

             g_can_rx_complete = true;
             rx_cmd = g_recvMsg.id;
#if 0
			 switch(g_recvMsg.id)
			 {
			   case  CAN_CMD_UPDATE:
			        rx_cmd = rx_flash_update;
			   break;

			   case  CAN_CMD_ERASE:
			        rx_cmd = rx_flash_erase;
			   break;

			   case  CAN_CMD_DATA:
		            rx_cmd = rx_flash_data;
			   break;

			   case  CAN_CMD_END:
			        rx_cmd = rx_flash_end;
			   break;
			 }
#endif

			 //__asm__ ("NOP");
		 break;
		 default:
		 break;
	 }
}

/*END OF FILE*/
