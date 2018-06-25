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



/** @brief      Add a message to the global log.
 *  @details    This macro accepts variadic arguments `printf` style. Messages
 *              are echoed upon being added to the log, either `stdout` or
 *              `stderr`, depending on the type.
 *  @param      kind        The message kind string. This works a lot like the
 *                          `mode` parameter of `fopen`; include all the
 *                          relevant characters in this string parameter to
 *                          describe this message's kind.
 *                            - `a` : Abort after logging this error.
 *                            - `c` : Continue the program after logging this
 *                              error. This is the default behavior, so the
 *                              inclusion of `c` in the string is optional.
 *                            - `e` : Error message
 *                            - `i` : Info message
 *                            - `w` : Warning message
 *                          `a` and `c` are mutually exclusive. `e`, `i`, and
 *                          `w` are mutually exclusive. In the case that
 *                          mutually exclusive characters exist in `kind`, a
 *                          warning message is logged and the first mutually
 *                          exclusive character in `kind` overrides any that
 *                          follow.
 *  @param      message     The message itself. Supports formatting like
 *                          `printf`. It is assumed that the length of this
 *                          string is at least a few dozen characters less than
 *                          `INT_MAX`.
 *  @param      ...         `printf` style variadic arguments.
 */
#define EZC_ERROR(kind, message, ...) \
    (ezc_error(__FILE__, __LINE__, kind, message, __VA_ARGS__))



/* Use the macro instead! */
void            ezc_error(char const *file, unsigned int line,
                          char const *kind, char const *message, ...);



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
