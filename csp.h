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
*                                      uC/CSP COMMON DRIVER API
* Date          : 10/10/2011
* Filename      : csp.h
* Version       : V1.00
* Programmer(s) : LGB
*********************************************************************************************************
* Note(s)       : 
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  CSP_MODULE_PRESENT
#define  CSP_MODULE_PRESENT


/*$PAGE*/
/*
*********************************************************************************************************
*                                CHIP SUPPORT PACKAGE MODULE VERSION NUMBER
*
* Note(s) : (1) (a) The chip support package module software version is denoted as follows :
*
*                       Vx.yy
*
*                           where
*                                   V               denotes 'Version' label
*                                   x               denotes major software version revision number
*                                   yy              denotes minor software version revision number
*
*               (b) The software version label #define is formatted as follows :
*
*                       ver = x.yy * 100
*
*                           where
*                                   ver             denotes software version number scaled as an integer value
*                                   x.yy            denotes software version number
*********************************************************************************************************
*/

#define  CSP_VERSION                                     100u   /* See Note #1.                        */



/*$PAGE*/
/*
*********************************************************************************************************
*                                        CHIP SUPPORT PACKAGE INCLUDE FILES
*
* Note(s) : (1) The chip support package files are located in the following directories :
*
*               (a) \<Your Product Application>\csp_cfg.h
*
*               (b) \<Chip Support Package>\MCU\csp.c
*                                              \csp.h
*
*               (c) \<Chip Support Package>\MCU\<manufacturer>\<family>\csp_grp_def.h
*                                                                      \csp_*.c
*
*               (d) \<Chip Support Package>\MCU\<manufacturer>\<family>\<dev>\csp_dev_def.h
*
*               (e) \<Chip Support Package>\OS\<os>\csp_os.c
*                                                  \csp_os.h
*
*                       where
*                               <Your Product Application>      directory path for Your Product's Application.
*                               <Chip Support Package>          directory path for chip support package.
*                               <manufacturer>                  directory name for microcontroller manufacturer.
*                               <family>                        directory name for microcontroller family.
*                               <dev>                           directory name for specific microcontroller on the same family.
*                               <os>                            directory name for specific operating system  (OS)
*
*           (2) CPU-configuration software files are located in the following directories :
*
*               (a) \<CPU-Compiler Directory>\cpu_def.h
*
*               (b) \<CPU-Compiler Directory>\<cpu>\<compiler>\cpu*.*
*
*                       where
*                               <CPU-Compiler Directory>        directory path for common   CPU-compiler software
*                               <cpu>                           directory name for specific processor (CPU)
*                               <compiler>                      directory name for specific compiler
*
*           (3) NO compiler-supplied standard library functions are used by the chip support package
*
*               (a) Standard library functions are implemented in the custom library module(s) :
*
*                       \<Custom Library Directory>\lib*.*
*
*                           where
*                                   <Custom Library Directory>      directory path for custom library software
*
*           (4) Compiler MUST be configured to include as additional include path directories :
*
*               (a) '\<Your Product Application>\'  directory                                    See Note #1a
*
*               (b) '\<Chip Support Package>\MCU\'  directory                                    See Note #1b
*
*               (c) '\<Custom Library Directory>\'  directory                                    See Note #3a
*
*               (d) Specific port directories :
*
*                   (1) (A) '\<CPU-Compiler Directory>\'                            directory    See Note #2
*                       (B) '\<CPU-Compiler Directory>\<cpu>\<compiler>'            directory
*
*                   (2) '\<Chip Support Package>\MCU\<manufacturer>\<family>\'      directory    See Note #1c
*
*                   (3) '\<Chip Support Package>\MCU\<manufacturer>\<family>\<dev>' directory    See Note #1d
*
*                   (3) '\<Chip Support Package>\OS\<os>\'                          directory    See Note #1e
*
*                       where
*                               <Your Product Application>      directory path for Your Product's Application
*                               <Chip Support Package>          directory path for chip support package
*                               <Custom Library Directory>      directory path for custom  library software
*                               <CPU-Compiler Directory>        directory path for common  CPU-compiler software
*                               <manufacturer>                  directory name for microcontroller manufacturer.
*                               <family>                        directory name for microcontroller family.
*                               <dev>                           directory name for specific microcontroller on the same family.
*                               <os>                            directory name for specific operating system  (OS)
*
*           (5) An application MUST pre-processor include ONLY this chip support package header file,
*               'csp.h'.  All other chip support package files are included via this main header file.
*
*               See also 'MODULE  Note #1'.
*********************************************************************************************************
*/


