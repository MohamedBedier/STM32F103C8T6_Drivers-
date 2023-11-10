/*************************************************************/
/*************************************************************/
/**                                                         **/
/**  LayerArchitecture : HAL                                **/
/** File Name : SSD_Interface.h                             **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_



#define   SSD_COMMON_ANODE       1u
#define   SSD_COMMON_CATHODE     2u


/**
 * @brief: this a function to initiate SSD Pin configuration its [PORT , PinNum , Mode , CNF_Output]
 * @param[in] PinConfig :this is a pointer from PinConfig_t struct which carry PinConfiguration
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t SSD_u8PinInit(PinConfig_t *PinConfig);


/**
 * @brief: this a function to SSD DisplayOn
 * @param[in] Copy_u8SSDNum : to configure which SSD work on it
 * @param[in] Copy_u8SSDType : to configure SSD type Common cathode or anode
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t SSD_u8DisplayOn(uint8_t Copy_u8SSDNum , uint8_t Copy_u8SSDType);

/**
 * @brief: this a function to SSD DisplayOFF
 * @param[in] Copy_u8SSDNum : to configure which SSD work on it
 * @param[in] Copy_u8SSDType : to configure SSD type Common cathode or anode
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t SSD_u8DisplayOFF(uint8_t Copy_u8SSDNum , uint8_t Copy_u8SSDType);
/**
 * @brief: this a function to set number on SSD
 * @param[in] Copy_u8SSDNum: this is a variable to carry which SSD you want to work on it
 * @param[in] Copy_u8Number
 * @return : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t SSD_u8DisplayNumber( uint8_t Copy_u8SSDNum , uint8_t Copy_u8SSDType, uint8_t Copy_u8Number );


#endif /* SSD_INTERFACE_H_ */
