/*++

Module Name:

    Communication.h

Abstract:

    Declarations of the filter communication port used to exchange messages
    with user-mode applications.

Environment:

    Kernel mode (C++)

--*/

#pragma once

#include <fltKernel.h>

EXTERN_C_START

//
//  Communication port creation and closing
//

NTSTATUS
$safeprojectname$CreateCommunicationPort (
    _In_ PFLT_FILTER Filter
    );

VOID
$safeprojectname$CloseCommunicationPort (
    VOID
    );

//
//  Communication port callbacks
//

NTSTATUS
$safeprojectname$PortConnect (
    _In_ PFLT_PORT ClientPort,
    _In_opt_ PVOID ServerPortCookie,
    _In_reads_bytes_opt_(SizeOfContext) PVOID ConnectionContext,
    _In_ ULONG SizeOfContext,
    _Outptr_result_maybenull_ PVOID *ConnectionCookie
    );

VOID
$safeprojectname$PortDisconnect (
    _In_opt_ PVOID ConnectionCookie
    );

NTSTATUS
$safeprojectname$PortMessage (
    _In_opt_ PVOID ConnectionCookie,
    _In_reads_bytes_opt_(InputBufferSize) PVOID InputBuffer,
    _In_ ULONG InputBufferSize,
    _Out_writes_bytes_to_opt_(OutputBufferSize,*ReturnOutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferSize,
    _Out_ PULONG ReturnOutputBufferLength
    );

EXTERN_C_END