#include  <os_cpu.h>
#include  <lpc17xx.h>




/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   CSP_MODULE
#define  CSP_EXT
#else
#define  CSP_EXT  extern
#endif


/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                               CHIP SUPPORT PACKAGE OSCILLATOR CONFIGURATION
*
* Note(s) : (1) Configure CSP_CFG_PM_MAIN_XTAL_FREQ_HZ  with the frequency in Hertz of the main oscillator.
*
*           (2) Configure CSP_CFG_PM_SLOW_XTAL_FREQ_HZ  with the frequency in Hertz of the slow oscillator.
*
*           (3) Configure CSP_CFG_PM_EXT_CLK_FREQ_HZ    with the frequency on Hertz of the external clock.
*********************************************************************************************************
*/

#define  CSP_CFG_PM_MAIN_XTAL_FREQ_HZ             12000000u
#define  CSP_CFG_PM_SLOW_XTAL_FREQ_HZ                32768u
#define  CSP_CFG_PM_EXT_CLK_FREQ_HZ                      0u


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  DEF_BIT_24                               0x01000000uL
#define  DEF_BIT_25                               0x02000000uL
#define  DEF_BIT_26                               0x04000000uL


                                                                /* ---------- PCONP REGISTERS RESERVED VALUES -------- */
#define  CSP_PM_PER_CLK_NBR_PCONP_RSVD0               0u
#define  CSP_PM_PER_CLK_NBR_PCONP_RSVD1               5u
#define  CSP_PM_PER_CLK_NBR_PCONP_RSVD2              11u
#define  CSP_PM_PER_CLK_NBR_PCONP_RSVD3              20u
#define  CSP_PM_PER_CLK_NBR_PCONP_RSVD4              28u

                                                                /* --------- PCLKSEL REGISTERS RESERVED VALUES -------- */
#define  CSP_PM_PER_CLK_NBR_PCLKSEL_RSVD0             5u  
#define  CSP_PM_PER_CLK_NBR_PCLKSEL_RSVD1             9u  
#define  CSP_PM_PER_CLK_NBR_PCLKSEL_RSVD2            20u  
#define  CSP_PM_PER_CLK_NBR_PCLKSEL_RSVD3            28u  

                                                                /* ---------------- REGISTER DEFINES ------------------ */
#define  CSP_PM_ADDR_PLL0                       ( (INT32U )0x400FC080)
#define  CSP_PM_ADDR_PLL1                       ( (INT32U )0x400FC0A0)
  
#define  CSP_PM_REG_PLLCTRL0                    (*(CPU_REG32 *)(CSP_PM_ADDR_PLL0 + 0x00))
#define  CSP_PM_REG_PLLCFG0                     (*(CPU_REG32 *)(CSP_PM_ADDR_PLL0 + 0x04))
#define  CSP_PM_REG_PLLSTAT0                    (*(CPU_REG32 *)(CSP_PM_ADDR_PLL0 + 0x08))
#define  CSP_PM_REG_PLLFEED0                    (*(CPU_REG32 *)(CSP_PM_ADDR_PLL0 + 0x0C))

