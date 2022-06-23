/********************************************************************************************************
 * @file    concurrent_main.c
 *
 * @brief   This is the source file for concurrent_main
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *******************************************************************************************************/

#include "zb_common.h"
#include "stack/ble/ble_config.h"
#include "stack/ble/ble_common.h"
#include "stack/ble/ble.h"
#include "zigbee_ble_switch.h"

extern void user_zb_init(bool isRetention);
extern void user_ble_init(bool isRetention);
volatile u8 T_taskRunCnt = 0;
volatile u8 T_taskBleTrig = 0;

int main(void){
#if VOLTAGE_DETECT_ENABLE
	u32 tick = 0;
#endif
	u8 isRetention = drv_platform_init();

#if VOLTAGE_DETECT_ENABLE
	if(!isRetention){
		voltage_detect();
	}
#endif

	//extern void moduleTest_start(void);
	//moduleTest_start();


	os_init(isRetention);
	user_zb_init(isRetention);

	user_ble_init(isRetention);
	if(CURRENT_SLOT_GET() == DUALMODE_SLOT_BLE){
		ble_radio_init();
	}else{
		switch_to_zb_context();
	}

	drv_enable_irq();

#if (MODULE_WATCHDOG_ENABLE)
	drv_wd_setInterval(600);
    drv_wd_start();
#endif

#if PM_ENABLE
	app_pm_init();
#endif

	while(1){
#if VOLTAGE_DETECT_ENABLE
		if(clock_time_exceed(tick, 200 * 1000)){
			voltage_detect();
			tick = clock_time();
		}
#endif

		concurrent_mode_main_loop();

		app_key_handler();

#if PM_ENABLE
		app_pm_task();
#endif

		T_taskRunCnt++;

		/* for debugging ble start/stop */
		if(T_taskBleTrig){
			if(T_taskBleTrig == 0x01){
				ble_task_stop();
			}else if(T_taskBleTrig == 0x02){
				ble_task_restart();
			}
			T_taskBleTrig = 0;
		}
	}

	return 0;
}
