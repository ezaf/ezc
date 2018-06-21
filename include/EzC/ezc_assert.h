/** @file       ezc_assert.h
 *  @brief      Macro for assertions when debugging.
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

#ifndef EZC_ASSERT_H
#define EZC_ASSERT_H

#ifdef __cplusplus
extern C
{
#endif



/** @brief      Macor for assertions when debugging.
 *  @details    Like normal assertions, `EZC_ASSERT` expands to an expression
 *              and can be toggled via `NDEBUG`. `EZC_ASSERT` will attempt to
 *              write to both `stderr` and a `*.assert` text file.
 *  @param      expr    Expression to test. As is standard, the assertion is
 *                      triggered when the expression evaluates to `0`.
 */
#ifdef NDEBUG
#define EZC_ASSERT(expr) ((void)0)
#else
#define EZC_ASSERT(expr) \
    ((void) ((expr) || (ezc_assert(expr, __FILE__, __LINE__), 0)))
#endif



/* Use the macro instead! */
void ezc_assert(char const *expr, char const *file, unsigned int line);



#ifdef __cplusplus
}
#endif

#endif /* EZC_ASSERT_H */
