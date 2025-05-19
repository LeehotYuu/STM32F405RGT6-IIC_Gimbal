#include "Bsp_IOI2C1.h"
#include "main.h"



#define BSP_IOI2C1_DELAY_US     3



ioi2c_drv_t bspIOI2C1;



static void     bspIOI2C1_SCK_H(void){ HAL_GPIO_WritePin(IOI2C_LEFT_SCL_GPIO_Port, IOI2C_LEFT_SCL_Pin, GPIO_PIN_SET);   ioi2cDelay_us(BSP_IOI2C1_DELAY_US);}
static void     bspIOI2C1_SCK_L(void){ HAL_GPIO_WritePin(IOI2C_LEFT_SCL_GPIO_Port, IOI2C_LEFT_SCL_Pin, GPIO_PIN_RESET); ioi2cDelay_us(BSP_IOI2C1_DELAY_US);}
static void     bspIOI2C1_SDA_H(void){ HAL_GPIO_WritePin(IOI2C_LEFT_SDA_GPIO_Port, IOI2C_LEFT_SDA_Pin, GPIO_PIN_SET);   ioi2cDelay_us(BSP_IOI2C1_DELAY_US);}
static void     bspIOI2C1_SDA_L(void){ HAL_GPIO_WritePin(IOI2C_LEFT_SDA_GPIO_Port, IOI2C_LEFT_SDA_Pin, GPIO_PIN_RESET); ioi2cDelay_us(BSP_IOI2C1_DELAY_US);}
static uint8_t  bspIOI2C1_SDA_R(void){ ioi2cDelay_us(BSP_IOI2C1_DELAY_US);return HAL_GPIO_ReadPin(IOI2C_LEFT_SDA_GPIO_Port, IOI2C_LEFT_SDA_Pin); }



const GPIO_InitTypeDef bspIOI2C1_GPIOInit_SDA_I = {
    .Mode = GPIO_MODE_INPUT,
    .Pin = IOI2C_LEFT_SDA_Pin,
    .Pull = GPIO_PULLUP,
    .Speed = GPIO_SPEED_FREQ_LOW,
};
static void bspIOI2C1_SDA_I(void){
    HAL_GPIO_Init(IOI2C_LEFT_SDA_GPIO_Port, (GPIO_InitTypeDef*)&bspIOI2C1_GPIOInit_SDA_I);
}



const GPIO_InitTypeDef bspIOI2C1_GPIOInit_SDA_O = {
    .Mode = GPIO_MODE_OUTPUT_OD,
    .Pin = IOI2C_LEFT_SDA_Pin,
    .Pull = GPIO_PULLUP,
    .Speed = GPIO_SPEED_FREQ_LOW,
};
static void bspIOI2C1_SDA_O(void){
    HAL_GPIO_Init(IOI2C_LEFT_SDA_GPIO_Port, (GPIO_InitTypeDef*)&bspIOI2C1_GPIOInit_SDA_O);
}



ioi2c_drv_t* bspIOI2C1_Register(void){
    bspIOI2C1._sckH = bspIOI2C1_SCK_H;
    bspIOI2C1._sckL = bspIOI2C1_SCK_L;
    bspIOI2C1._sdaH = bspIOI2C1_SDA_H;
    bspIOI2C1._sdaL = bspIOI2C1_SDA_L;
    bspIOI2C1._sdaR = bspIOI2C1_SDA_R;
    bspIOI2C1._sdaI = bspIOI2C1_SDA_I;
    bspIOI2C1._sdaO = bspIOI2C1_SDA_O;
    
    return &bspIOI2C1;
}


