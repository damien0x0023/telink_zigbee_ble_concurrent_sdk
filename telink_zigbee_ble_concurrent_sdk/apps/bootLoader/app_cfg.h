/********************************************************************************************************
 * @file    app_cfg.h
 *
 * @brief   This is the header file for app_cfg
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

#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

/**********************************************************************
 * Version configuration
 */
#include "version_cfg.h"

/**********************************************************************
 * Product Information
 */
/* Debug mode config */
#define	UART_PRINTF_MODE				0
#define USB_PRINTF_MODE         		0

/* Board ID */
#define BOARD_826x_EVK					0
#define BOARD_826x_DONGLE				1
#define BOARD_826x_DONGLE_PA			2
#define BOARD_8258_EVK					3
#define BOARD_8258_EVK_V1P2				4//C1T139A30_V1.2
#define BOARD_8258_DONGLE				5
#define BOARD_8278_EVK					6
#define BOARD_8278_DONGLE				7
#define BOARD_B91_EVK					8
#define BOARD_B91_DONGLE				9

/* Board define */
#if defined(MCU_CORE_826x)
	#define BOARD						BOARD_826x_DONGLE
	#define CLOCK_SYS_CLOCK_HZ  		32000000
#elif defined(MCU_CORE_8258)
#if (CHIP_TYPE == TLSR_8258_1M)
	#define FLASH_CAP_SIZE_1M			1
#endif
	#define BOARD						BOARD_8258_DONGLE
	#define CLOCK_SYS_CLOCK_HZ  		48000000
#elif defined(MCU_CORE_8278)
	#define FLASH_CAP_SIZE_1M		  	1
	#define BOARD						BOARD_8278_DONGLE//BOARD_8278_EVK
	#define CLOCK_SYS_CLOCK_HZ  		48000000
#elif defined(MCU_CORE_B91)
	#define FLASH_CAP_SIZE_1M		  	1
	#define BOARD						BOARD_B91_DONGLE//BOARD_B91_EVK
	#define CLOCK_SYS_CLOCK_HZ  		48000000
#else
	#error "MCU is undefined!"
#endif

/* Board include */
#if (BOARD == BOARD_826x_EVK)
	#include "board_826x_evk.h"
#elif (BOARD == BOARD_826x_DONGLE)
	#include "board_826x_dongle.h"
#elif (BOARD == BOARD_8258_DONGLE)
	#include "board_8258_dongle.h"
#elif (BOARD == BOARD_8258_EVK)
	#include "board_8258_evk.h"
#elif (BOARD == BOARD_8258_EVK_V1P2)
	#include "board_8258_evk_v1p2.h"
#elif (BOARD == BOARD_8278_EVK)
	#include "board_8278_evk.h"
#elif (BOARD == BOARD_8278_DONGLE)
	#include "board_8278_dongle.h"
#elif (BOARD == BOARD_B91_EVK)
	#include "board_b91_evk.h"
#elif (BOARD == BOARD_B91_DONGLE)
	#include "board_b91_dongle.h"
#endif


/* Voltage detect module */
/* If you want to define the VOLTAGE_DETECT_ENABLE to 1,
 * and the model of the development board is B91 evk or dongle,
 * be sure to connect GPIO_PB0 to VCC.
 */
#define VOLTAGE_DETECT_ENABLE			0

/**********************************************************************
 * EV configuration
 */
typedef enum{
	EV_POLL_ED_DETECT,
	EV_POLL_FACTORY_RST,
	EV_POLL_HCI,
    EV_POLL_IDLE,
	EV_POLL_MAX,
}ev_poll_e;

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
