This is a project to use gpio to simulate iic to read rocker channel values with resolution 0~8191.

The two channels of each joystick share an iic bus, X channel device address 5C, Y channel device address 7C.

Each channel needs to request 3 bytes of data each time, if you use uint8_t buf[3] to save in read order, then buf[0]=channel high 8bits, buf[1]=channel low 8bits, buf[2]=checksum. When ((buf[0]&0x7F)+buf[1]+buf[2])&0xFF = 0, this data is valid.

![This is an IIC waveform reading the 0x5C address](relative/path/to/IIC gimbal wave.png)
