/** @file       ezc_error.h
 *  @brief      Prioritize and write to file your error and debugging messages.
 *  
 *  <!-------------------------------------------------------------------------
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
 *  -------------------------------------------------------------------------->
 */

#ifndef EZC_ERROR_H
#define EZC_ERROR_H

#ifdef __cplusplus
extern C
{
#endif



/** @brief      Severity of the message.
 *  @details    Describes what behavior should ensue after a message of such
 *              severity is added.
 */
typedef enum ezc_error_t
{
    ABORT,  /** Abort the program after logging this error. */
    ERROR,  /** Continue the program after logging this error. */
    WARN,   /** Continue the program, this is only a warning. */
    INFO    /** Continue the program, this is just diagnostic information. */
}
ezc_error_t;



/** @brief      Add a message to the global log.
 *  @details    This macro accepts variadic arguments `printf` style. Speaking
 *              of printing, messages are echoed upon being added to the log,
 *              either `stdout` or `stderr`, depending on the type.
 *  @param      severity    The message type, indicating whether the program
 *                          should abort or not.
 *              message     The message, followed by variadic arguments just
 *                          like `printf`.
 */
#define EZC_ERROR(severity, message, ...) \
    (ezc_error(__FILE__, __LINE__, severity, message))



/* Use the macro instead! */
void            ezc_error(char const *file, unsigned int line,
                          ezc_error_t severity, char const *message, ...);



/** @brief      Get the most recent message.
 *  @return     The most recent message in the global log. Returns `NULL` if
 *              there have been no messages whatsoever.
 */
char const*     ezc_error_get();


/** @brief      Get the @a n most recent messages.
 *  @param      n       How many of the most recent messages should be
 *                      returned.
 *  @return     The @a n most recent messages in the global log. Returns `NULL`
 *              if there have been no messages whatsoever. Note that it is @a
 *              not an array of C strings that is being returned, but rather
 *              a single C string. Each message is seperated by a standardized
 *              message header line.
 */
char const*     ezc_error_getn(size_t n_recent);



/** @brief      Write the global log to a file.
 *  @details    The file name is `YYYY-MM-DD-HH-MM-SS.error`, located in the
 *              same directory as the executable. If this file somehow already
 *              exists, it is overwritten.
 */
void            ezc_error_fwrite();



/** @brief      Clear the global log.
 */
void            ezc_error_clear();



#ifdef __cplusplus
}
#endif

#endif /* EZC_ERROR_H */
