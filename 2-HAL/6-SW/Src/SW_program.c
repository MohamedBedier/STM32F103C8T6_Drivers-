/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: HAL                                     **/
/** File Name : SW_Program.c                                **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#include "stdint.h"
#include "ErrType.h"
#include "GPIO_interface.h"

#include "SW_interface.h"
#include "SW_private.h"

/**
 * @brief : this function is used to get switch state press or not pressed
 * @param Copy_u8Port
 * @param Copy_Pin
 * @param Copy_u8PullType
 * @param Copy_pu8Value
 * @return Local_u8ErrorState
 */

uint8_t SW_u8GetSwitchState(uint8_t Copy_u8Port , uint8_t Copy_u8Pin , uint8_t Copy_u8PullType , uint8_t* Copy_pu8Value)
{
	/* define error state variable */
	uint8_t Local_u8ErrorState = OK;

	/* define a variable to carry state of sw */
	uint8_t Local_u8Value = INIT_VALUE_BY_ZERO;
/* check on pointer */
	if(Copy_pu8Value != NULL)
	{
		/* check on pull type is pull up or pull down */
		if(Copy_u8PullType == SW_u8PULL_UP)
		{
			GPIO_u8SetPinValue(Copy_u8Port , Copy_u8Pin , PIN_HIGH);

			GPIO_u8ReadPinValue(Copy_u8Port , Copy_u8Pin , &Local_u8Value);

			if(Local_u8Value == SW_u8VALUE_LOW)
			{
				*Copy_pu8Value = SW_u8PRESSED;
			}
			else
			{
				*Copy_pu8Value = SW_u8NOT_PRESSED;
			}

		}
		else if(Copy_u8PullType == SW_u8PULL_DOWN)
		{
			GPIO_u8SetPinValue(Copy_u8Port , Copy_u8Pin , PIN_LOW);

			GPIO_u8ReadPinValue(Copy_u8Port , Copy_u8Pin , &Local_u8Value);

			if(Local_u8Value == SW_u8VALUE_HIGH)
			{
				*Copy_pu8Value = SW_u8PRESSED;
			}
			else
			{
				*Copy_pu8Value = SW_u8NOT_PRESSED;
			}
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
