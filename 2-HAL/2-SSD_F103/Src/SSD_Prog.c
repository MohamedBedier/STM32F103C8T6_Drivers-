/*************************************************************/
/*************************************************************/
/**                                                         **/
/**  LayerArchitecture : HAL                                **/
/** File Name : SSD_Program.c                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#include  <stdint.h>
#include "BIT_MATH.h"
#include "ErrType.h"
#include "GPIO_interface.h"

#include "SSD_Cfg.h"
#include "SSD_Private.h"
#include "SSD_Interface.h"



/* This is a 2_DIM array to carry the NUMBER from 0 to 9 as Common cathode and if you want to work as common anode ~NUMBER */
uint8_t SSD_NUMBER_Arr[NUM_OF_SSD_IN_PROJECT][NUM_FROM_0_TO_9] =
{
		{SSD1_NUMBER0 , SSD1_NUMBER1 , SSD1_NUMBER2 , SSD1_NUMBER3 , SSD1_NUMBER4 , SSD1_NUMBER5 ,	SSD1_NUMBER6 , SSD1_NUMBER7 , SSD1_NUMBER8 , SSD1_NUMBER9 } ,
		{SSD2_NUMBER0 , SSD2_NUMBER1 , SSD2_NUMBER2 , SSD2_NUMBER3 , SSD2_NUMBER4 , SSD2_NUMBER5 ,	SSD2_NUMBER6 , SSD2_NUMBER7 , SSD2_NUMBER8 , SSD2_NUMBER9 } ,
		{SSD3_NUMBER0 , SSD3_NUMBER1 , SSD3_NUMBER2 , SSD3_NUMBER3 , SSD3_NUMBER4 , SSD3_NUMBER5 ,	SSD3_NUMBER6 , SSD3_NUMBER7 , SSD3_NUMBER8 , SSD3_NUMBER9 }
} ;

/* this array carries PORT ,which SSD LED connected with it */
uint8_t SSD_LED_PORT [ NUM_OF_SSD_LED ] = {LED_A_PORT , LED_B_PORT , LED_C_PORT , LED_D_PORT , LED_E_PORT , LED_F_PORT  , LED_G_PORT , DOT_PORT};
/* this array carries PIN ,which SSD LED connected with it */
uint8_t SSD_LED_PINS [ NUM_OF_SSD_LED ] = {LED_A_PIN  , LED_B_PIN  , LED_C_PIN , LED_D_PIN , LED_E_PIN , LED_F_PIN  , LED_G_PIN , DOT_PIN};
/* this array carries EN PORT ,which SSD EN PIN connected with it */
uint8_t SSD_EN_PORT[ NUM_OF_SSD_IN_PROJECT ] = {COM_SSD_1_PORT , COM_SSD_2_PORT , COM_SSD_3_PORT};
/* this array carries EN PIN  */
uint8_t SSD_EN_PIN[ NUM_OF_SSD_IN_PROJECT ] = {COM_SSD_1_PIN , COM_SSD_2_PIN , COM_SSD_3_PIN};


