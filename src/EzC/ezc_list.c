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
#include "EzC/ezc_mem.h"
#include <stdarg.h>
#include <string.h>



ezc_list* ezc_list_new(void *data, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, data);

    ezc_list *head = NULL;
    ezc_list **iter = &head;

    while (data != NULL)
    {
        EZC_NEW(*iter);
        (*iter)->data = data;
        iter = &(*iter)->next;

        /* Increment data args */
        data = va_arg(arg_ptr, void *);
    }

    *iter = NULL;
    va_end(arg_ptr);
    return head;
}



ezc_list* ezc_list_copy(ezc_list *orig)
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



void ezc_list_swap(ezc_list *listA, ezc_list *listB)
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



void ezc_list_delete(ezc_list *self)
{
    ezc_list *next;

    while (self != NULL)
    {
        next = self->next;
        EZC_FREE(self);
        self = next;
    }
}



size_t ezc_list_length(ezc_list *self)
{
    size_t length = 0;

    while (self != NULL)
    {
        length++;
        self = self->next;
    }

    return length;
}



void ezc_list_push(ezc_list *self, char const *mode, ...)
{
    assert(self != NULL && mode != NULL);
    /* Mutually exclusive modes */
    assert(!!strstr(mode, "f") ^ !!strstr(mode, "b") ^
           !!strstr(mode, "n") ^ !!strstr(mode, "r") ^
           !!strstr(mode, "c"));

    va_list arg_ptr;
    va_start(arg_ptr, mode);

    if (strstr(mode, "c")) /* Concatenate */
    {
        ezc_list *other;
        
        while ((other = va_arg(arg_ptr, ezc_list*)) != NULL)
        {
            while (self->next != NULL) self = self->next;
            self->next = ezc_list_copy(other);
        }
    }
    else if (strstr(mode, "f") || strstr(mode, "b") || /* Push front or back */
             strstr(mode, "n") || strstr(mode, "r"))   /* Insert at or rel */
    {
        ezc_list *data_list = NULL;
        void *data;
        long n = 0;
        
        /* Figure out index */
        if (strstr(mode, "f")) n = 0;
        else if (strstr(mode, "b")) n = -1;
        else if (strstr(mode, "n")) n = va_arg(arg_ptr, long);
        else if (strstr(mode, "r"))
        {
            void *ref = va_arg(arg_ptr, void*);
            
            /* Get position of reference item */
            /* TODO: relegate this task to ezc_list_get(...) */
            ezc_list *iter = self;
            while (iter != NULL && iter->data != ref)
            {
                n++;
                iter = iter->next;
            }
            
            n += va_arg(arg_ptr, long);
        }

        /* Correct out-of-bounds indices */
        n %= ((long) ezc_list_length(self) + 1);
        if (n < 0) n += (long) ezc_list_length(self) + 1;

        /* Confirm out-of-bounds index correction */
        assert(n <= ezc_list_length(self));
        assert(n >= 0);

        /* Get all data out of arg_ptr */
        while ((data = va_arg(arg_ptr, void*)) != NULL)
        {
            if (data_list == NULL)
            {
                data_list = ezc_list_new(data, NULL);
            }
            else
            {
                /* Functional programming FTW! */
                ezc_list_push(data_list, "c", ezc_list_new(data, NULL), NULL);
            }
        }
        
        /* Now actually add it to self */
        if (data_list != NULL)
        {
            /* Concatenate new data with self[-n:] */
            if (n != 0)
            {
                ezc_list *iter = self, *prev = 0;
                while (iter != NULL && n-- > 0)
                {
                    prev = iter;
                    iter = iter->next;
                }
                
                if (prev != NULL) prev->next = NULL;

                ezc_list_push(data_list, "c", iter, NULL);
            }
            else
            {
                /* Must swap order to push to front (n == 0) */
                ezc_list_swap(data_list, self);
            }

            ezc_list_push(self, "c", data_list, NULL);
        }
    }
    else
    {
        /*
        ezc_error("ce", "No recognized char within mode string detected.", 0);
        */
    }

    va_end(arg_ptr);
}
