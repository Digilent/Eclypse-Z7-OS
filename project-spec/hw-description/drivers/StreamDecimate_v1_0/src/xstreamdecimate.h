// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XSTREAMDECIMATE_H
#define XSTREAMDECIMATE_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xstreamdecimate_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XStreamdecimate_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XStreamdecimate;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XStreamdecimate_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XStreamdecimate_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XStreamdecimate_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XStreamdecimate_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XStreamdecimate_Initialize(XStreamdecimate *InstancePtr, u16 DeviceId);
XStreamdecimate_Config* XStreamdecimate_LookupConfig(u16 DeviceId);
int XStreamdecimate_CfgInitialize(XStreamdecimate *InstancePtr, XStreamdecimate_Config *ConfigPtr);
#else
int XStreamdecimate_Initialize(XStreamdecimate *InstancePtr, const char* InstanceName);
int XStreamdecimate_Release(XStreamdecimate *InstancePtr);
#endif

void XStreamdecimate_Start(XStreamdecimate *InstancePtr);
u32 XStreamdecimate_IsDone(XStreamdecimate *InstancePtr);
u32 XStreamdecimate_IsIdle(XStreamdecimate *InstancePtr);
u32 XStreamdecimate_IsReady(XStreamdecimate *InstancePtr);
void XStreamdecimate_EnableAutoRestart(XStreamdecimate *InstancePtr);
void XStreamdecimate_DisableAutoRestart(XStreamdecimate *InstancePtr);

void XStreamdecimate_Set_axilConfig(XStreamdecimate *InstancePtr, u32 Data);
u32 XStreamdecimate_Get_axilConfig(XStreamdecimate *InstancePtr);

void XStreamdecimate_InterruptGlobalEnable(XStreamdecimate *InstancePtr);
void XStreamdecimate_InterruptGlobalDisable(XStreamdecimate *InstancePtr);
void XStreamdecimate_InterruptEnable(XStreamdecimate *InstancePtr, u32 Mask);
void XStreamdecimate_InterruptDisable(XStreamdecimate *InstancePtr, u32 Mask);
void XStreamdecimate_InterruptClear(XStreamdecimate *InstancePtr, u32 Mask);
u32 XStreamdecimate_InterruptGetEnabled(XStreamdecimate *InstancePtr);
u32 XStreamdecimate_InterruptGetStatus(XStreamdecimate *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
