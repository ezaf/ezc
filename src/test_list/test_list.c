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

#include <stdio.h>

#include "EzC/ezc_list.h"



int main(int argc, char *argv[])
{
    ezc_list *names[2];
    names[0] = ezc_list_new("Adam", "Ben", "Charles", NULL);
    names[1] = ezc_list_copy(names[0]);
    
    size_t i;
    for (i = 0; i < 2; i++)
    {
        ezc_list *iter = names[i];
        printf("-- List #%u : length=%u --\n", i, ezc_list_length(names[i]));

        for (; iter != NULL; iter = iter->next)
        {
            printf("%s\n", iter->data);
        }

        ezc_list_delete(names[i]);
    }

    return 0;
}