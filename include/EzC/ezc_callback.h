/** ezc_callback.h
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
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#ifdef __cplusplus
extern C
{
#endif



typedef struct ezc_callback ezc_callback;



/** @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do
 *              eiusmod tempor incididunt ut labore et dolore magna aliqua.
 *  @param      alpha   Ut enim ad minim veniam, quis nostrud exercitation
 *                      ullamco laboris nisi ut aliquip ex ea commodo
 *                      consequat.
 *  @param      beta    Duis aute irure dolor in reprehenderit in voluptate
 *                      velit esse cillum dolore eu fugiat nulla pariatur.
 *  @return     Excepteur sint occaecat cupidatat non proident, sunt in culpa
 *              qui officia deserunt mollit anim id est laborum.
 */
ezc_callback* ezc_callback_new(void (*fn)(void*), void *arg);



/** @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do
 *              eiusmod tempor incididunt ut labore et dolore magna aliqua.
 *  @param      self    Ut enim ad minim veniam, quis nostrud exercitation
 *                      ullamco laboris nisi ut aliquip ex ea commodo
 *                      consequat.
 *  @returns    N/A
 */
void ezc_callback_delete(ezc_callback *self);



/** @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do
 *              eiusmod tempor incididunt ut labore et dolore magna aliqua.
 *  @param      self    Ut enim ad minim veniam, quis nostrud exercitation
 *                      ullamco laboris nisi ut aliquip ex ea commodo
 *                      consequat.
 *  @returns    N/A
 */
void ezc_callback_call(ezc_callback const *self);



#ifdef __cplusplus
}
#endif

#endif /* EZC_CALLBACK_H */
