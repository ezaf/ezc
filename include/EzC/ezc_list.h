/*  ezc_list.h
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

#ifndef EZC_LIST_H
#define EZC_LIST_H

/** @file       ezc_list.h
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#ifdef __cplusplus
extern C
{
#endif

#include <stddef.h>



/** @brief      Lorem ipsum
 *  @details    Lorem ipsum
 */
typedef struct ezc_list
{
    void *data;
    struct ezc_list *next;
}
ezc_list;



/** @brief      Lorem ipsum
 *  @details    etc... must be NULL-terminated, data can = NULL etc...
 *  @param      data    Lorem ipsum
 *  @param      ...     Lorem ipsum
 */
ezc_list* ezc_list_new(void *data, ...);



ezc_list* ezc_list_copy(ezc_list *orig);



void ezc_list_delete(ezc_list *self);



size_t ezc_list_length(ezc_list *self);



void ezc_list_push(ezc_list *self, char const *mode, ...);



void* ezc_list_pop(ezc_list *self, char const *mode, ...);



void* ezc_list_get(ezc_list *self, char const *mode, ...);



/* Rather than have a bunch of functions with crazy-long names, there's going
 * to be only one function of each category with a mode parameter string.

void ezc_list_push_front(ezc_list *list, void *data);
void ezc_list_push_back(ezc_list *list, void *data);
void ezc_list_push_n(ezc_list *list, void *data, size_t n);
void ezc_list_push_rel(ezc_list *list, void *data, void *ref, long offset);
void ezc_list_cat(ezc_list *listA, ezc_list *listB);

void* ezc_list_pop_front(ezc_list *list);
void* ezc_list_pop_back(ezc_list *list);
void* ezc_list_pop_n(ezc_list *list, size_t n);
void? ezc_list_remove(ezc_list *list, void *data);

void* ezc_list_front(ezc_list *list);
void* ezc_list_back(ezc_list *list);
void* ezc_list_n(ezc_list *list, size_t n);
*/



#ifdef __cplusplus
}
#endif

#endif /* EZC_LIST_H */
