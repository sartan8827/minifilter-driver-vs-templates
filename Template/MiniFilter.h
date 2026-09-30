/*++

Module Name:

    $safeprojectname$.h

Abstract:

    Common definitions shared by the source files of the mini-filter driver.

Environment:

    Kernel mode (C++)

--*/

#pragma once

#include <fltKernel.h>
#include <dontuse.h>

#pragma prefast(disable:__WARNING_ENCODE_MEMBER_FUNCTION_POINTER, "Not valid for kernel mode drivers")

//
//  Debug output
//
//  Set bits in gTraceFlags to print the corresponding traces with DbgPrint.
//  Use a kernel debugger or DebugView to see the output.
//

#define MFDBG_TRACE_ROUTINES    0x00000001  // Routine entry
#define MFDBG_TRACE_OPERATIONS  0x00000002  // Individual I/O operations

extern ULONG gTraceFlags;

#define MF_DBG_PRINT( _dbgLevel, _string )          \
    (FlagOn( gTraceFlags, (_dbgLevel) ) ?           \
        DbgPrint _string :                          \
        ((int)0))
