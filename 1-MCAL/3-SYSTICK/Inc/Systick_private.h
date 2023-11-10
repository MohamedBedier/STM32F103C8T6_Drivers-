/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : Systick_private.h                           **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/


#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_


#define  AHB_CLK_DIVIDED_bY_8 0u
#define AHB_CLK  1u

#define CONVERT_FROM_US_TO_MS  1000u

#define MAX_RELOAD_VALUE   16777215U

#define MAX_RELOAD_VALUE_AS_FLOAT   16777215.0f


#define  FLAG_NOT_RAISED     0u

#define RESET_RELOAD_VALUE  0u
#define SYS_FREQ_8MHZ  8u

#define SYSTICK_MASK    0xFFFFFF


#define AHB_TICK_TIME     0.0625f
#define AHB_BY8_TICK_TIME 0.5f


#endif /* SYSTICK_PRIVATE_H_ */
