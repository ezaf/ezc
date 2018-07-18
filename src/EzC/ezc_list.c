/*  ezc_list.c
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

#include "EzC/ezc_list.h"

#include "EzC/ezc_assert.h"
#include "EzC/ezc_log.h"
#include "EzC/ezc_macro.h"
#include "EzC/ezc_mem.h"
#include <limits.h>
#include <stdarg.h>



ezc_list* ezc_list_new__(void const *data, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, data);

    ezc_list * const head = NULL;
    ezc_list **iter = &head;

    while (data != NULL)
    {
        /* Initialize this item and append to list */
        EZC_NEW(*iter);
        (*iter)->data = data;

        /* Increment iterator and data args */
        iter = &(*iter)->next;
        data = va_arg(arg_ptr, void const *);
    }

    *iter = NULL;
    va_end(arg_ptr);
    return head;
}



ezc_list* ezc_list_copy__(ezc_list const *orig)
{
    ezc_list * const head = NULL;
    ezc_list **iter = &head;

    while (orig != NULL)
    {
        EZC_NEW(*iter);
        (*iter)->data = orig->data;

        iter = &(*iter)->next;
        orig = orig->next;
    }

    *iter = 0;
    return head;
}



void ezc_list_swap__(ezc_list *a, ezc_list *b)
{
    assert(a != NULL && b != NULL);

    /* All we need to do is swap the heads of each list */
    ezc_list temp;

    temp.data = a->data;
    temp.next  = a->next;

    a->data = b->data;
    a->next = b->next;

    b->data = temp.data;
    b->next = temp.next;
}



ezc_list* ezc_list_cat__(ezc_list *self, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, self);

    ezc_list * const head = self;
    ezc_list *prev;

    while(self != NULL)
    {
        prev = self;
        self = va_arg(arg_ptr, ezc_list*);

        while (prev->next != NULL) prev = prev->next;
        prev->next = self;
    }

    return head;
}



void ezc_list_delete__(ezc_list *self, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, self);

    while (self != NULL)
    {
        ezc_list *iter = self, *temp;

        while (iter != NULL)
        {
            temp = iter->next;
            EZC_FREE(iter);
            iter = temp;
        }

        self = va_arg(arg_ptr, ezc_list*);
    }
}



long ezc_list_length__(ezc_list const *self)
{
    long length = 0;

    while (self != NULL && length >= 0)
    {
        length++;
        self = self->next;
    }

    return length;
}



long ezc_list_get_index_of__(ezc_list const *self, ezc_list const *head)
{
    long n = 0;

    if (self != NULL && head != NULL)
    {
        long const LENGTH = ezc_list_length(head);

        while (head != NULL && head != self)
        {
            n++;
            head = head->next;
        }

        if (n == LENGTH)
        {
            n = -1;
            ezc_log(EZC_LOG_WARN, "Could not find item in list.");
        }
    }
    else
    {
        n = -1;
    }

    return n;
}



ezc_list* ezc_list_get_at__(ezc_list const *self, long n)
{
    assert(n >= 0 && n < ezc_list_length(self));

    /* Find nth item */
    while (self != NULL && n-- > 0)
    {
        self = self->next;
    }

    return self;
}



ezc_list* ezc_list_get_match_fn__(ezc_list const *self,
                                  int (*neq)(void const *, void const *),
                                  void const *data)
{
    while (self != NULL &&
            (neq != 0 ? (*neq)(self->data, data) : self->data != data))
    {
        self = self->next;
    }

    return self;
}



void ezc_list_push_at__(ezc_list *self, long n, ...)
{
    /* Pushing at list length is valid. This is equivalent to push_back. */
    assert(n >= 0 && n <= ezc_list_length(self));

    va_list arg_ptr;
    va_start(arg_ptr, n);

    void *data;
    ezc_list *data_list = NULL;

    /* Get all data out of arg_ptr */
    while ((data = va_arg(arg_ptr, void const *)) != NULL)
    {
        if (data_list == NULL) data_list = ezc_list_new(data);
        else ezc_list_cat(data_list, ezc_list_new(data));
    }

    /* Now actually add it to self */
    if (data_list != NULL)
    {
        if (n == 0)
        {
            /* Must swap order when n == 0 to push to front */
            ezc_list_swap(data_list, self);
        }
        else
        {
            /* Concatenate new data with 0-to-(n-1) chunck of self */
            ezc_list *prev = ezc_list_get_at(self, n-1),
                     *split = prev->next;

            prev->next = NULL;

            ezc_list_cat(data_list, split);
        }

        ezc_list_cat(self, data_list);
    }

    va_end(arg_ptr);
}



ezc_list* ezc_list_pop_at__(ezc_list **self, long n)
{
    /* Mind the double pointer parameter! */
    assert(n >= 0 && n < ezc_list_length(*self));

    ezc_list *popped = NULL;

    if (self != NULL && *self != NULL)
    {
        if (n == 0)
        {
            popped = *self;
            *self = (*self)->next;
        }
        else
        {
            ezc_list *prev = ezc_list_get_at(*self, n-1);
            popped = prev->next;
            prev->next = (popped == NULL ? NULL : popped->next);
        }

        if (popped != NULL) popped->next = NULL;
    }

    return popped;
}



ezc_list* ezc_list_pop_match_fn__(ezc_list const *self,
                                  int (*neq)(void const *, void const *),
                                  void const *data)
{
    ezc_list *popped = ezc_list_get_match_fn(self, neq, data);

    if (popped != NULL)
    {
        popped = ezc_list_pop_at(self, ezc_list_get_index_of(popped, self));
    }

    return popped;
}
