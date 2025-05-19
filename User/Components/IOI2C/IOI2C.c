#include "IOI2C.h"
#include "main.h"



/* us delay, but not accurate */
void ioi2cDelay_us(uint32_t timeout){
    if(timeout == 0)return;
    
    volatile uint32_t t = timeout * 12;
    while(--t);
}



/* ms delay, but not accurate */
void ioi2cDelay_ms(uint32_t timeout){
    if(timeout == 0)return;
    
    volatile uint32_t t;
    while(--timeout){
        t = 10290;
        while(--t);
    }
}



uint32_t ioi2cGetTick(void){
    return HAL_GetTick();
}



void ioi2cStart(ioi2c_dev_t* dev){
    dev->drv->_sdaL();
    dev->drv->_sckL();
}



ioi2c_ret_e ioi2cSendByte(ioi2c_dev_t* dev, uint8_t* byte){
    ioi2c_ret_e ret = IOI2C_RET_OK;
    
    uint8_t data = *byte;
    for(uint8_t i=0; i<8; i++, data<<=1){
        if(data & 0x80){
            dev->drv->_sdaH();
        }else{
            dev->drv->_sdaL();
        }
        dev->drv->_sckH();
        dev->drv->_sckL();
    }
    
    dev->drv->_sdaH();
    dev->drv->_sdaI();
    if(dev->ack){
        ret = IOI2C_RET_ERROR;
        dev->drv->_sckH();
        uint32_t startTick = ioi2cGetTick();
        while(ioi2cGetTick() - startTick < 5){
            if(dev->drv->_sdaR() == 0){
                ret = IOI2C_RET_OK;
                break;
            }
        };
        dev->drv->_sckL();
    }else{
        dev->drv->_sckH();
        dev->drv->_sckL();
    }
    dev->drv->_sdaO();
    
    return ret;
}



uint8_t ioi2cReadByte(ioi2c_dev_t* dev, uint8_t ack){
    uint8_t data = 0;
    
    dev->drv->_sdaH();
    dev->drv->_sdaI();
    for(uint8_t i=0; i<8; i++){
        dev->drv->_sckH();
        data <<= 1;
        if(dev->drv->_sdaR() == 1)data++;
        dev->drv->_sckL();
    }
    
    dev->drv->_sdaO();
    
    if(ack){
        dev->drv->_sdaL();
        dev->drv->_sckH();
        dev->drv->_sckL();
        dev->drv->_sdaH();
    }else{
        dev->drv->_sckH();
        dev->drv->_sckL();
    }
    
    return data;
}



void ioi2cStop(ioi2c_dev_t* dev){
    dev->drv->_sckH();
    dev->drv->_sdaH();
}


