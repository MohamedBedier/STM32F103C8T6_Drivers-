/*************************************************************/
/*************************************************************/
/**                                                         **/
/**  LayerArchitecture : HAL                                **/
/** File Name : SSD_Cfg.h                                   **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#ifndef SSD_CFG_H_
#define SSD_CFG_H_

/* determine NUM_OF_SSD_IN_PROJECT because we use it to do 2_DIM array to carry NUMBERS  */
#define NUM_OF_SSD_IN_PROJECT  3u

/* SSD LEDS its PORTS AND PINS */

/* LED_A */
#define LED_A_PORT   PORTA
#define LED_A_PIN    PIN11

/* LED_B */
#define LED_B_PORT   PORTA
#define LED_B_PIN    PIN8

/* LED_C */
#define LED_C_PORT   PORTB
#define LED_C_PIN    PIN15

/* LED_D */
#define LED_D_PORT   PORTB
#define LED_D_PIN    PIN14

/* LED_E */
#define LED_E_PORT   PORTB
#define LED_E_PIN    PIN13

/* LED_F */
#define LED_F_PORT   PORTB
#define LED_F_PIN    PIN12

/* LED_G */
#define LED_G_PORT   PORTA
#define LED_G_PIN    PIN12

/* LED_DOT */
#define DOT_PORT    PORTA
#define DOT_PIN     PIN15

#define COM_SSD_1_PORT PORTB
#define COM_SSD_1_PIN  PIN8

#define COM_SSD_2_PORT PORTB
#define COM_SSD_2_PIN  PIN9

#define COM_SSD_3_PORT PORTB
#define COM_SSD_3_PIN  PIN3

#endif /* SSD_CFG_H_ */
