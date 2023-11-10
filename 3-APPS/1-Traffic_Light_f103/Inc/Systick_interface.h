/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : Systick_interface.h                         **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/


#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_


/**
 * @brief this enum carries the bits of SysTick Control and Status Register
 */
typedef enum
{
	ENABLE=0,   /**< ENABLE */
	TICKINT,    /**< TICKINT */
	CLKSOURCE,  /**< CLKSOURCE */
	COUNTFLAG=16/**< COUNTFLAG */

} SYST_CSR_t;


/**
 * @fn SYSTICK_voidDelay_MS
 * @brief this function to delay in mili second
 * @param[in] Copy_u32TimeIn_MS : time in MSec
 * retval Local_u8ErrorState
 */

uint8_t SYSTICK_u8Delay_MS(uint32_t Copy_u32TimeIn_MS);

/**
 * @fn SYSTICK_voidDelay_US
 * @brief this function to delay in Micro second
 * @param[in] Copy_u32TimeIn_MS : time in USec
 * retval Local_u8ErrorState
 */
uint8_t SYSTICK_u8Delay_US(uint32_t Copy_u32TimeIn_US);

#endif /* SYSTICK_INTERFACE_H_ */
