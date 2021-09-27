#ifndef FREERTOS_HELPER_H
#define FREERTOS_HELPER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "r_cg_macrodriver.h"

extern void vTaskNotifyGiveFromISR_R_Helper(TaskHandle_t *pxTask);
extern void xTaskNotifyFromISR_R_Helper(TaskHandle_t *pxTask, uint32_t ulValue);
extern uint32_t ulTaskNotifyTake_R_Helper(TickType_t xTicksToWait);
extern uint32_t ulTaskNotifyTake_R_Helper_Ex2__helper(TaskHandle_t *pxTask, MD_STATUS xStatus, TickType_t xTicksToWait);
extern void ulTaskNotifyTake_R_Abort_Helper(TaskHandle_t *pxTask);
extern TaskHandle_t xTaskGetCurrentTaskHandle_R_Helper(void);

#define xTaskCreateStatic_R_Helper(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask) \
do{ \
    static StaticTask_t pxTaskCode##_xTCBBuffer; \
    static StackType_t  pxTaskCode##_xStackBuffer[usStackDepth]; \
    TaskHandle_t xCreatedTask; \
    xCreatedTask = xTaskCreateStatic( pxTaskCode, (pcName), (usStackDepth), (pvParameters), (uxPriority), pxTaskCode##_xStackBuffer, &pxTaskCode##_xTCBBuffer ); \
    if (0U != (uint8_t *)(TaskHandle_t *)(pxCreatedTask) - (uint8_t *)NULL) \
    { \
        *(TaskHandle_t *)(pxCreatedTask) = xCreatedTask; \
    } \
}while (0)

#define xSemaphoreCreateMutexStatic_R_Helper(pxCreatedSemaphore) \
do{ \
    static StaticSemaphore_t xStaticSemaphore; \
    QueueHandle_t xCreatedQueue; \
    xCreatedQueue = xSemaphoreCreateMutexStatic( &xStaticSemaphore ); \
    if (0U != (uint8_t *)(QueueHandle_t *)(pxCreatedSemaphore) - (uint8_t *)NULL) \
    { \
        *(QueueHandle_t *)(pxCreatedSemaphore) = xCreatedQueue; \
    } \
}while (0)

#define ulTaskNotifyTake_R_Helper_Ex(pxTask, vStartFunc, xTicksToWait) \
( \
    /* Setup the interrupt/callback ready to post a notification */ \
    (*(pxTask) = xTaskGetCurrentTaskHandle_R_Helper()), \
    /* Wait for a notification from the interrupt/callback */ \
    ulTaskNotifyTake_R_Helper( \
        ( \
            (vStartFunc), \
            (xTicksToWait) \
        ) \
    ) \
)

#define ulTaskNotifyTake_R_Helper_Ex2(pxTask, xStartFunc, xTicksToWait) \
( \
    /* Setup the interrupt/callback ready to post a notification */ \
    (*(pxTask) = xTaskGetCurrentTaskHandle_R_Helper()), \
    /* Wait for a notification from the interrupt/callback */ \
    ulTaskNotifyTake_R_Helper_Ex2__helper( \
        (pxTask), \
        (xStartFunc), \
        (xTicksToWait) \
    ) \
)

#define ulTaskNotifyTake_R_Abort_Helper_Ex(pxTask, vAbortFunc) \
do{ \
    /* Abort the interrupt/callback posting a notification */ \
    (vAbortFunc); \
    ulTaskNotifyTake_R_Abort_Helper(pxTask); \
}while (0)

#ifdef __cplusplus
}
#endif

#endif /* FREERTOS_HELPER_H */
