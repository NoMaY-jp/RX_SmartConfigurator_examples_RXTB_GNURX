/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef PORTMACRO_H
#define PORTMACRO_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/* Hardware specifics. */
#include <machine.h>

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* If configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H is set to 0 then iodefine.h
 * is included and used in FreeRTOS Kernel's Renesas RX port.  If the macro is set
 * to 1 then platform.h is included and used in the port.  If the macro is set to 2
 * then neither iodefine.h nor platform.h are included.  If the macro is undefined,
 * it is set to 0 (CC-RX/GNURX) or 2 (ICCRX) internally for backward compatibility.
 * When the FIT configurator or the Smart Configurator is used, platform.h has to be
 * used. */
#ifndef configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H
    #define configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H    0
#endif

/* If configUSE_TASK_DPFPU_SUPPORT is set to 1 (or undefined) then each task will
 * be created without a DPFPU context, and a task must call vTaskUsesDPFPU() before
 * making use of any DPFPU registers.  If configUSE_TASK_DPFPU_SUPPORT is set to 2 then
 * tasks are created with a DPFPU context by default, and calling vTaskUsesDPFPU() has
 * no effect.  If configUSE_TASK_DPFPU_SUPPORT is set to 0 then tasks never take care
 * of any DPFPU context (even if DPFPU registers are used). */
#ifdef __DPFPU
    /* The compiler may use DPFPU registers. */
    #ifndef configUSE_TASK_DPFPU_SUPPORT
        #define configUSE_TASK_DPFPU_SUPPORT    1
    #endif
#else
    /* The compiler does not use DPFPU registers. */
    #ifdef configUSE_TASK_DPFPU_SUPPORT
        #undef configUSE_TASK_DPFPU_SUPPORT
    #endif
    #define configUSE_TASK_DPFPU_SUPPORT    0
#endif
#define portUSE_TASK_DPFPU_SUPPORT          configUSE_TASK_DPFPU_SUPPORT

#ifdef __FPU
    /* The compiler may use FPSW register. */
    #define portUSE_TASK_FPU_SUPPORT    1
#else
    /* The compiler does not use FPSW register. */
    #define portUSE_TASK_FPU_SUPPORT    0
#endif

#ifdef __RXV1
    /* The CPU has only one accumulator. */
    #define portUSE_TASK_ACC_SUPPORT    1
#elif !defined( __RXV2 ) && !defined( __RXV3 ) && ( __RENESAS_VERSION__ < 0x03010000 )
    /* The CPU is RXv1 and has only one accumulator. */
    #define portUSE_TASK_ACC_SUPPORT    1
#else
    /* The CPU has two accumulators. */
    #define portUSE_TASK_ACC_SUPPORT    2
#endif

/*-----------------------------------------------------------*/

/* Type definitions - these are a bit legacy and not really used now, other than
 * portSTACK_TYPE and portBASE_TYPE. */
#define portCHAR          char
#define portFLOAT         float
#define portDOUBLE        double
#define portLONG          long
#define portSHORT         short
#define portSTACK_TYPE    uint32_t
#define portBASE_TYPE     long

typedef portSTACK_TYPE   StackType_t;
typedef long             BaseType_t;
typedef unsigned long    UBaseType_t;

#if ( configUSE_16_BIT_TICKS == 1 )
    typedef uint16_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#else
    typedef uint32_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
     * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#endif

/*-----------------------------------------------------------*/

/* Inline assembler specifics. */
#if ( defined( __STDC_VERSION__ ) && ( __STDC_VERSION__ >= 199901L ) )
    /* *INDENT-OFF* */
    #ifdef __CDT_PARSER__
        #define _portASM( ... )          (void) ( #__VA_ARGS__ "\n" );
    #else
        #define _portASM( ... )          __VA_ARGS__
    #endif
    #define portASM( ... )               _portASM( __VA_ARGS__ )
    #define portASM_LAB_NEXT( name )     ?+
    #define portASM_LAB_PREV( name )     ?-
    #define portASM_LAB( name_colon )    _portASM( ?: )
    #define portASM_BEGIN
    #define portASM_END
    /* *INDENT-ON* */
#endif /* if ( defined( __STDC_VERSION__ ) && ( __STDC_VERSION__ >= 199901L ) ) */

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT    8     /* Could make four, according to manual. */
#define portSTACK_GROWTH      -1
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portNOP()    nop()

#if !defined( RENESAS_SIMULATOR_DEBUGGING ) || ( RENESAS_SIMULATOR_DEBUGGING == 0 )

/* Yield equivalent to "*portITU_SWINTR = 0x01; ( void ) ( *portITU_SWINTR == XXX );"
 * where portITU_SWINTR is the location of the software interrupt register
 * (0x000872E0) and XXX is an arbitrary number.  Don't rely on the assembler to
 * select a register, so instead  save and restore clobbered registers manually. */
/* *INDENT-OFF* */
#pragma inline_asm vPortYield
static void vPortYield( void )
{
#ifndef __CDT_PARSER__
    /* Save clobbered register - may not actually be necessary if inline asm
     * functions are considered to use the same rules as function calls by the
     * compiler. */
    PUSH.L R5
    /* Set ITU SWINTR. */
    MOV.L  #000872E0H, R5
    MOV.B  #1, [ R5 ]
    /* Read back to ensure the value is taken before proceeding. */
    CMP    [ R5 ].UB, R5
    /* Restore clobbered register to its previous value. */
    POP    R5
#endif
}
/* *INDENT-ON* */

#else /* !defined( RENESAS_SIMULATOR_DEBUGGING ) || ( RENESAS_SIMULATOR_DEBUGGING == 0 ) */

