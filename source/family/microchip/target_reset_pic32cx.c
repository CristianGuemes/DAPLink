/**
 * @file    target_reset.c
 * @brief   Target reset for the new target
 *
 * DAPLink Interface Firmware
 * Copyright (c) 2009-2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "target_reset.h"
#include "swd_host.h"
#include "target_family.h"

typedef struct {
  uint32_t EEFC_FMR;      /**< \brief (Sefc Offset: 0x0) SEFC Flash Mode Register */
  uint32_t EEFC_FCR;      /**< \brief (Sefc Offset: 0x4) SEFC Flash Command Register */
  uint32_t EEFC_FSR;      /**< \brief (Sefc Offset: 0x8) SEFC Flash Status Register */
  uint32_t EEFC_FRR;      /**< \brief (Sefc Offset: 0xC) SEFC Flash Result Register */
  uint32_t EEFC_USR;      /**< \brief (Sefc Offset: 0x10) SEFC User Signature Rights Register */
  uint32_t EEFC_KBLR;     /**< \brief (Sefc Offset: 0x14) SEFC Key Bus Lock Register */
  uint32_t Reserved1[51];
  uint32_t EEFC_WPMR;     /**< \brief (Sefc Offset: 0xE4) Write Protection Mode Register */
} Sefc;

#define SEFC0        ((Sefc *)0x460E0000U) /**< \brief (SEFC0) Base Address */
#define SEFC1        ((Sefc *)0x460E0200U) /**< \brief (SEFC1) Base Address */

static void target_before_init_debug(void)
{
    // any target specific sequences needed before attaching
    //	to the DAP across JTAG or SWD
}

static uint8_t target_set_state(TARGET_RESET_STATE state)
{
    // if a custom state machine is needed to set the TARGET_RESET_STATE state
    return 1;
}

static uint8_t security_bits_set(uint32_t addr, uint8_t *data, uint32_t size)
{
    uint32_t ul_status;
	uint32_t ul_value;
	Sefc *p_sefc;
	
	/* Get GPNVM bits */
	p_sefc->EEFC_FCR = 0x5A00000D;
	do {
		ul_status = p_sefc->EEFC_FSR;
	} while ((ul_status & EEFC_FSR_FRDY) != EEFC_FSR_FRDY);
	ul_value = p_sefc->EEFC_FRR;
	
	/* Check Security bit */
	if (ul_value & 0x01) {
		// Any access to the flash through the DW-DP/JTAG-DP interface is forbidden
		return 1;
	}
	
    return 0;
}

const target_family_descriptor_t g_target_family = {
    .family_id = myFamilyID,
    .default_reset_type = kSoftwareReset,
	.soft_reset_type = SYSRESETREQ,
    .target_before_init_debug = target_before_init_debug,
    .target_set_state = target_set_state,
    .security_bits_set = security_bits_set,
};
