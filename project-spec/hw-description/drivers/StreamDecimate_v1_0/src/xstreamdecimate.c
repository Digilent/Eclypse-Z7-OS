// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xstreamdecimate.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XStreamdecimate_CfgInitialize(XStreamdecimate *InstancePtr, XStreamdecimate_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XStreamdecimate_Start(XStreamdecimate *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStreamdecimate_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_AP_CTRL) & 0x80;
    XStreamdecimate_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XStreamdecimate_IsDone(XStreamdecimate *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStreamdecimate_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XStreamdecimate_IsIdle(XStreamdecimate *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStreamdecimate_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XStreamdecimate_IsReady(XStreamdecimate *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStreamdecimate_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XStreamdecimate_EnableAutoRestart(XStreamdecimate *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamdecimate_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XStreamdecimate_DisableAutoRestart(XStreamdecimate *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamdecimate_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_AP_CTRL, 0);
}

void XStreamdecimate_Set_axilConfig(XStreamdecimate *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamdecimate_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_AXILCONFIG_DATA, Data);
}

u32 XStreamdecimate_Get_axilConfig(XStreamdecimate *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStreamdecimate_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_AXILCONFIG_DATA);
    return Data;
}

void XStreamdecimate_InterruptGlobalEnable(XStreamdecimate *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamdecimate_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_GIE, 1);
}

void XStreamdecimate_InterruptGlobalDisable(XStreamdecimate *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamdecimate_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_GIE, 0);
}

void XStreamdecimate_InterruptEnable(XStreamdecimate *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XStreamdecimate_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_IER);
    XStreamdecimate_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_IER, Register | Mask);
}

void XStreamdecimate_InterruptDisable(XStreamdecimate *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XStreamdecimate_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_IER);
    XStreamdecimate_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_IER, Register & (~Mask));
}

void XStreamdecimate_InterruptClear(XStreamdecimate *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStreamdecimate_WriteReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_ISR, Mask);
}

u32 XStreamdecimate_InterruptGetEnabled(XStreamdecimate *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XStreamdecimate_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_IER);
}

u32 XStreamdecimate_InterruptGetStatus(XStreamdecimate *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XStreamdecimate_ReadReg(InstancePtr->Control_BaseAddress, XSTREAMDECIMATE_CONTROL_ADDR_ISR);
}

