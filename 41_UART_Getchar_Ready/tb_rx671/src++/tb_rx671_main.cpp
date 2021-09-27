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

// Note
// 1. This example uses MCU's SCI1 (TxD1/RxD1 = CN2's Pin22/Pin20)
//    and the UART is configured with 9600 baud.

U_CONFIG_UART_PRINTF_IMPL(  SCI1, 128 /* transmit buffer size */ );
U_CONFIG_UART_GETCHAR_IMPL( SCI1, 128 /* receive ring buffer size */ );

void main_task(void *pvParameters)
{
    INTERNAL_NOT_USED(pvParameters);

    char c;
    int i;

    for (;;)
    {
        Printf( SCI1, "Please enter a character:\r\n" );

        for (i = 0; i < 3; i++)
        {
            vTaskDelay( pdMS_TO_TICKS( 1000 ) );

            if (Is_Getchar_Ready( SCI1 ))
            {
                c = Getchar( SCI1 );
                Printf( SCI1, "\r\nYeah, %c is entered.\r\n\r\n", c );

                vTaskDelay( pdMS_TO_TICKS( 1000 ) );

                break;
            }
        }
    }

    /* vTaskDelete(NULL); */
}
