#include "platform.h"
#include "freertos_helper.h"
#include <limits.h>

int open(const char *file, int flags, ...);
int getpid(void);
int kill(int pid, int sig);

int write(int fileno, char *buf, int count)
{
    static QueueHandle_t mutex;

    taskENTER_CRITICAL();
    {
        static bool is_mutex_created = false;

        if (!is_mutex_created)
        {
            xSemaphoreCreateMutexStatic_R_Helper(&mutex);
            is_mutex_created = true;
        }
    }
    taskEXIT_CRITICAL();

    if (1 == fileno || 2 == fileno)
    {
        if (0 < count)
        {
            xSemaphoreTake(mutex, portMAX_DELAY);
            {
                int remain = count;

                while (remain-- > 0)
                {
                    charput( *buf++ );
                }
            }
            xSemaphoreGive(mutex);
        }
    }
    else
    {
        /* Force an assert. */
        vAssertCalled();
    }

    return count;
}

int read(int fileno, char *buf, int count)
{
    static QueueHandle_t mutex;

    taskENTER_CRITICAL();
    {
        static bool is_mutex_created = false;

        if (!is_mutex_created)
        {
            xSemaphoreCreateMutexStatic_R_Helper(&mutex);
            is_mutex_created = true;
        }
    }
    taskEXIT_CRITICAL();

    if (0 == fileno)
    {
        if (0 < count)
        {
            xSemaphoreTake(mutex, portMAX_DELAY);
            {
                *buf = charget();
                count = 1;
            }
            xSemaphoreGive(mutex);
        }
    }
    else
    {
        /* Force an assert. */
        vAssertCalled();
    }

    return count;
}

void close(void)
{
    /* Force an assert. */
    vAssertCalled();
}

void fstat(void)
{
#if 0 /* This function is called! */
    /* Force an assert. */
    vAssertCalled();
#endif /* #if 0 */
}

void isatty(void)
{
    /* Force an assert. */
    vAssertCalled();
}

void lseek(void)
{
    /* Force an assert. */
    vAssertCalled();
}

int open(const char *file, int flags, ...)
{
    INTERNAL_NOT_USED(file);
    INTERNAL_NOT_USED(flags);

    /* Force an assert. */
    vAssertCalled();

    return INT_MAX;
}

int getpid(void)
{
    /* Force an assert. */
    vAssertCalled();

    return INT_MAX;
}

int kill(int pid, int sig)
{
    INTERNAL_NOT_USED(pid);
    INTERNAL_NOT_USED(sig);

    /* Force an assert. */
    vAssertCalled();

    return 0;
}
