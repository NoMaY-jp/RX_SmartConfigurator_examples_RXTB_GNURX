#include "platform.h"

#if BSP_CFG_RTOS_USED != 0

#if defined(__ICCRX__)

void main( void );

/* Never called but necessary for linking without an undefined error. */
void main( void )
{
    /* Nothing to do. */
}

#endif /* defined(__ICCRX__) */

#else

#if BSP_CFG_HEAP_BYTES == 0

#if defined(__CCRX__) || defined(__GNUC__)

int8_t *sbrk( size_t size );

/* Maybe not called but necessary for linking without an undefined error. */
int8_t *sbrk( size_t size )
{
    INTERNAL_NOT_USED( size );

    return (int8_t *)-1;
}

#endif /* defined(__CCRX__) || defined(__GNUC__) */

#endif /* BSP_CFG_HEAP_BYTES == 0 */

#endif /* BSP_CFG_RTOS_USED != 0 */
