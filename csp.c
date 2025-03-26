/*
*********************************************************************************************************
*                                              uC/CSP
*                                        Chip Support Package
*
*                            (c) Copyright 2010; Micrium, Inc.; Weston, FL
*                         (c) Copyright 2003-2010; Micrium, Inc.; Weston, FL
*
*               All rights reserved. Protected by international copyright laws.
*
*               uC/CSP is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                      uC/CSP COMMON DRIVER API.
* Date          : 10/10/2011
* Filename      : csp.c
* Version       : V1.00
* Programmer(s) : LGB
*********************************************************************************************************
* Note(s)       : 
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/


#define  CSP_MODULE

#include "csp.h"


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/

                                                            /* ------------------------ TICKS ----------------------- */
#define  OS_CFG_TICK_RATE_HZ            1000u               /* Tick rate in Hertz (10 to 1000 Hz)                     */
#define  OS_CFG_TICK_TASK_PRIO            10u               /* Priority                                               */
#define  OS_CFG_TICK_TASK_STK_SIZE       128u               /* Stack size (number of CPU_STK elements)                */
#define  OS_CFG_TICK_WHEEL_SIZE           17u               /* Number of 'spokes' in tick  wheel; SHOULD be prime     */


INT32U     const  OSCfg_TickRate_Hz          = ( INT32U ) OS_CFG_TICK_RATE_HZ;


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         CSP_GPIO_BitDir()
*
* Description : Clear a group of pins for a specific I/O port.
*
* Argument(s) : port_nbr    GPIO port number. (See 'CSP_GPIO_Cfg()' note #1).
*
*               pins        Bit mask specifying which pins to clear.
*
* Return(s)   : none
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  CSP_GPIO_BitDir (INT8U    port_nbr,
                       INT8U  pins)
{
    LPC_GPIO[port_nbr]->FIODIR |= pins;
}

/*
*********************************************************************************************************
*                                         CSP_GPIO_BitClr()
*
* Description : Clear a group of pins for a specific I/O port.
*
* Argument(s) : port_nbr    GPIO port number. (See 'CSP_GPIO_Cfg()' note #1).
*
*               pins        Bit mask specifying which pins to clear.
*
* Return(s)   : none
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  CSP_GPIO_BitClr (INT8U   port_nbr,
                       INT8U  pins)
{
    LPC_GPIO[port_nbr]->FIOCLR |= pins;
}

/*
*********************************************************************************************************
*                                         CSP_GPIO_BitSet()
*
* Description : Set a group of pins for a specific I/O port
*
* Argument(s) : port_nbr    GPIO port number. (See 'CSP_GPIO_Cfg()' note #1).
*
*               pins        Bit mask specifying which pins to set.
*
* Return(s)   : none
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  CSP_GPIO_BitSet (INT8U    port_nbr,
                       INT8U  pins)
{
    LPC_GPIO[port_nbr]->FIOSET |= pins;
}


/*
*********************************************************************************************************
*                                         CSP_PM_CPU_ClkFreqGet()
*
* Description : Return the CPU clock frequency.
*                   
* Argument(s) : none
*  
* Return(s)   : The CPU frequency in Hertz.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

INT32U  CSP_PM_CPU_ClkFreqGet (void)
{
    INT32U  cpu_freq;
    INT8U   cpu_div;
    INT16U  pll_mul;
    INT8U   pll_div;
    INT32U  reg_val;


    reg_val = CSP_PM_REG_CLKSRCSEL & DEF_BIT_FIELD(2u, 0u);
 
    switch (reg_val) {
        case 0u:
             cpu_freq = CSP_PM_INT_RC_OSC_FREQ_HZ;
             break;
    
        case 1u:
             cpu_freq = CSP_CFG_PM_MAIN_XTAL_FREQ_HZ;
             break;

        case 2u:
             cpu_freq = CSP_PM_INT_RTC_OSC_FREQ_HZ;
             break;
                  
        default:
             return ((INT32U)(0u));
    }
 
    pll_mul =   ((CSP_PM_REG_PLLSTAT0 & CSP_PM_MSK_PLLSTAT0_MSEL)          + 1u);
    pll_div = ((((CSP_PM_REG_PLLSTAT0 & CSP_PM_MSK_PLLSTAT0_PSEL)) >> 16u) + 1u);

    if (DEF_BIT_IS_SET(CSP_PM_REG_PLLSTAT0, (CSP_PM_MSK_PLLSTAT0_PLLE | 
                                             CSP_PM_MSK_PLLSTAT0_PLLC |
                                             CSP_PM_MSK_PLLSTAT0_PLOCK ))) {
        cpu_freq = ((cpu_freq * 2u * pll_mul) / pll_div);
    }
        
    cpu_div = CSP_PM_REG_CCLKCFG & DEF_BIT_FIELD(8u, 0u); 
    cpu_div++;
    
    cpu_freq /= cpu_div;
        
    return (cpu_freq);

}

/*
************************************************************************************************************************
*                                                INITIALIZE TICKER INTERRUPT
*
* Description: Initialize the the Tick Interrupt.
*
* Arguments  : none.
*
* Note(s)    : (1) This function MUST be called after OSStart() & after processor initialization.
************************************************************************************************************************
*/

void  OS_CSP_TickInit (void)
{
    INT32U  cnts;
    INT32U  cpu_freq;
    
    
    cpu_freq = CSP_PM_CPU_ClkFreqGet();                         /* Get the CPU clock                                    */
    cnts     = (cpu_freq / OSCfg_TickRate_Hz);                  /* Calculate the number of SysTick counts               */

    OS_CPU_SysTickInit(cnts);                                   /* Call the Generic OS Systick initialization           */
}

/*
*********************************************************************************************************
*                                             CSP_Init()
*
* Description : Initializes all Chip peripherals
*               
*
* Argument(s) : main().
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  CSP_Init (void)
{
    SystemInit();
                                           /* SystemClockUpdate() updates the SystemFrequency variable */
    SystemCoreClockUpdate();

    OS_CSP_TickInit();

    UARTInit(0, 9600);
}
