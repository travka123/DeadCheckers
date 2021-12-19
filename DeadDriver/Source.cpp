#include <ntddk.h>

#include "DispatchProcedures.h"
#include "Globals.h"

Globals g_Globals;

#define PROCESS_TERMINATE 1;

void DCheckersUnload(_In_ PDRIVER_OBJECT DriverObject);

OB_PREOP_CALLBACK_STATUS OnPreOpenProcess(PVOID, POB_PRE_OPERATION_INFORMATION info) {
	if (info->KernelHandle) {
		return OB_PREOP_SUCCESS;
	}

	//KdPrint(("callback called"));

	PEPROCESS process = (PEPROCESS)info->Object;
	ULONG pid = HandleToUlong(PsGetProcessId(process));

	if (g_Globals.protect && (pid == g_Globals.processId)) {
		KdPrint(("process protected"));
		info->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_TERMINATE;
	}

	return OB_PREOP_SUCCESS;
}

void OnProcessNotify(PEPROCESS Process, HANDLE ProcessId, PPS_CREATE_NOTIFY_INFO CreateInfo) {
	UNREFERENCED_PARAMETER(Process);
	UNREFERENCED_PARAMETER(ProcessId);
	UNREFERENCED_PARAMETER(CreateInfo);

	if ((CreateInfo != NULL) && g_Globals.blockCreation) {
		CreateInfo->CreationStatus = STATUS_ACCESS_DENIED;
		KdPrint(("process creation blocked"));
	}
}

extern "C" NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT  DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(RegistryPath);

	UNICODE_STRING devName = RTL_CONSTANT_STRING(L"\\Device\\DCheckers");
	UNICODE_STRING symLink = RTL_CONSTANT_STRING(L"\\??\\DCheckers");
	PDEVICE_OBJECT deviceObject;
	NTSTATUS status;

	g_Globals.protect = false;
	g_Globals.blockCreation = false;

	status = IoCreateDevice(DriverObject, 0, &devName, FILE_DEVICE_UNKNOWN, 0, FALSE, &deviceObject);
	if (!NT_SUCCESS(status)) {
		KdPrint(("Failed to create device"));
		return status;
	}

	status = IoCreateSymbolicLink(&symLink, &devName);
	if (!NT_SUCCESS(status)) {
		KdPrint(("Failed to create link"));
		IoDeleteDevice(deviceObject);
		return status;
	}

	status = PsSetCreateProcessNotifyRoutineEx(OnProcessNotify, FALSE);
	if (!NT_SUCCESS(status)) {
		KdPrint(("Failed to register callback"));
		IoDeleteSymbolicLink(&symLink);
		IoDeleteDevice(deviceObject);
		return status;
	}

	OB_OPERATION_REGISTRATION operations[] = {
		{
			PsProcessType,
			OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE,
			OnPreOpenProcess,
			nullptr
		}
	};

	OB_CALLBACK_REGISTRATION reg = {
		OB_FLT_REGISTRATION_VERSION,
		1,
		RTL_CONSTANT_STRING(L"2280.077700228"),
		nullptr,
		operations
	};

	status = ObRegisterCallbacks(&reg, &g_Globals.regHandle);
	if (!NT_SUCCESS(status)) {
		KdPrint(("Failed to register callback"));
		PsSetCreateProcessNotifyRoutineEx(OnProcessNotify, TRUE);
		IoDeleteSymbolicLink(&symLink);
		IoDeleteDevice(deviceObject);
		return status;
	}

	DriverObject->DriverUnload = DCheckersUnload;

	DriverObject->MajorFunction[IRP_MJ_CREATE] = DriverObject->MajorFunction[IRP_MJ_CLOSE] = DCheckersCreateClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DCheckersDeviceControl;

	KdPrint(("Driver init"));

	return STATUS_SUCCESS;
}

void DCheckersUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNICODE_STRING symLink = RTL_CONSTANT_STRING(L"\\??\\DCheckers");

	ObUnRegisterCallbacks(g_Globals.regHandle);
	PsSetCreateProcessNotifyRoutineEx(OnProcessNotify, TRUE);
	IoDeleteSymbolicLink(&symLink);
	IoDeleteDevice(DriverObject->DeviceObject);

	KdPrint(("Driver unload"));
}