/* *INDENT-OFF* */
#pragma inline_asm vPortYield
static void vPortYield( void )
{
#ifndef __CDT_PARSER__
    /* Disable the timer 1 interrupt. */
    /* _IEN( _CMT1_CMI1 ) = 0; */
    MOV.L #00087203H, R14
    BCLR  #05H, [R14].B
    /* Read back and test to complete a write access here. */
    /* if( _IEN( _CMT1_CMI1 ) == 0 ){}else{} */
    BTST  #05H, [R14].B

    /* Enable interrupt on compare match. (Divide the PCLK by 8.) */
    /* CMT1.CMCR.WORD = 0x00C0; */
    MOV.L #00088008H, R15
    MOV.W #00C0H, [R15]

    /* Wait for the timer 1 interrupt request. */
    /* while( _IR( _CMT1_CMI1 ) == 0 ){} */
    MOV.L #0008701DH, R5
?:  BTST  #00H, [R5].B
    BEQ   ?-

    /* Disable interrupt on compare match. (Divide the PCLK by 8.) */
    /* CMT1.CMCR.WORD = 0x0080; */
    MOV.W #0080H, [R15]

    /* Enable the timer 1 interrupt. */
    /* _IEN( _CMT1_CMI1 ) = 1; */
    BSET  #05H, [R14].B
    /* Read back and test to complete a write access here. */
    /* if( _IEN( _CMT1_CMI1 ) == 1 ){}else{} */
    BTST  #05H, [R14].B
#endif
}
/* *INDENT-ON* */

#endif /* !defined( RENESAS_SIMULATOR_DEBUGGING ) || ( RENESAS_SIMULATOR_DEBUGGING == 0 )) */

#define portYIELD()                                       vPortYield()
#define portYIELD_FROM_ISR( x )                           do { if( ( x ) != pdFALSE ) portYIELD(); } while( 0 )

/* These macros should not be called directly, but through the
 * taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros.  An extra check is
 * performed if configASSERT() is defined to ensure an assertion handler does not
 * inadvertently attempt to lower the IPL when the call to assert was triggered
 * because the IPL value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY
 * when an ISR safe FreeRTOS API function was executed.  ISR safe FreeRTOS API
 * functions are those that end in FromISR.  FreeRTOS maintains a separate
 * interrupt API to ensure API function and interrupt entry is as fast and as
 * simple as possible. */
#define portENABLE_INTERRUPTS()                           set_ipl( ( long ) 0 )
#ifdef configASSERT
    #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    configASSERT( ( get_ipl() <= configMAX_SYSCALL_INTERRUPT_PRIORITY ) )
    #define portDISABLE_INTERRUPTS()                      if( get_ipl() < configMAX_SYSCALL_INTERRUPT_PRIORITY ) set_ipl( ( long ) configMAX_SYSCALL_INTERRUPT_PRIORITY )
#else
    #define portDISABLE_INTERRUPTS()                      set_ipl( ( long ) configMAX_SYSCALL_INTERRUPT_PRIORITY )
#endif

/* Critical nesting counts are stored in the TCB. */
#define portCRITICAL_NESTING_IN_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
extern void vTaskEnterCritical( void );
extern void vTaskExitCritical( void );
#define portENTER_CRITICAL()                                           vTaskEnterCritical()
#define portEXIT_CRITICAL()                                            vTaskExitCritical()

/* As this port allows interrupt nesting... */
#define portSET_INTERRUPT_MASK_FROM_ISR()                              ( UBaseType_t ) get_ipl(); set_ipl( ( long ) configMAX_SYSCALL_INTERRUPT_PRIORITY )
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus )    set_ipl( ( long ) uxSavedInterruptStatus )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    void vFunction( void * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          void vFunction( void * pvParameters )

/*-----------------------------------------------------------*/

/* If portUSE_TASK_DPFPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without a DPFPU context and must call vPortTaskUsesDPFPU() to give
 * themselves a DPFPU context before using any DPFPU instructions.  If
 * portUSE_TASK_DPFPU_SUPPORT is set to 2 then all tasks will have a DPFPU context
 * by default. */
#if ( portUSE_TASK_DPFPU_SUPPORT == 1 )
    void vPortTaskUsesDPFPU( void );
#else

    /* Each task has a DPFPU context already, so define this function away to
     * nothing to prevent it being called accidentally. */
    #define vPortTaskUsesDPFPU()
#endif
#define portTASK_USES_DPFPU()             vPortTaskUsesDPFPU()

/* Definition to allow compatibility with existing FreeRTOS Demo using flop.c. */
#define portTASK_USES_FLOATING_POINT()    vPortTaskUsesDPFPU()

/*-----------------------------------------------------------*/

/* Checks whether the current execution context is interrupt.
 * Return pdTRUE if the current execution context is interrupt,
 * pdFALSE otherwise. */
#pragma inline xPortIsInsideInterrupt
static BaseType_t xPortIsInsideInterrupt( void )
{
    /* When the user stack pointer is used, the context is not interrupt.
     * When the interrupt stack pointer is used, the context is interrupt.
     * Don't call this function before the scheduler has started because
     * this function always returns pdTRUE before the timing. */
    return ( get_psw() & 0x00020000 /* PSW.U */ ) != 0 ? pdFALSE : pdTRUE;
}

/*-----------------------------------------------------------*/

#pragma inline_asm vPortMemoryBarrier
static void vPortMemoryBarrier( void )
{
}

#define portMEMORY_BARRIER()    vPortMemoryBarrier()

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
