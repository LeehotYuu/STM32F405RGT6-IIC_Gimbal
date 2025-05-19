#include "Dev_IOI2C1.h"



ioi2c_dev_t devIOI2C1;



static ioi2c_ret_e devIOI2C1_MasterReceive(uint8_t dev, uint8_t* buf, uint16_t len){
    ioi2c_ret_e ret = IOI2C_RET_OK;
    
    ioi2cStart(&devIOI2C1);
    
    dev = (dev<<1) | 0x01;
    
    if(ioi2cSendByte(&devIOI2C1, &dev) == IOI2C_RET_ERROR){
        ret = IOI2C_RET_ERROR;
    }
    for(uint16_t i=0; i<len; i++){
        if(i == len-1){
            buf[i] = ioi2cReadByte(&devIOI2C1, IOI2C_DEV_NOACK);
        }else{
            buf[i] = ioi2cReadByte(&devIOI2C1, IOI2C_DEV_ACK);
        }
    }
    
    ioi2cStop(&devIOI2C1);
    
    return ret;
}



static ioi2c_ret_e devIOI2C1_MasterTransmit(uint8_t dev, uint8_t* buf, uint16_t len){
    ioi2c_ret_e ret = IOI2C_RET_OK;
    
    ioi2cStart(&devIOI2C1);
    
    dev = dev << 1;
    
    if(ioi2cSendByte(&devIOI2C1, &dev) == IOI2C_RET_ERROR){
        ret = IOI2C_RET_ERROR;
    }
    
    for(uint16_t i=0; i<len; i++){
        if(ioi2cSendByte(&devIOI2C1, &buf[i]) == IOI2C_RET_ERROR){
            ret = IOI2C_RET_ERROR;
        }
    }
    
    ioi2cStop(&devIOI2C1);
    
    return ret;
}



static ioi2c_ret_e devIOI2C1_MemReceive(
uint8_t dev, 
uint16_t mem, 
ioi2c_mem_size_e size, 
uint8_t* buf, 
uint16_t len){
    ioi2c_ret_e ret = IOI2C_RET_OK;
    
    ioi2cStart(&devIOI2C1);
    
    ioi2cStop(&devIOI2C1);
    
    return ret;
}



static ioi2c_ret_e devIOI2C1_MemTransmit(
uint8_t dev, 
uint16_t mem, 
ioi2c_mem_size_e size, 
uint8_t* buf, 
uint16_t len){
    ioi2c_ret_e ret = IOI2C_RET_OK;
    
    ioi2cStart(&devIOI2C1);
    
    ioi2cStop(&devIOI2C1);
    
    return ret;
}



ioi2c_dev_t* devIOI2C1_Register(ioi2c_drv_t* drv, ioi2c_ack_e ack){
    devIOI2C1.drv = drv;
    devIOI2C1.ack = ack;
    devIOI2C1.masterReceive = devIOI2C1_MasterReceive;
    devIOI2C1.masterTransmit = devIOI2C1_MasterTransmit;
    devIOI2C1.memReceive = devIOI2C1_MemReceive;    // This feature is not implemented
    devIOI2C1.memTransmit = devIOI2C1_MemTransmit;  // This feature is not implemented
    
    return &devIOI2C1;
}


