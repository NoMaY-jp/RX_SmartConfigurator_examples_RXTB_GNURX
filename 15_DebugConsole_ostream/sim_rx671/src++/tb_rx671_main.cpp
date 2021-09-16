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

// Please open the following e2 studio's views
// 1. Debug Virtual Console View
// 2. Visual Expression View

#include <iostream>

using namespace std;

string strHelloWorld = "Hello world.";

void main_task(void *pvParameters)
{
    INTERNAL_NOT_USED(pvParameters);

    LED0 = LED_ON;

    for (;;)
    {
        cout << strHelloWorld << endl;

        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
        LED0 = ~LED0;

        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
        LED0 = ~LED0;
    }

    /* vTaskDelete(NULL); */
}
