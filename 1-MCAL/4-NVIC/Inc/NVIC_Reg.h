/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : NVIC_Reg.h                                  **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/


#ifndef NVIC_REG_H_
#define NVIC_REG_H_

#define  ISER    ((volatile uint32_t*)0xE000E100)

#define  ICER    ((volatile uint32_t*)0XE000E180)

#define  ISPR    ((volatile uint32_t*)0XE000E200)

#define  ICPR    ((volatile uint32_t*)0XE000E280)

#define  IABR    ((volatile uint32_t*)0xE000E300)

#define  IPR     ((volatile uint32_t*)0xE000E400)

#define  STIR    ((volatile uint32_t*)0xE000EF00)






#endif
/* NVIC_REG_H_ */
