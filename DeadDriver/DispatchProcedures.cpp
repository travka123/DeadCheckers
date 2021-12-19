#include "DispatchProcedures.h"

#include "DCheckersCommon.h"
#include "Globals.h"

extern Globals g_Globals;

NTSTATUS CompleteIrp(PIRP Irp, NTSTATUS status, ULONG_PTR info);

NTSTATUS DCheckersCreateClose(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp) {
	UNREFERENCED_PARAMETER(DeviceObject);

	return CompleteIrp(Irp, STATUS_SUCCESS, 0);
}

NTSTATUS DCheckersDeviceControl(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp) {
	UNREFERENCED_PARAMETER(DeviceObject);

	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	switch (stack->Parameters.DeviceIoControl.IoControlCode) {
	case IOCTL_DCHECKERS_SET_PROTECT_PID:

		if (stack->Parameters.DeviceIoControl.InputBufferLength >= sizeof(ULONG)) {
			g_Globals.processId = *(ULONG*)stack->Parameters.DeviceIoControl.Type3InputBuffer;
			g_Globals.protect = true;
			KdPrint(("pid set"));
		}
		else {
			status = STATUS_BUFFER_TOO_SMALL;
			KdPrint(("error pid not set"));
		}

		break;

	case IOCTL_DCHECKERS_STOP_PROTECTING:
		g_Globals.protect = false;
		KdPrint(("pid cleared"));
		break;

	case IOCTL_DCHECKERS_BLOCK_PROCESS_CREATION:
		g_Globals.blockCreation = true;
		break;

	case IOCTL_DCHECKERS_STOP_BLOCKING_PROCESS_CREATION:
		g_Globals.blockCreation = false;
		break;

	case IOCTL_DCHECKERS_KILL_SYSTEM:
		KdPrint(("kill request"));
		KeBugCheck(0x00000053);
		break;
	}

	return CompleteIrp(Irp, status, 0);
}

NTSTATUS CompleteIrp(PIRP Irp, NTSTATUS status, ULONG_PTR info) {
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = info;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
}