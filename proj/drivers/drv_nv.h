/********************************************************************************************************
 * @file    drv_nv.h
 *
 * @brief   This is the header file for drv_nv
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
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
 *
 *******************************************************************************************************/

#pragma once



/********************************************************************
 * @brief	Flash map usage.
 *
 * #if !defined(BOOT_LOADER_MODE) || (BOOT_LOADER_MODE == 0)
 *
 *	 				512k							  1M
 * 		0x80000  ------------			0x100000  ------------
 *	 			|		     |					 |  MAC_Addr  |
 *	  		    |  	 NV_2 	 |			 0xFF000 |------------|
 *	 		    |		     |					 | F_CFG_Info |
 *		0x7A000 |------------|			 0xFE000 |------------|
 *	 		    | U_Cfg_Info |					 | U_Cfg_Info |
 * 		0x78000 |------------|			 0xFC000 |------------|
 *	   		    |            |                   |			  |
 *	   		    |            |           0xF9000 |------------|
 *		   		|            |					 |   NV_BLE   |
 *	   		    |F_CFG_Info	 |           0xF7000 |------------|
 *	   		    |            |                   |			  |
 *		   		|		   	 |	                 |  NV_ZIGBEE |
 *		   		|			 |                   |			  |
 * 		0x77000 |------------|			 0xE0000 |------------|
 * 		   		|  MAC_Addr  |					 |     Resv   |
 * 		0x76000 |------------|			 0x80000 |------------|
 * 		   		|  NV_BLE	 |					 |			  |
 * 		0x74000 |------------|					 |			  |
 * 		   		|		     |					 |			  |
 * 		   		|  OTA_Image |					 |			  |
 * 		   		|		     |					 |	OTA_Image |
 * 		0x40000 |------------|					 |			  |
 * 		   		|		     |					 |			  |
 * 		   		|  	 NV_1 	 |			 0x40000 |------------|
 * 		   		|		     |					 |			  |
 * 		0x34000 |------------|					 |			  |
 * 		   		|		     |					 |  Firmware  |
 * 		   		|  Firmware  |	208k			 |			  | 256k
 * 		   		|		     |					 |			  |
 * 		0x00000  ------------			 0x00000  ------------
 *
 * #else
 *    #if !DUAL_MODE_WITH_SIG && !DUAL_MODE_WITH_MATTER
 *	 				512k							  1M
 * 		0x80000  ------------			0x100000  ------------
 *	 			|			 |					 |  MAC_Addr  |
 *	 			|  	 NV_2 	 |			 0xFF000 |------------|
 *	 			|			 |					 | F_CFG_Info |
 *	 	0x7A000 |------------|			 0xFE000 |------------|
 *	 			| U_Cfg_Info |					 | U_Cfg_Info |
 *	 	0x78000 |------------|			 0xFC000 |------------|
 *	 			| F_CFG_Info |					 |		      |
 *	 	0x77000 |------------|					 |     NV     |
 *	 			|  MAC_Addr  |					 |		      |
 *	 	0x76000 |------------|			 0xE6000 |------------|
 *	 			|		     |					 |	 NV_BLE   |
 *	 			|		     |			 0xE4000 |------------|
 *	 			|  	 NV_1	 |					 |		      |
 *	 			|		     |					 |	OTA_Image |
 *	 	0x6A000 |------------|					 |		      |
 *	 	        |   NV_BLE   |					 |		      |
 *	 	0x68000 |------------|					 |		      |
 *	 			|		     |					 |		      |
 *	 			|  OTA_Image |			 0x76000 |------------|
 *	 			|		     |					 |		      |
 *	 	0x38000 |------------|					 |		      |
 *	 			|			 |					 |  Firmware  |
 *	 			|  Firmware	 |	192k			 |		      | 440k
 *	 			|			 |					 |		      |
 *	 	0x08000 |------------|			 0x08000 |------------|
 *	 			| BootLoader |					 | BootLoader |
 *	 	0x00000  ------------			 0x00000  ------------
 *
 *	 #else if DUAL_MODE_WITH_SIG
 *	 				 1M
 * 		0x100000  ------------
 *	 	   	    |  MAC_Addr  |
 *	 	0xFF000 |------------|
 *	 	        | F_CFG_Info |
 *	 	0xFE000 |------------|
 *	 			| U_Cfg_Info |
 *	 	0xFC000 |------------|
 *	 			|		     |
 *	 			|  Firmware  |
 *	 			|		     |
 *	 	0x80000 |------------|
 *	 			|		     |
 *	 			|  OTA_Image |
 *	 			|		     |
 *      0x40000 |------------|
 *	 			|   RESV	 |
 *	 	0x3E000 |------------|
 *	 			|   NV-BLE   |
 *	 	0x3C000	|------------|
 *	 			|            |
 *	 			| NV_ZIGBEE	 |
 *	 			|            |
 *	 	0x26000 |------------|
 *	 			|  SDK_TYPE  |
 *	 	0x24000	|------------|
 *	 			|			 |
 *	 			|FW-BLE_MESH |
 *	 			|		     |
 *	 	0x08000 |------------|
 *	 			| BootLoader |
 *	 	0x00000  ------------
 *	 #else if DUAL_MODE_WITH_MATTER
 *	 				 4M
 * 	   0x400000  ------------
 *	 	   	    |  MAC_Addr  |
 * 	   0x3FF000 |------------|
 *	 	        | F_CFG_Info |
 * 	   0x3FE000 |------------|
 *	 			|            |
 * 	   0x3A7000 |------------|
 *	 			| SHARE_PARA |
 * 	   0x3A6000 |------------|
 *	 			|		     |
 * 	   0x3A5000 |------------|
 *	 			| U_Cfg_Info |
 * 	   0x3A3000 |------------|
 *	 			|  NV_ZIGBEE |
 * 	   0x38D000 |------------|
 *	 			|   NV_BLE   |
 * 	   0x38B000 |------------|
 *	 			|            |
 * 	   0x35E000 |------------|------
 *	 			|            |
 *	 			|            | slot1
 *	 			|            |
 * 	   0x1B9000 |------------|------
 *	 			| ZIGBEE_FW  |
 * 	   0x154000 |------------|
 *	 			|			 | slot0
 *	 			| MATTER_FW  |
 *	 			|		     |
 *	 	0x14000 |------------|------
 *	 			|MATTER_BOOT |
 *	 	0x00000  ------------
 *	 #endif
 *
 * #endif
 */


