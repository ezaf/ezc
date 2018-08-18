/*  ezc_callback.h
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

#ifndef EZC_CALLBACK_H
#define EZC_CALLBACK_H

/** @file       ezc_callback.h
 *  @brief      Callback/Observer interface.
 *  @details    Can be made into the observer design pattern when coupled with
 *              `ezc_list`.
 */

#ifdef __cplusplus
extern C
{
#endif



/** @brief      Callback object.
 *  @details    This is an opaque `struct`. Please use the provided interface
 *              to interact with it.
 */
typedef struct ezc_callback ezc_callback;



/** @brief      Create a new callback object.
 *  @details    As of now there are no "setter" methods that allow you to
 *              change this object's values later. (Instead, delete and
 *              recreate the object instead.)
 *  @param      fn      Pointer to a function. This function must accept one
 *                      argument, a pointer to the same type as `arg`.
 *  @param      arg     `void *` Pointer to data that you want passed to `fn`.
 *  @returns    Pointer to newly allocated callback object.
 */
ezc_callback* ezc_callback_new(void (*fn)(void*), void *arg);



/** @brief      Free given callback object.
 *  @param      self    `ezc_callback *` Pointer to a callback object.
 */
void ezc_callback_delete(ezc_callback *self);



/** @brief      Perform a callback.
 *  @param      self    `ezc_callback const *` Pointer to a callback object.
 */
void ezc_callback_call(ezc_callback const *self);



#ifdef __cplusplus
}
#endif

#endif /* EZC_CALLBACK_H */
