/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : RCC_Program.c                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#include <stdint.h>
#include "ErrType.h"
#include "BIT_MATH.h"
#include "Stm32F103xx.h"
#include "RCC_Private.h"
#include "RCC_Interface.h"


/******************************    AHB Peripheral Base Addresses    ******************************/

#define  RCC_BASE_ADDRESS    (RCC_Reg_t*)0x40021000U

/* define a pointer from type of struct [RCC_Reg_t] which carry the base address of RCC
			   Don't forget to cast it to (RCC_Reg_t* ) */

RCC_Reg_t *RCC = RCC_BASE_ADDRESS;

/**
 * @fn RCC_u8SetClkSts
 * @brief this function to set clock from its options [HSE,HSI,PLL] and set its status too [on,off]
 * @param[in] Copy_EnumCLkType : to set clock from its options [HSE,HSI,PLL]
 * @param[in] Copy_EnumCLkStatus : TO set clock status from its options [on,off]
 * @retval Local_u8ErrorState
 */


uint8_t RCC_u8SetClkSts(ClkType_t Copy_EnumCLkType ,ClkStatus_t Copy_EnumCLkStatus)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* This variable for TimeOutCounter */
	uint32_t Local_u32TimeOutCounter=0u;



	if(Copy_EnumCLkType == HSE)
	{

		if(Copy_EnumCLkStatus == CLK_ON)
		{
			/* enable HSE */
			SET_BIT((RCC->RCC_CR),HSE_ON);

			/* Polling method : waiting until the HSE_RDY or the timeout is passed  */
			while((GET_BIT((RCC->RCC_CR),HSE_RDY) == 1) && (Local_u32TimeOutCounter < RCC_TIMEOUT))
			{
				/* increment by 1 */
				Local_u32TimeOutCounter++;
			}

			/* check if loop ended because RCC_TIMEOUT is passed or the flag is raised */
			if(Local_u32TimeOutCounter >= RCC_TIMEOUT)
			{
				/* loop is broken because flag isn't raised until timeout is passed */
				Local_u8ErrorState = TIMEOUT_ERR;
			}else
			{
				/* loop is broken because flag is raised , and we have another func to enable peripheral */
			}
		}else if (Copy_EnumCLkStatus == CLK_OFF)
		{
			/* disable HSE */
			CLR_BIT((RCC->RCC_CR),HSE_ON);

		}else
		{
			Local_u8ErrorState =NOK;/* if the user send invalid options */
		}


	}else if (Copy_EnumCLkType == HSI)
	{
		if(Copy_EnumCLkStatus == CLK_ON)
		{
			/* enable HSI */
			SET_BIT((RCC->RCC_CR),HSI_ON);

			/* Polling method : waiting until the HSI_RDY or the timeout is passed  */
			while((GET_BIT((RCC->RCC_CR),HSI_RDY) == 1) && (Local_u32TimeOutCounter < RCC_TIMEOUT))
			{
				/* increment by 1 */
				Local_u32TimeOutCounter++;
			}

			/* check if loop ended because RCC_TIMEOUT is passed or the flag is raised */
			if(Local_u32TimeOutCounter >= RCC_TIMEOUT)
			{
				/* loop is broken because flag isn't raised until timeout is passed */
				Local_u8ErrorState = TIMEOUT_ERR;
			}else
			{
				/* loop is broken because flag is raised , and we have another func to enable peripheral */
			}
		}else if (Copy_EnumCLkStatus == CLK_OFF)
		{
			/* disable HSI */
			CLR_BIT((RCC->RCC_CR),HSI_ON);

		}else
		{
			Local_u8ErrorState =NOK;/* if the user send invalid options */
		}
	}
	else if (Copy_EnumCLkType == PLL)
	{
		if(Copy_EnumCLkStatus == CLK_ON)
		{
			/* enable PLL */
			SET_BIT((RCC->RCC_CR),PLL_ON);

			/* Polling method : waiting until the PLL_RDY or the timeout is passed  */
			while((GET_BIT((RCC->RCC_CR),PLL_RDY) == 1) && (Local_u32TimeOutCounter < RCC_TIMEOUT))
			{
				/* increment by 1 */
				Local_u32TimeOutCounter++;
			}

			/* check if loop ended because RCC_TIMEOUT is passed or the flag is raised */
			if(Local_u32TimeOutCounter >= RCC_TIMEOUT)
			{
				/* loop is broken because flag isn't raised until timeout is passed */
				Local_u8ErrorState = TIMEOUT_ERR;
			}else
			{
				/* loop is broken because flag is raised , and we have another func to enable peripheral */
			}
		}else if (Copy_EnumCLkStatus == CLK_OFF)
		{
			/* disable PLL */
			CLR_BIT((RCC->RCC_CR),PLL_ON);

		}else
		{
			Local_u8ErrorState =NOK;/* if the user send invalid options */
		}

	}else
	{
		Local_u8ErrorState =NOK; /* if the user send invalid options */
	}

	return Local_u8ErrorState;
}

/**
 * @fn RCC_u8SetSysClk
 * @brief this function to set clock system from its options [HSE,HSI,PLL]
 * @param[in] Copy_EnumCLkType : to set clock from its options [HSE,HSI,PLL]
 * @retval Local_u8ErrorState
 */