#define  CSP_PM_REG_PLLCTRL1                    (*(CPU_REG32 *)(CSP_PM_ADDR_PLL1 + 0x00))
#define  CSP_PM_REG_PLLCFG1                     (*(CPU_REG32 *)(CSP_PM_ADDR_PLL1 + 0x04))
#define  CSP_PM_REG_PLLSTAT1                    (*(CPU_REG32 *)(CSP_PM_ADDR_PLL1 + 0x08))
#define  CSP_PM_REG_PLLFEED1                    (*(CPU_REG32 *)(CSP_PM_ADDR_PLL1 + 0x0C))

                                                                /* ---------- POWER CONTROL REGISTER DEFINES ---------- */
#define  CSP_PM_REG_PCON                        (*(CPU_REG32 *)(0x400FC0C0))
#define  CSP_PM_REG_PCONP                       (*(CPU_REG32 *)(0x400FC0C4))

                                                                /* -------- CLOCK SOURCE SELECT REGISTER DEFINE ------- */
#define  CSP_PM_REG_CLKSRCSEL                   (*(CPU_REG32 *)(0x400FC10Cu))

                                                                /* ---------- PLL STATUS REGISTER BIT DEFINES --------- */
#define  CSP_PM_MSK_PLLSTAT0_MSEL               DEF_BIT_FIELD(15,  0)
#define  CSP_PM_MSK_PLLSTAT0_PSEL               DEF_BIT_FIELD(8 , 16)
#define  CSP_PM_MSK_PLLSTAT0_PLLE               DEF_BIT_24      /* Read-back for the PLL enable bit.                    */
#define  CSP_PM_MSK_PLLSTAT0_PLLC               DEF_BIT_25      /* Read-back for the PLL connect bit.                   */
#define  CSP_PM_MSK_PLLSTAT0_PLOCK              DEF_BIT_26      /* Refkect the PLL lock status.                         */

#define  CSP_PM_MSK_PLLSTAT1_MSEL               DEF_BIT_FIELD(5,  0)
#define  CSP_PM_MSK_PLLSTAT1_PSEL               DEF_BIT_FIELD(2 , 5)
#define  CSP_PM_MSK_PLLSTAT1_PLLE               DEF_BIT_08      /* Read-back for the PLL enable bit.                    */
#define  CSP_PM_MSK_PLLSTAT1_PLLC               DEF_BIT_09      /* Read-back for the PLL connect bit.                   */
#define  CSP_PM_MSK_PLLSTAT1_PLOCK              DEF_BIT_10      /* Refkect the PLL lock status.                         */


                                                                /* --------- CLOCK DIVIDERS REGISTER DEFINITION ------- */
#define  CSP_PM_REG_CCLKCFG                     (*(CPU_REG32 *)(0x400FC104))
#define  CSP_PM_REG_USBCLKCFG                   (*(CPU_REG32 *)(0x400FC108))
#define  CSP_PM_REG_IRCTRIM                     (*(CPU_REG32 *)(0x400FC1A4))
#define  CSP_PM_REG_PCLKSEL0                    (*(CPU_REG32 *)(0x400FC1A8))
#define  CSP_PM_REG_PCLKSEL1                    (*(CPU_REG32 *)(0x400FC1AC))

                                                                /* ------ INTERNAL OSCILLATOR/CLOCK FREQUENCY ------- */
#define  CSP_PM_INT_RC_OSC_FREQ_HZ               4000000L       /* IRC frequency is 4Mhz.                             */
                                                                /* RTC oscillator frequency                           */
#define  CSP_PM_INT_RTC_OSC_FREQ_HZ              CSP_CFG_PM_SLOW_XTAL_FREQ_HZ