/* Flash Base Address define */
#if defined(MCU_CORE_826x) || defined(MCU_CORE_8258) || defined(MCU_CORE_8278)
	#define FLASH_TLNK_FLAG_OFFSET		8
#elif defined(MCU_CORE_B91) || defined(MCU_CORE_B92) || defined(MCU_CORE_B95)
	#define FLASH_TLNK_FLAG_OFFSET		32
#endif



/************************************************************************
 * Flash address of factory setting parameters,
 * where are stored the MAC ADDRESS and CALIBRATION information.
 */
//512k flash
#define FLASH_ADDR_OF_MAC_ADDR_512K		0x76000
#define FLASH_ADDR_OF_F_CFG_INFO_512K	0x77000
//1M flash
#define FLASH_ADDR_OF_MAC_ADDR_1M		0xFF000
#define FLASH_ADDR_OF_F_CFG_INFO_1M		0xFE000
//2M flash
#define FLASH_ADDR_OF_MAC_ADDR_2M		0x1FF000
#define FLASH_ADDR_OF_F_CFG_INFO_2M		0x1FE000
//4M flash
#define FLASH_ADDR_OF_MAC_ADDR_4M		0x3FF000
#define FLASH_ADDR_OF_F_CFG_INFO_4M		0x3FE000

/************************************************************************/
extern u32 g_u32MacFlashAddr;
extern u32 g_u32CfgFlashAddr;

#define MAC_BASE_ADD					(g_u32MacFlashAddr)
#define FACTORY_CFG_BASE_ADD			(g_u32CfgFlashAddr)
/************************************************************************/

