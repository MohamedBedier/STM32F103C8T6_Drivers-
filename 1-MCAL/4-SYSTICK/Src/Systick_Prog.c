/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : Systick_prog.c                              **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#include <stdint.h>
#include "ErrType.h"
#include "BIT_MATH.h"
#include "Stm32F446xx.h"
#include "Systick_private.h"
#include "Systick_interface.h"


/******************************    SYSTICK Peripheral Base Addresses    ******************************/

#define  SYST_BASE_ADDRESS   (SYSTICK_RegDef_t*)0xE000E010U

/* define a pointer from type of struct [SYSTICK_RegDef_t] which carry the base address of SYST
			   Don't forget to cast it to (SYSTICK_RegDef_t* ) */

SYSTICK_RegDef_t* SYSTICK = SYST_BASE_ADDRESS;

/**
 * @fn SYSTICK_voidDelay_MS
 * @brief this function to delay in mili second
 * @param[in] Copy_u32TimeIn_MS : time in MSec
 * @param[in] Copy_enumAHBFreq: this variable to set AHB Frequency
 * retval Local_u8ErrorState
 */

uint8_t SYSTICK_voidDelay_MS(uint32_t Copy_u32TimeIn_MS ,AHBFreq_t Copy_enumAHBFreq )
{
	/* define a variable to carry error state */
	uint8_t Local_u8ErrorState=OK;

	/* check on AHB frequency if the user worked on external frequency [SYSTEM_FREQ_DIVISIED_BY_8] or  system frequency [SYSTEM_FREQ_NO_DIVISION] */
	if(Copy_enumAHBFreq == SYSTEM_FREQ_DIVISIED_BY_8 )
	{
		/* define a variable to carry Local_u32NeededTicks */
		uint32_t Local_u32NeededTicks= INIT_VALUE_BY_ZERO ;

		/* clear CLKSOURCE bit to make it as external freq that's meaning that system freq divided by 8 */
		CLR_BIT((SYSTICK->SYST_CSR),CLKSOURCE);

		/* RESET the count falg TO make sure that is initially by 0*/
		CLR_BIT(SYSTICK->SYST_CSR,COUNTFLAG);

		/* ticks needed for Copy_u32TimeIn_MS */
		/* we multiply by 1000 to convert it from MS to US */
		Local_u32NeededTicks = (Copy_u32TimeIn_MS * CONVERT_FROM_MS_TO_US);

		/* check on value inside SysTick Reload Value Register is reach to max value or not */
		if(Local_u32NeededTicks > MAX_RELOAD_VALUE)
		{
			/* if it reached to max value reset it by MAX_RELOAD_VALUE */
			Local_u32NeededTicks= MAX_RELOAD_VALUE;
		}else
		{
			/* if not reach to max value */

			/* clear 24 bits of reload value */
			SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

			/* put the value into SYST_RVR and start count down until flag raised  */
			SYSTICK->SYST_RVR |= Local_u32NeededTicks;

			/* Enable systick */
			SET_BIT(SYSTICK->SYST_CSR,ENABLE);

			/* busy waiting by using polling method */
			while(GET_BIT(SYSTICK->SYST_CSR,COUNTFLAG) == FLAG_RAISED);

			/* Disable systick */
			CLR_BIT(SYSTICK->SYST_CSR,ENABLE);
		}

	}else if(Copy_enumAHBFreq == SYSTEM_FREQ_NO_DIVISION)
	{

		/* define a variable to carry Local_u32NeededTicks */
		uint32_t Local_u32NeededTicks= INIT_VALUE_BY_ZERO;

		/* SET CLKSOURCE bit to make it as system freq that's meaning that system freq with no division */
		SET_BIT((SYSTICK->SYST_CSR),CLKSOURCE);

		/* RESET the count falg TO make sure that is initially by 0*/
		CLR_BIT(SYSTICK->SYST_CSR,COUNTFLAG);

		/* we multiply by 1000 to convert it from MS to US */
		Local_u32NeededTicks = (Copy_u32TimeIn_MS * CONVERT_FROM_MS_TO_US * SYS_FREQ_WITH_PRE_8);

		/* check on value inside SysTick Reload Value Register is reach to max value or not */
		if(Local_u32NeededTicks > MAX_RELOAD_VALUE)
		{
			/* if it reached to max value reset it by 0 */
			Local_u32NeededTicks= MAX_RELOAD_VALUE;
		}else
		{
			/* if not reach to max value */

			/* clear 24 bits of reload value */
			SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

			/* put the value into SYST_RVR and start count down until flag raised  */
			SYSTICK->SYST_RVR |= Local_u32NeededTicks;
			/* Enable systick */
			SET_BIT(SYSTICK->SYST_CSR,ENABLE);

			/* busy waiting by using polling method */
			while(GET_BIT(SYSTICK->SYST_CSR,COUNTFLAG) == FLAG_RAISED);

			/* Disable systick */
			CLR_BIT(SYSTICK->SYST_CSR,ENABLE);
		}

	}else

	{
		/* update Error state value  */
		Local_u8ErrorState=NOK;

	}

	/* return Error state value  and end the function */
	return Local_u8ErrorState;
}

