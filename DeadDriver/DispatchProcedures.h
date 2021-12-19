#pragma once

#include <ntddk.h>

NTSTATUS DCheckersCreateClose(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp);

NTSTATUS DCheckersDeviceControl(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp);