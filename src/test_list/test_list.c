/*  test_list.c
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

/** @file       test_list.c
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#include "EzC/ezc_list.h"
#include <stdio.h>
#include <string.h>

void printme(char *str)
{
    printf(">> ");

    while(*str && str != NULL)
    {
        printf("%c", *str);
        str++;
    }
    
    printf("\n");
}



int main(int argc, char *argv[])
{
    size_t const TOTAL = 3;
    ezc_list *names[TOTAL];

    names[0] = ezc_list_new("Monica", "Olivia");
    ezc_list_push_at(names[0], -2, "Natalie");

    names[1] = ezc_list_copy(names[0]);
    names[2] = ezc_list_new("Zoe");
    
    ezc_list_push_front(names[1], "Amanda", "Bella", "Christy");
    ezc_list_push_back(names[1], "Xiaotian", "Yana");

    ezc_list_swap(names[0], names[1]);
    ezc_list_cat(names[0], names[2]);

    ezc_list_map(names[1], printme);

    char const *findme = "Yana";
    printf("Find index of \"%s\" in names[0]: %d\n\n", findme,
            ezc_list_get_match_fn(names[0], findme, strcmp));
    
    long i, j, length;
    for (i = 0; i < TOTAL; i++)
    {
        ezc_list *iter = names[i];
        length = ezc_list_length(names[i]);
        printf("-- List #%i : length=%i --\n", i, length);

        /* Not as efficient as iterating manually but we need to test
         * ezc_list_get_at anyway */
        for (j=0; j < length; j++)
        {
            printf("%s\n", ezc_list_get_at(names[i], j)->data);
        }

        ezc_list_delete(names[i]);
    }

    return 0;
}
