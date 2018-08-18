/*  test_log/main.c
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

/** @file       test_log/main.c
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#include "ezc/ezc_log.h"



int main(int argc, char *argv[])
{
    ezc_log_echo(stdout);

    ezc_log(EZC_LOG_INFO, "Some boring info. Blah!");
    ezc_log(EZC_LOG_WARN, "This is a benign...");
    ezc_log(EZC_LOG_ERROR, "Now we're getting serious!");
    ezc_log(EZC_LOG_INFO, "Just kidding, all is fine.");

    printf("<ezc_log_get>\n%s</ezc_log_get>\n", ezc_log_get(EZC_LOG_WARN));

    printf("Writing log to file...\n");
    ezc_log_fwrite();
    printf("Clearing log...\n");
    ezc_log_clear();

    printf("<ezc_log_get>\n%s</ezc_log_get>\n", ezc_log_get(EZC_LOG_WARN));

    return 0;
}
