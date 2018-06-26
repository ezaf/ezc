/*  ezc_observer.c
 *
 *  Copyright (c) 2018 Kirk Lange <github.com/kirklange
 *  
 *  This software is provided 'as-is', without any express or implied
 *  warranty.  In no event will the authors be held liable for any damages
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

#if 0

#include "EzC/ezc_observer.h"
#include "EzC/ezc_log.h"



uint8_t ezc_observer_isNull(ezc_observer *subject, const char *caller);



ezc_observer* ezc_observer_new()
{
    ezc_observer *self = (ezc_observer*) malloc(sizeof(ezc_observer));
    self->prev = self->next = self->notify = self->data = 0;
    return self;
}



uint8_t ezc_observer_del(ezc_observer **head)
{
    uint8_t error = ezc_observer_isNull(*head, __func__);

    if (!error)
    {
        ezc_observer *iter = *head;
        ezc_observer *next = 0;

        /* We know head is not null thanks to earlier error check. */
        do
        {
            next = iter->next;
            free(iter);
        }
        while (iter = next);

        free(*head);
        *head = 0;
    }

    return !error;
}



uint8_t ezc_observer_notifyAll(ezc_observer *head)
{
    uint8_t error = ezc_observer_isNull(head, __func__);

    if (!error)
    {
        /* Notify everybody on the linked list. */
        do if (head->notify) head->notify(head->data);
        while (head = head->next);
    }
    
    return !error;
}



ezc_observer* ezc_observer_add(ezc_observer *head,
        void (*notify)(void*), void *data)
{
    uint8_t error = ezc_observer_isNull(head, __func__);
    ezc_observer *self = 0;

    if (error |= !notify)
    {
        ezutil_log(MAJOR, __func__, "Notify function pointer is null.");
    }

    if (!error)
    {
        self = (ezc_observer*) malloc(sizeof(ezc_observer));
        self->prev = head;
        self->next = head->next;
        self->notify = notify;
        self->data = data;
        head->next = self;
    }

    return self;
}



uint8_t ezc_observer_remove(ezc_observer *node)
{
    uint8_t error = ezc_observer_isNull(node, __func__);

    if (!error)
    {
        /* TODO: see how this holds up when removing the last node in list */
        if (node->next)
        {
            ezc_observer *temp = node->next;
            node->next = temp->next;
            node->notify = temp->notify;
            node->data = temp->data;
            free(temp);
        }
        else
        {
            node->next = node->notify = node->data = 0;
            free(node);
        }
    }
    
    return !error;
}



uint8_t ezc_observer_isNull(ezc_observer *node, const char *caller)
{
    uint8_t error = 0;

    if (error |= !node)
    {
        ezutil_log(MAJOR, caller, "Observer node paramter is null.");
    }

    return error;
}

#endif
