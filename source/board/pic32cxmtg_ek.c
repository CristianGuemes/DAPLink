/**
 * @file    pic32cxmtg_ek.c
 * @brief   board ID for the Microchip PIC32CXMTG Evaluation Kit board
 *
 * DAPLink Interface Firmware
 * Copyright (c) 2020, ARM Limited, All Rights Reserved
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

#include "target_family.h"
#include "target_board.h"

#define PIC32CXMTG_BOARD_ID       "0921"
#define PIC32CXMTG_FAMILY_ID      kStub_HWReset_FamilyID  

const board_info_t g_board_info = {
    .info_version = kBoardInfoVersion,
    .board_id = PIC32CXMTG_BOARD_ID,
    .family_id = PIC32CXMTG_FAMILY_ID,
    .daplink_url_name =       "PRODINFOHTM",
    .daplink_drive_name =       "PIC32CXMTG",
    .daplink_target_url = "https://os.mbed.com/platforms/PIC32CXMTG-EK/",
    .target_cfg = &target_device,
	.soft_reset_type = SYSRESETREQ,
};