/**************************************************************************************
 * The following is the detailed factory configure information (F_CFG_Info).
 */
/* 8 bytes for MAC address. */
#define CFG_MAC_ADDRESS              	(MAC_BASE_ADD)

/* 2 bytes for USB ID. */
#define CFG_TELINK_USB_ID				(MAC_BASE_ADD + 0x40)

/* 1 byte for frequency offset calibration. */
#define CFG_FREQUENCY_OFFSET			(FACTORY_CFG_BASE_ADD)

/* 2 bytes for TP GAIN.
 * 0x77040(or 0xFE040) for BLE TP_GAIN_0, 0x77041(or 0xFE041) for BLE TP_GAIN_1,
 * 0x77042(or 0xFE042) for zigbee TP_GAIN_0, 0x77043(or 0xFE043) for zigbee TP_GAIN_1. */
#define CFG_TP_GAIN                  	(FACTORY_CFG_BASE_ADD + 0x42)

/* Not supported for current SDK. */
#define CFG_32K_COUNTER_CALIBRATION	 	(FACTORY_CFG_BASE_ADD + 0x80)

/* Not supported for current SDK. */
#define CFG_ADC_CALIBRATION           	(FACTORY_CFG_BASE_ADD + 0xC0)

/* Not supported for current SDK. */
#define CFG_24M_CRYSTAL_CALIBRATION     (FACTORY_CFG_BASE_ADD + 0x100)

/* Not supported for current SDK. */
#define CFG_T_SENSOR_CALIBRATION     	(FACTORY_CFG_BASE_ADD + 0x140)

/* UID-based Firmware Encryption data(16 bytes), 0x77180(or 0xFE180) ~ 0x7718F(or 0xFE18F). */
#define CFG_FIRMWARE_ENCRYPTION			(FACTORY_CFG_BASE_ADD + 0x180)

/* 2 bytes for VDD_F calibration.
 * 0x771C0(or 0xFF1C0) for DCDC trim,
 * 0x771C1(or 0xFF1C1) for LDO trim.
 */
#define CFG_VDD_F_CALIBRATION			(FACTORY_CFG_BASE_ADD + 0x1C0)


/**************************************************************************************
 * The following is the detailed user configure information (U_CFG_Info).
 */
/* 16 bytes for pre-install code. */
#if(FLASH_CAP_SIZE_1M || FLASH_CAP_SIZE_2M || FLASH_CAP_SIZE_4M)
#if DUAL_MODE_WITH_MATTER
	#define CFG_PRE_INSTALL_CODE		(0x3A4000)
#else
	#define CFG_PRE_INSTALL_CODE		(0xFD000)
#endif
#else
#define CFG_PRE_INSTALL_CODE			(0x78000)
#endif

/* 1 byte for factory reset.
 * If not 0xFF, means the device is doing factory reset(erase NV).
 * The device will check this byte when powered on, if it is not 0xFF,
 * it will erase NV first.
 */
#if(FLASH_CAP_SIZE_1M || FLASH_CAP_SIZE_2M || FLASH_CAP_SIZE_4M)
#if DUAL_MODE_WITH_MATTER
	#define CFG_FACTORY_RST_CNT			(0x3A3000)
#else
	#define CFG_FACTORY_RST_CNT			(0xFC000)
#endif
#else
#define CFG_FACTORY_RST_CNT			  	(0x79000)
#endif

/**************************************************************************************
 * Flash address of NV module.
 */
#if !defined(BOOT_LOADER_MODE) || (BOOT_LOADER_MODE == 0)
#if(FLASH_CAP_SIZE_1M || FLASH_CAP_SIZE_2M || FLASH_CAP_SIZE_4M)
	#define NV_BASE_ADDRESS				(0xE0000)
	#define CFG_NV_START_FOR_BLE		(0xF7000)
#else
	#define	NV_BASE_ADDRESS				(0x34000)
    #define	NV_BASE_ADDRESS2			(0x7A000)
    #define CFG_NV_START_FOR_BLE		(0x74000)
#endif
#if DUAL_MODE_WITH_SIG || DUAL_MODE_WITH_MATTER
    #error "should use bootloade mode!!!"
