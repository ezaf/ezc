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

#include "EzC/ezc_macro.h"
#include <stdarg.h>
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
 *  @details    Lorem ipsum
 *  @param      ...     Lorem ipsum
 */
#define ezc_list_new(self, ...) \
    (ezc_list_new__((self), ##__VA_ARGS__, NULL))

ezc_list* ezc_list_new__(void const *data, ...);



#define ezc_list_copy(orig) \
    (ezc_list_copy__((orig)))

ezc_list* ezc_list_copy__(ezc_list const *orig);



#define ezc_list_swap(listA, listB) \
    (ezc_list_swap__((listA), (listB)))

void ezc_list_swap__(ezc_list *listA, ezc_list *listB);



#define ezc_list_join(self, ...) \
    (ezc_list_join__((self), ##__VA_ARGS__, NULL))

void ezc_list_join__(ezc_list *self, ...);



#define ezc_list_cat(self, ...) \
    (ezc_list_join__((self), SST_MAP_LIST(ezc_list_copy, ##__VA_ARGS__), NULL))



#define ezc_list_delete(self, ...) \
    (ezc_list_delete__((self), ##__VA_ARGS__, NULL), \
     SST_MAP(EZC_TO_ZERO, (self), ##__VA_ARGS__))

void ezc_list_delete__(ezc_list *self, ...);



/* long used so overflow is more obvious */
#define ezc_list_length(self) \
    (ezc_list_length__((self)))

long ezc_list_length__(ezc_list const *self);



#define ezc_list_map(self, fn, ...) \
    do { ezc_list *iter = (self); while (iter != NULL) { \
        (fn)(iter->data, ##__VA_ARGS__); iter = iter->next; \
    } } while(0)



#define ezc_list_get_at(self, n) \
    (ezc_list_get_at__((self), (n)))

ezc_list* ezc_list_get_at__(ezc_list const *self, long n);



#define ezc_list_get_match(self, index_out, data) \
    (ezc_list_get_match_fn__((self), (index_out), NULL, (data)))



#define ezc_list_get_match_fn(self, index_out, neq, data) \
    (ezc_list_get_match_fn__((self), (index_out), (neq), (data)))

ezc_list* ezc_list_get_match_fn__(ezc_list const *self, long *index_out,
                                  int (*neq)(void const *, void const *),
                                  void const *data);



#define ezc_list_push_at(self, n, ...) \
    (ezc_list_push_at__((self), (n), ##__VA_ARGS__, NULL))

void ezc_list_push_at__(ezc_list *self, long n, ...);



#define ezc_list_push_front(self, ...) \
    (ezc_list_push_at__((self), 0, ##__VA_ARGS__, NULL))



#define ezc_list_push_back(self, ...) \
    (ezc_list_join__((self), SST_MAP_LIST(ezc_list_new, ##__VA_ARGS__), NULL))



#define ezc_list_pop_at(self, n) \
    (ezc_list_pop_at__(&(self), (n)))

ezc_list* ezc_list_pop_at__(ezc_list **self, long n);



#define ezc_list_pop_front(self) \
    (ezc_list_pop_at__(&(self), 0))



#define ezc_list_pop_back(self) \
    (ezc_list_pop_at__(&(self), -1))



#define ezc_list_pop_match(self, index_out, data) \
    (ezc_list_pop_match_fn__((self), (index_out), NULL, (data)))



#define ezc_list_pop_match_fn(self, index_out, neq, data, ...) \
    (ezc_list_pop_match_fn__((self), (index_out), (neq), (data)))

ezc_list* ezc_list_pop_match_fn__(ezc_list const *self, long *index_out,
                                  int (*neq)(void const *, void const *),
                                  void const *data);



/* TODO: document that macro implementations must use the actual functions */
#define ezc_list_erase_at(self, n) \
    (ezc_list_delete__(ezc_list_pop_at__(&(self), (n)), NULL))

#define ezc_list_erase_front(self) \
    (ezc_list_delete__(ezc_list_pop_at__(&(self), 0), NULL))

#define ezc_list_erase_back(self) \
    (ezc_list_delete__(ezc_list_pop_at__(&(self), -1), NULL))

#define ezc_list_erase_match(self, index_out, data) \
    (ezc_list_delete__( \
            ezc_list_pop_match_fn__((self), (index_out), NULL, (data)), NULL))

#define ezc_list_erase_match_fn(self, index_out, neq, data, ...) \
    (ezc_list_delete__( \
            ezc_list_pop_match_fn__((self), (index_out), (neq), (data)), NULL))



#ifdef __cplusplus
}
#endif

#endif /* EZC_LIST_H */
