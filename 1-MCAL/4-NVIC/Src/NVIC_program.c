/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : MVIC_program.c                              **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#include <stdint.h>
#include "ErrType.h"
#include "BIT_MATH.h"
#include "Stm32F446xx.h"
#include "NVIC_private.h"
#include "NVIC_interface.h"
#include "NVIC_Reg.h"


/**
 * @brief: This function to enable Peripheral from NVIC
 * @param[IN] Copy_EnumIRQNum : this variable carry peripheral position in vector table
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t NVIC_u8Enable(IRQNum_t Copy_EnumIRQNum)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState;
	/* define a variable to carry RegNum */
	uint8_t Local_u8RegNum;
	/* define a variable to carry BitNum */
	uint8_t Local_u8BitNum;

	/* Calculate this IRQNum at which register from 0 to 7  */
	Local_u8RegNum = Copy_EnumIRQNum / REGISTER_BITS;

	/* Calculate this IRQNum at which Bit from 0 to 31  */
	Local_u8BitNum = Copy_EnumIRQNum % REGISTER_BITS;

	/* protect our function to check on Copy_EnumIRQNum */
	if((Copy_EnumIRQNum>=WWDG) && (Copy_EnumIRQNum<= FMPI2C1_error))
	{
		/* set BitNum at RegNum */
		ISER[Local_u8RegNum] = ONE_VALUE << Local_u8BitNum;
	}else
	{
		/* update Local_u8ErrorState value*/
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief: This function to Disable Peripheral from NVIC
 * @param[IN] Copy_EnumIRQNum : this variable carry peripheral position in vector table
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t NVIC_u8Disable(IRQNum_t Copy_EnumIRQNum)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState;
	/* define a variable to carry RegNum */
	uint8_t Local_u8RegNum;
	/* define a variable to carry BitNum */
	uint8_t Local_u8BitNum;

	/* Calculate this IRQNum at which register from 0 to 7  */
	Local_u8RegNum = Copy_EnumIRQNum / REGISTER_BITS;

	/* Calculate this IRQNum at which Bit from 0 to 31  */
	Local_u8BitNum = Copy_EnumIRQNum % REGISTER_BITS;

	/* protect our function to check on Copy_EnumIRQNum */
	if((Copy_EnumIRQNum>=WWDG) && (Copy_EnumIRQNum<= FMPI2C1_error))
	{
		/* Clear BitNum at RegNum */
		ICER[Local_u8RegNum] = ONE_VALUE << Local_u8BitNum;
	}else
	{
		/* update Local_u8ErrorState value*/
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief: This function to Set Pending Flag
 * @param[IN] Copy_EnumIRQNum : this variable carry peripheral position in vector table
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */

uint8_t NVIC_u8SetPendingFlag(IRQNum_t Copy_EnumIRQNum)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState;
	/* define a variable to carry RegNum */
	uint8_t Local_u8RegNum;
	/* define a variable to carry BitNum */
	uint8_t Local_u8BitNum;

	/* Calculate this IRQNum at which register from 0 to 7  */
	Local_u8RegNum = Copy_EnumIRQNum / REGISTER_BITS;

	/* Calculate this IRQNum at which Bit from 0 to 31  */
	Local_u8BitNum = Copy_EnumIRQNum % REGISTER_BITS;

	/* protect our function to check on Copy_EnumIRQNum */
	if((Copy_EnumIRQNum>=WWDG) && (Copy_EnumIRQNum<= FMPI2C1_error))
	{
		/* Calculate this IRQNum at which register from 0 to 7  */
		Local_u8RegNum = Copy_EnumIRQNum / REGISTER_BITS;

		/* Calculate this IRQNum at which Bit from 0 to 31  */
		Local_u8BitNum = Copy_EnumIRQNum % REGISTER_BITS;

		/* set BitNum at RegNum */
		ISPR[Local_u8RegNum] = ONE_VALUE << Local_u8BitNum;
	}else
	{
		/* update Local_u8ErrorState value*/
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;

}

/**
 * @brief: This function to clear Pending Flag
 * @param[IN] Copy_EnumIRQNum : this variable carry peripheral position in vector table
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */

uint8_t NVIC_u8ClearPendingFlag(IRQNum_t Copy_EnumIRQNum)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState;
	/* define a variable to carry RegNum */
	uint8_t Local_u8RegNum;
	/* define a variable to carry BitNum */
	uint8_t Local_u8BitNum;

	/* Calculate this IRQNum at which register from 0 to 7  */
	Local_u8RegNum = Copy_EnumIRQNum / REGISTER_BITS;

	/* Calculate this IRQNum at which Bit from 0 to 31  */
	Local_u8BitNum = Copy_EnumIRQNum % REGISTER_BITS;

	/* protect our function to check on Copy_EnumIRQNum */
	if((Copy_EnumIRQNum>=WWDG) && (Copy_EnumIRQNum<= FMPI2C1_error))
	{
		/* CLEAR BitNum at RegNum */
		ICPR[Local_u8RegNum] = ONE_VALUE << Local_u8BitNum;
	}else
	{
		/* update Local_u8ErrorState value*/
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;


}

/**
 * @brief: This function to read active Flag
 * @param[IN] Copy_EnumIRQNum : this variable carry peripheral position in vector table
 * @param[OUT] Copy_u8ActiveFlag : this variable carry ActiveFlag State
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t NVIC_u8GetActiveFlag(IRQNum_t Copy_EnumIRQNum,uint8_t* Copy_u8ActiveFlag)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState;
	/* define a variable to carry RegNum */
	uint8_t Local_u8RegNum;
	/* define a variable to carry BitNum */
	uint8_t Local_u8BitNum;

	/* Calculate this IRQNum at which register from 0 to 7  */
	Local_u8RegNum = Copy_EnumIRQNum / REGISTER_BITS;

	/* Calculate this IRQNum at which Bit from 0 to 31  */
	Local_u8BitNum = Copy_EnumIRQNum % REGISTER_BITS;

	/* check on pointer is not equal null or not */
	if(Copy_u8ActiveFlag !=NULL)
	{
		/* protect our function to check on Copy_EnumIRQNum */
		if((Copy_EnumIRQNum>=WWDG) && (Copy_EnumIRQNum<= FMPI2C1_error))
		{
			/* check on pending flag is raised or not */
			if(GET_BIT(IABR[Local_u8RegNum],Local_u8BitNum) == ONE_VALUE)
			{
				/* Read BitNum at RegNum */
				*Copy_u8ActiveFlag=PENDING;

			}else
			{
				/* Read BitNum at RegNum */
				*Copy_u8ActiveFlag=NOT_PENDING;

			}

		}else
		{
			/* update Local_u8ErrorState value*/
			Local_u8ErrorState=NOK;
		}
	}else
	{
		/* update Local_u8ErrorState value*/
		Local_u8ErrorState=NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

