/*++

Module Name:

    Callbacks.cpp

Abstract:

    The operation registration table and the pre/post-operation callbacks of
    the mini-filter. Pre-operation callbacks are invoked before a request is
    passed to the file system; post-operation callbacks are invoked after the
    file system has completed it.

Environment:

    Kernel mode (C++)

--*/

#include "$safeprojectname$.h"
#include "Callbacks.h"

//
//  Operation registration
//
//  Move the entries you need out of the #if 0 block, or enable the block.
//  Every entry already has its own pre/post-operation callback below.
//

CONST FLT_OPERATION_REGISTRATION Callbacks[] = {

    { IRP_MJ_CREATE,
      0,
      $safeprojectname$PreCreateCallback,
      $safeprojectname$PostCreateCallback },

#if 0 // TODO: Enable only the operations you need

    { IRP_MJ_CREATE_NAMED_PIPE,
      0,
      $safeprojectname$PreCreateNamedPipeCallback,
      $safeprojectname$PostCreateNamedPipeCallback },

    { IRP_MJ_CLOSE,
      0,
      $safeprojectname$PreCloseCallback,
      $safeprojectname$PostCloseCallback },

    { IRP_MJ_READ,
      0,
      $safeprojectname$PreReadCallback,
      $safeprojectname$PostReadCallback },

    { IRP_MJ_WRITE,
      0,
      $safeprojectname$PreWriteCallback,
      $safeprojectname$PostWriteCallback },

    { IRP_MJ_QUERY_INFORMATION,
      0,
      $safeprojectname$PreQueryInformationCallback,
      $safeprojectname$PostQueryInformationCallback },

    { IRP_MJ_SET_INFORMATION,
      0,
      $safeprojectname$PreSetInformationCallback,
      $safeprojectname$PostSetInformationCallback },

    { IRP_MJ_QUERY_EA,
      0,
      $safeprojectname$PreQueryEaCallback,
      $safeprojectname$PostQueryEaCallback },

    { IRP_MJ_SET_EA,
      0,
      $safeprojectname$PreSetEaCallback,
      $safeprojectname$PostSetEaCallback },

    { IRP_MJ_FLUSH_BUFFERS,
      0,
      $safeprojectname$PreFlushBuffersCallback,
      $safeprojectname$PostFlushBuffersCallback },

    { IRP_MJ_QUERY_VOLUME_INFORMATION,
      0,
      $safeprojectname$PreQueryVolumeInformationCallback,
      $safeprojectname$PostQueryVolumeInformationCallback },

    { IRP_MJ_SET_VOLUME_INFORMATION,
      0,
      $safeprojectname$PreSetVolumeInformationCallback,
      $safeprojectname$PostSetVolumeInformationCallback },

    { IRP_MJ_DIRECTORY_CONTROL,
      0,
      $safeprojectname$PreDirectoryControlCallback,
      $safeprojectname$PostDirectoryControlCallback },

    { IRP_MJ_FILE_SYSTEM_CONTROL,
      0,
      $safeprojectname$PreFileSystemControlCallback,
      $safeprojectname$PostFileSystemControlCallback },

    { IRP_MJ_DEVICE_CONTROL,
      0,
      $safeprojectname$PreDeviceControlCallback,
      $safeprojectname$PostDeviceControlCallback },

    { IRP_MJ_INTERNAL_DEVICE_CONTROL,
      0,
      $safeprojectname$PreInternalDeviceControlCallback,
      $safeprojectname$PostInternalDeviceControlCallback },

    //  A post-operation callback cannot be registered for IRP_MJ_SHUTDOWN
    { IRP_MJ_SHUTDOWN,
      0,
      $safeprojectname$PreShutdownCallback,
      nullptr },

    { IRP_MJ_LOCK_CONTROL,
      0,
      $safeprojectname$PreLockControlCallback,
      $safeprojectname$PostLockControlCallback },

    { IRP_MJ_CLEANUP,
      0,
      $safeprojectname$PreCleanupCallback,
      $safeprojectname$PostCleanupCallback },

    { IRP_MJ_CREATE_MAILSLOT,
      0,
      $safeprojectname$PreCreateMailslotCallback,
      $safeprojectname$PostCreateMailslotCallback },

    { IRP_MJ_QUERY_SECURITY,
      0,
      $safeprojectname$PreQuerySecurityCallback,
      $safeprojectname$PostQuerySecurityCallback },

    { IRP_MJ_SET_SECURITY,
      0,
      $safeprojectname$PreSetSecurityCallback,
      $safeprojectname$PostSetSecurityCallback },

    { IRP_MJ_QUERY_QUOTA,
      0,
      $safeprojectname$PreQueryQuotaCallback,
      $safeprojectname$PostQueryQuotaCallback },

    { IRP_MJ_SET_QUOTA,
      0,
      $safeprojectname$PreSetQuotaCallback,
      $safeprojectname$PostSetQuotaCallback },

    { IRP_MJ_PNP,
      0,
      $safeprojectname$PrePnpCallback,
      $safeprojectname$PostPnpCallback },

    { IRP_MJ_ACQUIRE_FOR_SECTION_SYNCHRONIZATION,
      0,
      $safeprojectname$PreAcquireForSectionSynchronizationCallback,
      $safeprojectname$PostAcquireForSectionSynchronizationCallback },

    { IRP_MJ_RELEASE_FOR_SECTION_SYNCHRONIZATION,
      0,
      $safeprojectname$PreReleaseForSectionSynchronizationCallback,
      $safeprojectname$PostReleaseForSectionSynchronizationCallback },

    { IRP_MJ_ACQUIRE_FOR_MOD_WRITE,
      0,
      $safeprojectname$PreAcquireForModWriteCallback,
      $safeprojectname$PostAcquireForModWriteCallback },

    { IRP_MJ_RELEASE_FOR_MOD_WRITE,
      0,
      $safeprojectname$PreReleaseForModWriteCallback,
      $safeprojectname$PostReleaseForModWriteCallback },

    { IRP_MJ_ACQUIRE_FOR_CC_FLUSH,
      0,
      $safeprojectname$PreAcquireForCcFlushCallback,
      $safeprojectname$PostAcquireForCcFlushCallback },

    { IRP_MJ_RELEASE_FOR_CC_FLUSH,
      0,
      $safeprojectname$PreReleaseForCcFlushCallback,
      $safeprojectname$PostReleaseForCcFlushCallback },

    { IRP_MJ_FAST_IO_CHECK_IF_POSSIBLE,
      0,
      $safeprojectname$PreFastIoCheckIfPossibleCallback,
      $safeprojectname$PostFastIoCheckIfPossibleCallback },

    { IRP_MJ_NETWORK_QUERY_OPEN,
      0,
      $safeprojectname$PreNetworkQueryOpenCallback,
      $safeprojectname$PostNetworkQueryOpenCallback },

    { IRP_MJ_MDL_READ,
      0,
      $safeprojectname$PreMdlReadCallback,
      $safeprojectname$PostMdlReadCallback },

    { IRP_MJ_MDL_READ_COMPLETE,
      0,
      $safeprojectname$PreMdlReadCompleteCallback,
      $safeprojectname$PostMdlReadCompleteCallback },

    { IRP_MJ_PREPARE_MDL_WRITE,
      0,
      $safeprojectname$PrePrepareMdlWriteCallback,
      $safeprojectname$PostPrepareMdlWriteCallback },

    { IRP_MJ_MDL_WRITE_COMPLETE,
      0,
      $safeprojectname$PreMdlWriteCompleteCallback,
      $safeprojectname$PostMdlWriteCompleteCallback },

    { IRP_MJ_VOLUME_MOUNT,
      0,
      $safeprojectname$PreVolumeMountCallback,
      $safeprojectname$PostVolumeMountCallback },

    { IRP_MJ_VOLUME_DISMOUNT,
      0,
      $safeprojectname$PreVolumeDismountCallback,
      $safeprojectname$PostVolumeDismountCallback },

#endif // TODO

    { IRP_MJ_OPERATION_END }
};


