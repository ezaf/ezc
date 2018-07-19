/*  ezc_assert.c
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

#include "EzC/ezc_assert.h"
#include "EzC/ezc_mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void ezc_assert(char const *file, unsigned int line, char const *expr)
{
    time_t rawtime;
    struct tm *infotime;

    time(&rawtime);
    infotime = localtime(&rawtime);

    char name[27], message[2048];
    strftime(name, EZC_LENGTH(name), "%Y-%m-%d-%H-%M-%S.assert", infotime);
    snprintf(message, EZC_LENGTH(message),
            "EzC assertion failed!\n"
            "%s:%u\n"
            "%s\n", file, line, expr);

    FILE *out = fopen(name, "w");

    if (out != NULL)
    {
        fprintf(out, message);
        fclose(out);
    }

    fprintf(stderr, message);

    abort();
}
