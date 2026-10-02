/*++

Module Name:

    Control.cpp

Abstract:

    The control device object of the mini-filter. User-mode applications open
    it through its symbolic link (\\.\$safeprojectname$) and send I/O control
    requests with DeviceIoControl. The names and I/O control codes are
    defined in Public.h.

    Only the kernel, SYSTEM, and administrators can open the device
    (SDDL_DEVOBJ_SYS_ALL_ADM_ALL).

Environment:

    Kernel mode (C++)

--*/

#include "$safeprojectname$.h"
#include "Control.h"
#include "Public.h"

#include <wdmsec.h>

//
//  Global variables
//

static PDEVICE_OBJECT gControlDeviceObject = nullptr;
static BOOLEAN gSymbolicLinkCreated = FALSE;

//
//  Assign text sections for each routine
//

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, $safeprojectname$CreateControlDevice)
#pragma alloc_text(PAGE, $safeprojectname$DeleteControlDevice)
#pragma alloc_text(PAGE, $safeprojectname$DispatchCreateClose)
#pragma alloc_text(PAGE, $safeprojectname$DispatchDeviceControl)
#endif


/*************************************************************************
    Control device creation and deletion
*************************************************************************/

NTSTATUS
$safeprojectname$CreateControlDevice (
    _In_ PDRIVER_OBJECT DriverObject
    )
/*++

Routine Description:

    Creates the control device object and its symbolic link, and sets the
    dispatch routines for the requests sent to it.
    Called from DriverEntry.

Arguments:

    DriverObject - Pointer to the driver object for this driver.

Return Value:

    The NTSTATUS result of the creation. On failure, nothing is left behind.

--*/
{
    NTSTATUS status;
    UNICODE_STRING deviceName = RTL_CONSTANT_STRING( MF_DEVICE_NAME );
    UNICODE_STRING symbolicLinkName = RTL_CONSTANT_STRING( MF_SYMBOLIC_LINK_NAME );

    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$CreateControlDevice: Entered\n") );

    //
    //  Create the control device object.
    //  IoCreateDeviceSecure applies the given security descriptor, so only
    //  privileged callers can open the device.
    //

    status = IoCreateDeviceSecure( DriverObject,
                                   0,
                                   &deviceName,
                                   FILE_DEVICE_UNKNOWN,
                                   FILE_DEVICE_SECURE_OPEN,
                                   FALSE,
                                   &SDDL_DEVOBJ_SYS_ALL_ADM_ALL,
                                   nullptr,
                                   &gControlDeviceObject );

    if (!NT_SUCCESS( status )) {

        MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                      ("$safeprojectname$!$safeprojectname$CreateControlDevice: IoCreateDeviceSecure failed, status=0x%08X\n",
                       status) );
        gControlDeviceObject = nullptr;
        return status;
    }

    //
    //  Create the symbolic link so that user mode can open the device.
    //

    status = IoCreateSymbolicLink( &symbolicLinkName, &deviceName );

    if (!NT_SUCCESS( status )) {

        MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                      ("$safeprojectname$!$safeprojectname$CreateControlDevice: IoCreateSymbolicLink failed, status=0x%08X\n",
                       status) );
        $safeprojectname$DeleteControlDevice();
        return status;
    }

    gSymbolicLinkCreated = TRUE;

    //
    //  Set the dispatch routines.
    //  These requests reach this driver only through the control device;
    //  file system I/O is delivered to the pre/post-operation callbacks by
    //  the Filter Manager.
    //

    DriverObject->MajorFunction[IRP_MJ_CREATE] = $safeprojectname$DispatchCreateClose;
    DriverObject->MajorFunction[IRP_MJ_CLEANUP] = $safeprojectname$DispatchCreateClose;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = $safeprojectname$DispatchCreateClose;
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = $safeprojectname$DispatchDeviceControl;

    ClearFlag( gControlDeviceObject->Flags, DO_DEVICE_INITIALIZING );

    return STATUS_SUCCESS;
}

