/** @file       EzC/ezc_observer.h
 *  @brief      Observer design pattern using a linked list.
 *  
 *  <!-------------------------------------------------------------------------
 *  Copyright (c) 2018 Kirk Lange <github.com/kirklange>
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
 *  -------------------------------------------------------------------------->
 */

#if 0

#ifndef EZC_OBSERVER_H
#define EZC_OBSERVER_H

#ifdef __cplusplus
extern "C"
{
#endif



#include <stdint.h>



typedef struct ezc_observer
{
    struct ezc_observer     *next;
    void                   (*notify)(void*);
    void                    *data;
}
ezc_observer;



ezc_observer*       ezc_observer_new();
uint8_t             ezc_observer_del(ezc_observer **head);

uint8_t             ezc_observer_notifyAll(ezc_observer *head);
ezc_observer*       ezc_observer_add(ezc_observer *head, void (*notify)(void*),
                                     void *data);
uint8_t             ezc_observer_remove(ezc_observer *node);



#ifdef __cplusplus
}
#endif

#endif /* EZC_OBSERVER_H */

#endif
