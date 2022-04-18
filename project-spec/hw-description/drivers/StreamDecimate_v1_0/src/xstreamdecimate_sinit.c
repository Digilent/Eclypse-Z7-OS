// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xstreamdecimate.h"

extern XStreamdecimate_Config XStreamdecimate_ConfigTable[];

XStreamdecimate_Config *XStreamdecimate_LookupConfig(u16 DeviceId) {
	XStreamdecimate_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XSTREAMDECIMATE_NUM_INSTANCES; Index++) {
		if (XStreamdecimate_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XStreamdecimate_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XStreamdecimate_Initialize(XStreamdecimate *InstancePtr, u16 DeviceId) {
	XStreamdecimate_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XStreamdecimate_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XStreamdecimate_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

