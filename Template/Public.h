/*++

Module Name:

    Public.h

Abstract:

    Definitions shared between the mini-filter driver and user-mode
    applications: the control device names, the I/O control codes, and the
    structures exchanged through DeviceIoControl.

    In user mode, include <windows.h> (or <winioctl.h>) before this header.

Environment:

    Kernel mode and user mode

--*/

#pragma once

//
//  Control device names
//
//  MF_DEVICE_NAME and MF_SYMBOLIC_LINK_NAME are used by the driver.
//  User-mode applications open the device with CreateFile(MF_USER_DEVICE_NAME, ...).
//

#define MF_DEVICE_NAME          L"\\Device\\$safeprojectname$"
#define MF_SYMBOLIC_LINK_NAME   L"\\DosDevices\\$safeprojectname$"
#define MF_USER_DEVICE_NAME     L"\\\\.\\$safeprojectname$"

//
//  I/O control codes
//
//  Device types 0x8000-0xFFFF and function codes 0x800-0xFFF are reserved
//  for vendors.
//

#define MF_DEVICE_TYPE          0x8000

#define IOCTL_MF_GET_VERSION \
    CTL_CODE( MF_DEVICE_TYPE, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS )

//
//  TODO: Add your own I/O control codes here.
//

//
//  Output buffer of IOCTL_MF_GET_VERSION
//

#define MF_VERSION_MAJOR        1
#define MF_VERSION_MINOR        0

typedef struct _MF_VERSION_INFO {

    ULONG Major;
    ULONG Minor;

} MF_VERSION_INFO, *PMF_VERSION_INFO;
