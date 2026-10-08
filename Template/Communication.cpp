/*++

Module Name:

    Communication.cpp

Abstract:

    The filter communication port of the mini-filter. User-mode applications
    connect to it with FilterConnectCommunicationPort and send messages with
    FilterSendMessage. The mini-filter can also send messages to the
    connected client with FltSendMessage. The port name and the messages are
    defined in Public.h.

    Only SYSTEM and administrators can connect to the port
    (FltBuildDefaultSecurityDescriptor).

Environment:

    Kernel mode (C++)

--*/

#include "$safeprojectname$.h"
#include "Communication.h"
#include "Public.h"

//
//  Global variables
//
//  gServerPort listens for connections. gClientPort is the connection to
//  the user-mode client and is the port to pass to FltSendMessage.
//

static PFLT_PORT gServerPort = nullptr;
static PFLT_PORT gClientPort = nullptr;

//
//  Assign text sections for each routine
//

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, $safeprojectname$CreateCommunicationPort)
#pragma alloc_text(PAGE, $safeprojectname$CloseCommunicationPort)
#pragma alloc_text(PAGE, $safeprojectname$PortConnect)
#pragma alloc_text(PAGE, $safeprojectname$PortDisconnect)
#pragma alloc_text(PAGE, $safeprojectname$PortMessage)
#endif


/*************************************************************************
    Communication port creation and closing
*************************************************************************/

NTSTATUS
$safeprojectname$CreateCommunicationPort (
    _In_ PFLT_FILTER Filter
    )
/*++

Routine Description:

    Creates the communication server port that user-mode applications
    connect to. Called from DriverEntry after FltRegisterFilter.

Arguments:

    Filter - The filter handle returned by FltRegisterFilter.

Return Value:

    The NTSTATUS result of the creation.

--*/
{
    NTSTATUS status;
    PSECURITY_DESCRIPTOR securityDescriptor;
    OBJECT_ATTRIBUTES objectAttributes;
    UNICODE_STRING portName = RTL_CONSTANT_STRING( MF_PORT_NAME );

    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$CreateCommunicationPort: Entered\n") );

    //
    //  Build a security descriptor that allows only SYSTEM and
    //  administrators to connect to the port.
    //

    status = FltBuildDefaultSecurityDescriptor( &securityDescriptor,
                                                FLT_PORT_ALL_ACCESS );

    if (!NT_SUCCESS( status )) {

        return status;
    }

    InitializeObjectAttributes( &objectAttributes,
                                &portName,
                                OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                                nullptr,
                                securityDescriptor );

    //
    //  Create the server port. MaxConnections is 1, so only one client can
    //  be connected at a time.
    //

    status = FltCreateCommunicationPort( Filter,
                                         &gServerPort,
                                         &objectAttributes,
                                         nullptr,
                                         $safeprojectname$PortConnect,
                                         $safeprojectname$PortDisconnect,
                                         $safeprojectname$PortMessage,
                                         1 );

    //
    //  The security descriptor is no longer needed once the port is created.
    //

    FltFreeSecurityDescriptor( securityDescriptor );

    if (!NT_SUCCESS( status )) {

        MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                      ("$safeprojectname$!$safeprojectname$CreateCommunicationPort: FltCreateCommunicationPort failed, status=0x%08X\n",
                       status) );
        gServerPort = nullptr;
    }

    return status;
}

VOID
$safeprojectname$CloseCommunicationPort (
    VOID
    )
/*++

Routine Description:

    Closes the communication server port so that no new connections are
    accepted. Must be called before FltUnregisterFilter, which disconnects
    the remaining client connection.
    Safe to call even if the port was not created.

--*/
{
    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$CloseCommunicationPort: Entered\n") );

    if (gServerPort != nullptr) {

        FltCloseCommunicationPort( gServerPort );
        gServerPort = nullptr;
    }
}


/*************************************************************************
    Communication port callbacks
*************************************************************************/

NTSTATUS
$safeprojectname$PortConnect (
    _In_ PFLT_PORT ClientPort,
    _In_opt_ PVOID ServerPortCookie,
    _In_reads_bytes_opt_(SizeOfContext) PVOID ConnectionContext,
    _In_ ULONG SizeOfContext,
    _Outptr_result_maybenull_ PVOID *ConnectionCookie
    )
