/*++

Module Name:

    $safeprojectname$.cpp

Abstract:

    This is the main module of the file system mini-filter driver.
    It registers the filter with the Filter Manager (fltmgr.sys) and provides
    the callbacks that are invoked before (pre) and after (post) I/O operations.

Environment:

    Kernel mode (C++)

    The following are not available in kernel-mode C++:
      - C++ exceptions (try/catch/throw) and RTTI (dynamic_cast, typeid)
      - The standard library (STL) and the default new/delete
        (define your own with ExAllocatePool2 / ExFreePoolWithTag if needed)
      - Global objects with constructors (they are not initialized)
    Structured exception handling (__try/__except) is available.

--*/

#include <fltKernel.h>
#include <dontuse.h>

#pragma prefast(disable:__WARNING_ENCODE_MEMBER_FUNCTION_POINTER, "Not valid for kernel mode drivers")

//
//  Global variables
//

PFLT_FILTER gFilterHandle = nullptr;

//
//  Debug output
//
//  Set bits in gTraceFlags to print the corresponding traces with DbgPrint.
//  Use a kernel debugger or DebugView to see the output.
//

#define MFDBG_TRACE_ROUTINES    0x00000001  // Routine entry
#define MFDBG_TRACE_OPERATIONS  0x00000002  // Individual I/O operations

#if DBG
ULONG gTraceFlags = MFDBG_TRACE_ROUTINES;
#else
ULONG gTraceFlags = 0;
#endif

#define MF_DBG_PRINT( _dbgLevel, _string )          \
    (FlagOn( gTraceFlags, (_dbgLevel) ) ?           \
        DbgPrint _string :                          \
        ((int)0))

//
//  Function prototypes
//
//  DriverEntry must be extern "C" because the system calls it by its C name.
//  The callbacks are declared extern "C" as well, because #pragma alloc_text
//  can only be applied to functions with C linkage.
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

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreOperation (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    );

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostOperation (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
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
//  Operation registration
//
//  Move the entries you need out of the #if 0 block, or enable the block.
//  You can also use separate pre/post callbacks for each operation.
//

CONST FLT_OPERATION_REGISTRATION Callbacks[] = {

    { IRP_MJ_CREATE,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

#if 0 // TODO: Enable only the operations you need

    { IRP_MJ_CREATE_NAMED_PIPE,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_CLOSE,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_READ,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_WRITE,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_QUERY_INFORMATION,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_SET_INFORMATION,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_QUERY_EA,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_SET_EA,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_FLUSH_BUFFERS,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_QUERY_VOLUME_INFORMATION,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_SET_VOLUME_INFORMATION,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_DIRECTORY_CONTROL,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_FILE_SYSTEM_CONTROL,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_DEVICE_CONTROL,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_INTERNAL_DEVICE_CONTROL,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    //  A post-operation callback cannot be registered for IRP_MJ_SHUTDOWN
    { IRP_MJ_SHUTDOWN,
      0,
      $safeprojectname$PreOperation,
      nullptr },

    { IRP_MJ_LOCK_CONTROL,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_CLEANUP,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_CREATE_MAILSLOT,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_QUERY_SECURITY,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_SET_SECURITY,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_QUERY_QUOTA,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_SET_QUOTA,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_PNP,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_ACQUIRE_FOR_SECTION_SYNCHRONIZATION,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_RELEASE_FOR_SECTION_SYNCHRONIZATION,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_ACQUIRE_FOR_MOD_WRITE,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_RELEASE_FOR_MOD_WRITE,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_ACQUIRE_FOR_CC_FLUSH,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_RELEASE_FOR_CC_FLUSH,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_FAST_IO_CHECK_IF_POSSIBLE,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_NETWORK_QUERY_OPEN,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_MDL_READ,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_MDL_READ_COMPLETE,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_PREPARE_MDL_WRITE,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_MDL_WRITE_COMPLETE,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_VOLUME_MOUNT,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

    { IRP_MJ_VOLUME_DISMOUNT,
      0,
      $safeprojectname$PreOperation,
      $safeprojectname$PostOperation },

#endif // TODO

    { IRP_MJ_OPERATION_END }
};

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


/*************************************************************************
    Mini-filter callback routines
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreOperation (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for the registered operations.
    Called before the request is passed to the file system.

Arguments:

    Data - Callback data for this I/O operation.

    FltObjects - Pointer to the objects related to this operation
                 (volume, instance, and file object).

    CompletionContext - A context to pass to the post-operation callback
                        can be set here.

Return Value:

    FLT_PREOP_SUCCESS_WITH_CALLBACK - Continue processing and call the post-operation callback.
    FLT_PREOP_SUCCESS_NO_CALLBACK   - Continue processing without calling the post-operation callback.
    FLT_PREOP_COMPLETE              - Complete the operation here (set Data->IoStatus).
    See the FLT_PREOP_CALLBACK_STATUS documentation for other values.

--*/
{
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreOperation: MajorFunction=%u\n",
                   Data->Iopb->MajorFunction) );

    //
    //  TODO: Implement pre-operation processing here.
    //        Example: use FltGetFileNameInformation to get the file name.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostOperation (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for the registered operations.
    Called after the file system has completed the request.

    Note: This routine can be called at DISPATCH_LEVEL.
          Do not access pageable code or memory.
          Use FltDoCompletionProcessingWhenSafe if processing must be done
          at PASSIVE_LEVEL.

Arguments:

    Data - Callback data for this I/O operation.

    FltObjects - Pointer to the objects related to this operation.

    CompletionContext - The context set by the pre-operation callback.

    Flags - If FLTFL_POST_OPERATION_DRAINING is set, the instance is being
            torn down; do only minimal post-processing.

Return Value:

    FLT_POSTOP_FINISHED_PROCESSING - Post-processing is complete.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostOperation: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}