/**
 * @fn SYSTICK_voidDelay_US
 * @brief this function to delay in Micro second
 * @param[in] Copy_u32TimeIn_MS : time in USec
 * @param[in] Copy_enumAHBFreq: this variable to set AHB Frequency
 * retval Local_u8ErrorState
 */

uint8_t SYSTICK_voidDelay_US(uint32_t Copy_u32TimeIn_US ,AHBFreq_t Copy_enumAHBFreq )
{
	/* define a variable to carry error state */
	uint8_t Local_u8ErrorState=OK;

	/* check on AHB frequency if the user worked on external frequency [SYSTEM_FREQ_DIVISIED_BY_8] or  system frequency [SYSTEM_FREQ_NO_DIVISION] */
	if(Copy_enumAHBFreq == SYSTEM_FREQ_DIVISIED_BY_8 )
	{
		/* define a variable to carry Local_u32NeededTicks */
		uint32_t Local_u32NeededTicks= INIT_VALUE_BY_ZERO;

		/* clear CLKSOURCE bit to make it as external freq that's meaning that system freq divided by 8 */
		CLR_BIT((SYSTICK->SYST_CSR),CLKSOURCE);

		/* RESET the count falg TO make sure that is initially by 0*/
		CLR_BIT(SYSTICK->SYST_CSR,COUNTFLAG);

		/* ticks needed for Copy_u32TimeIn_US */
		Local_u32NeededTicks = Copy_u32TimeIn_US;

		/* check on value inside SysTick Reload Value Register is reach to max value or not */
		if(Local_u32NeededTicks > MAX_RELOAD_VALUE)
		{
			/* if it reached to max value reset it by 0 */
			Local_u32NeededTicks= MAX_RELOAD_VALUE;
		}else
		{
			/* if not reach to max value */

			/* clear 24 bits of reload value */
			SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

			/* put the value into SYST_RVR and start count down until flag raised  */
			SYSTICK->SYST_RVR |= Local_u32NeededTicks;

			/* Enable systick */
			SET_BIT(SYSTICK->SYST_CSR,ENABLE);

			/* busy waiting by using polling method */
			while(GET_BIT(SYSTICK->SYST_CSR,COUNTFLAG) == FLAG_RAISED);

			/* Disable systick */
			CLR_BIT(SYSTICK->SYST_CSR,ENABLE);
		}



	}else if(Copy_enumAHBFreq == SYSTEM_FREQ_NO_DIVISION)
	{

		/* define a variable to carry Local_u32NeededTicks */
		uint32_t Local_u32NeededTicks= INIT_VALUE_BY_ZERO;

		/* SET CLKSOURCE bit to make it as system freq that's meaning that system freq with no division */
		SET_BIT((SYSTICK->SYST_CSR),CLKSOURCE);

		/* RESET the count falg TO make sure that is initially by 0*/
		CLR_BIT(SYSTICK->SYST_CSR,COUNTFLAG);

		/* ticks needed for Copy_u32TimeIn_US */
		Local_u32NeededTicks = (Copy_u32TimeIn_US * SYS_FREQ_WITH_PRE_8);

		/* check on value inside SysTick Reload Value Register is reach to max value or not */
		if(Local_u32NeededTicks > MAX_RELOAD_VALUE)
		{
			/* if it reached to max value reset it by 0 */
			Local_u32NeededTicks= MAX_RELOAD_VALUE;
		}else
		{
			/* if not reach to max value */

			/* clear 24 bits of reload value */
			SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

			/* put the value into SYST_RVR and start count down until flag raised  */
			SYSTICK->SYST_RVR |= Local_u32NeededTicks;
			/* Enable systick */
			SET_BIT(SYSTICK->SYST_CSR,ENABLE);

			/* busy waiting by using polling method */
			while(GET_BIT(SYSTICK->SYST_CSR,COUNTFLAG) == FLAG_RAISED);

			/* Disable systick */
			CLR_BIT(SYSTICK->SYST_CSR,ENABLE);
		}

	}else

	{
		/* update Error state value  */
		Local_u8ErrorState=NOK;

	}

	/* return Error state value  and end the function */
	return Local_u8ErrorState;
}
