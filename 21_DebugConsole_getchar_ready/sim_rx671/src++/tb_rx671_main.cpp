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
    int i;

    for (;;)
    {
        printf( "Please enter a character:\r\n" );

        for (i = 0; i < 3; i++)
        {
            vTaskDelay( pdMS_TO_TICKS( 1000 ) );

            if (is_getchar_ready())
            {
                c = getchar();
                printf( "\r\nYeah, %c is entered.\r\n\r\n", c );

                vTaskDelay( pdMS_TO_TICKS( 1000 ) );

                break;
            }
        }
    }

    /* vTaskDelete(NULL); */
}