VOID
$safeprojectname$DeleteControlDevice (
    VOID
    )
/*++

Routine Description:

    Deletes the symbolic link and the control device object.
    Called from the unload routine and on DriverEntry failure.
    Safe to call even if the control device was not created.

--*/
{
    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$DeleteControlDevice: Entered\n") );

    if (gSymbolicLinkCreated) {

        UNICODE_STRING symbolicLinkName = RTL_CONSTANT_STRING( MF_SYMBOLIC_LINK_NAME );

        IoDeleteSymbolicLink( &symbolicLinkName );
        gSymbolicLinkCreated = FALSE;
    }

    if (gControlDeviceObject != nullptr) {

        IoDeleteDevice( gControlDeviceObject );
        gControlDeviceObject = nullptr;
    }
}


/*************************************************************************
    Dispatch routines
*************************************************************************/

NTSTATUS
$safeprojectname$DispatchCreateClose (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Inout_ PIRP Irp
    )
/*++

Routine Description:

    Handles IRP_MJ_CREATE, IRP_MJ_CLEANUP, and IRP_MJ_CLOSE sent to the
    control device (CreateFile and CloseHandle in user mode).

Arguments:

    DeviceObject - Pointer to the control device object.

    Irp - Pointer to the I/O request packet.

Return Value:

    STATUS_SUCCESS - The handle may be opened/closed.

--*/
{
    UNREFERENCED_PARAMETER( DeviceObject );

    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$DispatchCreateClose: Entered, MajorFunction=0x%02X\n",
                   IoGetCurrentIrpStackLocation( Irp )->MajorFunction) );

    //
    //  TODO: Track or reject clients here if needed (for example, allow only
    //        one open handle at a time).
    //

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest( Irp, IO_NO_INCREMENT );

    return STATUS_SUCCESS;
}

NTSTATUS
$safeprojectname$DispatchDeviceControl (
    _In_ PDEVICE_OBJECT DeviceObject,
    _Inout_ PIRP Irp
    )
/*++

Routine Description:

    Handles IRP_MJ_DEVICE_CONTROL sent to the control device
    (DeviceIoControl in user mode). The I/O control codes are defined in
    Public.h.

Arguments:

    DeviceObject - Pointer to the control device object.

    Irp - Pointer to the I/O request packet.

Return Value:

    The NTSTATUS result of the request.

--*/
{
    NTSTATUS status;
    ULONG_PTR information = 0;
    PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation( Irp );
    ULONG ioControlCode = irpSp->Parameters.DeviceIoControl.IoControlCode;
    ULONG outputBufferLength = irpSp->Parameters.DeviceIoControl.OutputBufferLength;

    UNREFERENCED_PARAMETER( DeviceObject );

    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$DispatchDeviceControl: Entered, IoControlCode=0x%08X\n",
                   ioControlCode) );

    switch (ioControlCode) {

    case IOCTL_MF_GET_VERSION: {

        //
        //  METHOD_BUFFERED: the input and output share the system buffer.
        //  Always validate the buffer lengths before using it.
        //

        if (outputBufferLength < sizeof( MF_VERSION_INFO )) {

            status = STATUS_BUFFER_TOO_SMALL;
            break;
        }

        PMF_VERSION_INFO versionInfo = static_cast<PMF_VERSION_INFO>( Irp->AssociatedIrp.SystemBuffer );

        versionInfo->Major = MF_VERSION_MAJOR;
        versionInfo->Minor = MF_VERSION_MINOR;

        information = sizeof( MF_VERSION_INFO );
        status = STATUS_SUCCESS;
        break;
    }

    //
    //  TODO: Handle your own I/O control codes here.
    //

    default:
        status = STATUS_INVALID_DEVICE_REQUEST;
        break;
    }

    Irp->IoStatus.Status = status;
    Irp->IoStatus.Information = information;
    IoCompleteRequest( Irp, IO_NO_INCREMENT );

    return status;
}
