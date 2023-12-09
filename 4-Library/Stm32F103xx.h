/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: Library                                 **/
/** File Name : Stm32F103xx.h                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#ifndef  STM32F103XX_H_
#define  STM32F103XX_H_


/******************************    Various Memory Base Addresses    ******************************/

#define  FLASH_BASE_ADDRESS   0x08000000UL  
#define  SRAM_BASE_ADDRESS    0x20000000UL  
#define  ROM_BASE_ADDRESS     0x1FFFB000UL

/******************************    APB2 Peripheral Base Addresses       ******************************/

#define  GPIOA_BASE_ADDRESS   0x40010800UL
#define  GPIOB_BASE_ADDRESS   0x40010C00UL
#define  GPIOC_BASE_ADDRESS   0x40011000UL
#define  GPIOD_BASE_ADDRESS   0x40011400UL
#define  GPIOE_BASE_ADDRESS   0x40011800UL
#define  GPIOF_BASE_ADDRESS   0x40011C00UL
#define  GPIOG_BASE_ADDRESS   0x40012000UL

/******************************    AHB Peripheral Base Addresses    ******************************/

#define  RCC_BASE_ADDRESS    0x40021000UL


/******************************    CORTEX-M4 Core Peripheral Base Addresses    ******************************/
#define    NVIC_BASE_ADDRESS   0xE000E100UL

#define    SYST_BASE_ADDRESS   0xE000E010UL

#define    SCB_BASE_ADDRESS    0xE000ED00UL


/******************************    RCC Register Definitions Structure  ******************************/

typedef struct
{
	volatile uint32_t RCC_CR;        /* Clock control register */
	volatile uint32_t RCC_CFGR;      /* Clock configuration register */
	volatile uint32_t RCC_CIR;       /* Clock interrupt register */
	volatile uint32_t RCC_APB2RSTR;  /* APB2 peripheral reset register  */
	volatile uint32_t RCC_APB1RSTR;  /* APB1 peripheral reset register  */
	volatile uint32_t RCC_AHBENR;    /* AHB peripheral clock enable register */
	volatile uint32_t RCC_APB2ENR;   /* APB2 peripheral clock enable register  */
	volatile uint32_t RCC_APB1ENR;   /* APB1 peripheral clock enable register  */
	volatile uint32_t RCC_BDCR;      /* Backup domain control register */
	volatile uint32_t RCC_CSR;       /* Control/status register */
}RCC_Reg_t;

/******************************    RCC Peripheral Definitions       ******************************/
#define   RCC  ((RCC_Reg_t*)RCC_BASE_ADDRESS)


/******************************    GPIO Register Definitions Structure  ******************************/

typedef  struct
{
	volatile  uint32_t  CR[2];          /*Port configuration register low , High */
	volatile  uint32_t  IDR;            /*GPIO PORT input data Register*/
	volatile  uint32_t  ODR;            /*GPIO PORT Output data Register*/
	volatile  uint32_t  BSRR;           /*GPIO PORT Bit set/Reset Register*/
	volatile  uint32_t  BRR;            /*GPIO PORT Bit Reset Register*/
	volatile  uint32_t  LCKR;           /*GPIO PORT Lock Register*/
	volatile  uint32_t  AFIO_EVCR;      /* Event control register  */
	volatile  uint32_t  AFIO_MAPR;      /* AF remap and debug I/O configuration register */
	volatile  uint32_t  AFIO_EXTICR[4]; /* External interrupt configuration register 1,2,3,4 */	
	volatile  uint32_t  AFIO_MAPR2;     /* AF remap and debug I/O configuration register2  */

}GPIO_RegDef_t;	

/******************************    GPIO Peripheral Definitions       ******************************/

#define   GPIOA     ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define   GPIOB     ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define   GPIOC     ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define   GPIOD     ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define   GPIOE     ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define   GPIOF     ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define   GPIOG     ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)


/******************************    Systick Register Definitions Structure  ******************************/

typedef  struct
{
	volatile  uint32_t  SYST_CSR;            /*SysTick Control and Status Register*/
	volatile  uint32_t  SYST_RVR;            /*SysTick Reload Value Register*/
	volatile  uint32_t  SYST_CVR;            /* SysTick Current Value Register */
	volatile  uint32_t   SYST_CALIB;         /* SysTick Calibration Value Register */

}SYSTICK_RegDef_t;

/******************************    SYSTICK Peripheral Definitions       ******************************/
#define   SYSTICK  ((SYSTICK_RegDef_t*)SYST_BASE_ADDRESS)


/******************************    NVIC Register Definitions   ******************************/

/* if you want to work by Struct */

typedef struct
{
	volatile uint32_t ISER[8]; /* Interrupt Set-enable Registers */
	volatile uint32_t Reserved_1[24]; /* Offset */
	volatile uint32_t ICER[8]; /* Interrupt Clear-enable Registers */
	volatile uint32_t Reserved_2[24]; /* Offset */
	volatile uint32_t ISPR[8]; /* Interrupt Set-pending Registers */
	volatile uint32_t Reserved_3[24]; /* Offset */
	volatile uint32_t ICPR[8]; /* Interrupt Clear-pending Registers */
	volatile uint32_t Reserved_4[24]; /* Offset */
	volatile uint32_t IABR[8]; /* Interrupt Active Bit Registers */
	volatile uint32_t Reserved_5[56]; /* Offset */
	volatile uint8_t  IPR[240] ; /* Interrupt Priority Registers */
	volatile uint32_t Reserved_6[643]; /* Offset */
	volatile uint32_t STIR; /* Software Trigger Interrupt Register*/

}NVIC_Reg_t;
/******************* NVIC structure pointer **********************/
#define      NVIC		((NVIC_Reg_t *)(NVIC_BASE_ADDRESS))


/* if you want to work by Macros ,but you change in our code only delete [NVIC->] */

//#define  ISER    ((volatile uint32_t*)0xE000E100) /* Interrupt Set-enable Registers */
//#define  ICER    ((volatile uint32_t*)0XE000E180) /* Interrupt Clear-enable Registers */
//#define  ISPR    ((volatile uint32_t*)0XE000E200) /* Interrupt Set-pending Registers */
//#define  ICPR    ((volatile uint32_t*)0XE000E280) /* Interrupt Clear-pending Registers */
//#define  IABR    ((volatile uint32_t*)0xE000E300) /* Interrupt Active Bit Registers */
//#define  IPR     ((volatile uint8_t*)0xE000E400) /* Interrupt Priority Registers */
//#define  STIR    ((volatile uint32_t*)0xE000EF00) /* Software Trigger Interrupt Register*/


/******************************    SCB Register Definitions   ******************************/
typedef struct
{
	volatile  uint32_t   CPUID;
	volatile  uint32_t   ICSR;
	volatile  uint32_t   VTOR;
	volatile  uint32_t   AIRCR;
	volatile  uint32_t   SCR;
	volatile  uint32_t   CCR;
	volatile  uint32_t   SHPR1;
	volatile  uint32_t   SHPR2;
	volatile  uint32_t   SHPR3;
	volatile  uint32_t   SHCSR;
	volatile  uint32_t   CFSR;
	volatile  uint32_t   HFSR;
	volatile  uint32_t   MMAR;
	volatile  uint32_t   BFAR;
	volatile  uint32_t   AFSR;
}SCB_Reg_t;

/******************************    SCB structure pointer **********************/
#define      SCB		((SCB_Reg_t *)(SCB_BASE_ADDRESS))

/******************************    APB1 Peripheral Base Addresses       ******************************/






#endif