/**
 * @brief: this a function to initiate SSD Pin configuration its [PORT , PinNum , Mode , CNF_Output]
 * @param[in] PinConfig :this is a pointer from PinConfig_t struct which carry PinConfiguration
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t SSD_u8PinInit(PinConfig_t *PinConfig)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState =OK;

	/* check on pointer 'SSD_Configuration' if not refer to NULL  */
	if(PinConfig !=NULL)
	{
		/* set Direction of SSD Pins */
		GPIO_u8PinInit(PinConfig);
	}else
	{
		/* Update Local_u8ErrorState */
		Local_u8ErrorState =NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


/**
 * @brief: this a function to SSD DisplayOn
 * @param[in] Copy_u8SSDNum : to configure which SSD work on it
 * @param[in] Copy_u8SSDType : to configure SSD type Common cathode or anode
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t SSD_u8DisplayOn(uint8_t Copy_u8SSDNum , uint8_t Copy_u8SSDType)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState =OK;

	/* check on Copy_u8SSDNum Boundaries >= 1 At least one SSD in the project, and max  NUM_OF_SSD_IN_PROJECT  */
	if((Copy_u8SSDNum >= ONE_VALUE) && (Copy_u8SSDNum <= NUM_OF_SSD_IN_PROJECT))
	{
		/* check on SSD_TYPE [SSD_COMMON_ANODE,SSD_COMMON_CATHODE]  */
		if(Copy_u8SSDType == SSD_COMMON_CATHODE)
		{
			/* Set common pin as low because SSD is SSD_COMMON_CATHODE  */
			GPIO_u8SetPinValue(SSD_EN_PORT[Copy_u8SSDNum - ONE_VALUE],SSD_EN_PIN[Copy_u8SSDNum - ONE_VALUE] , PIN_LOW);
		}else if (Copy_u8SSDType == SSD_COMMON_ANODE)
		{
			/* Set common pin as high because SSD is SSD_COMMON_ANODE  */
			GPIO_u8SetPinValue(SSD_EN_PORT[Copy_u8SSDNum - ONE_VALUE],SSD_EN_PIN[Copy_u8SSDNum - ONE_VALUE] , PIN_HIGH);
		}else
		{
			/* Update Local_u8ErrorState */
			Local_u8ErrorState =NOK;
		}
	}else
	{
		/* Update Local_u8ErrorState */
		Local_u8ErrorState =NOK;
	}

	return Local_u8ErrorState;
}



/**
 * @brief: this a function to SSD DisplayOFF
 * @param[in] Copy_u8SSDNum : to configure which SSD work on it
 * @param[in] Copy_u8SSDType : to configure SSD type Common cathode or anode
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t SSD_u8DisplayOFF(uint8_t Copy_u8SSDNum , uint8_t Copy_u8SSDType)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState =OK;

	/* check on Copy_u8SSDNum Boundaries >= 1 At least one SSD in the project, and max  NUM_OF_SSD_IN_PROJECT  */
	if((Copy_u8SSDNum >= ONE_VALUE) && (Copy_u8SSDNum <= NUM_OF_SSD_IN_PROJECT))
	{
		/* check on SSD_TYPE [SSD_COMMON_ANODE,SSD_COMMON_CATHODE]  */
		if(Copy_u8SSDType == SSD_COMMON_CATHODE)
		{
			/* Set common pin as low because SSD is SSD_COMMON_CATHODE  */
			GPIO_u8SetPinValue(SSD_EN_PORT[Copy_u8SSDNum - ONE_VALUE],SSD_EN_PIN[Copy_u8SSDNum - ONE_VALUE] , PIN_HIGH);
		}else if (Copy_u8SSDType == SSD_COMMON_ANODE)
		{
			/* Set common pin as high because SSD is SSD_COMMON_ANODE  */
			GPIO_u8SetPinValue(SSD_EN_PORT[Copy_u8SSDNum - ONE_VALUE],SSD_EN_PIN[Copy_u8SSDNum - ONE_VALUE] ,PIN_LOW );
		}else
		{
			/* Update Local_u8ErrorState */
			Local_u8ErrorState =NOK;
		}
	}else
	{
		/* Update Local_u8ErrorState */
		Local_u8ErrorState =NOK;
	}

	return Local_u8ErrorState;
}

