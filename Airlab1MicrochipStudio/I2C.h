
#ifndef __I2C_H__
#define __I2C_H__

extern unsigned char I2CBufferOutPtrTop;
extern unsigned char I2CBufferInPtrTop;
extern unsigned char I2CBufferInPtrBottom;
extern unsigned char I2CBufferOutPtrBottom;
extern unsigned char I2CSendReady;
extern unsigned char I2CError;
extern unsigned char I2CMasterReciever;

//void SetupSIO1(void);

#define RTC_ADDR 0xE0
#define RTC_WRITE 0x00
#define RTC_READ 0x01

void init_twi(void);


void ReadData(unsigned char I2CAddress, unsigned int StartAddress, unsigned char *Buffer, unsigned char NrOfBytes);

void WriteData(unsigned char I2CAddress, unsigned int StartAddress, unsigned char *Buffer, unsigned char NrOfBytes);

void SetAddress(unsigned char I2CAddress, unsigned int StartAddress);



#endif


