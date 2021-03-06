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

/* Hardware specifics. */
#include <intrinsics.h>

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

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
    #define configINCLUDE_PLATFORM_H_INSTEAD_OF_IODEFINE_H    2
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
#elif !defined( __RXV2 ) && !defined( __RXV3 ) && ( __VER__ < 414 )
    /* This version of the compiler is not supported because the CPU core is unknown. */
    #define portUSE_TASK_ACC_SUPPORT    0
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
    #define _portASM( ... )              __asm volatile ( #__VA_ARGS__ "\n" );
    #define portASM( ... )               _portASM( __VA_ARGS__ )
    #define portASM_LAB_NEXT( name )     _lab_##name
    #define portASM_LAB_PREV( name )     _lab_##name
    #define portASM_LAB( name_colon )    _portASM( _lab_##name_colon: )
    #define portASM_BEGIN                _Pragma( "diag_suppress = Pe010" )
    #define portASM_END                  _Pragma( "diag_default = Pe010" )
    /* *INDENT-ON* */
#endif /* if ( defined( __STDC_VERSION__ ) && ( __STDC_VERSION__ >= 199901L ) ) */

/* Workaround to reduce errors/warnings caused by e2 studio CDT's INDEXER and CODAN. */
#ifdef __CDT_PARSER__
    #ifndef __asm
        #define __asm    asm
    #endif
    #ifndef __attribute__
        #define __attribute__( ... )
    #endif
    #define portCDT_NO_PARSE( token )
#else
    #define portCDT_NO_PARSE( token )    token
#endif

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT    8     /* Could make four, according to manual. */
#define portSTACK_GROWTH      -1
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portNOP()    __no_operation()

/* Yield equivalent to "*portITU_SWINTR = 0x01; ( void ) ( *portITU_SWINTR == XXX );"
 * where portITU_SWINTR is the location of the software interrupt register
 * (0x000872E0) and XXX is an arbitrary number.  Don't rely on the assembler to
 * select a register, so instead  save and restore clobbered registers manually. */
/* *INDENT-OFF* */
#define portYIELD()             \
__asm volatile                  \
(                               \
    "PUSH.L R10              \n"\
    "MOV.L  #0x872E0, R10    \n"\
    "MOV.B  #0x1, [ R10 ]    \n"\
    "CMP    [ R10 ].UB, R10  \n"\
    "POP    R10                "\
    portCDT_NO_PARSE( ::: ) "cc"\
)
/* *INDENT-ON* */

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
#define portENABLE_INTERRUPTS()                           __set_interrupt_level( ( uint8_t ) 0 )
#ifdef configASSERT
    #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    configASSERT( ( __get_interrupt_level() <= configMAX_SYSCALL_INTERRUPT_PRIORITY ) )
    #define portDISABLE_INTERRUPTS()                      if( __get_interrupt_level() < configMAX_SYSCALL_INTERRUPT_PRIORITY ) __set_interrupt_level( ( uint8_t ) configMAX_SYSCALL_INTERRUPT_PRIORITY )
#else
    #define portDISABLE_INTERRUPTS()                      __set_interrupt_level( ( uint8_t ) configMAX_SYSCALL_INTERRUPT_PRIORITY )
#endif

/* Critical nesting counts are stored in the TCB. */
#define portCRITICAL_NESTING_IN_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
extern void vTaskEnterCritical( void );
extern void vTaskExitCritical( void );
#define portENTER_CRITICAL()                                           vTaskEnterCritical()
#define portEXIT_CRITICAL()                                            vTaskExitCritical()

/* As this port allows interrupt nesting... */
#define portSET_INTERRUPT_MASK_FROM_ISR()                              __get_interrupt_level(); portDISABLE_INTERRUPTS()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus )    __set_interrupt_level( ( uint8_t ) ( uxSavedInterruptStatus ) )

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
#pragma inline = forced
static __inline BaseType_t xPortIsInsideInterrupt( void )
{
    /* When the user stack pointer is used, the context is not interrupt.
     * When the interrupt stack pointer is used, the context is interrupt.
     * Don't call this function before the scheduler has started because
     * this function always returns pdTRUE before the timing. */
    return ( __get_PSW_register() & 0x00020000 /* PSW.U */ ) != 0 ? pdFALSE : pdTRUE;
}

/*-----------------------------------------------------------*/

#define portMEMORY_BARRIER()    __asm volatile ( "" portCDT_NO_PARSE( ::: ) "memory" )

/*-----------------------------------------------------------*/

/* Prevent warnings of undefined behaviour: the order of volatile accesses is
 * undefined - all warnings have been manually checked and are not an issue, and
 * the warnings cannot be prevent by code changes without undesirable effects. */
#pragma diag_suppress=Pa082

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
