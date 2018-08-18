/*  test_callback/main.c
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

/** @file       test_callback/main.c
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#include "ezc/ezc_callback.h"
#include "ezc/ezc_list.h"
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846



void printCircleArea(double *r)
{
    printf("r: %f -- A: %f\n", *r, PI*pow(*r, 2));
}



int main(int argc, char *argv[])
{
    double radii[3] = { 1.0, 2.0, 3.0 };

    ezc_list *circles = ezc_list_new(
            ezc_callback_new(printCircleArea, &radii[0]),
            ezc_callback_new(printCircleArea, &radii[1]),
            ezc_callback_new(printCircleArea, &radii[2]));

    ezc_list_map(circles, ezc_callback_call);

    ezc_list_map(circles, ezc_callback_delete);
    ezc_list_delete(circles);

    return 0;
}
