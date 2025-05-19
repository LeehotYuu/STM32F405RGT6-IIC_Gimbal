#ifndef __IOI2C_H
#define __IOI2C_H



#include <stdio.h>
#include <stdint.h>



/**
Use GPIO to simulate the IIC protocol. The hardware driver is in the bsp file. 
An IIC device calls a driver to implement the IIC communication process.
*/



/**
This is the definition of the ioi2c driver. You only need to implement the interface functions 
required in the driver definition and call it from the ioi2c device.
*/
typedef void    (*ioi2c_drv_set_t)  (void);
typedef uint8_t (*ioi2c_drv_get_t)  (void);
typedef void    (*ioi2c_drv_sda_i_t)(void);
typedef void    (*ioi2c_drv_sda_o_t)(void);

typedef struct ioi2c_driver_s{
    ioi2c_drv_set_t                 _sckL;  // Set sck low level
    ioi2c_drv_set_t                 _sckH;  // Set sck low level
    ioi2c_drv_set_t                 _sdaL;  // Set sda low level
    ioi2c_drv_set_t                 _sdaH;  // Set sda high level
    ioi2c_drv_get_t                 _sdaR;  // Read sda level
    ioi2c_drv_sda_i_t               _sdaI;  // Set sda input mode
    ioi2c_drv_sda_o_t               _sdaO;  // Set sda output mode
}ioi2c_drv_t;



/** 
This is the definition of the ioi2c device. 
After calling the registration function, you can use the functional interface provided by this device 
*/
typedef enum {
    IOI2C_RET_OK = 0x00U,
    IOI2C_RET_ERROR,
}ioi2c_ret_e;

typedef enum {
    IOI2C_MEM_ADDR_SIZE_8BITS = 0x00U,
    IOI2C_MEM_ADDR_SIZE_16BITS,
}ioi2c_mem_size_e;

typedef ioi2c_ret_e (*ioi2c_dev_master_receive_t)   (uint8_t addr, uint8_t* buf, uint16_t len);
typedef ioi2c_ret_e (*ioi2c_dev_master_transmit_t)  (uint8_t addr, uint8_t* buf, uint16_t len);
typedef ioi2c_ret_e (*ioi2c_dev_mem_receive_t)      (uint8_t addr, uint16_t mem, ioi2c_mem_size_e size, uint8_t* buf, uint16_t len);
typedef ioi2c_ret_e (*ioi2c_dev_mem_transmit_t)     (uint8_t addr, uint16_t mem, ioi2c_mem_size_e size, uint8_t* buf, uint16_t len);

typedef enum {
    IOI2C_DEV_NOACK = 0x00U,
    IOI2C_DEV_ACK,
}ioi2c_ack_e;

typedef struct ioi2c_master_device_s{
    ioi2c_ack_e                     ack;    // ioi2c_ack_e
    ioi2c_drv_t*                    drv;
    ioi2c_dev_master_receive_t      masterReceive;
    ioi2c_dev_master_transmit_t     masterTransmit;
    ioi2c_dev_mem_receive_t         memReceive;
    ioi2c_dev_mem_transmit_t        memTransmit;
}ioi2c_dev_t;



void        ioi2cDelay_us   (uint32_t timeout);
void        ioi2cDelay_ms   (uint32_t timeout);

void        ioi2cStart      (ioi2c_dev_t* dev);
void        ioi2cStop       (ioi2c_dev_t* dev);
ioi2c_ret_e ioi2cSendByte   (ioi2c_dev_t* dev, uint8_t* byte);
uint8_t     ioi2cReadByte   (ioi2c_dev_t* dev, uint8_t ack);



#endif /* __IOI2C_H */
