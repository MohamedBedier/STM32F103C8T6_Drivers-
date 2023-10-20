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
 *
 * @brief this enum carries options of prescaler of AHBFreq no division or division by 8
 */
typedef enum
{
	SYSTEM_FREQ_DIVISIED_BY_8=0,/**< SYSTEM_FREQ_DIVISIED_BY_8 */
	SYSTEM_FREQ_NO_DIVISION  /**< SYSTEM_FREQ_NO_DIVISION */

}AHBFreq_t;


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
 * @param[in] Copy_enumAHBFreq: this variable to set AHB Frequency
 * retval Local_u8ErrorState
 */

uint8_t SYSTICK_voidDelay_MS(uint32_t Copy_u32TimeIn_MS ,AHBFreq_t Copy_enumAHBFreq);

/**
 * @fn SYSTICK_voidDelay_US
 * @brief this function to delay in Micro second
 * @param[in] Copy_u32TimeIn_MS : time in USec
 * @param[in] Copy_enumAHBFreq: this variable to set AHB Frequency
 * retval Local_u8ErrorState
 */
uint8_t SYSTICK_voidDelay_US(uint32_t Copy_u32TimeIn_US ,AHBFreq_t Copy_enumAHBFreq);

#endif /* SYSTICK_INTERFACE_H_ */