#endif
#else
#if(FLASH_CAP_SIZE_1M || FLASH_CAP_SIZE_2M || FLASH_CAP_SIZE_4M)
    #if DUAL_MODE_WITH_SIG
        #define NV_ADDR_FOR_SDK_TYPE	(0x24000)
        #define NV_BASE_ADDRESS			(0x26000)
        #define CFG_NV_START_FOR_BLE	(0x3C000)
	#elif DUAL_MODE_WITH_MATTER
		#define CFG_NV_START_FOR_BLE	(0x38B000)
		#define NV_BASE_ADDRESS			(0x38D000)
	#else
		#define CFG_NV_START_FOR_BLE	(0xE4000)
		#define NV_BASE_ADDRESS			(0xE6000)
	#endif
#else
    #define CFG_NV_START_FOR_BLE		(0x68000)
	#define	NV_BASE_ADDRESS				(0x6A000)
	#define	NV_BASE_ADDRESS2			(0x7A000)
    #if DUAL_MODE_WITH_SIG || DUAL_MODE_WITH_MATTER
        #error "should larger capacity flash!!!"
    #endif
#endif
#endif

#if DUAL_MODE_WITH_SIG
typedef enum{
	TYPE_TLK_MESH  						= 0x000000A3,// don't change, must same with telink mesh SDK
	TYPE_SIG_MESH  						= 0x0000003A,// don't change, must same with telink mesh SDK
	TYPE_TLK_BLE_SDK 					= 0x000000C3,// don't change, must same with telink mesh SDK
	TYPE_TLK_ZIGBEE  					= 0x0000003C,// don't change, must same with telink mesh SDK
	TYPE_DUAL_MODE_STANDBY				= 0x00000065,// dual mode state was standby to be selected
	TYPE_DUAL_MODE_RECOVER 				= 0x00000056,// don't change, must same with telink mesh SDK, recover for mesh
}telink_sdk_type_t;

#define CFG_TELINK_SDK_TYPE				(NV_ADDR_FOR_SDK_TYPE)
#endif	/* DUAL_MODE_WITH_SIG */


/*
 * Flash address of APP firmware.
 */
#define FLASH_ADDR_OF_APP_FW			APP_IMAGE_ADDR

#ifndef FLASH_SMP_PAIRING_MAX_SIZE
#define FLASH_SMP_PAIRING_MAX_SIZE         						(4096)
#endif


/************************************************************************
 * Flash address of OTA image.
 */
#if !defined(BOOT_LOADER_MODE) || (BOOT_LOADER_MODE == 0)
//unchangeable address
#define FLASH_ADDR_OF_OTA_IMAGE		    (0x40000)

#if(FLASH_CAP_SIZE_1M || FLASH_CAP_SIZE_2M || FLASH_CAP_SIZE_4M)
	//max size = (0x80000 - 0) / 2 = 256k
	#define FLASH_OTA_IMAGE_MAX_SIZE	    (FLASH_ADDR_OF_OTA_IMAGE - FLASH_ADDR_OF_APP_FW)
#else
	//max size = (0x34000 - 0) = 204k
	#define FLASH_OTA_IMAGE_MAX_SIZE	    (NV_BASE_ADDRESS - FLASH_ADDR_OF_APP_FW)
#endif

#else
    #if DUAL_MODE_WITH_SIG
        #define FLASH_OTA_IMAGE_MAX_SIZE	(0x40000)
        #define FLASH_ADDR_OF_OTA_IMAGE		(0x40000)
	#elif DUAL_MODE_WITH_MATTER
		#define FLASH_OTA_IMAGE_MAX_SIZE	(0x1B9000 - 0x154000)
		#define FLASH_ADDR_OF_OTA_IMAGE		(0x2F9000)
	#else
		//1M   Flash: max size = (0xE4000 - 0x8000) / 2 = 440k
		//512k Flash: max size = (0x68000 - 0x8000) / 2 = 192k
		#define FLASH_OTA_IMAGE_MAX_SIZE	((CFG_NV_START_FOR_BLE - FLASH_ADDR_OF_APP_FW) / 2)
		//1M   Flash: ota addr = 0x8000 + 440k = 0x76000
		//512k Flash: ota addr = 0x8000 + 192k = 0x38000
		#define FLASH_ADDR_OF_OTA_IMAGE		(FLASH_ADDR_OF_APP_FW + FLASH_OTA_IMAGE_MAX_SIZE)
	#endif
