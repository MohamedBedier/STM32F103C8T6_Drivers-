/*************************************************************/
/*************************************************************/
/**                                                         **/
/**  LayerArchitecture : HAL                                **/
/** File Name :KPD_Program.c                                **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/


#include "stdint.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "Stm32F103xx.h"

#include "GPIO_interface.h"
#include "Systick_interface.h"
#include "KPD_Cfg.h"
#include "KPD_Interface.h"
#include "KPD_Private.h"

/**
 * @details : All row pins are input pulled up , All column pins are output high
 */

uint8_t KPD_u8GetPressedKey(void)
{
	/* define a variable to carry pressed key value */
	uint8_t Local_u8PressedKey = KPD_u8NO_PRESSED_KEY_VAL;
	/* define two Counter variables for row and column */
	uint8_t Local_u8ROWCounter;
	uint8_t Local_u8ColCounter;

	uint8_t Local_u8KeyState;
	/* TO Save stack consumption using static keyword ===> sort in .data section  */
	static uint8_t Local_u8ColArr[KPD_u8COL_NUM] = {KPD_u8COL1_PIN,KPD_u8COL2_PIN,KPD_u8COL3_PIN,KPD_u8COL4_PIN};
	static uint8_t Local_u8ROWArr[KPD_u8ROW_NUM] = {KPD_u8ROW1_PIN,KPD_u8ROW2_PIN,KPD_u8ROW3_PIN,KPD_u8ROW4_PIN};
	static uint8_t Local_u8KPDArr[KPD_u8ROW_NUM][KPD_u8COL_NUM] = KPD_u8BUTTON_ARR;


	/* this loop to activate the column pins  */
	for(Local_u8ColCounter = INIT_VALUE_BY_ZERO ; Local_u8ColCounter < KPD_u8COL_NUM ; Local_u8ColCounter++)
	{
		/* Activate the current column by low */
		GPIO_u8SetPinValue(KPD_u8COL_PORT , Local_u8ColArr[Local_u8ColCounter],PIN_LOW);

		/* this loop to activate the Row pins */
		for(Local_u8ROWCounter = INIT_VALUE_BY_ZERO ; Local_u8ROWCounter < KPD_u8ROW_NUM ; Local_u8ROWCounter++)
		{
			/* READ the current row */
			GPIO_u8ReadPinValue(KPD_u8ROW_PORT ,Local_u8ROWArr[Local_u8ROWCounter] , &Local_u8KeyState);

			/* if the current row is low , button is pressed */
			if(Local_u8KeyState == PIN_LOW)
			{

				/* wait until key is released */
				while (Local_u8KeyState == PIN_LOW)
				{
					GPIO_u8ReadPinValue(KPD_u8ROW_PORT ,Local_u8ROWArr[Local_u8ROWCounter] , &Local_u8KeyState);

				}
				Local_u8PressedKey = Local_u8KPDArr[Local_u8ROWCounter][Local_u8ColCounter];
				return Local_u8PressedKey;
			}
		}
		/* Deactivate the current col */
		GPIO_u8SetPinValue(KPD_u8COL_PORT , Local_u8ColArr[Local_u8ColCounter],PIN_HIGH);
	}

	/* if the compiler reach here , return  0xff  */
	return Local_u8PressedKey;
}