/*
*********************************************************************************************************
*                                            CLOCK DEFINES
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*                                            GPIO GENERIC DEFINES
*
* Note(s) : (1) 'CSP_GPIO_DIR_xxx' defines the direction of the pin when the pin is controlled by the GPIO controller..
* 
*           (2) Driver mode flags defines the pin configuration:
*                
*                   CSP_GPIO_FLAG_MODE_NONE         Pin has a has neither pull-up nor pull-down resister.
*                   CSP_GPIO_FLAG_MODE_PULLUP       Pin has a pull-up   resistor enabled.
*                   CSP_GPIO_FLAG_MODE_PULLDOWN     Pin has a pull-down resistor enabled.
*                   CSP_GPIO_FLAG_MODE_REPEATER     Pin has repeater mode enabled
*                   CSP_GPIO_FLAG_MODE_OPEN_DRAIN   Pin is in normal open drain mode.
*                   CSP_GPIO_FLAG_MODE_SCH_TRIGGER  pin has schmitt trigger enabled.
* 
*           (3) The Option flags allows to perform optional operation in the GPIO configuration.
*                   CSP_GPIO_OPT_RD_WR_EN   Controlled pin is affected by writes to the port's.
*                   CSP_GPIO_OPT_RD_WR_DIS  Controlled pin is not affected by writes to the port.
* 
*           (3) I/O pins are shared with other peripherals or functions. 'CSP_GPIO_FNCT_xx' controls the IO function 
*               for a specific pin.
*********************************************************************************************************
*/

#define PORT0       0u
#define PORT1       1u
#define PORT2       2u
#define PORT3       3u

static LPC_GPIO_TypeDef (* const LPC_GPIO[4]) = { LPC_GPIO0, LPC_GPIO1, LPC_GPIO2, LPC_GPIO3 };


/*
*********************************************************************************************************
*                                             BIT MACRO'S
*********************************************************************************************************
*/

                                                        /* ---------------------- CPU WORD SIZE ----------------------- */
#define  CPU_WORD_SIZE_08                          1u   /*  8-bit word size (in octets).                                */
#define  CPU_WORD_SIZE_16                          2u   /* 16-bit word size (in octets).                                */
#define  CPU_WORD_SIZE_32                          4u   /* 32-bit word size (in octets).                                */
#define  CPU_WORD_SIZE_64                          8u   /* 64-bit word size (in octets).                                */


#define  CPU_CFG_DATA_SIZE              CPU_WORD_SIZE_32        /* Defines CPU data    word size  (in octets).          */


#define  DEF_INT_32U_MIN_VAL                               0uL
#define  DEF_INT_32U_MAX_VAL                      4294967295uL

                                                                /* ------------------ OCTET DEFINES ------------------- */
#define  DEF_OCTET_NBR_BITS                                8
#define  DEF_OCTET_MASK                                 0xFFuL

#define  DEF_NIBBLE_NBR_BITS                               4
#define  DEF_NIBBLE_MASK                                0x0FuL


#define  DEF_INT_CPU_NBR_BITS                           (CPU_CFG_DATA_SIZE * DEF_OCTET_NBR_BITS)

#define  DEF_INT_CPU_U_MIN_VAL                           DEF_INT_32U_MIN_VAL
#define  DEF_INT_CPU_U_MAX_VAL                           DEF_INT_32U_MAX_VAL

/*
*********************************************************************************************************
*                                              DEF_BIT()
*
* Description : Create bit mask with single, specified bit set.
*
* Argument(s) : bit         Bit number of bit to set.
*
* Return(s)   : Bit mask with single, specified bit set.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) 'bit' values that overflow the target CPU &/or compiler environment (e.g. negative 
*                       or greater-than-CPU-data-size values) MAY generate compiler warnings &/or errors.
*
*                   (b) To avoid overflowing any target CPU &/or compiler's integer data type, unsigned 
*                       bit constant '1' is suffixed with 'L'ong integer modifier.
*
*                       This may still be insufficient for CPUs &/or compilers that support 'long long' 
*                       integer data types, in which case 'LL' integer modifier should be suffixed.  
*                       However, since almost all 16- & 32-bit CPUs & compilers support 'long' integer 
*                       data types but many may NOT support 'long long' integer data types, only 'long' 
*                       integer data types & modifiers are supported.
*********************************************************************************************************
*/

