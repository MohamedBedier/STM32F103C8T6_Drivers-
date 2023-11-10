/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : RCC_Interface.h                             **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/**
 * @brief: define enum to carry Type of CLock source
 */
typedef enum
{
	HSE=0,
	HSI,
	PLL

}ClkType_t;

/**
 * @brief: define enum to carry Type of CLock status
 */
typedef enum
{
	CLK_ON=0,
	CLK_OFF

}ClkStatus_t;

/**
 * @brief: define enum to carry PLL multiplication factors
 */
typedef enum
{
	PLL_INPUT_CLK_X2=0,
	PLL_INPUT_CLK_X3,
	PLL_INPUT_CLK_X4,
	PLL_INPUT_CLK_X5,
	PLL_INPUT_CLK_X6,
	PLL_INPUT_CLK_X7,
	PLL_INPUT_CLK_X8,
	PLL_INPUT_CLK_X9,
	PLL_INPUT_CLK_X10,
	PLL_INPUT_CLK_X11,
	PLL_INPUT_CLK_X12,
	PLL_INPUT_CLK_X13,
	PLL_INPUT_CLK_X14,
	PLL_INPUT_CLK_X15,
	PLL_INPUT_CLK_X16,

}PLL_MULTI_Factor_t;

/**
 * @brief: define enum to work on Bit 17 PLLXTPRE: HSE divider for PLL entry
 */
typedef enum
{
	HSE_NOT_DIVIDED=0,
	HSE_DIVIDED_BY_2

}HSE_InputForPLL_t;

/**
 * @brief: define enum to Config PLL CLOCK SRC
 */
typedef enum
{
	PLL_HSI=0,
	PLL_HSE

}PLL_CLK_SRC_t;


/**
 * @brief: define enum to configure APB2 high-speed prescaler
 */
typedef enum
{
	APB2_HCLK_NOT_DIVIDED=3,
	APB2_HCLK_DIVIDED_BY_2,
	APB2_HCLK_DIVIDED_BY_4,
	APB2_HCLK_DIVIDED_BY_8,
	APB2_HCLK_DIVIDED_BY_16,

}APB_2_Precaler_t;

/**
 * @brief: define enum to configure APB1 high-speed prescaler
 */
typedef enum
{
	APB1_HCLK_NOT_DIVIDED=3,
	APB1_HCLK_DIVIDED_BY_2,
	APB1_HCLK_DIVIDED_BY_4,
	APB1_HCLK_DIVIDED_BY_8,
	APB1_HCLK_DIVIDED_BY_16,

}APB1_Precaler_t;

/**
 * @brief: define enum to configure AHB prescaler
 */
typedef enum
{
	SYSCLK_NOT_DIVIDED=7,
	SYSCLK_DIVIDED_BY_2,
	SYSCLK_DIVIDED_BY_4,
	SYSCLK_DIVIDED_BY_8,
	SYSCLK_DIVIDED_BY_16,
	SYSCLK_DIVIDED_BY_64,
	SYSCLK_DIVIDED_BY_128,
	SYSCLK_DIVIDED_BY_256,
	SYSCLK_DIVIDED_BY_512

}AHB_Precaler_t;

/**
 * @brief: define enum to configure RCC_CR BITS
 */
typedef enum
{
	HSI_ON=0,
	HSI_RDY,
	HSI_TRIM0=3,
	HSI_TRIM1,
	HSI_TRIM2,
	HSI_TRIM3,
	HSI_TRIM4,
	HSICAL0,
	HSICAL1,
	HSICAL2,
	HSICAL3,
	HSICAL4,
	HSICAL5,
	HSICAL8,
	HSICAL7,
	HSE_ON,
	HSE_RDY,
	HSE_BYP,
	CSS_ON ,
	PLL_ON=24,
	PLL_RDY
}RCC_CR_t;

/**
 * @brief: define enum to configure RCC_CFGR BITS
 */
typedef enum
{
	SW0=0,
	SW1,
	SWS0,
	SWS1,
	HPRE0,
	HPRE1,
	HPRE2,
	HPRE3,
	PPRE1_BIT0,
	PPRE1_BIT1,
	PPRE1_BIT2,
	PPRE2_BIT0,
	PPRE2_BIT1,
	PPRE2_BIT2,
	ADCPRE0,
	ADCPRE1,
	PLLSRC,
	PLLXTPRE,
	PLLMUL0,
	PLLMUL1,
	PLLMUL2,
	PLLMUL3,
	USBPRE,
	MCO_0=24,
	MCO_1,
	MCO_2,

}RCC_CFGR_t;

/**
 * @brief: define enum to configure RCC_APB_2_RSTR BITS
 */

typedef enum
{
	AFIO_RST=0,
	IOPA_RST=2,
	IOPB_RST,
	IOPC_RST,
	IOPD_RST,
	IOPE_RST,
	IOPF_RST,
	IOPG_RST,
	ADC1_RST,
	ADC2_RST,
	TIM1_RST,
	SPI1_RST,
	TIM8_RST,
	USART1_RST,
	ADC3_RST,
	TIM9_RST=19,
	TIM10_RST,
	TIM11_RST

}RCC_APB_2_RSTR_t;

/**
 * @brief: define enum to configure RCC_APB_1_RSTR BITS
 */

