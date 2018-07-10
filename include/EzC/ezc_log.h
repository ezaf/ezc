/* ezc_log.h
 *  
 *  Copyright (c) 2018 Kirk Lange <github.com/kirklange>
 *  
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
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
 */

#ifndef EZC_LOG_H
#define EZC_LOG_H

/** @file       ezc_log.h
 *  @brief      Prioritize and write to file your error and debugging messages.
 */

#ifdef __cplusplus
extern C
{
#endif

#include <stdarg.h>
#include <stdio.h>



/**
 *
 */
typedef enum ezc_log_t
{
    EZC_LOG_INFO,
    EZC_LOG_WARN,
    EZC_LOG_ERROR,
    EZC_LOG_FATAL
}
ezc_log_t;



/** @brief      Add message to global log
 *  @details    This macro accepts variadic arguments `printf` style. Messages
 *              are echoed to `stdout` by default. This can be changed via
 *              `ezc_log_echo(FILE *)`.
 *  @param      type        The message type enum. See `ezc_log_t`
 *                          documentation for more info.
 *  @param      message     The message itself. Supports formatting just like
 *                          `printf`.
 *  @param      ...         `printf` style variadic arguments.
 *  @returns    N/A
 */
#define ezc_log(type, message, ...) \
    (ezc_log__(__FILE__, __LINE__, (type), (message), ##__VA_ARGS__))

void ezc_log__(char const *file, long line,
               ezc_log_t type, char const *message, ...);



/** @brief      Set where logs are echoed to
 *  @details    By default, without calling this function, logs are echoed to
 *              `stdout`.
 *  @param      dest        Echo destination. This can be `stdout`, `stderr`,
 *                          or any file of your choosing.
 */
void ezc_log_echo(FILE *dest);



/** @brief      Get most recent message of at least given severity
 *  @details    For example, if the most recent item in the log is of type
 *              `EZC_LOG_WARN`, but `ezc_log_get(EZC_LOG_ERROR)` is called, it
 *              will skip over the warning item and keep stepping back through
 *              the log until an `EZC_LOG_ERROR` item is found.
 *  @param      type        The returned log will be at least as severe as
 *                          the log type specified by this argument.
 *  @return     The most recent message in the global log. Returns `NULL` if
 *              there have been no messages since the beginning of the program
 *              or the most recent `ezc_log_clear()`, or if no message of at
 *              least `type` priority was found.
 */
char const* ezc_log_get(ezc_log_t type);



/** @brief      Write the global log to a file.
 *  @details    The file name is `YYYY-MM-DD-HH-MM-SS.error`, located in the
 *              same directory as the executable. If this file somehow already
 *              exists, it is overwritten. This function <i>does not</i> clear
 *              the log.
 */
void ezc_log_fwrite();



/** @brief      Clear the global log.
 *  @details    Clears absolutely everything from info logs to critical logs.
 */
void ezc_log_clear();



#ifdef __cplusplus
}
#endif

#endif /* EZC_LOG_H */
