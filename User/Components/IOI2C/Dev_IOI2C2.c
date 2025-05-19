#include "Dev_IOI2C2.h"



ioi2c_dev_t devIOI2C2;



static ioi2c_ret_e devIOI2C2_MasterReceive(uint8_t dev, uint8_t* buf, uint16_t len){
    ioi2c_ret_e ret = IOI2C_RET_OK;
    
    ioi2cStart(&devIOI2C2);
    
    dev = (dev<<1) | 0x01;
    
    if(ioi2cSendByte(&devIOI2C2, &dev) == IOI2C_RET_ERROR){
        ret = IOI2C_RET_ERROR;
    }
    for(uint16_t i=0; i<len; i++){
        if(i == len-1){
            buf[i] = ioi2cReadByte(&devIOI2C2, IOI2C_DEV_NOACK);
        }else{
            buf[i] = ioi2cReadByte(&devIOI2C2, IOI2C_DEV_ACK);
        }
    }
    
    ioi2cStop(&devIOI2C2);
    
    return ret;
}



static ioi2c_ret_e devIOI2C2_MasterTransmit(uint8_t dev, uint8_t* buf, uint16_t len){
    ioi2c_ret_e ret = IOI2C_RET_OK;
    
    ioi2cStart(&devIOI2C2);
    
    dev = dev << 1;
    
    if(ioi2cSendByte(&devIOI2C2, &dev) == IOI2C_RET_ERROR){
        ret = IOI2C_RET_ERROR;
    }
    
    for(uint16_t i=0; i<len; i++){
        if(ioi2cSendByte(&devIOI2C2, &buf[i]) == IOI2C_RET_ERROR){
            ret = IOI2C_RET_ERROR;
        }
    }
    
    ioi2cStop(&devIOI2C2);
    
    return ret;
}



static ioi2c_ret_e devIOI2C2_MemReceive(
uint8_t dev, 
uint16_t mem, 
ioi2c_mem_size_e size, 
uint8_t* buf, 
uint16_t len){
    ioi2c_ret_e ret = IOI2C_RET_OK;
    
    ioi2cStart(&devIOI2C2);
    
    ioi2cStop(&devIOI2C2);
    
    return ret;
}



static ioi2c_ret_e devIOI2C2_MemTransmit(
uint8_t dev, 
uint16_t mem, 
ioi2c_mem_size_e size, 
uint8_t* buf, 
uint16_t len){
    ioi2c_ret_e ret = IOI2C_RET_OK;
    
    ioi2cStart(&devIOI2C2);
    
    ioi2cStop(&devIOI2C2);
    
    return ret;
}



ioi2c_dev_t* devIOI2C2_Register(ioi2c_drv_t* drv, ioi2c_ack_e ack){
    devIOI2C2.drv = drv;
    devIOI2C2.ack = ack;
    devIOI2C2.masterReceive = devIOI2C2_MasterReceive;
    devIOI2C2.masterTransmit = devIOI2C2_MasterTransmit;
    devIOI2C2.memReceive = devIOI2C2_MemReceive;    // This feature is not implemented
    devIOI2C2.memTransmit = devIOI2C2_MemTransmit;  // This feature is not implemented
    
    return &devIOI2C2;
}


