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

#include "EzC/ezc_mem.h"
#include <stdarg.h>



ezc_list* ezc_list_new(void *data, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, data);
    
    ezc_list *head, **iter;
    iter = &head;

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
    ezc_list *head, **iter;
    iter = &head;
    
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



void ezc_list_delete(ezc_list *self)
{
    ezc_list *next;

    while (self)
    {
        next = self->next;
        EZC_FREE(self);
        self = next;
    }
}



size_t ezc_list_length(ezc_list *self)
{
    size_t length = 0;

    while (self)
    {
        length++;
        self = self->next;
    }

    return length;
}
