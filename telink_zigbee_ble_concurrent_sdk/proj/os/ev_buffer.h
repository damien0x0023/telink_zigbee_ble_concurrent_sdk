/********************************************************************************************************
 * @file     ev_buffer.h
 *
 * @brief    Interface of Telink EV Buffer Module
 *
 * @author   jian.zhang@telink-semi.com
 * @date     Oct. 8, 2016
 *
 * @par      Copyright (c) 2016, Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *
 *           The information contained herein is confidential property of Telink
 *           Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *           of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *           Co., Ltd. and the licensee or the terms described here-in. This heading
 *           MUST NOT be removed from this file.
 *
 *           Licensees are granted free, non-transferable use of the information in this
 *           file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 *
 *******************************************************************************************************/
#pragma once

#include "../common/types.h"
#include "../common/compiler.h"


/** @addtogroup  TELINK_COMMON_MODULE TELINK Common Module
 *  @{
 */

/** @addtogroup  EV_BUFFER EV Buffer
 *  @{
 */
 
/** @defgroup EV_BUFFER_CONSTANT EV Buffer Constants
 *  @{
 */


/** @addtogroup ev_buffer_groups EV Buffer Groups 
 * Definition the length of each buffer group
 * @{
 */
#define BUFFER_GROUP_0                   24
#define BUFFER_GROUP_1                   60
#define BUFFER_GROUP_2                   150
#define MAX_BUFFER_SIZE                  BUFFER_GROUP_2

/** @} end of group ev_buffer_groups */

/**
 * @brief Default buffer number in each group
 */
#define BUFFER_NUM_IN_GROUP0             8
#define BUFFER_NUM_IN_GROUP1             20
#define BUFFER_NUM_IN_GROUP2             5

/** @addtogroup ev_buffer_typical_size EV Buffer Typical Application Size
 * Definition default buffer size for different typical usage
 * @{
 */
#define SMALL_BUFFER                     48    
#define LARGE_BUFFER                     142

#define EV_BUFFER_DEBUG		0

/** @} end of group ev_buffer_typical_size */

/** @} end of group EV_BUFFER_CONSTANT */


/** @defgroup EV_BUFFER_TYPE EV Buffer Types
 *  @{
 */

/**
 *  @brief Definition of a buffer item, it is internal used.
 */
typedef struct ev_bufItem {
    struct ev_bufItem* next;
#if EV_BUFFER_DEBUG
    u8 groupIndex;
    u8 flag;
    u16 line;
#else
    u32 groupIndex;
#endif
    u8 data[1];
} ev_bufItem_t;


/**
 *  @brief Definiton error code of EV buffer operation
 */
typedef enum buf_sts_e {
    // SUCCESS always be ZERO
	BUFFER_SUCC,
    BUFFER_INVALID_PARAMETER = 1,  //!< Invalid parameter passed to the buffer API
    BUFFER_DUPLICATE_FREE          //!< The same buffer is freed more than once
} buf_sts_t;

/**  @} end of group EV_BUFFER_TYPE */


/** @defgroup EV_BUFFER_FUNCTIONS EV Buffer API
 *  @brief Function declaration of EV Buffer module
 *  @{
 */

 /**
  * @brief       Reset the EV Buffer module
  *
  * @param       None
  *
  * @return      None
  */
void ev_buf_reset(void);

 /**
  * @brief       Initialize the EV Buffer module
  *
  * @param       None
  *
  * @return      None
  */
void ev_buf_init(void);

 /**
  * @brief       Allocate an available buffer according to the requested size
  *              The allocated buffer will have only three kind of size, defined 
  *              in @ref EV_BUFFER_CONSTANT
  *
  * @param       size - The requested size
  *
  * @return      Pointer to an allocated buffer.
  *              NULL means the there is no available buffer.
  */

#if EV_BUFFER_DEBUG
#define ev_buf_allocate(size)	my_ev_buf_allocate(size, __LINE__)
#else
u8 *ev_buf_allocate(u16 size);
#endif

 /**
  * @brief       Free the specified buffer 
  *
  * @param       pBuf - the pointer to the specified buffer to free.
  *
  * @return      Status.
  */

#if EV_BUFFER_DEBUG
#define ev_buf_free(pBuf)	my_ev_buf_free(pBuf, __LINE__)
#else
buf_sts_t ev_buf_free(u8* pBuf);
#endif

 /**
  * @brief       Get the header of a buffer item  
  *
  * @param       pd - the pointer of a data, which is previously allocated
  *
  * @return      Pointer of bufferItem
  */
ev_bufItem_t* ev_buf_getHead(u8* pd);

/**
 * @brief       judge if the buffer is ev buffer
 *
 * @param       the buffer adrress
 *
 * @return      1: if ev buffer; 0: others
 */
u8 is_ev_buf(void *arg);


/**  @} end of group EV_BUFFER_FUNCTIONS */

/**  @} end of group EV_BUFFER */

/**  @} end of group TELINK_COMMON_MODULE */


