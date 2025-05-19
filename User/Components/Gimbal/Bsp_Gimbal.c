#include "Bsp_Gimbal.h"
#include "Bsp_IOI2C1.h"
#include "Bsp_IOI2C2.h"
#include "Dev_IOI2C1.h"
#include "Dev_IOI2C2.h"



ioi2c_drv_t* drvIOI2C_Left;
ioi2c_dev_t* devIOI2C_Left;
ioi2c_drv_t* drvIOI2C_Right;
ioi2c_dev_t* devIOI2C_Right;

gimbal_driver_t bspGimbalL = { 0 };
gimbal_driver_t bspGimbalR = { 0 };



static uint16_t bspGimbal_L_GetX(){
    uint16_t    ret;
    uint8_t     buf[3];
    
    devIOI2C_Left->masterReceive(0x5C>>1, buf, 3);
    buf[0] &= 0x7F;// The highest bit is invalid
    if(((buf[0]+buf[1]+buf[2])&0xFF) != 0)return 0xFFFF;   // error value
    ret = buf[0];
    ret = (ret<<8) + buf[1];
    
    return ret;
}



static uint16_t bspGimbal_L_GetY(){
    uint16_t    ret;
    uint8_t     buf[3];
    
    devIOI2C_Left->masterReceive(0x7C>>1, buf, 3);
    buf[0] &= 0x7F;// The highest bit is invalid
    if(((buf[0]+buf[1]+buf[2])&0xFF) != 0)return 0xFFFF;   // error value
    ret = buf[0];
    ret = (ret<<8) + buf[1];
    
    return ret;
}



static uint16_t bspGimbal_R_GetX(){
    uint16_t    ret;
    uint8_t     buf[3];
    
    devIOI2C_Right->masterReceive(0x5C>>1, buf, 3);
    buf[0] &= 0x7F;// The highest bit is invalid
    if(((buf[0]+buf[1]+buf[2])&0xFF) != 0)return 0xFFFF;   // error value
    ret = buf[0];
    ret = (ret<<8) + buf[1];
    
    return ret;
}



static uint16_t bspGimbal_R_GetY(){
    uint16_t    ret;
    uint8_t     buf[3];
    
    devIOI2C_Right->masterReceive(0x7C>>1, buf, 3);
    buf[0] &= 0x7F;// The highest bit is invalid
    if(((buf[0]+buf[1]+buf[2])&0xFF) != 0)return 0xFFFF;   // error value
    ret = buf[0];
    ret = (ret<<8) + buf[1];
    
    return ret;
}



gimbal_driver_t* bspGimbalRegister_L(void){
    drvIOI2C_Left  = bspIOI2C1_Register();
    devIOI2C_Left  = devIOI2C1_Register(drvIOI2C_Left,  IOI2C_DEV_ACK);// ACK mode
    
    bspGimbalL._getX = bspGimbal_L_GetX;
    bspGimbalL._getY = bspGimbal_L_GetY;
    
    return &bspGimbalL;
}



gimbal_driver_t* bspGimbalRegister_R(void){
    drvIOI2C_Right = bspIOI2C2_Register();
    devIOI2C_Right = devIOI2C2_Register(drvIOI2C_Right, IOI2C_DEV_ACK);// ACK mode
    
    bspGimbalR._getX = bspGimbal_R_GetX;
    bspGimbalR._getY = bspGimbal_R_GetY;
    
    return &bspGimbalR;
}