/**
 * @brief: this a function to set number on SSD
 * @param[in] Copy_u8SSDNum: this is a variable to carry which SSD you want to work on it
 * @param[in] Copy_u8Number
 * @return : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t SSD_u8DisplayNumber( uint8_t Copy_u8SSDNum , uint8_t Copy_u8SSDType, uint8_t Copy_u8Number )
{
	/* Define a variable to carry which SSD you want to work on it */
	uint8_t Local_u8SSDCounter = INIT_VALUE_BY_ZERO ;
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState = OK ;


	/* check on SSD_TYPE [SSD_COMMON_ANODE,SSD_COMMON_CATHODE]  */
	if(Copy_u8SSDType == SSD_COMMON_CATHODE)
	{
		/* Enable Common of the SSD  you want to work on it */
		switch( Copy_u8SSDNum )
		{
		case 1 :
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD1] , SSD_EN_PIN[SSD1] , PIN_HIGH ) ;
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD2] , SSD_EN_PIN[SSD2] , PIN_LOW ) ;
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD3] , SSD_EN_PIN[SSD3] , PIN_LOW ) ;
			break;
		case 2 :
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD1] , SSD_EN_PIN[SSD1] , PIN_LOW ) ;
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD2] , SSD_EN_PIN[SSD2] , PIN_HIGH ) ;
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD3] , SSD_EN_PIN[SSD3] , PIN_LOW ) ;
			break;
		case 3 :
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD1] , SSD_EN_PIN[SSD1] , PIN_LOW ) ;
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD2] , SSD_EN_PIN[SSD2] , PIN_LOW ) ;
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD3] , SSD_EN_PIN[SSD3] , PIN_HIGH ) ;
			break;
		default:Local_u8ErrorState=NOK;break;/* Update Local_u8ErrorState */

		}
		/* DISPLAY The Number on the Required SSD */
		for( Local_u8SSDCounter = SSD_START_WITH_A_PIN ; Local_u8SSDCounter <= SSD_END_WITH_G_PIN ; Local_u8SSDCounter++ )
		{
			/* From global arrays and SSD_Cfg we able to determinate PORT AND PIN OF SSD led  */
			GPIO_u8SetPinValue( SSD_LED_PORT[ Local_u8SSDCounter ] , SSD_LED_PINS[ Local_u8SSDCounter ] , (( SSD_NUMBER_Arr[ Copy_u8SSDNum - ONE_VALUE ][ Copy_u8Number ] >> Local_u8SSDCounter )&SSD_ADDING_WITH_0X01 ) ) ;
		}
	}else if (Copy_u8SSDType == SSD_COMMON_ANODE)
	{
		/* Enable Common of the SSD  you want to work on it */
		switch( Copy_u8SSDNum )
		{
		case 1 :
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD1] , SSD_EN_PIN[SSD1] , PIN_LOW ) ;
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD2] , SSD_EN_PIN[SSD2] , PIN_HIGH ) ;
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD3] , SSD_EN_PIN[SSD3] , PIN_HIGH ) ;
			break;
		case 2 :
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD1] , SSD_EN_PIN[SSD1] , PIN_HIGH ) ;
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD2] , SSD_EN_PIN[SSD2] , PIN_LOW ) ;
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD3] , SSD_EN_PIN[SSD3] , PIN_HIGH ) ;
			break;
		case 3 :
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD1] , SSD_EN_PIN[SSD1] , PIN_HIGH ) ;
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD2] , SSD_EN_PIN[SSD2] , PIN_HIGH ) ;
			GPIO_u8SetPinValue(SSD_EN_PORT[SSD3] , SSD_EN_PIN[SSD3] , PIN_LOW ) ;
			break;
		default:Local_u8ErrorState=NOK;break;/* Update Local_u8ErrorState */

		}
		/* DISPLAY The Number on the Required SSD */
		for( Local_u8SSDCounter = SSD_START_WITH_A_PIN ; Local_u8SSDCounter <= SSD_END_WITH_G_PIN ; Local_u8SSDCounter++ )
		{
			/* From global arrays and SSD_Cfg we able to determinate PORT AND PIN OF SSD led  */
			GPIO_u8SetPinValue( SSD_LED_PORT[ Local_u8SSDCounter ] , SSD_LED_PINS[ Local_u8SSDCounter ] , ~(( SSD_NUMBER_Arr[ Copy_u8SSDNum - ONE_VALUE ][ Copy_u8Number ] >> Local_u8SSDCounter )&SSD_ADDING_WITH_0X01 ) ) ;
		}
	}else
	{
		/* Update Local_u8ErrorState */
		Local_u8ErrorState =NOK;
	}



	return Local_u8ErrorState;
}
