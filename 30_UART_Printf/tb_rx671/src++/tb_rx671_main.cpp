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
// 1. This example uses MCU's SCI1 (TxD1 = CN2's Pin22)
//    and the UART is configured with 9600 baud.

U_CONFIG_UART_PRINTF_IMPL(  SCI1, 128 /* transmit buffer size */ );

void main_task(void *pvParameters)
{
    INTERNAL_NOT_USED(pvParameters);

    LED0 = LED_ON;

    for (;;)
    {
        Printf( SCI1, "Hello World\r\n" );

        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
        LED0 = ~LED0;

        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
        LED0 = ~LED0;
    }

    /* vTaskDelete(NULL); */
}