typedef enum
{
	TIM2_RST=0,
	TIM3_RST,
	TIM4_RST,
	TIM5_RST,
	TIM6_RST,
	TIM7_RST,
	TIM12_RST,
	TIM13_RST,
	TIM14_RST,
	WWDG_RST=11,
	SPI2_RST=14,
	SPI3_RST,
	USART2_RST=17,
	USART3_RST,
	USART4_RST,
	USART5_RST,
	I2C1_RST,
	I2C2_RST,
	USB_RST,
	CAN_RST,
	BKP_RST=27,
	PWR_RST,
	DAC_RST

}RCC_APB_1_RSTR_t;

/**
 * @brief: define enum to configure RCC_AHBENR BITS
 */


typedef enum
{
	DMA1_EN=0,
	DMA2_EN,
	SRAM_EN,
	FLITF_EN=4,
	CRC_EN=6,
	FSMC_EN=8,
	SDIO_EN=10,
}RCC_AHBENR_t;


/**
 * @brief: define enum to configure RCC_APB_2_ENR BITS
 */


typedef enum
{
	AFIO_EN=0,
	IOPA_EN=2,
	IOPB_EN,
	IOPC_EN,
	IOPD_EN,
	IOPE_EN,
	IOPF_EN,
	IOPG_EN,
	ADC1_EN,
	ADC2_EN,
	TIM1_EN,
	SPI1_EN,
	TIM8_EN,
	USART1_EN,
	ADC3_EN,
	TIM9_EN=19,
	TIM10_EN,
	TIM11_EN

}RCC_APB_2_ENR_t;


/**
 * @brief: define enum to configure RCC_APB_1_ENR BITS
 */


typedef enum
{
	TIM2_EN=0,
	TIM3_EN,
	TIM4_EN,
	TIM5_EN,
	TIM6_EN,
	TIM7_EN,
	TIM12_EN,
	TIM13_EN,
	TIM14_EN,
	WWDG_EN=11,
	SPI2_EN=14,
	SPI3_EN,
	USART2_EN=17,
	USART3_EN,
	USART4_EN,
	USART5_EN,
	I2C1_EN,
	I2C2_EN,
	USB_EN,
	CAN_EN,
	BKP_EN=27,
	PWR_EN,
	DAC_EN

}RCC_APB_1_ENR_t;

typedef enum
{
	APB1=0,
	APB2,
	AHB
}BusName_t;


/**
 * @brief this function to set clock type(HSE,HSI,PLL) and its status (on or off)
 * @param Copy_EnumCLkType
 * @param Copy_EnumCLkStatus
 * @return Local_u8ErrorState
 */

uint8_t RCC_u8SetClkSts(ClkType_t Copy_EnumCLkType ,ClkStatus_t Copy_EnumCLkStatus );

/**
 * @brief this function to set system clock type(HSE,HSI,PLL)
 * @param Copy_EnumCLkType
 * @return Local_u8ErrorState
 */
uint8_t RCC_u8SetSysClk(ClkType_t Copy_EnumCLkType);

/**
 * @brief this function to set input which entering to PLL with divided factor 2 or no divide factor
 * @param Copy_EnumHSE_Division_Fact
 * @return Local_u8ErrorState
 */
uint8_t RCC_u8SetHSEConfig(HSE_InputForPLL_t Copy_EnumHSE_Division_Fact);

/**
 * @brief this function to configure PLL SRC and PLLMUL
 * @param Copy_EnumPLLMul
 * @param Copy_EnumPLLSRC
 * @return Local_u8ErrorState
 */
uint8_t RCC_u8PLLConfig(PLL_MULTI_Factor_t Copy_EnumPLLMul,PLL_CLK_SRC_t Copy_EnumPLLSRC);

/**
 * @brief this function to ENABLE peripheral clk on AHB
 * @param Copy_EnumAHBPeripheral
 *
 */
void RCC_voidAHBEnableClk(RCC_AHBENR_t  Copy_EnumAHBPeripheral);
/**
 * @brief this function to DISABLE peripheral clk on AHB
 * @param Copy_EnumAHBPeripheral
 *
 */
void RCC_voidAHBDisableClk(RCC_AHBENR_t  Copy_EnumAHBPeripheral);

/**
 * @brief this function to ENABLE peripheral clk on APB1
 * @param Copy_EnumAPB_1_Peripheral
 *
 */
void RCC_voidAPB_1_EnableClk(RCC_APB_1_ENR_t  Copy_EnumAPB_1_Peripheral);

/**
 * @brief this function to DISABLE peripheral clk on APB1
 * @param Copy_EnumAPB_1_Peripheral
 *
 */
void RCC_voidAPB_1_DisableClk(RCC_APB_1_ENR_t  Copy_EnumAPB_1_Peripheral);

/**
 * @brief this function to ENABLE peripheral clk on APB2
 * @param Copy_EnumAPB_2_Peripheral
 *
 */
void RCC_voidAPB_2_EnableClk(RCC_APB_2_ENR_t  Copy_EnumAPB_2_Peripheral);
/**
 * @brief this function to DISABLE peripheral clk on APB2
 * @param Copy_EnumAPB_2_Peripheral
 *
 */
void RCC_voidAPB_2_DisableClk(RCC_APB_2_ENR_t  Copy_EnumAPB_2_Peripheral);

#endif /* RCC_INTERFACE_H_ */
