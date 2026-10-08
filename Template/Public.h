/*++

Module Name:

    Public.h

Abstract:

    Definitions shared between the mini-filter driver and user-mode
    applications: the communication port name, the message commands, and the
    structures exchanged through the filter communication port.

    User-mode applications include <windows.h> and <fltUser.h> before this
    header and link with FltLib.lib.

Environment:

    Kernel mode and user mode

--*/

#pragma once

//
//  Communication port name
//
//  User-mode applications connect to the port with
//  FilterConnectCommunicationPort( MF_PORT_NAME, ... ) and send messages
//  with FilterSendMessage.
//

#define MF_PORT_NAME            L"\\$safeprojectname$Port"

//
//  Commands sent from user mode to the mini-filter (FilterSendMessage)
//

typedef enum _MF_COMMAND {

    MfCommandGetVersion = 1,

    //
    //  TODO: Add your own commands here.
    //

} MF_COMMAND;

//
//  Input buffer of FilterSendMessage. Every message starts with the command.
//

typedef struct _MF_COMMAND_MESSAGE {

    MF_COMMAND Command;

} MF_COMMAND_MESSAGE, *PMF_COMMAND_MESSAGE;

//
//  Output buffer of MfCommandGetVersion
//

#define MF_VERSION_MAJOR        1
#define MF_VERSION_MINOR        0

typedef struct _MF_VERSION_INFO {

    ULONG Major;
    ULONG Minor;

} MF_VERSION_INFO, *PMF_VERSION_INFO;
