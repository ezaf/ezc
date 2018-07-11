/*  ezc_log.c
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

#include "EzC/ezc_log.h"

#include "EzC/ezc_list.h"
#include "EzC/ezc_mem.h"
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



static ezc_list *EZC_LOG_LIST = NULL;
static long const EZC_LOG_BUFFER_SIZE = 4092;
static FILE *EZC_LOG_ECHO_DEST = NULL;



typedef struct ezc_log_data
{
    ezc_log_t type;
    char *message;
}
ezc_log_data;



void ezc_log__(char const *file, long line,
               ezc_log_t type, char const *message, ...)
{
    va_list args;
    va_start(args, message);

    int is_fatal = 0;

    ezc_log_data *log;
    EZC_NEW(log);

    log->type = type;
    EZC_NEWN(log->message, EZC_LOG_BUFFER_SIZE);
    strcat(log->message, ">> ");

    switch (type)
    {
        case EZC_LOG_INFO:
            strcat(log->message, "INF");
            break;
        case EZC_LOG_WARN:
            strcat(log->message, "WRN");
            break;
        case EZC_LOG_ERROR:
            strcat(log->message, "ERR");
            break;
        case EZC_LOG_FATAL:
            strcat(log->message, "FTL");
            is_fatal = 1;
            break;
        default:
            strcat(log->message, "???");
            break;
    }

    char *buf;
    EZC_NEWN(buf, EZC_LOG_BUFFER_SIZE);
    snprintf(buf, EZC_LOG_BUFFER_SIZE, " @ %s:%u <<\n", file, line);
    strcat(log->message, buf);
    EZC_FREE(buf);

    EZC_NEWN(buf, EZC_LOG_BUFFER_SIZE);
    vsnprintf(buf, EZC_LOG_BUFFER_SIZE, message, args);
    strcat(log->message, buf);
    EZC_FREE(buf);

    strcat(log->message, "\n\n");

    if (EZC_LOG_LIST == NULL)
    {
        EZC_LOG_LIST = ezc_list_new(log);
    }
    else
    {
        ezc_list_push_front(EZC_LOG_LIST, log);
    }

    if (EZC_LOG_ECHO_DEST != NULL)
    {
        fprintf(EZC_LOG_ECHO_DEST, log->message);
    }

    va_end(args);

    if (is_fatal)
    {
        ezc_log_fwrite();
        abort();
    }
}



void ezc_log_echo(FILE *dest)
{
    EZC_LOG_ECHO_DEST = dest;
}



char const* ezc_log_get(ezc_log_t type)
{
    ezc_list *iter = EZC_LOG_LIST;

    while (iter != NULL)
    {
        if (((ezc_log_data *) iter->data)->type >= type)
        {
            break;
        }

        iter = iter->next;
    }

    return iter == NULL ? NULL : ((ezc_log_data *) iter->data)->message;
}



void ezc_log_fwrite()
{
    time_t rawtime;
    struct tm *infotime;

    time(&rawtime);
    infotime = localtime(&rawtime);

    char buf[26];
    strftime(buf, 26, "%Y-%m-%d-%H-%M-%S.error", infotime);

    FILE *file = fopen(buf, "w");
    ezc_list *iter = EZC_LOG_LIST;

    if (file != NULL)
    {
        while (iter != NULL)
        {
            char const * const message =
                ((ezc_log_data *) iter->data)->message;
            fwrite(message, sizeof(char), strlen(message), file);
            iter = iter->next;
        }
    }
    else
    {
        ezc_log(EZC_LOG_ERROR, "Unable to write log to file. "
                "Error while opening/creating file.");
    }

    fclose(file);
}



void ezc_log_clear()
{
    ezc_list_delete(EZC_LOG_LIST);
}
