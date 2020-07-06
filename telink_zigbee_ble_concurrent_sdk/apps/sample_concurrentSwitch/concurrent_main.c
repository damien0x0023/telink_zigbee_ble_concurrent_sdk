/********************************************************************************************************
 * @file     concurrent_main.c
 *
 * @brief	 Common main entry
 *
 * @author
 * @date     Dec. 1, 2017
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
#include "zcl_include.h"
#include "sampleSwitch.h"
#include "zigbee_ble_switch.h"
#include "app_ui.h"
#include "app_pm.h"

#if BLE_CONCURRENT_MODE


extern void user_zb_init();
extern void user_ble_init(void);

/* system clock configuration
 *
 * platform:
 * 		826x
 * 		8258
 * 		HAWK
 *
 *  */
#if(CLOCK_SYS_CLOCK_HZ == 24000000)
	SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_24M_Crystal;
#elif(CLOCK_SYS_CLOCK_HZ == 32000000)
	SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_32M_Crystal;
#elif(CLOCK_SYS_CLOCK_HZ == 16000000)
	SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_16M_Crystal;
#elif(CLOCK_SYS_CLOCK_HZ == 48000000)
	SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_48M_Crystal;
#else
	#error please config system clock
#endif

enum{
	SYSTEM_RETENTION_NONE,
	SYSTEM_RETENTION_EN,
};

/*
 * platform initiation:
 * 		clock_init: 	system clock selection
 * 		ZB_RADIO_INIT: 	RF module
 * 		gpio_init:		gpio configuration
 * 		ZB_TIMER_INIT:  enable a timer for zigbee mac cca-csma
 *
 * */
static u8 platform_init(void){
	u8 ret = SYSTEM_RETENTION_NONE;

#if defined(MCU_CORE_8258)
	extern void bss_section_clear(void);
	extern void data_section_load();
	if( (analog_read(0x7f) & 0x01) ){	  //recovery from deep sleep
		bss_section_clear();
		data_section_load();
	}else{
		ret = SYSTEM_RETENTION_EN;
	}
#endif

	blc_pm_select_internal_32k_crystal();

	cpu_wakeup_init();

	clock_init(g_sysClk);

#if defined(MCU_CORE_8258)
	internalFlashSizeCheck();
	random_generator_init();   //for random generation
#endif

	gpio_init();

	ZB_RADIO_INIT();

	//ZB_TIMER_INIT();
	return ret;
}


int main (void) {
	if(platform_init() == SYSTEM_RETENTION_NONE){
		os_init(0);
	}

#if(TX_POWER_CAL_ENABLE)
	app_txPowerCal();
#endif

	user_zb_init();

	if(!pmParam.is_deepretn_back || !zigbee_process){
		//backup the registers
		backup_zigbee_rf_context();

		ble_rf_drv_init(RF_MODE_BLE_1M);
		user_ble_init();
	}

#if PM_ENABLE
	app_pm_init();
#endif

    irq_enable();
	while (1) {
    	concurrent_mode_main_loop ();

    	app_key_handler();

#if PM_ENABLE
    	app_pm_task();
#endif
	}
}

#endif
