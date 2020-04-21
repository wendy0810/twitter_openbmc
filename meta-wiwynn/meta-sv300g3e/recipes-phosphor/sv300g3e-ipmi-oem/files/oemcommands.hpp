/*
// Copyright (c) 2019 Wiwynn Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#pragma once

#include <map>
#include <string>

static constexpr ipmi_netfn_t netFnSv300g3eOEM1 = 0x2E;
static constexpr ipmi_netfn_t netFnSv300g3eOEM2 = 0x30;
static constexpr ipmi_netfn_t netFnSv300g3eOEM3 = 0x3E;
static constexpr ipmi_netfn_t netFnSv300g3eOEM4 = 0x3C;

static const size_t maxPatternLen = 256;
static const uint8_t maxLbaThresholdNum = 3;

enum ipmi_sv300g3e_oem2_cmds : uint8_t
{
    CMD_SET_FAN_PWM = 0x11,
    CMD_SET_FSC_MODE = 0x12,
};

enum ipmi_sv300g3e_oem3_cmds : uint8_t
{
    CMD_SET_SOL_PATTERN = 0xB2,
    CMD_GET_SOL_PATTERN = 0xB3,
    CMD_SET_LBA_THRESHOLD = 0xB4,
    CMD_GET_LBA_THRESHOLD = 0xB5,
    CMD_GET_LBA_TOTAL_CNT = 0xB6,
    CMD_GET_LBA_RELATIVE_CNT = 0xB7,
    CMD_SET_BMC_TIMESYNC_MODE = 0xB8,
};

enum ipmi_sv300g3e_oem4_cmds : uint8_t
{
    CMD_GET_VR_VERSION = 0x51,
};

enum
{
    FSC_MODE_MANUAL = 0x00,
    FSC_MODE_AUTO = 0x01,
};

enum vr_type : uint8_t
{
    CPU0_VCCIN = 0x00,
    CPU1_VCCIN,
    CPU0_DIMM0,
    CPU0_DIMM1,
    CPU1_DIMM0,
    CPU1_DIMM1,
    CPU0_VCCIO,
    CPU1_VCCIO,
};

typedef struct
{
    uint8_t mode; // 00h Manual, 01h Auto

}__attribute__((packed)) SetFscModeCmdRequest;

/**
 *  Maintain the request data pwmIndex(which pwm we are going to write)
 *  Map request data pwmIndex to pwm file name.
 **/
std::map<uint8_t, std::string> pwmFileTable =
{
    {0x00, "pwm1"}, {0x01, "pwm2"},
    {0x02, "pwm3"}, {0x03, "pwm4"},
    {0x04, "pwm5"}, {0x05, "pwm6"},
};

typedef struct
{
    uint8_t pwmIndex; // 00h - 05h (pwm1-pwm6)
    uint8_t pwmValue; // 01h - 64h (1-100)

}__attribute__((packed)) SetPwmCmdRequest;

typedef struct
{
    uint8_t patternIdx;
    char data[maxPatternLen];
}__attribute__((packed)) SetSolPatternCmdReq;

typedef struct
{
    uint8_t patternIdx;
}__attribute__((packed)) GetSolPatternCmdReq;

typedef struct
{
    char data[maxPatternLen];
}__attribute__((packed)) GetSolPatternCmdRes;

typedef struct
{
    uint8_t thresholdIdx;
    uint16_t thresholdVal;
}__attribute__((packed)) SetLbaThresholdCmdReq;

typedef struct
{
    uint8_t thresholdIdx;
}__attribute__((packed)) GetLbaThresholdCmdReq;

typedef struct
{
    uint16_t thresholdVal;
}__attribute__((packed)) GetLbaThresholdCmdRes;

typedef struct
{
    uint8_t dimmIdx;
}__attribute__((packed)) GetLbaTotalCntReq;

typedef struct
{
    uint32_t totalCnt;
}__attribute__((packed)) GetLbaTotalCntRes;

typedef struct
{
    uint8_t dimmIdx;
}__attribute__((packed)) GetLbaRelativeCntReq;

typedef struct
{
    uint32_t relativeCnt;
}__attribute__((packed)) GetLbaRelativeCntRes;

typedef struct
{
    uint8_t syncMode;
}__attribute__((packed)) SetBmcTimeSyncModeReq;

typedef struct
{
    uint8_t vrType;
}__attribute__((packed)) GetVrVersionCmdReq;

typedef struct
{
    uint16_t verData0;
    uint16_t verData1;
}__attribute__((packed)) GetVrVersionCmdRes;
