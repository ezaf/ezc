/** @file       ezc_log.h
 *  @brief      Prioritize your log messages.
 *  
 *  <!-------------------------------------------------------------------------
 *  Copyright (c) 2018 Kirk Lange <github.com/kirklange>
 *  
 *  This software is provided 'as-is', without any express or implied
 *  warranty.  In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *  3. This notice may not be removed or altered from any source distribution.
 *  -------------------------------------------------------------------------->
 */

#if 0

#ifndef EZC_LOG_H
#define EZC_LOG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>



/* TODO: Move this to its own *.h file `ezc_assert` */
#ifndef ezc_assert
#define ezc_assert(expA, op, expB) \
{ \
    if (!( expA op expB )) \
        fprintf(stdout, "FAIL:   !( " #expA " " #op " " #expB " )\n"); \
}
#endif /* ezc_assert */

/* TODO: Placeholder. Replace with OOP-like file I/O system? */
#ifndef EZC_LOG_OUT
#define EZC_LOG_OUT stdout
#endif

/*
#ifndef EZC_LOG
#define EZC_LOG(severity, message, ...) \
    ezutil_log(severity, __func__, message, __VA_ARGS__);
#endif
*/

/* ezdebug_log will only print messages at least as severe as this */
#ifndef EZC_LOG_VERBOSITY
#define EZC_LOG_VERBOSITY DEBUG
#endif



typedef enum ezc_log_t
{
    FATAL='X', MAJOR='M', MINOR='m', DEBUG='d'
} ezc_log_t;

/* ezc_log_t Reference
 * 
 * FATAL
 *   - So bad that either a crash is imminent or the program will not run
 *   - e.g. failed to initialize SDL, could not get display mode
 *
 * MAJOR
 *   - Bad enough that some of the program's functionality is compromised
 *   - e.g. missing textures, cannot fetch user input
 *
 * MINOR
 *   - Still an error but not that bad of one
 *   - e.g. had to skip a frame, using default values due to bad user input
 *
 * DEBUG
 *   - Miscellaneous debugging messages; not necessarily errors
 *   - e.g. input log, application state log, etc
 *
 */



void            ezc_log(ezc_log_t severity, const char *callee,
                        const char *message, ...);



#ifdef __cplusplus
}
#endif

#endif /* EZC_LOG_H */

#endif