uint8_t RCC_u8SetSysClk(ClkType_t Copy_EnumCLkType)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;


	/* configure system clk */
	switch(Copy_EnumCLkType)
	{
	case HSE:CLR_BIT((RCC->RCC_CFGR),SW1);CLR_BIT((RCC->RCC_CFGR),SW0);break;
	case HSI:CLR_BIT((RCC->RCC_CFGR),SW1);SET_BIT((RCC->RCC_CFGR),SW0);break;
	case PLL:SET_BIT((RCC->RCC_CFGR),SW1);CLR_BIT((RCC->RCC_CFGR),SW0);break;
	default:Local_u8ErrorState=NOK;break;/* if the user send invalid options */
	}

/* return Local_u8ErrorState */
	return Local_u8ErrorState;
}

/**
 * @fn RCC_u8SetHSEConfig
 * @brief this function to set HSE division factor
 * @param[in] Copy_EnumHSE_Division_Fact : to set HSE division factor [1 or 2]
 * @retval Local_u8ErrorState
 */
uint8_t RCC_u8SetHSEConfig(HSE_InputForPLL_t Copy_EnumHSE_Division_Fact)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;


	/* configure HSE which entering to PLL*/
	switch(Copy_EnumHSE_Division_Fact)
	{
	case HSE_NOT_DIVIDED:CLR_BIT((RCC->RCC_CFGR),PLLXTPRE);break;
	case HSE_DIVIDED_BY_2:SET_BIT((RCC->RCC_CFGR),PLLXTPRE);break;
	default:Local_u8ErrorState=NOK;break;/* if the user send invalid options */
	}
	/* return Local_u8ErrorState */
	return Local_u8ErrorState;
}

/**
 * @fn RCC_u8PLLConfig
 * @brief this function to set MULTI factor of PLL
 * @param[in] Copy_EnumPLLMul : to set  MULTI factor of PLL
 * @param[in] Copy_EnumPLLSRC : to choice PLL Src [HSE OR HSI]
 * @retval Local_u8ErrorState
 */
uint8_t RCC_u8PLLConfig(PLL_MULTI_Factor_t Copy_EnumPLLMul,PLL_CLK_SRC_t Copy_EnumPLLSRC)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* configure  which CLK entering to PLL */
	switch(Copy_EnumPLLSRC)
	{
	case PLL_HSE:SET_BIT((RCC->RCC_CFGR),PLLSRC);break;
	case PLL_HSI:CLR_BIT((RCC->RCC_CFGR),PLLSRC);break;
	default:Local_u8ErrorState=NOK;break;/* if the user send invalid options */
	}

	/* clear only PLLMUL Bits in CFGR  */
	RCC->RCC_CFGR &= RCC_CFGR_PLLMUL_MASK;
	/* set the factor */
	RCC->RCC_CFGR |= Copy_EnumPLLMul;

	return Local_u8ErrorState;
}

/**
 * @brief this function to ENABLE peripheral clk on AHB
 * @param Copy_EnumAHBPeripheral
 *
 */
void RCC_voidAHBEnableClk(RCC_AHBENR_t  Copy_EnumAHBPeripheral)
{
	/* enable the clk on this peripheral */
	SET_BIT((RCC->RCC_AHBENR),Copy_EnumAHBPeripheral);
}

/**
 * @brief this function to DISABLE peripheral clk on AHB
 * @param Copy_EnumAHBPeripheral
 *
 */
void RCC_voidAHBDisableClk(RCC_AHBENR_t  Copy_EnumAHBPeripheral)
{
	/* Disable the clk on this peripheral */
	CLR_BIT((RCC->RCC_AHBENR),Copy_EnumAHBPeripheral);
}
/**
 * @brief this function to ENABLE peripheral clk on APB_1
 * @param Copy_EnumAHBPeripheral
 *
 */
void RCC_voidAPB_1_EnableClk(RCC_APB_1_ENR_t  Copy_EnumAPB_1_Peripheral)
{
	/* enable the clk on this peripheral */
	SET_BIT((RCC->RCC_APB1ENR),Copy_EnumAPB_1_Peripheral);
}
/**
 * @brief this function to DISABLE peripheral clk on APB_1
 * @param Copy_EnumAHBPeripheral
 *
 */
void RCC_voidAPB_1_DisableClk(RCC_APB_1_ENR_t  Copy_EnumAPB_1_Peripheral)
{
	/* Disable the clk on this peripheral */
	CLR_BIT((RCC->RCC_APB1ENR),Copy_EnumAPB_1_Peripheral);
}

/**
 * @brief this function to ENABLE peripheral clk on APB_2
 * @param Copy_EnumAHBPeripheral
 *
 */
void RCC_voidAPB_2_EnableClk(RCC_APB_2_ENR_t  Copy_EnumAPB_2_Peripheral)
{
	/* enable the clk on this peripheral */
	SET_BIT((RCC->RCC_APB2ENR),Copy_EnumAPB_2_Peripheral);
}
/**
 * @brief this function to DISABLE peripheral clk on APB_2
 * @param Copy_EnumAHBPeripheral
 *
 */
void RCC_voidAPB_2_DisableClk(RCC_APB_2_ENR_t  Copy_EnumAPB_2_Peripheral)
{
	/* Disable the clk on this peripheral */
	CLR_BIT((RCC->RCC_APB2ENR),Copy_EnumAPB_2_Peripheral);
}



