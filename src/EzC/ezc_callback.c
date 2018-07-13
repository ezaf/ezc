/*  ezc_callback.c
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

#include "EzC/ezc_callback.h"
#include "EzC/ezc_log.h"
#include "EzC/ezc_mem.h"



typedef struct ezc_callback
{
    void (*fn)(void*);
    void *arg;
}
ezc_callback;



ezc_callback* ezc_callback_new(void (*fn)(void*), void *arg)
{
    ezc_callback *self;
    EZC_NEW(self);

    self->fn = fn;
    self->arg = arg;

    return self;
}



void ezc_callback_delete(ezc_callback *self)
{
    EZC_FREE(self);
}



void ezc_callback_call(ezc_callback const *self)
{
    if (self != NULL)
    {
        (*self->fn)(self->arg);
    }
    else
    {
        ezc_log(EZC_LOG_WARN, "Attempting to use uninitialized callback.");
    }
}
