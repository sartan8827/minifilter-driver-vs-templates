/*++

Module Name:

    Control.h

Abstract:

    Declarations of the control device object, its symbolic link, and the
    dispatch routines that handle requests (such as DeviceIoControl) from
    user-mode applications.

Environment:

    Kernel mode (C++)

--*/

#pragma once

#include <fltKernel.h>

EXTERN_C_START

//
//  Control device creation and deletion
//

NTSTATUS
$safeprojectname$CreateControlDevice (
    _In_ PDRIVER_OBJECT DriverObject
    );

VOID
$safeprojectname$DeleteControlDevice (
    VOID
    );

//
//  Dispatch routines of the control device
//

_Dispatch_type_( IRP_MJ_CREATE )
_Dispatch_type_( IRP_MJ_CLEANUP )
_Dispatch_type_( IRP_MJ_CLOSE )
DRIVER_DISPATCH $safeprojectname$DispatchCreateClose;

_Dispatch_type_( IRP_MJ_DEVICE_CONTROL )
DRIVER_DISPATCH $safeprojectname$DispatchDeviceControl;

EXTERN_C_END
