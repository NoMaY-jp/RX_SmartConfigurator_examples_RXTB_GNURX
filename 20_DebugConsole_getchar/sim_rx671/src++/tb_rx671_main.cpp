/***********************************************************************
*
*  FILE        : tb_rx671_main.cpp
*  DATE        : 2021-09-10
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
extern "C" {
#include "task_function.h"
#include "r_smc_entry.h"
#include "tbrx671def.h"
}

// Please open the following e2 studio's view
// 1. Debug Virtual Console View

void main_task(void *pvParameters)
{
    INTERNAL_NOT_USED(pvParameters);

    char c;

    for (;;)
    {
        printf( "Please enter a character:\r\n" );

        c = getchar();

        printf( "\r\nNow %c is entered.\r\n\r\n", c );
    }

    /* vTaskDelete(NULL); */
}