#endif

/******************************************** END ***********************************************************/




#define NV_SECT_INFO_CHECK_BITS			6
#define NV_SECT_INFO_CHECK_BITMASK		0x3f
#define NV_SECT_INFO_SECTNO_BITS		(8-NV_SECT_INFO_CHECK_BITS)
#define NV_SECT_INFO_SECTNO_BITMASK		0x3

/* sector info(4Bytes) + index info(8Bytes) + index info(8Bytes) + ... */
typedef struct{
	u16 usedFlag;
	u8  idName;
	u8  opSect;    //crcCheckBit(6bits) + opSect(2bits)
}nv_sect_info_t;

typedef struct{
	u32 offset;
	u16 size;
	u8  itemId;
	u8  usedState;
#if defined(MCU_CORE_B91) || defined(MCU_CORE_B92)
	u8  resv[8];   //PUYA flash only supports re-write 64 times
#endif
}nv_info_idx_t;

/* item:  item_hdr(8Bytes) + payload*/
typedef struct{
	u32 checkSum;
	u16 size;
	u8  itemId;
	u8  used;
}itemHdr_t;

typedef struct _attribute_packed_{
	u16 opIndex;
	u8 	opSect;
}itemIfno_t;

//If OTA enabled, the maximum space used for nv module t is 56K, thus the item num cannot over 14
/*****************************************************************************************************************************
 * Store zigbee information in flash.
 * 		Module ID				|			512K Flash				|			1M Flash				|
 * -----------------------------|-----------------------------------|-----------------------------------|
 * NV_MODULE_ZB_INFO			|		0x34000 - 0x36000			|		0xE0000 - 0xE2000			|
 * NV_MODULE_ADDRESS_TABLE		|		0x36000 - 0x38000			|		0xE2000 - 0xE4000			|
 * NV_MODULE_APS				|		0x38000 - 0x3a000			|		0xE4000 - 0xE6000			|
 * NV_MODULE_ZCL				|		0x3a000 - 0x3c000			|		0xE6000 - 0xE8000			|
 * NV_MODULE_NWK_FRAME_COUNT	|		0x3c000 - 0x3e000			|		0xE8000 - 0xEa000			|
 * NV_MODULE_OTA				|		0x3e000 - 0x40000			|		0xEa000 - 0xEc000			|
 * NV_MODULE_APP				|		0x7a000 - 0x7c000			|		0xEc000 - 0xEe000			|
 * NV_MODULE_KEYPAIR			|		0x7c000 - 0x80000			|		0xEe000 - 0xF6000			|
 * 								|	*16K - can store 127 nodes		|	*32K - can store 302 nodes		|
 * NV_MAX_MODULS
 */
typedef enum{
	NV_MODULE_ZB_INFO 				= 0,      /* mustn't modify it */
	NV_MODULE_ADDRESS_TABLE 		= 1,      /* mustn't modify it */
    NV_MODULE_APS 					= 2,      /* mustn't modify it */
    NV_MODULE_ZCL 					= 3,      /* mustn't modify it */
	NV_MODULE_NWK_FRAME_COUNT 		= 4,      /* mustn't modify it */
	NV_MODULE_OTA 					= 5,
	NV_MODULE_APP 					= 6,
	NV_MODULE_KEYPAIR 				= 7,
    NV_MAX_MODULS
}nv_module_t;


