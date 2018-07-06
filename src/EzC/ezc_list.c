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
#include "EzC/ezc_error.h"
#include "EzC/ezc_macro.h"
#include "EzC/ezc_mem.h"
#include <stdarg.h>
#include <string.h>



ezc_list* ezc_list_new__(void const *data, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, data);

    ezc_list *head = NULL;
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
    ezc_list *head = NULL;
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



void ezc_list_swap__(ezc_list *listA, ezc_list *listB)
{
    assert(listA != NULL && listB != NULL);
    
    /* All we need to do is swap the heads of each list */
    ezc_list temp;

    temp.data = listA->data;
    temp.next  = listA->next;

    listA->data = listB->data;
    listA->next = listB->next;

    listB->data = temp.data;
    listB->next = temp.next;
}



void ezc_list_join__(ezc_list *self, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, self);

    ezc_list *prev;

    while(self != NULL)
    {
        prev = self;
        self = va_arg(arg_ptr, ezc_list*);

        while (prev->next != NULL) prev = prev->next;
        prev->next = self;
    }
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



ezc_list* ezc_list_get_at(ezc_list const *self, long n)
{
    /* Correct out-of-bounds indices, behave like Python indices */
    n %= (ezc_list_length(self) + 1);
    if (n < 0) n += (ezc_list_length(self) + 1);

    /* Find item n */
    while (self != NULL && n-- > 0)
    {
        self = self->next;
    }

    return self;
}



long ezc_list_get_match(ezc_list const *self, void *data,
                        int (*neq)(void const *, void const *))
{
    long n = 0;

    /* Find item n */
    while (self != NULL && (*neq)(self->data, data))
    {
        n++;
        self = self->next;
    }

    return n;
}



void ezc_list_push_at__(ezc_list *self, long n, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, n);

    void *data;
    ezc_list *data_list = NULL;
    
    /* Get all data out of arg_ptr */
    while ((data = va_arg(arg_ptr, void*)) != NULL)
    {
        if (data_list == NULL) data_list = ezc_list_new(data);
        else ezc_list_cat(data_list, ezc_list_new(data));
    }
    
    /* Now actually add it to self */
    if (data_list != NULL)
    {
        /* Concatenate new data with self[-n:] */
        if (n != 0)
        {
            ezc_list *prev = ezc_list_get_at(self, n-1),
                     *split = prev->next;

            assert(prev != NULL);
            prev->next = NULL;

            ezc_list_cat(data_list, split);
        }
        else
        {
            /* Must swap order when n == 0 to push to front */
            ezc_list_swap(data_list, self);
        }

        ezc_list_cat(self, data_list);
    }
}
