/*++

Module Name:

    $safeprojectname$.cpp

Abstract:

    This is the main module of the file system mini-filter driver.
    It registers the filter with the Filter Manager (fltmgr.sys) and handles
    unload and instance management.
    The pre/post-operation callbacks are in Callbacks.cpp.

Environment:

    Kernel mode (C++)

    The following are not available in kernel-mode C++:
      - C++ exceptions (try/catch/throw) and RTTI (dynamic_cast, typeid)
      - The standard library (STL) and the default new/delete
        (define your own with ExAllocatePool2 / ExFreePoolWithTag if needed)
      - Global objects with constructors (they are not initialized)
    Structured exception handling (__try/__except) is available.

--*/

#include "$safeprojectname$.h"
#include "Callbacks.h"

//
//  Global variables
//

PFLT_FILTER gFilterHandle = nullptr;

#if DBG
ULONG gTraceFlags = MFDBG_TRACE_ROUTINES;
#else
ULONG gTraceFlags = 0;
#endif

//
//  Function prototypes
//
//  DriverEntry must be extern "C" because the system calls it by its C name.
//  The callbacks are declared extern "C" as well, because #pragma alloc_text
//  can only be applied to functions with C linkage.
//  The pre/post-operation callbacks are declared in Callbacks.h.
//

EXTERN_C_START

DRIVER_INITIALIZE DriverEntry;
NTSTATUS
DriverEntry (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
    );

NTSTATUS
$safeprojectname$Unload (
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
    );

NTSTATUS
$safeprojectname$InstanceSetup (
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
    );

NTSTATUS
$safeprojectname$InstanceQueryTeardown (
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
    );

VOID
$safeprojectname$InstanceTeardownStart (
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags
    );

VOID
$safeprojectname$InstanceTeardownComplete (
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags
    );

EXTERN_C_END

//
//  Assign text sections for each routine
//

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, $safeprojectname$Unload)
#pragma alloc_text(PAGE, $safeprojectname$InstanceSetup)
#pragma alloc_text(PAGE, $safeprojectname$InstanceQueryTeardown)
#pragma alloc_text(PAGE, $safeprojectname$InstanceTeardownStart)
#pragma alloc_text(PAGE, $safeprojectname$InstanceTeardownComplete)
#endif

//
//  Filter registration
//

CONST FLT_REGISTRATION FilterRegistration = {

    sizeof( FLT_REGISTRATION ),                     //  Size
    FLT_REGISTRATION_VERSION,                       //  Version
    0,                                              //  Flags

    nullptr,                                        //  Context
    Callbacks,                                      //  Operation callbacks

    $safeprojectname$Unload,                        //  MiniFilterUnload

    $safeprojectname$InstanceSetup,                 //  InstanceSetup
    $safeprojectname$InstanceQueryTeardown,         //  InstanceQueryTeardown
    $safeprojectname$InstanceTeardownStart,         //  InstanceTeardownStart
    $safeprojectname$InstanceTeardownComplete,      //  InstanceTeardownComplete

    nullptr,                                        //  GenerateFileName
    nullptr,                                        //  NormalizeNameComponent
    nullptr,                                        //  NormalizeContextCleanup
    nullptr,                                        //  TransactionNotification
    nullptr                                         //  NormalizeNameComponentEx
};


/*************************************************************************
    Mini-filter initialization and unload routines
*************************************************************************/

NTSTATUS
DriverEntry (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
    )
/*++

Routine Description:

    This is the initialization routine for the driver. It registers the
    mini-filter with the Filter Manager and starts filtering.

Arguments:

    DriverObject - Pointer to the driver object for this driver.

    RegistryPath - Path to this driver's registry key (the service key).

Return Value:

    The NTSTATUS result of the initialization.

--*/
{
    NTSTATUS status;

    UNREFERENCED_PARAMETER( RegistryPath );

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!DriverEntry: Entered\n") );

    //
    //  Register with the Filter Manager.
    //

    status = FltRegisterFilter( DriverObject,
                                &FilterRegistration,
                                &gFilterHandle );

    FLT_ASSERT( NT_SUCCESS( status ) );

    if (NT_SUCCESS( status )) {

        //
        //  Start filtering I/O.
        //

        status = FltStartFiltering( gFilterHandle );

        if (!NT_SUCCESS( status )) {

            FltUnregisterFilter( gFilterHandle );
        }
    }

    return status;
}

NTSTATUS
$safeprojectname$Unload (
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
    )
/*++

Routine Description:

    Called when the mini-filter is unloaded (for example, by fltmc unload).
    Unregisters the filter and frees any allocated resources.

Arguments:

    Flags - Indicates whether the unload is mandatory
            (FLTFL_FILTER_UNLOAD_MANDATORY).

Return Value:

    Returning STATUS_SUCCESS lets the unload proceed.
    For a non-mandatory unload, an error status can be returned to refuse it.

--*/
{
    UNREFERENCED_PARAMETER( Flags );

    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$Unload: Entered\n") );

    FltUnregisterFilter( gFilterHandle );

    return STATUS_SUCCESS;
}


/*************************************************************************
    Instance management
*************************************************************************/

NTSTATUS
$safeprojectname$InstanceSetup (
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
    )
/*++

Routine Description:

    Decides whether to attach an instance to a volume.
    Called, for example, when a new volume is mounted.

Arguments:

    FltObjects - Pointer to the related filter, instance, and volume.

    Flags - Flags indicating why this instance is being created.

    VolumeDeviceType - Device type of the volume.

    VolumeFilesystemType - File system type of the volume.

Return Value:

    STATUS_SUCCESS - Attach.
    STATUS_FLT_DO_NOT_ATTACH - Do not attach.

--*/
{
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( Flags );
    UNREFERENCED_PARAMETER( VolumeDeviceType );
    UNREFERENCED_PARAMETER( VolumeFilesystemType );

    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$InstanceSetup: Entered\n") );

    //
    //  TODO: Return STATUS_FLT_DO_NOT_ATTACH for volumes you do not want to filter.
    //        Example: skip network volumes
    //
    //  if (VolumeDeviceType == FILE_DEVICE_NETWORK_FILE_SYSTEM) {
    //      return STATUS_FLT_DO_NOT_ATTACH;
    //  }
    //

    return STATUS_SUCCESS;
}

NTSTATUS
$safeprojectname$InstanceQueryTeardown (
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
    )
/*++

Routine Description:

    Called to ask whether an instance may be removed in response to a manual
    detach request (for example, fltmc detach).
    If this callback is not registered, manual detach requests are always
    refused.

Arguments:

    FltObjects - Pointer to the related filter, instance, and volume.

    Flags - Reserved.

Return Value:

    Returning STATUS_SUCCESS allows the detach.

--*/
{
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( Flags );

    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$InstanceQueryTeardown: Entered\n") );

    return STATUS_SUCCESS;
}

VOID
$safeprojectname$InstanceTeardownStart (
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags
    )
/*++

Routine Description:

    Called when instance teardown begins.
    Complete or cancel any pending I/O here.

Arguments:

    FltObjects - Pointer to the related filter, instance, and volume.

    Flags - Reason for the teardown.

--*/
{
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( Flags );

    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$InstanceTeardownStart: Entered\n") );
}

VOID
$safeprojectname$InstanceTeardownComplete (
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags
    )
/*++

Routine Description:

    Called when instance teardown is complete.
    Free any resources allocated for this instance.

Arguments:

    FltObjects - Pointer to the related filter, instance, and volume.

    Flags - Reason for the teardown.

--*/
{
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( Flags );

    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$InstanceTeardownComplete: Entered\n") );
}