typedef enum{
	NV_ITEM_ID_INVALID				= 0,/* Item id 0 should not be used. */

	NV_ITEM_ZB_INFO 				= 1, /* mustn't modify it */
	NV_ITEM_ADDRESS_FOR_NEIGHBOR,        /* mustn't modify it */
	NV_ITEM_ADDRESS_FOR_BIND,            /* mustn't modify it */
	NV_ITEM_APS_SSIB,                    /* mustn't modify it */
	NV_ITEM_APS_GROUP_TABLE,             /* mustn't modify it */
	NV_ITEM_APS_BINDING_TABLE,           /* mustn't modify it */

	NV_ITEM_NWK_FRAME_COUNT,             /* mustn't modify it */

	NV_ITEM_SS_KEY_PAIR,                 /* mustn't modify it */

	NV_ITEM_OTA_HDR_SERVERINFO,
	NV_ITEM_OTA_CODE,

	NV_ITEM_ED_TIMEOUT,

	NV_ITEM_ZCL_REPORT 				= 0x20,
	NV_ITEM_ZCL_ON_OFF,
	NV_ITEM_ZCL_LEVEL,
	NV_ITEM_ZCL_COLOR_CTRL,
	NV_ITEM_ZCL_SCENE_TABLE,
	NV_ITEM_ZCL_GP_PROXY_TABLE,
	NV_ITEM_ZCL_GP_SINK_TABLE,
	NV_ITEM_ZCL_WWAH_APS_AUTH_INFO,
	NV_ITEM_ZCL_WWAH_APS_ACKS_INFO,
	NV_ITEM_ZCL_WWAH_USE_TC_CLUSTER_INFO,

	NV_ITEM_APP_SIMPLE_DESC,
	NV_ITEM_APP_POWER_CNT,
	NV_ITEM_APP_GP_TRANS_TABLE,

	NV_ITEM_ZCL_ON_OFF_2			= 0x31,
	NV_ITEM_ZCL_LEVEL_2				= 0x32,
	NV_ITEM_ZCL_COLOR_CTRL_2		= 0x33,

	NV_ITEM_APP_COMM_TIMEOUT		= 0x40,
	NV_ITEM_APP_PRIVATE_SCENE_STORED= 0x41,

	NV_ITEM_APS_BINDING_TABLE_V2    = 0x80,  /* mustn't modify it */

	NV_ITEM_ID_MAX					= 0xFF,/* Item id 0xFF should not be used. */
}nv_item_t;

typedef enum{
	NV_SUCC,
    NV_INVALID_MODULS 				= 1,
    NV_INVALID_ID ,
    NV_ITEM_NOT_FOUND,
    NV_NOT_ENOUGH_SAPCE,
    NV_ITEM_LEN_NOT_MATCH,
    NV_CHECK_SUM_ERROR,
    NV_ENABLE_PROTECT_ERROR,
    NV_NO_MEDIA,
    NV_DATA_CHECK_ERROR,
	NV_ITEM_CHECK_ERROR,
	NV_MODULE_NOT_FOUND,
	NV_MODULE_ERASE_NEED
} nv_sts_t;


#define FLASH_PAGE_SIZE							256
#define	FLASH_SECTOR_SIZE						4096//4K

#define NV_SECTOR_VALID							0x5A5A
#define NV_SECTOR_VALID_CHECKCRC				0x7A7A
#define NV_SECTOR_VALID_READY_CHECKCRC			0xFAFA
#define NV_SECTOR_INVALID						0x5050
#define NV_SECTOR_IDLE							0xFFFF

#define ITEM_FIELD_VALID						0x5A
#define ITEM_FIELD_VALID_SINGLE					0x7A
#define ITEM_FIELD_INVALID						0x50
#define ITEM_FIELD_OPERATION					0xFA
#define ITEM_FIELD_IDLE							0xFF

#define ITEM_HDR_FIELD_VALID_CHECKSUM			0x5A
#define ITEM_HDR_FIELD_VALID_CHECKCRC			0x7A


