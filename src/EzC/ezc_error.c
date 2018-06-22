/*  ezc_error.c
 *  
 *  <!-------------------------------------------------------------------------
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
 *  -------------------------------------------------------------------------->
 */

#if 0

#include "EzC/ezc_error.h"

#include <limits.h>
#include <string.h>



static char *EZC_ERROR_LOG = NULL;
static size_t EZC_ERROR_LOG_CAPACITY = 0;



void ezc_error(char const *file, unsigned int line,
               ezc_error_t severity, char const *message, ...)
{
    if (EZC_ERROR_LOG_CAPACITY < EZC_ERROR_LOG_CAPACITY + strlen(message))
    {
        if (EZC_ERROR_LOG_CAPACITY == 0)
            EZC_ERROR_LOG_CAPACITY = INT_MAX;
        else
            EZC_ERROR_LOG_CAPACITY *= 2;

        EZC_ERROR_LOG = (char*) realloc(EZC_ERROR_LOG_CAPACITY, sizeof(char));

        /* Inelegant! We need a growable strings data structure. */
    }
}



/* TODO: in ezc_error_add, seperate each error by something like
 * "\n[TYPE #%u; FILE:LINE; DATE-TIME]\n" */

#endif
