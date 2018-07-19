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
 *  @brief      Featureful singly linked list implementation.
 *  @details    The included functions and macros allow for this module to be
 *              used like a stack, queue, or vector. Note to Contributors: I've
 *              found that when implementing macros, it is best to have the
 *              macros use the actual functions themselves.
 */

#ifdef __cplusplus
extern C
{
#endif

#include "EzC/ezc_macro.h"
#include <stdarg.h>
#include <stddef.h>



/** @brief      List item structure.
 *  @details    Because the first block stores the data, list items can in
 *              theory be case to the desired type, i.e. `(char *) item`. In
 *              practice, however, this is not recommended, do `item->data`
 *              instead.
 */
typedef struct ezc_list
{
    /** Pointer storing item's data. */
    void *data;

    /** Pointer to next item in list. */
    struct ezc_list *next;
}
ezc_list;



/** @brief      Initialize a list.
 *  @details    Blank lists cannot be initialized. Attempting so will result
 *              in this function returning `NULL`. Populate the list by
 *              writing as many arguments as you want. For example,
 *              `ezc_list *names = ezc_list_new("Adam", "Bob", "Carlos");`
 *  @param      self    `void const *` First item of the list. You must provide
 *                      at least one argument to this function.
 *  @param      ...     `void const *` Optional additional list item arguments.
 *  @returns    `ezc_list *` Pointer to allocated list.
 */
#define ezc_list_new(self, ...) \
    (ezc_list_new__((self), ##__VA_ARGS__, NULL))

ezc_list* ezc_list_new__(void const *data, ...);



/** @brief      Create deep copy.
 *  @details    Creates a deep copy of the provided list.
 *  @param      orig    `ezc_list const *` Pointer to the list that you want
 *                      copied.
 *  @returns    `ezc_list *` Pointer to allocated list. If provided list was
 *              `NULL`, returns `NULL`.
 */
#define ezc_list_copy(orig) \
    (ezc_list_copy__((orig)))

ezc_list* ezc_list_copy__(ezc_list const *orig);



/** @brief      Swap contents of two lists.
 *  @details    Neither list can be `NULL`. This can be used to switch two
 *              items in a list or switch what list each pointer is pointing
 *              to, for example.
 *  @param      a       `ezc_list *` Pointer to a list.
 *  @param      b       `ezc_list *` Pointer to another list.
 *  @returns    N/A
 */
#define ezc_list_swap(a, b) \
    (ezc_list_swap__((a), (b)))

void ezc_list_swap__(ezc_list *a, ezc_list *b);



/** @brief      Join multiple lists (no new memory allocated).
 *  @details    Attach tail-to-head the given lists.
 *  @param      self    `ezc_list *` Pointer to the list you want to be the
 *                      front-most.
 *  @param      ...     `ezc_list *` Pointers to other lists in the order that
 *                      you want them to be appended.
 *  @returns    `ezc_list *` The head of the new list, which should equal the
 *              first argument. Returns `NULL` if any problems occured.
 */
#define ezc_list_cat(self, ...) \
    (ezc_list_cat__((self), ##__VA_ARGS__, NULL))

ezc_list* ezc_list_cat__(ezc_list *self, ...);



/** @brief      Free given lists.
 *  @details    Free the memory holding the lists. Also set the pointers to
 *              equal `NULL` to help prevent dangling pointers.
 *  @param      self    `ezc_list *` Pointer to a list.
 *  @param      ...     `ezc_list *` Optional pointers to additional lists to
 *                      be freed.
 *  @returns    N/A
 */
#define ezc_list_delete(self, ...) \
    (ezc_list_delete__((self), ##__VA_ARGS__, NULL), \
     SST_MAP(EZC_TO_ZERO, (self), ##__VA_ARGS__))

void ezc_list_delete__(ezc_list *self, ...);



/** @brief      Length of list.
 *  @details    The use of signed `long` is encouraged so that overflow is
 *              easier to detect.
 *  @param      self    `ezc_list const *` Pointer to a list.
 *  @returns    `long` Length of the given list.
 */
#define ezc_list_length(self) \
    (ezc_list_length__((self)))

long ezc_list_length__(ezc_list const *self);



/** @brief      Apply function to each item of list.
 *  @details    See `fn` documentation for how to design the function's
 *              interface.
 *  @param      self    `ezc_list *` Pointer to a list.
 *  @param      fn      Pointer to a function. The first argument of the
 *                      function must accept a pointer to the type of item in
 *                      the list `self`. The arguments that it accepts
 *                      thereafter should match what you provide in the `...`.
 *  @param      ...     The arguments to be passed to `fn` following the
 *                      pointer to the list item.
 *  @returns    N/A
 */
#define ezc_list_map(self, fn, ...) \
    do { ezc_list *iter = (self); while (iter != NULL) { \
        (fn)(iter->data, ##__VA_ARGS__); iter = iter->next; \
    } } while(0)



/** @brief      Get index of item.
 *  @details    Out-of-bounds (negative) indices are this module's way of
 *              communicating errors or otherwise not finding the item.
 *  @param      self    `ezc_list const *` Pointer to the item in question.
 *  @param      head    `ezc_list const *` Pointer to the list containing the
 *                      item `self`.
 *  @returns    `long` The index of the item, assuming it was found. Returns
 *              `-1` and pushes an `EZC_LOG_WARN` if the item was not found or
 *              if any other problems occured.
 */
#define ezc_list_get_index_of(self, head) \
    (ezc_list_get_index_of__((self), (head)))

long ezc_list_get_index_of__(ezc_list const *self, ezc_list const *head);




/** @brief      Get item at index `n`.
 *  @details    Asserts that `n` must be not out-of-bounds.
 *  @param      self    `ezc_list const *` Pointer to a list.
 *  @param      n       `long` Index you want to look at.
 *  @returns    `ezc_list *` Pointer to the item at index `n`. Returns `NULL`
 *              if any problems occured.
 */
#define ezc_list_get_at(self, n) \
    (ezc_list_get_at__((self), (n)))

ezc_list* ezc_list_get_at__(ezc_list const *self, long n);



/** @brief      Get item matching given data (via `!=` operator).
 *  @details    Get the first item in the list whose data matches what is
 *              provided.
 *  @param      self        `ezc_list const *` Pointer to a list.
 *  @param      data        `void const *` Pointer to data that you want the
 *                          fetched item to match.
 *  @returns    `ezc_list *` Pointer to the first matching item. Returns `NULL`
 *              if any problems occured.
 */
#define ezc_list_get_match(self, data) \
    (ezc_list_get_match_fn__((self), NULL, (data)))



/** @brief      Get item matching given data (via custom comparison function).
 *  @details    Get the first item in the list whose data matches what is
 *              provided. When checking whether an item does or does not equal
 *              the provided data, use a custom comparison function.
 *  @param      self        `ezc_list const *` Pointer to a list.
 *  @param      neq         Pointer to a function. This function should accept
 *                          two `void const *` arguments. It should <i>return
 *                          </i>`0`<i> if the two are equal</i>, anything else
 *                          otherwise.
 *  @param      data        `void const *` Pointer to data that you want the
 *                          fetched item to match.
 *  @returns    `ezc_list *` Pointer to the first matching item. Returns `NULL`
 *              if any problems occured.
 */
#define ezc_list_get_match_fn(self, neq, data) \
    (ezc_list_get_match_fn__((self), (neq), (data)))

ezc_list* ezc_list_get_match_fn__(ezc_list const *self,
                                  int (*neq)(void const *, void const *),
                                  void const *data);



/** @brief      Push items to index `n`.
 *  @details    Asserts that `n` must be not out-of-bounds, with the exception
 *              of `n == ezc_list_length(self)`. This case is valid and
 *              equivalent to `ezc_list_push_back(self)`.
 *  @param      self    `ezc_list const *` Pointer to a list.
 *  @param      n       `long` Index you want the first pushed item to be at.
 *  @param      ...     `void const *` Data you want to be pushed to the list.
 *                      Provide as many as you want.
 *  @returns    N/A
 */
#define ezc_list_push_at(self, n, ...) \
    do { \
        if ((self) == NULL) (self) = ezc_list_new__(__VA_ARGS__, NULL); \
        else ezc_list_push_at__((self), (n), ##__VA_ARGS__, NULL); \
    } while (0)

void ezc_list_push_at__(ezc_list *self, long n, ...);



/** @brief      Push items to the front.
 *  @details    Equivalent to `ezc_list_push_at(self, 0, ...)`.
 *  @param      self    `ezc_list const *` Pointer to a list.
 *  @param      ...     `void const *` Data you want to be pushed to the list.
 *                      Provide as many as you want.
 *  @returns    N/A
 */
#define ezc_list_push_front(self, ...) \
    do { \
        if ((self) == NULL) (self) = ezc_list_new__(__VA_ARGS__, NULL); \
        else ezc_list_push_at__((self), 0, ##__VA_ARGS__, NULL); \
    } while (0)



/** @brief      Push items to the back.
 *  @details    Equivalent to
 *              `ezc_list_push_at(self, ezc_list_length(self), ...)`.
 *  @param      self    `ezc_list const *` Pointer to a list.
 *  @param      ...     `void const *` Data you want to be pushed to the list.
 *                      Provide as many as you want.
 *  @returns    N/A
 */
#define ezc_list_push_back(self, ...) \
    do { \
        if ((self) == NULL) (self) = ezc_list_new__(__VA_ARGS__, NULL); \
        else ezc_list_push_at__((self), \
                ezc_list_length((self)), \
                ##__VA_ARGS__, \
                NULL); \
    } while (0)




/** @brief      Pop item at index `n`.
 *  @details    Asserts that `n` must be not out-of-bounds.
 *  @param      self    `ezc_list const *` Pointer to a list.
 *  @param      n       `long` The index of the item you want to be popped.
 *  @returns    `ezc_list *` Pointer to the item that got popped. Note: no
 *              memory is freed by this function. It is your responsability
 *              to free the popped item. Consider using `ezc_list_erase_at` if
 *              you don't want to worry about freeing memory yourself. Returns
 *              `NULL` if any problems occured.
 */
#define ezc_list_pop_at(self, n) \
    (ezc_list_pop_at__(&(self), (n)))

ezc_list* ezc_list_pop_at__(ezc_list **self, long n);



/** @brief      Pop first item.
 *  @details    Equivalent to `ezc_list_pop_at(self, 0)`.
 *  @param      self    `ezc_list const *` Pointer to a list.
 *  @returns    `ezc_list *` Pointer to the item that got popped. See
 *              `ezc_list_pop_at` documentation for more details.
 */
#define ezc_list_pop_front(self) \
    (ezc_list_pop_at__(&(self), 0))



/** @brief      Pop last item.
 *  @details    Equivalent to `ezc_list_pop_at(self, ezc_list_length(self)-1)`.
 *  @param      self    `ezc_list const *` Pointer to a list.
 *  @returns    `ezc_list *` Pointer to the item that got popped. See
 *              `ezc_list_pop_at` documentation for more details.
 */
#define ezc_list_pop_back(self) \
    (ezc_list_pop_at__(&(self), ezc_list_length__((self))-1))



/** @brief      Pop item matching given data (via `!=` operator).
 *  @details    Pop the first item in the list whose data matches what is
 *              provided.
 *  @param      self        `ezc_list const *` Pointer to a list.
 *  @param      data        `void const *` Pointer to data that you want the
 *                          popped item to match.
 *  @returns    `ezc_list *` Pointer to the popped first matching item. Returns
 *              `NULL` if any problems occured. See `ezc_list_pop_at`
 *              documentation for more details regarding memory management.
 */
#define ezc_list_pop_match(self, data) \
    (ezc_list_pop_match_fn__((self), NULL, (data)))



/** @brief      Pop item matching given data (via custom comparison function).
 *  @details    Pop the first item in the list whose data matches what is
 *              provided. When checking whether an item does or does not equal
 *              the provided data, use a custom comparison function.
 *  @param      self        `ezc_list const *` Pointer to a list.
 *  @param      neq         Pointer to a function. This function should accept
 *                          two `void const *` arguments. It should <i>return
 *                          </i>`0`<i> if the two are equal</i>, anything else
 *                          otherwise.
 *  @param      data        `void const *` Pointer to data that you want the
 *                          popped item to match.
 *  @returns    `ezc_list *` Pointer to the popped first matching item. Returns
 *              `NULL` if any problems occured. See `ezc_list_pop_at`
 *              documentation for more details regarding memory management.
 */
#define ezc_list_pop_match_fn(self, neq, data, ...) \
    (ezc_list_pop_match_fn__((self), (neq), (data)))

ezc_list* ezc_list_pop_match_fn__(ezc_list const *self,
                                  int (*neq)(void const *, void const *),
                                  void const *data);



/** @brief      Erase item at index `n`.
 *  @details    Asserts that `n` must be not out-of-bounds.
 *  @param      self    `ezc_list const *` Pointer to a list.
 *  @param      n       `long` The index of the item you want to be erased.
 *  @returns    N/A
 */
#define ezc_list_erase_at(self, n) \
    (ezc_list_delete__(ezc_list_pop_at__(&(self), (n)), NULL))



/** @brief      Erase first item.
 *  @details    Equivalent to `ezc_list_erase_at(self, 0)`.
 *  @param      self    `ezc_list const *` Pointer to a list.
 *  @returns    N/A
 */
#define ezc_list_erase_front(self) \
    (ezc_list_delete__(ezc_list_pop_at__(&(self), 0), NULL))



/** @brief      Erase last item.
 *  @details    Equivalent to
 *              `ezc_list_erase_at(self, ezc_list_length(self)-1)`.
 *  @param      self    `ezc_list const *` Pointer to a list.
 *  @returns    N/A
 */
#define ezc_list_erase_back(self) \
    (ezc_list_delete__( \
            ezc_list_pop_at__(&(self), ezc_list_length__((self))-1), \
            NULL))



/** @brief      Erase item matching given data (via `!=` operator).
 *  @details    Erase the first item in the list whose data matches what is
 *              provided.
 *  @param      self        `ezc_list const *` Pointer to a list.
 *  @param      data        `void const *` Pointer to data that you want the
 *                          erased item to match.
 *  @returns    N/A
 */
#define ezc_list_erase_match(self, data) \
    (ezc_list_delete__(ezc_list_pop_match_fn__((self), NULL, (data)), NULL))



/** @brief      Erase item matching given data (via custom comparison
 *              function).
 *  @details    Erase the first item in the list whose data matches what is
 *              provided. When checking whether an item does or does not equal
 *              the provided data, use a custom comparison function.
 *  @param      self        `ezc_list const *` Pointer to a list.
 *  @param      neq         Pointer to a function. This function should accept
 *                          two `void const *` arguments. It should <i>return
 *                          </i>`0`<i> if the two are equal</i>, anything else
 *                          otherwise.
 *  @param      data        `void const *` Pointer to data that you want the
 *                          erased item to match.
 *  @returns    N/A
 */
#define ezc_list_erase_match_fn(self, neq, data, ...) \
    (ezc_list_delete__(ezc_list_pop_match_fn__((self), (neq), (data)), NULL))



#ifdef __cplusplus
}
#endif

#endif /* EZC_LIST_H */
