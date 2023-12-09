/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: Hal                                     **/
/** File Name : SW_Interface.h                              **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

/* Preprocessor File Guard */
#ifndef SW_INTERFACE_H_
#define SW_INTERFACE_H_

/**
 * @brief : this function is used to get switch state press or not pressed
 * @param Copy_u8Port
 * @param Copy_Pin
 * @param Copy_u8PullType
 * @param Copy_pu8Value
 * @return Local_u8ErrorState
 */
uint8_t SW_u8GetSwitchState(uint8_t Copy_u8Port , uint8_t Copy_Pin , uint8_t Copy_u8PullType , uint8_t* Copy_pu8Value);

#endif