#if(FLASH_CAP_SIZE_1M || FLASH_CAP_SIZE_2M || FLASH_CAP_SIZE_4M)
#define MODULES_START_ADDR(id)					(NV_BASE_ADDRESS + FLASH_SECTOR_SIZE * (2 * id))
#define NV_SECTOR_SIZE(id)						((id == NV_MODULE_KEYPAIR) ? (4 * FLASH_SECTOR_SIZE) : FLASH_SECTOR_SIZE)
#define MODULE_INFO_SIZE(id)					((id == NV_MODULE_OTA || id == NV_MODULE_KEYPAIR || id == NV_MODULE_ADDRESS_TABLE) ? ((id == NV_MODULE_KEYPAIR) ? (12*FLASH_PAGE_SIZE) : (4*FLASH_PAGE_SIZE)) : (2*FLASH_PAGE_SIZE))
#else
#define MODULES_START_ADDR(id)					((id < 6) ? (NV_BASE_ADDRESS + FLASH_SECTOR_SIZE * (2 * id)) : (NV_BASE_ADDRESS2 + FLASH_SECTOR_SIZE * (2 * (id-6))))
#define NV_SECTOR_SIZE(id)						((id == NV_MODULE_KEYPAIR) ?  (2 * FLASH_SECTOR_SIZE) : FLASH_SECTOR_SIZE)
#define MODULE_INFO_SIZE(id)					((id == NV_MODULE_OTA || id == NV_MODULE_KEYPAIR || id == NV_MODULE_ADDRESS_TABLE) ? (4*FLASH_PAGE_SIZE) : (2*FLASH_PAGE_SIZE))
#endif

#define MODULE_SECTOR_NUM						(2)

#define MODULE_IDX_SIZE(id)						(MODULE_INFO_SIZE(id) - sizeof(nv_sect_info_t))
#define MODULE_SECT_START(id, sectNo)   		(MODULES_START_ADDR(id) + sectNo * (NV_SECTOR_SIZE(id)))
#define MODULE_SECT_END(id, sectNo)     		(MODULES_START_ADDR(id) + (sectNo + 1) * (NV_SECTOR_SIZE(id)))
#define MODULE_IDX_START(id, sectNo)    		(MODULE_SECT_START(id, sectNo) + sizeof(nv_sect_info_t))
#define MODULE_IDX_NUM(id)    					(MODULE_IDX_SIZE(id) / (sizeof(nv_info_idx_t)))
#define MODULE_CONTEXT_START(id, sectNo, len)  	(MODULE_SECT_START(id, sectNo) + MODULE_INFO_SIZE(id))
#define ITEM_TOTAL_LEN(len)						(len + sizeof(itemHdr_t))
#define FRAMECOUNT_PAYLOAD_START(opSect)		(((MODULE_SECT_START(NV_MODULE_NWK_FRAME_COUNT, opSect) + sizeof(nv_sect_info_t)) + 0x03) & (~0x03))
#define FRAMECOUNT_NUM_PER_SECT()				((((FLASH_SECTOR_SIZE - sizeof(nv_sect_info_t)) & (~0x03))) / 4)




nv_sts_t nv_resetAll(void);
nv_sts_t nv_resetModule(u8 modules);
nv_sts_t nv_flashWriteNew(u8 single, u16 id, u8 itemId, u16 len, u8 *buf);
nv_sts_t nv_flashReadNew(u8 single, u8 id, u8 itemId, u16 len, u8 *buf);
nv_sts_t nv_itemDeleteByIndex(u8 id, u8 itemId, u8 opSect, u16 opIdx);
nv_sts_t nv_flashSingleItemRemove(u8 id, u8 itemId, u16 len);
nv_sts_t nv_flashReadByIndex(u8 id, u8 itemId, u8 opSect, u16 opIdx, u16 len, u8 *buf);
void nv_itemLengthCheckAdd(u8 itemId, u16 len);
nv_sts_t nv_resetToFactoryNew(void);
bool nv_facrotyNewRstFlagCheck(void);
void nv_facrotyNewRstFlagSet(void);
void nv_facrotyNewRstFlagClear(void);
nv_sts_t nv_nwkFrameCountSaveToFlash(u32 frameCount);
nv_sts_t nv_nwkFrameCountFromFlash(u32 *frameCount);
nv_sts_t nv_flashSingleItemSizeGet(u8 id, u8 itemId, u16 *len);