#define  DEF_BIT(bit)                           (1uL << (bit))


/*
*********************************************************************************************************
*                                          DEF_BIT_IS_SET()
*
* Description : Determine if specified bit(s) in a value are set.
*
* Argument(s) : val         Value to check for specified bit(s) set.
*
*               mask        Mask of bits to check if set.
*
* Return(s)   : DEF_YES, if ALL specified bit(s) are     set in value.
*
*               DEF_NO,  if ALL specified bit(s) are NOT set in value.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

#define  DEF_BIT_IS_SET(val, mask)                   ((((val) & (mask)) == (mask)) ? (DEF_YES) : (DEF_NO ))

/*
*********************************************************************************************************
*                                           DEF_BIT_FIELD()
*
* Description : Create & shift a contiguous bit field.
*
* Argument(s) : bit_field   Number of contiguous bits to set in the bit field.
*
*               bit_shift   Number of bit positions   to left-shift bit field.
*
* Return(s)   : Shifted bit field.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) 'bit_field'/'bit_shift' values that overflow the target CPU &/or compiler 
*                       environment (e.g. negative or greater-than-CPU-data-size values) MAY generate 
*                       compiler warnings &/or errors.
*
*                   (b) To avoid overflowing any target CPU &/or compiler's integer data type, unsigned 
*                       bit constant '1' is suffixed with 'L'ong integer modifier.
*
*                       This may still be insufficient for CPUs &/or compilers that support 'long long' 
*                       integer data types, in which case 'LL' integer modifier should be suffixed.  
*                       However, since almost all 16- & 32-bit CPUs & compilers support 'long' integer 
*                       data types but many may NOT support 'long long' integer data types, only 'long' 
*                       integer data types & modifiers are supported.
*********************************************************************************************************
*/

#define  DEF_BIT_FIELD(bit_field, bit_shift)         ((((bit_field) >= DEF_INT_CPU_NBR_BITS) ? (DEF_INT_CPU_U_MAX_VAL)     \
                                                                                             : (DEF_BIT(bit_field) - 1uL)) \
                                                                                                    << (bit_shift))



/*
*********************************************************************************************************
*                                             I2C DEFINES
*
*  Note(s) : (1) The I2C specification defines the following speeds mode.
*
*                (a)  Standard   mode.  Transfer rate up to     100Kbit/s
*                (b)  Fast       mode.  Trasnfer rate up to     400Kbits/s
*                (c)  High Speed mode.  Transfer rate up to 3.4  Mbits/s
*
*            (2) The I2C specification defines the following addressing modes:
*   
*                (a)  7-bit addressing mode.
*                (b) 10-bit addressing mode.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             TIMER DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INTERRUPT DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                 SPI DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                    DEFINED IN FAMILIES csp_gpio.c
*********************************************************************************************************
*/

void           CSP_Init          	  (void);
																/* Direction.                                           */
void           CSP_GPIO_BitDir        (INT8U    port_nbr,
                                       INT8U   pins);

                                                                /* Clear a bit.                                         */
void           CSP_GPIO_BitClr        (INT8U    port_nbr,
                                       INT8U   pins);

                                                                /* Set a bit.                                           */
void           CSP_GPIO_BitSet        (INT8U    port_nbr,
                                       INT8U   pins);


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                    DEFINED IN FAMILIES csp_int.c
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                    DEFINED IN FAMILIES csp_pm.c
*********************************************************************************************************
*/

INT32U  CSP_PM_CPU_ClkFreqGet (void);

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                   DEFINED IN FAMILIES csp_tmr.c
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                   DEFINED IN FAMILIES csp_i2c.c
*
* Note(s) : (1) I2C common API limitations.
*               (a) Master mode only.
*               (b) 7-bit address.
*               (c) Only synchronous transfers (blocking) are supported.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                         /* End of CSP module include.                           */
