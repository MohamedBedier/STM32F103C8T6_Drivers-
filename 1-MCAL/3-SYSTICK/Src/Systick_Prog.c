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
#include <float.h>
#include "ErrType.h"
#include "BIT_MATH.h"
#include "Stm32F446xx.h"
#include "Systick_Cfg.h"
#include "Systick_private.h"
#include "Systick_interface.h"

/******************************    SYSTICK Peripheral Base Addresses    ******************************/

#define  SYST_BASE_ADDRESS   (SYSTICK_RegDef_t*)0xE000E010U

/* define a pointer from type of struct [SYSTICK_RegDef_t] which carry the base address of SYST
			   Don't forget to cast it to (SYSTICK_RegDef_t* ) */

static SYSTICK_RegDef_t* SYSTICK = SYST_BASE_ADDRESS;

/**
 * @fn SYSTICK_voidDelay_MS
 * @brief this function to delay in mili second
 * @param[in] Copy_u32TimeIn_MS : time in MSeccy
 * retval Local_u8ErrorState
 */

uint8_t SYSTICK_u8Delay_MS(uint32_t Copy_u32TimeIn_MS)
{
	/* define a variable to carry error state */
	uint8_t Local_u8ErrorState=OK;

	/* define a variable to carry Local_u32NeededTicks */
	uint32_t Local_u32NeededTicks= INIT_VALUE_BY_ZERO ;

	/* RESET the count falg TO make sure that is initially by 0*/
	CLR_BIT(SYSTICK->SYST_CSR,COUNTFLAG);


	/* check on AHB frequency if the user worked on external frequency [AHB_CLK_DIVIDED_bY_8] or  system frequency [AHB_CLK] */
	if(SYSTICK_CLK_SRC == AHB_CLK_DIVIDED_bY_8)
	{

		/* clear CLKSOURCE bit to make it as external freq that's meaning that AHB CLK divided by 8 */
		CLR_BIT((SYSTICK->SYST_CSR),CLKSOURCE);

		/* Calculate number of ticks needed for Copy_u32TimeIn_MS */
		Local_u32NeededTicks = (Copy_u32TimeIn_MS * CONVERT_FROM_US_TO_MS);

		/**********************************************/
		/* check on value inside Local_u32NeededTicks is reach to max value or not */
		if(Local_u32NeededTicks > MAX_RELOAD_VALUE)
		{
			/* define variable to carry No_OfUnderOverFlows */
			float Local_floatNo_OfUnderOverFlows =INIT_VALUE_BY_ZERO;
			/* define variable to carry FractionPart */
			float Local_floatFractionPart = INIT_VALUE_BY_ZERO*1.0;
			/* define variable to carry IntegerPart */
			uint8_t Local_u8IntegerPart=INIT_VALUE_BY_ZERO;
			/* define variable to carry NO_of_Needed ticks of the fraction part */
			uint32_t Local_u32RemainingTicks=INIT_VALUE_BY_ZERO;
			/* define a counter to calc the integer under over flow  */
			uint8_t Local_u8CounterForUnder_OVF=INIT_VALUE_BY_ZERO;

			/* calculate No_OfUnderOverFlows */
			Local_floatNo_OfUnderOverFlows = (Local_u32NeededTicks*1.0 /MAX_RELOAD_VALUE_AS_FLOAT);


			/* The integer part represents the number of full underflows needed */
			Local_u8IntegerPart = (uint8_t)Local_floatNo_OfUnderOverFlows;


			/* The fractional part represents the remaining count within the current underflow period */
			Local_floatFractionPart = Local_floatNo_OfUnderOverFlows - Local_u8IntegerPart ;

			/* Check if there's a non-zero fractional part */
			if (Local_floatFractionPart > 0.0f)
			{
				/* Calculate the number of ticks required within the current underflow period */
				Local_u32RemainingTicks = (Local_floatFractionPart * MAX_RELOAD_VALUE);

				/* clear 24 bits of reload value */
				SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

				/* put the value into SYST_RVR and start count down until flag raised  */
				SYSTICK->SYST_RVR |= MAX_RELOAD_VALUE;



				/* Enable SysTick */
				SET_BIT(SYSTICK->SYST_CSR, ENABLE);

				for(Local_u8CounterForUnder_OVF=INIT_VALUE_BY_ZERO;Local_u8CounterForUnder_OVF <Local_u8IntegerPart;Local_u8CounterForUnder_OVF++)
				{
					/* Wait for the current underflow to occur */
					while (GET_BIT(SYSTICK->SYST_CSR, COUNTFLAG) == FLAG_NOT_RAISED);

				}

				/* Disable SysTick */
				CLR_BIT(SYSTICK->SYST_CSR, ENABLE);

				/* clear 24 bits of reload value */
				SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

				/* put the value of Local_u32RemainingTicks into SYST_RVR and start count down until flag raised  */
				SYSTICK->SYST_RVR |= Local_u32RemainingTicks;


				/* Enable SysTick again */
				SET_BIT(SYSTICK->SYST_CSR, ENABLE);

				/* Wait for the remaining underflows */
				while (GET_BIT(SYSTICK->SYST_CSR, COUNTFLAG) == FLAG_NOT_RAISED);

				/* Disable SysTick */
				CLR_BIT(SYSTICK->SYST_CSR, ENABLE);

			}else
			{
				;
			}



		}else
		{

			/* clear 24 bits of reload value */
			SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

			/* put the value into SYST_RVR and start count down until flag raised  */
			SYSTICK->SYST_RVR |= Local_u32NeededTicks;

			/* Enable systick */
			SET_BIT(SYSTICK->SYST_CSR,ENABLE);

			/* busy waiting by using polling method */
			while(GET_BIT(SYSTICK->SYST_CSR,COUNTFLAG) == FLAG_NOT_RAISED);

			/* Disable systick */
			CLR_BIT(SYSTICK->SYST_CSR,ENABLE);;
		}



		/**********************************************/


	}else if(SYSTICK_CLK_SRC == AHB_CLK)
	{

		/* clear CLKSOURCE bit to make it as external freq that's meaning that AHB CLK */
		SET_BIT((SYSTICK->SYST_CSR),CLKSOURCE);

		/* Calculate number of ticks needed for Copy_u32TimeIn_MS */
		Local_u32NeededTicks = (Copy_u32TimeIn_MS * CONVERT_FROM_US_TO_MS*SYS_FREQ_8MHZ);


		/**********************************************/
		/* check on value inside Local_u32NeededTicks is reach to max value or not */
		if(Local_u32NeededTicks > MAX_RELOAD_VALUE)
		{
			/* define variable to carry No_OfUnderOverFlows */
			float Local_floatNo_OfUnderOverFlows =INIT_VALUE_BY_ZERO;
			/* define variable to carry FractionPart */
			float Local_floatFractionPart = INIT_VALUE_BY_ZERO*1.0;
			/* define variable to carry IntegerPart */
			uint8_t Local_u8IntegerPart=INIT_VALUE_BY_ZERO;
			/* define variable to carry NO_of_Needed ticks of the fraction part */
			uint32_t Local_u32RemainingTicks=INIT_VALUE_BY_ZERO;
			/* define a counter to calc the integer under over flow  */
			uint8_t Local_u8CounterForUnder_OVF=INIT_VALUE_BY_ZERO;

			/* calculate No_OfUnderOverFlows */
			Local_floatNo_OfUnderOverFlows = (Local_u32NeededTicks*1.0 /MAX_RELOAD_VALUE_AS_FLOAT);


			/* The integer part represents the number of full underflows needed */
			Local_u8IntegerPart = (uint8_t)Local_floatNo_OfUnderOverFlows;


			/* The fractional part represents the remaining count within the current underflow period */
			Local_floatFractionPart = Local_floatNo_OfUnderOverFlows - Local_u8IntegerPart ;

			/* Check if there's a non-zero fractional part */
			if (Local_floatFractionPart > 0.0f)
			{
				/* Calculate the number of ticks required within the current underflow period */
				Local_u32RemainingTicks = (Local_floatFractionPart * MAX_RELOAD_VALUE);

				/* clear 24 bits of reload value */
				SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

				/* put the value into SYST_RVR and start count down until flag raised  */
				SYSTICK->SYST_RVR |= MAX_RELOAD_VALUE;



				/* Enable SysTick */
				SET_BIT(SYSTICK->SYST_CSR, ENABLE);

				for(Local_u8CounterForUnder_OVF=INIT_VALUE_BY_ZERO;Local_u8CounterForUnder_OVF <Local_u8IntegerPart;Local_u8CounterForUnder_OVF++)
				{
					/* Wait for the current underflow to occur */
					while (GET_BIT(SYSTICK->SYST_CSR, COUNTFLAG) == FLAG_NOT_RAISED);

				}

				/* Disable SysTick */
				CLR_BIT(SYSTICK->SYST_CSR, ENABLE);

				/* clear 24 bits of reload value */
				SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

				/* put the value of Local_u32RemainingTicks into SYST_RVR and start count down until flag raised  */
				SYSTICK->SYST_RVR |= Local_u32RemainingTicks;


				/* Enable SysTick again */
				SET_BIT(SYSTICK->SYST_CSR, ENABLE);

				/* Wait for the remaining underflows */
				while (GET_BIT(SYSTICK->SYST_CSR, COUNTFLAG) == FLAG_NOT_RAISED);

				/* Disable SysTick */
				CLR_BIT(SYSTICK->SYST_CSR, ENABLE);

			}else
			{
				;
			}

		}else
		{
			/* clear 24 bits of reload value */
			SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

			/* put the value into SYST_RVR and start count down until flag raised  */
			SYSTICK->SYST_RVR |= Local_u32NeededTicks;

			/* Enable systick */
			SET_BIT(SYSTICK->SYST_CSR,ENABLE);

			/* busy waiting by using polling method */
			while(GET_BIT(SYSTICK->SYST_CSR,COUNTFLAG) == FLAG_NOT_RAISED);

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


/**************************************/

/**
 * @fn SYSTICK_voidDelay_US
 * @brief this function to delay in Micro second
 * @param[in] Copy_u32TimeIn_MS : time in USec
 * retval Local_u8ErrorState
 */
uint8_t SYSTICK_u8Delay_US(uint32_t Copy_u32TimeIn_US)
{
	/* define a variable to carry error state */
	uint8_t Local_u8ErrorState=OK;

	/* define a variable to carry Local_u32NeededTicks */
	uint32_t Local_u32NeededTicks= INIT_VALUE_BY_ZERO ;

	/* RESET the count falg TO make sure that is initially by 0*/
	CLR_BIT(SYSTICK->SYST_CSR,COUNTFLAG);


	/* check on AHB frequency if the user worked on external frequency [AHB_CLK_DIVIDED_bY_8] or  system frequency [AHB_CLK] */
	if(SYSTICK_CLK_SRC == AHB_CLK_DIVIDED_bY_8)
	{

		/* clear CLKSOURCE bit to make it as external freq that's meaning that AHB CLK divided by 8 */
		CLR_BIT((SYSTICK->SYST_CSR),CLKSOURCE);

		/* Calculate number of ticks needed for Copy_u32TimeIn_MS */
		Local_u32NeededTicks =Copy_u32TimeIn_US ;


		/**********************************************/
		/* check on value inside Local_u32NeededTicks is reach to max value or not */
		if(Local_u32NeededTicks > MAX_RELOAD_VALUE)
		{
			/* define variable to carry No_OfUnderOverFlows */
			float Local_floatNo_OfUnderOverFlows =INIT_VALUE_BY_ZERO;
			/* define variable to carry FractionPart */
			float Local_floatFractionPart = INIT_VALUE_BY_ZERO*1.0;
			/* define variable to carry IntegerPart */
			uint8_t Local_u8IntegerPart=INIT_VALUE_BY_ZERO;
			/* define variable to carry NO_of_Needed ticks of the fraction part */
			uint32_t Local_u32RemainingTicks=INIT_VALUE_BY_ZERO;
			/* define a counter to calc the integer under over flow  */
			uint8_t Local_u8CounterForUnder_OVF=INIT_VALUE_BY_ZERO;

			/* calculate No_OfUnderOverFlows */
			Local_floatNo_OfUnderOverFlows = (Local_u32NeededTicks*1.0 /MAX_RELOAD_VALUE_AS_FLOAT);


			/* The integer part represents the number of full underflows needed */
			Local_u8IntegerPart = (uint8_t)Local_floatNo_OfUnderOverFlows;


			/* The fractional part represents the remaining count within the current underflow period */
			Local_floatFractionPart = Local_floatNo_OfUnderOverFlows - Local_u8IntegerPart ;

			/* Check if there's a non-zero fractional part */
			if (Local_floatFractionPart > 0.0f)
			{
				/* Calculate the number of ticks required within the current underflow period */
				Local_u32RemainingTicks = (Local_floatFractionPart * MAX_RELOAD_VALUE);

				/* clear 24 bits of reload value */
				SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

				/* put the value into SYST_RVR and start count down until flag raised  */
				SYSTICK->SYST_RVR |= MAX_RELOAD_VALUE;



				/* Enable SysTick */
				SET_BIT(SYSTICK->SYST_CSR, ENABLE);

				for(Local_u8CounterForUnder_OVF=INIT_VALUE_BY_ZERO;Local_u8CounterForUnder_OVF <Local_u8IntegerPart;Local_u8CounterForUnder_OVF++)
				{
					/* Wait for the current underflow to occur */
					while (GET_BIT(SYSTICK->SYST_CSR, COUNTFLAG) == FLAG_NOT_RAISED);

				}

				/* Disable SysTick */
				CLR_BIT(SYSTICK->SYST_CSR, ENABLE);

				/* clear 24 bits of reload value */
				SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

				/* put the value of Local_u32RemainingTicks into SYST_RVR and start count down until flag raised  */
				SYSTICK->SYST_RVR |= Local_u32RemainingTicks;


				/* Enable SysTick again */
				SET_BIT(SYSTICK->SYST_CSR, ENABLE);

				/* Wait for the remaining underflows */
				while (GET_BIT(SYSTICK->SYST_CSR, COUNTFLAG) == FLAG_NOT_RAISED);

				/* Disable SysTick */
				CLR_BIT(SYSTICK->SYST_CSR, ENABLE);

			}else
			{
				;
			}
		}else
		{
			/* clear 24 bits of reload value */
			SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

			/* put the value into SYST_RVR and start count down until flag raised  */
			SYSTICK->SYST_RVR |= Local_u32NeededTicks;

			/* Enable systick */
			SET_BIT(SYSTICK->SYST_CSR,ENABLE);

			/* busy waiting by using polling method */
			while(GET_BIT(SYSTICK->SYST_CSR,COUNTFLAG) == FLAG_NOT_RAISED);

			/* Disable systick */
			CLR_BIT(SYSTICK->SYST_CSR,ENABLE);
		}
	}else if(SYSTICK_CLK_SRC == AHB_CLK)
	{

		/* clear CLKSOURCE bit to make it as external freq that's meaning that AHB CLK */
		SET_BIT((SYSTICK->SYST_CSR),CLKSOURCE);

		/* Calculate number of ticks needed for Copy_u32TimeIn_MS */
		Local_u32NeededTicks = (Copy_u32TimeIn_US *SYS_FREQ_8MHZ);


		/**********************************************/
		/* check on value inside Local_u32NeededTicks is reach to max value or not */
		if(Local_u32NeededTicks > MAX_RELOAD_VALUE)
		{
			/* define variable to carry No_OfUnderOverFlows */
			float Local_floatNo_OfUnderOverFlows =INIT_VALUE_BY_ZERO;
			/* define variable to carry FractionPart */
			float Local_floatFractionPart = INIT_VALUE_BY_ZERO*1.0;
			/* define variable to carry IntegerPart */
			uint8_t Local_u8IntegerPart=INIT_VALUE_BY_ZERO;
			/* define variable to carry NO_of_Needed ticks of the fraction part */
			uint32_t Local_u32RemainingTicks=INIT_VALUE_BY_ZERO;
			/* define a counter to calc the integer under over flow  */
			uint8_t Local_u8CounterForUnder_OVF=INIT_VALUE_BY_ZERO;

			/* calculate No_OfUnderOverFlows */
			Local_floatNo_OfUnderOverFlows = (Local_u32NeededTicks*1.0 /MAX_RELOAD_VALUE_AS_FLOAT);


			/* The integer part represents the number of full underflows needed */
			Local_u8IntegerPart = (uint8_t)Local_floatNo_OfUnderOverFlows;


			/* The fractional part represents the remaining count within the current underflow period */
			Local_floatFractionPart = Local_floatNo_OfUnderOverFlows - Local_u8IntegerPart ;

			/* Check if there's a non-zero fractional part */
			if (Local_floatFractionPart > 0.0f)
			{
				/* Calculate the number of ticks required within the current underflow period */
				Local_u32RemainingTicks = (Local_floatFractionPart * MAX_RELOAD_VALUE);

				/* clear 24 bits of reload value */
				SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

				/* put the value into SYST_RVR and start count down until flag raised  */
				SYSTICK->SYST_RVR |= MAX_RELOAD_VALUE;

				/* Enable SysTick */
				SET_BIT(SYSTICK->SYST_CSR, ENABLE);

				for(Local_u8CounterForUnder_OVF=INIT_VALUE_BY_ZERO;Local_u8CounterForUnder_OVF <Local_u8IntegerPart;Local_u8CounterForUnder_OVF++)
				{
					/* Wait for the current underflow to occur */
					while (GET_BIT(SYSTICK->SYST_CSR, COUNTFLAG) == FLAG_NOT_RAISED);

				}

				/* Disable SysTick */
				CLR_BIT(SYSTICK->SYST_CSR, ENABLE);

				/* clear 24 bits of reload value */
				SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

				/* put the value of Local_u32RemainingTicks into SYST_RVR and start count down until flag raised  */
				SYSTICK->SYST_RVR |= Local_u32RemainingTicks;


				/* Enable SysTick again */
				SET_BIT(SYSTICK->SYST_CSR, ENABLE);

				/* Wait for the remaining underflows */
				while (GET_BIT(SYSTICK->SYST_CSR, COUNTFLAG) == FLAG_NOT_RAISED);

				/* Disable SysTick */
				CLR_BIT(SYSTICK->SYST_CSR, ENABLE);

			}else
			{
				;
			}
		}else
		{
			/* clear 24 bits of reload value */
			SYSTICK->SYST_RVR &= ~(SYSTICK_MASK);

			/* put the value into SYST_RVR and start count down until flag raised  */
			SYSTICK->SYST_RVR |= Local_u32NeededTicks;

			/* Enable systick */
			SET_BIT(SYSTICK->SYST_CSR,ENABLE);

			/* busy waiting by using polling method */
			while(GET_BIT(SYSTICK->SYST_CSR,COUNTFLAG) == FLAG_NOT_RAISED);

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