/*************************************************************************
    IRP_MJ_CREATE
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreCreateCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_CREATE.
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
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreCreateCallback: Entered\n") );

    //
    //  TODO: Implement pre-create processing here.
    //        Example: use FltGetFileNameInformation to get the file name.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostCreateCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_CREATE.
    Called after the file system has completed the request.

    Note: Post-operation callbacks can be called at DISPATCH_LEVEL.
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
                  ("$safeprojectname$!$safeprojectname$PostCreateCallback: Entered\n") );

    //
    //  TODO: Implement post-create processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_CREATE_NAMED_PIPE
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreCreateNamedPipeCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_CREATE_NAMED_PIPE.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreCreateNamedPipeCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostCreateNamedPipeCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_CREATE_NAMED_PIPE.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostCreateNamedPipeCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_CLOSE
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreCloseCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_CLOSE.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreCloseCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostCloseCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_CLOSE.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostCloseCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_READ
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreReadCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_READ.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreReadCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostReadCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_READ.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostReadCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_WRITE
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreWriteCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_WRITE.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreWriteCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostWriteCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_WRITE.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostWriteCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_QUERY_INFORMATION
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreQueryInformationCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_QUERY_INFORMATION.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreQueryInformationCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostQueryInformationCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_QUERY_INFORMATION.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostQueryInformationCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_SET_INFORMATION
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreSetInformationCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_SET_INFORMATION.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreSetInformationCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostSetInformationCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_SET_INFORMATION.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostSetInformationCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_QUERY_EA
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreQueryEaCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_QUERY_EA.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreQueryEaCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostQueryEaCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_QUERY_EA.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostQueryEaCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_SET_EA
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreSetEaCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_SET_EA.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreSetEaCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostSetEaCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_SET_EA.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostSetEaCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_FLUSH_BUFFERS
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreFlushBuffersCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_FLUSH_BUFFERS.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreFlushBuffersCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostFlushBuffersCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_FLUSH_BUFFERS.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostFlushBuffersCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_QUERY_VOLUME_INFORMATION
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreQueryVolumeInformationCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_QUERY_VOLUME_INFORMATION.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreQueryVolumeInformationCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostQueryVolumeInformationCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_QUERY_VOLUME_INFORMATION.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostQueryVolumeInformationCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_SET_VOLUME_INFORMATION
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreSetVolumeInformationCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_SET_VOLUME_INFORMATION.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreSetVolumeInformationCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostSetVolumeInformationCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_SET_VOLUME_INFORMATION.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostSetVolumeInformationCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_DIRECTORY_CONTROL
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreDirectoryControlCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_DIRECTORY_CONTROL.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreDirectoryControlCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostDirectoryControlCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_DIRECTORY_CONTROL.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostDirectoryControlCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_FILE_SYSTEM_CONTROL
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreFileSystemControlCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_FILE_SYSTEM_CONTROL.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreFileSystemControlCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostFileSystemControlCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_FILE_SYSTEM_CONTROL.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostFileSystemControlCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_DEVICE_CONTROL
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreDeviceControlCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_DEVICE_CONTROL.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreDeviceControlCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostDeviceControlCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_DEVICE_CONTROL.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostDeviceControlCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_INTERNAL_DEVICE_CONTROL
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreInternalDeviceControlCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_INTERNAL_DEVICE_CONTROL.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreInternalDeviceControlCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostInternalDeviceControlCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_INTERNAL_DEVICE_CONTROL.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostInternalDeviceControlCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_SHUTDOWN
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreShutdownCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_SHUTDOWN.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

    No post-operation callback can be registered for this operation,
    so FLT_PREOP_SUCCESS_WITH_CALLBACK must not be returned.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreShutdownCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_NO_CALLBACK;
}


/*************************************************************************
    IRP_MJ_LOCK_CONTROL
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreLockControlCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_LOCK_CONTROL.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreLockControlCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostLockControlCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_LOCK_CONTROL.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostLockControlCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_CLEANUP
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreCleanupCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_CLEANUP.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreCleanupCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostCleanupCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_CLEANUP.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostCleanupCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_CREATE_MAILSLOT
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreCreateMailslotCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_CREATE_MAILSLOT.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreCreateMailslotCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostCreateMailslotCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_CREATE_MAILSLOT.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostCreateMailslotCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_QUERY_SECURITY
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreQuerySecurityCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_QUERY_SECURITY.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreQuerySecurityCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostQuerySecurityCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_QUERY_SECURITY.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostQuerySecurityCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_SET_SECURITY
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreSetSecurityCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_SET_SECURITY.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreSetSecurityCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostSetSecurityCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_SET_SECURITY.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostSetSecurityCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_QUERY_QUOTA
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreQueryQuotaCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_QUERY_QUOTA.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreQueryQuotaCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostQueryQuotaCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_QUERY_QUOTA.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostQueryQuotaCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_SET_QUOTA
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreSetQuotaCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_SET_QUOTA.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreSetQuotaCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostSetQuotaCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_SET_QUOTA.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostSetQuotaCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_PNP
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PrePnpCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_PNP.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PrePnpCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostPnpCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_PNP.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostPnpCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_ACQUIRE_FOR_SECTION_SYNCHRONIZATION
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreAcquireForSectionSynchronizationCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_ACQUIRE_FOR_SECTION_SYNCHRONIZATION.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreAcquireForSectionSynchronizationCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostAcquireForSectionSynchronizationCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_ACQUIRE_FOR_SECTION_SYNCHRONIZATION.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostAcquireForSectionSynchronizationCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_RELEASE_FOR_SECTION_SYNCHRONIZATION
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreReleaseForSectionSynchronizationCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_RELEASE_FOR_SECTION_SYNCHRONIZATION.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreReleaseForSectionSynchronizationCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostReleaseForSectionSynchronizationCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_RELEASE_FOR_SECTION_SYNCHRONIZATION.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostReleaseForSectionSynchronizationCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_ACQUIRE_FOR_MOD_WRITE
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreAcquireForModWriteCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_ACQUIRE_FOR_MOD_WRITE.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreAcquireForModWriteCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostAcquireForModWriteCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_ACQUIRE_FOR_MOD_WRITE.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostAcquireForModWriteCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_RELEASE_FOR_MOD_WRITE
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreReleaseForModWriteCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_RELEASE_FOR_MOD_WRITE.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreReleaseForModWriteCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostReleaseForModWriteCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_RELEASE_FOR_MOD_WRITE.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostReleaseForModWriteCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_ACQUIRE_FOR_CC_FLUSH
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreAcquireForCcFlushCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_ACQUIRE_FOR_CC_FLUSH.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreAcquireForCcFlushCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostAcquireForCcFlushCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_ACQUIRE_FOR_CC_FLUSH.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostAcquireForCcFlushCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_RELEASE_FOR_CC_FLUSH
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreReleaseForCcFlushCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_RELEASE_FOR_CC_FLUSH.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreReleaseForCcFlushCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostReleaseForCcFlushCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_RELEASE_FOR_CC_FLUSH.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostReleaseForCcFlushCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_FAST_IO_CHECK_IF_POSSIBLE
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreFastIoCheckIfPossibleCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_FAST_IO_CHECK_IF_POSSIBLE.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreFastIoCheckIfPossibleCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostFastIoCheckIfPossibleCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_FAST_IO_CHECK_IF_POSSIBLE.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostFastIoCheckIfPossibleCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_NETWORK_QUERY_OPEN
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreNetworkQueryOpenCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_NETWORK_QUERY_OPEN.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreNetworkQueryOpenCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostNetworkQueryOpenCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_NETWORK_QUERY_OPEN.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostNetworkQueryOpenCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_MDL_READ
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreMdlReadCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_MDL_READ.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreMdlReadCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostMdlReadCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_MDL_READ.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostMdlReadCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_MDL_READ_COMPLETE
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreMdlReadCompleteCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_MDL_READ_COMPLETE.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreMdlReadCompleteCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostMdlReadCompleteCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_MDL_READ_COMPLETE.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostMdlReadCompleteCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_PREPARE_MDL_WRITE
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PrePrepareMdlWriteCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_PREPARE_MDL_WRITE.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PrePrepareMdlWriteCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostPrepareMdlWriteCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_PREPARE_MDL_WRITE.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostPrepareMdlWriteCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_MDL_WRITE_COMPLETE
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreMdlWriteCompleteCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_MDL_WRITE_COMPLETE.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreMdlWriteCompleteCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostMdlWriteCompleteCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_MDL_WRITE_COMPLETE.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostMdlWriteCompleteCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_VOLUME_MOUNT
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreVolumeMountCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_VOLUME_MOUNT.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreVolumeMountCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostVolumeMountCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_VOLUME_MOUNT.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostVolumeMountCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}


/*************************************************************************
    IRP_MJ_VOLUME_DISMOUNT
*************************************************************************/

FLT_PREOP_CALLBACK_STATUS
$safeprojectname$PreVolumeDismountCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
    )
/*++

Routine Description:

    Pre-operation callback for IRP_MJ_VOLUME_DISMOUNT.
    See $safeprojectname$PreCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PreVolumeDismountCallback: Entered\n") );

    //
    //  TODO: Implement pre-operation processing here.
    //

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

FLT_POSTOP_CALLBACK_STATUS
$safeprojectname$PostVolumeDismountCallback (
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
    )
/*++

Routine Description:

    Post-operation callback for IRP_MJ_VOLUME_DISMOUNT.
    See $safeprojectname$PostCreateCallback for the arguments and return values.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    UNREFERENCED_PARAMETER( Flags );

    MF_DBG_PRINT( MFDBG_TRACE_OPERATIONS,
                  ("$safeprojectname$!$safeprojectname$PostVolumeDismountCallback: Entered\n") );

    //
    //  TODO: Implement post-operation processing here.
    //

    return FLT_POSTOP_FINISHED_PROCESSING;
}
