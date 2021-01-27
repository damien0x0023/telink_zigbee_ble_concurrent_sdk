/********************************************************************************************************
 * @file     zigbee_ble_switch.h
 *
 * @brief    the function for ble/zigbee switch
 *
 * @author
 * @date     Feb. 1, 2017
 *
 * @par      Copyright (c) 2016, Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *
 *			 The information contained herein is confidential and proprietary property of Telink
 * 		     Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *			 of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *			 Co., Ltd. and the licensee in separate contract or the terms described here-in.
 *           This heading MUST NOT be removed from this file.
 *
 * 			 Licensees are granted free, non-transferable use of the information in this
 *			 file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 *
 *******************************************************************************************************/
#include "user_config.h"
#include "zb_common.h"
#include "stack/ble/blt_config.h"
#include "stack/ble/ll/ll.h"

#include "tl_common.h"

#if BLE_CONCURRENT_MODE

#define  ZIGBEE_AFTER_TIME    (16 * 1000 * 5)	//4ms
#define  BLE_IDLE_TIME   	  (16 * 1000 * 5)	//5ms


typedef void (*master_service_t) (void);
typedef void (*master_update_t) (void);
typedef struct{
	master_service_t serviceCb;
	master_update_t  updateCb;
}ble_master_cb_t;

extern volatile u8 zigbee_process;

_attribute_ram_code_ void switch_to_zb_context(void);

_attribute_ram_code_ void switch_to_ble_context(void);

int is_switch_to_ble(void);

int is_switch_to_zigbee(void);

ble_sts_t ble_task_stop(void);

ble_sts_t ble_task_restart(void);

void zb_ble_switch_proc(void);

void concurrent_mode_main_loop(void);

#if BLE_MASTER_ROLE_ENABLE
void ble_master_serviceCbRegister(master_service_t cb);
void ble_master_updateIndCbRegister(master_update_t cb);
#endif

#endif
