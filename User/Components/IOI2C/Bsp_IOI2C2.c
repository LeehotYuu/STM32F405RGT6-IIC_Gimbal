#include "Bsp_IOI2C2.h"
#include "main.h"



#define BSP_IOI2C2_DELAY_US     2



ioi2c_drv_t bspIOI2C2;



static void     bspIOI2C2_SCK_H(void){ HAL_GPIO_WritePin(IOI2C_RIGHT_SCL_GPIO_Port, IOI2C_RIGHT_SCL_Pin, GPIO_PIN_SET);   ioi2cDelay_us(BSP_IOI2C2_DELAY_US);}
static void     bspIOI2C2_SCK_L(void){ HAL_GPIO_WritePin(IOI2C_RIGHT_SCL_GPIO_Port, IOI2C_RIGHT_SCL_Pin, GPIO_PIN_RESET); ioi2cDelay_us(BSP_IOI2C2_DELAY_US);}
static void     bspIOI2C2_SDA_H(void){ HAL_GPIO_WritePin(IOI2C_RIGHT_SDA_GPIO_Port, IOI2C_RIGHT_SDA_Pin, GPIO_PIN_SET);   ioi2cDelay_us(BSP_IOI2C2_DELAY_US);}
static void     bspIOI2C2_SDA_L(void){ HAL_GPIO_WritePin(IOI2C_RIGHT_SDA_GPIO_Port, IOI2C_RIGHT_SDA_Pin, GPIO_PIN_RESET); ioi2cDelay_us(BSP_IOI2C2_DELAY_US);}
static uint8_t  bspIOI2C2_SDA_R(void){ ioi2cDelay_us(BSP_IOI2C2_DELAY_US);return HAL_GPIO_ReadPin(IOI2C_RIGHT_SDA_GPIO_Port, IOI2C_RIGHT_SDA_Pin); }



const GPIO_InitTypeDef bspIOI2C2_GPIOInit_SDA_I = {
    .Mode = GPIO_MODE_INPUT,
    .Pin = IOI2C_RIGHT_SDA_Pin,
    .Pull = GPIO_PULLUP,
    .Speed = GPIO_SPEED_FREQ_LOW,
};
static void bspIOI2C2_SDA_I(void){
    HAL_GPIO_Init(IOI2C_RIGHT_SDA_GPIO_Port, (GPIO_InitTypeDef*)&bspIOI2C2_GPIOInit_SDA_I);
}



const GPIO_InitTypeDef bspIOI2C2_GPIOInit_SDA_O = {
    .Mode = GPIO_MODE_OUTPUT_OD,
    .Pin = IOI2C_RIGHT_SDA_Pin,
    .Pull = GPIO_PULLUP,
    .Speed = GPIO_SPEED_FREQ_LOW,
};
static void bspIOI2C2_SDA_O(void){
    HAL_GPIO_Init(IOI2C_RIGHT_SDA_GPIO_Port, (GPIO_InitTypeDef*)&bspIOI2C2_GPIOInit_SDA_O);
}



ioi2c_drv_t* bspIOI2C2_Register(void){
    bspIOI2C2._sckH = bspIOI2C2_SCK_H;
    bspIOI2C2._sckL = bspIOI2C2_SCK_L;
    bspIOI2C2._sdaH = bspIOI2C2_SDA_H;
    bspIOI2C2._sdaL = bspIOI2C2_SDA_L;
    bspIOI2C2._sdaR = bspIOI2C2_SDA_R;
    bspIOI2C2._sdaI = bspIOI2C2_SDA_I;
    bspIOI2C2._sdaO = bspIOI2C2_SDA_O;
    
    return &bspIOI2C2;
}


