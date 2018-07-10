/*  ezc_mem.h
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

#ifndef EZC_MEM_H
#define EZC_MEM_H

/** @file       ezc_mem.h
 *  @brief      Memory-related macros, such as allocation and array length
 *              getters.
 */

#ifdef __cplusplus
extern C
{
#endif

#include "EzC/ezc_macro.h"



/** @brief      Get the length of an array.
 *  @details    This works via the `sizeof(array)/sizeof(array[0])` technique.
 *  @param      array   Pointer to an array.
 */
#define EZC_LENGTH(array) (sizeof(array)/sizeof(array[0]))



/** @brief      Allocate memory based on the size of the given pointer.
 *  @details    Does the work of calling `sizeof` for you! This macro does the
 *              `ptr = ...` for you, all you need to do is `EZC_NEW(ptr);`.
 *  @param      ptr     Pointer to which you want memory allocated.
 */
#define EZC_NEW(ptr) ((ptr) = malloc(sizeof *(ptr)))



/** @brief      Allocate memory based on the size of the given pointer while
 *              also zero-initializing it.
 *  @details    `EZC_NEW` details documentation also applies to `EZC_NEW0`.
 *  @param      ptr     Pointer to which you want memory allocated.
 */
#define EZC_NEW0(ptr) ((ptr) = calloc(1, sizeof *(ptr)))


    
/** @brief      Allocate array and zero-initialize it.
 *  @details    `EZC_NEW` details documentation also applies to `EZC_NEWN`.
 *  @param      ptr     Pointer to which you want memory allocated.
 */
#define EZC_NEWN(ptr, n) ((ptr) = calloc((n), sizeof *(ptr)))



/** @brief      Free memory and avoid dangling pointers.
 *  @details    This macro does both the `free` and `ptr = 0` for you! Simply
 *              use `EZC_FREE(ptr);`.
 *  @param      ptr     Pointer that you want set to zero and whose memory it
 *                      was pointing to you want freed.
 *  @param      ...     Optional additional pointers you want to be freed.
 */
#define EZC_FREE(ptr, ...) \
    (SST_MAP(EZC_DO_FREE, ptr, ##__VA_ARGS__), \
     SST_MAP(EZC_TO_ZERO, ptr, ##__VA_ARGS__))




#ifdef __cplusplus
}
#endif

#endif /* EZC_MEM_H */