/*++

Routine Description:

    Called when a user-mode application connects to the server port with
    FilterConnectCommunicationPort.

Arguments:

    ClientPort - The client connection port. Pass it to FltSendMessage to
                 send messages to this client.

    ServerPortCookie - The context given to FltCreateCommunicationPort.

    ConnectionContext - The context passed by the client to
                        FilterConnectCommunicationPort.

    SizeOfContext - Size of ConnectionContext in bytes.

    ConnectionCookie - Receives a context that is passed to the disconnect
                       and message callbacks.

Return Value:

    STATUS_SUCCESS - Accept the connection.

--*/
{
    UNREFERENCED_PARAMETER( ServerPortCookie );
    UNREFERENCED_PARAMETER( ConnectionContext );
    UNREFERENCED_PARAMETER( SizeOfContext );

    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$PortConnect: Entered\n") );

    FLT_ASSERT( gClientPort == nullptr );

    //
    //  TODO: Validate ConnectionContext here if the client must identify
    //        itself, and return an error status to refuse the connection.
    //

    gClientPort = ClientPort;
    *ConnectionCookie = nullptr;

    return STATUS_SUCCESS;
}

VOID
$safeprojectname$PortDisconnect (
    _In_opt_ PVOID ConnectionCookie
    )
/*++

Routine Description:

    Called when the client closes its handle to the port, or when the
    mini-filter is being unloaded.

Arguments:

    ConnectionCookie - The context set by the connect callback.

--*/
{
    UNREFERENCED_PARAMETER( ConnectionCookie );

    PAGED_CODE();

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$PortDisconnect: Entered\n") );

    //
    //  Close the client port. FltCloseClientPort sets gClientPort to NULL.
    //

    FltCloseClientPort( gFilterHandle, &gClientPort );
}

NTSTATUS
$safeprojectname$PortMessage (
    _In_opt_ PVOID ConnectionCookie,
    _In_reads_bytes_opt_(InputBufferSize) PVOID InputBuffer,
    _In_ ULONG InputBufferSize,
    _Out_writes_bytes_to_opt_(OutputBufferSize,*ReturnOutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferSize,
    _Out_ PULONG ReturnOutputBufferLength
    )
/*++

Routine Description:

    Called when the client sends a message with FilterSendMessage.
    The commands are defined in Public.h.

    InputBuffer and OutputBuffer are raw user-mode addresses. The Filter
    Manager has probed them, but the client can still free or change the
    memory at any time, so every access must be inside __try/__except and
    values must be copied to locals before they are validated and used.

Arguments:

    ConnectionCookie - The context set by the connect callback.

    InputBuffer - The message sent by the client.

    InputBufferSize - Size of InputBuffer in bytes.

    OutputBuffer - Buffer that receives the reply.

    OutputBufferSize - Size of OutputBuffer in bytes.

    ReturnOutputBufferLength - Receives the number of bytes written to
                               OutputBuffer.

Return Value:

    The NTSTATUS result of the message, returned to FilterSendMessage.

--*/
{
    NTSTATUS status;
    MF_COMMAND command;

    UNREFERENCED_PARAMETER( ConnectionCookie );

    PAGED_CODE();

    *ReturnOutputBufferLength = 0;

    //
    //  Read the command.
    //

    if (InputBuffer == nullptr ||
        InputBufferSize < sizeof( MF_COMMAND_MESSAGE )) {

        return STATUS_INVALID_PARAMETER;
    }

    if (!IS_ALIGNED( InputBuffer, __alignof( MF_COMMAND_MESSAGE ) )) {

        return STATUS_DATATYPE_MISALIGNMENT;
    }

    __try {

        command = static_cast<PMF_COMMAND_MESSAGE>( InputBuffer )->Command;

    } __except (EXCEPTION_EXECUTE_HANDLER) {

        return GetExceptionCode();
    }

    MF_DBG_PRINT( MFDBG_TRACE_ROUTINES,
                  ("$safeprojectname$!$safeprojectname$PortMessage: Entered, Command=%d\n",
                   command) );

    switch (command) {

    case MfCommandGetVersion: {

        if (OutputBuffer == nullptr ||
            OutputBufferSize < sizeof( MF_VERSION_INFO )) {

            status = STATUS_BUFFER_TOO_SMALL;
            break;
        }

        if (!IS_ALIGNED( OutputBuffer, __alignof( MF_VERSION_INFO ) )) {

            status = STATUS_DATATYPE_MISALIGNMENT;
            break;
        }

        __try {

            PMF_VERSION_INFO versionInfo = static_cast<PMF_VERSION_INFO>( OutputBuffer );

            versionInfo->Major = MF_VERSION_MAJOR;
            versionInfo->Minor = MF_VERSION_MINOR;

            *ReturnOutputBufferLength = sizeof( MF_VERSION_INFO );
            status = STATUS_SUCCESS;

        } __except (EXCEPTION_EXECUTE_HANDLER) {

            status = GetExceptionCode();
        }

        break;
    }

    //
    //  TODO: Handle your own commands here.
    //

    default:
        status = STATUS_INVALID_PARAMETER;
        break;
    }

    return status;
}
