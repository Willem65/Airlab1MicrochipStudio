/*
 * TWI.h
 *
 *  Copyright (C) Daniel Kampert, 2020
 *	Website: www.kampis-elektroecke.de
 *  File info: Driver for XMega TWI.

  GNU GENERAL PUBLIC LICENSE:
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.

  Errors and commissions should be reported to DanielKampert@kampis-elektroecke.de.
 */

 #include <avr/io.h>
 #include <avr/interrupt.h>

#ifndef TWI_H_
#define TWI_H_

#define RTC_ADDR 0xE0
#define RTC_WRITE 0x00
#define RTC_READ 0x01

void init_twi(void);
void twi_write(unsigned char reg_addr,unsigned char* reg_data, unsigned char NrOfBytes);
void twi_read(unsigned char StartAddress, unsigned char* Data, unsigned char NrOfBytes);


////						Aantal Bytes     // Buffer           // Teller       // vlag completed
//extern unsigned char  twi_data_buffer[50], twi_data_buffer2[500],  twi_data_count;
//
//extern unsigned char twi_no_of_bytes, W_transfer_Interrupt_complete, R_transfer_Interrupt_complete;
//
//extern uint16_t wacht;


 ////#include <avr/io.h>
 ////#include <avr/interrupt.h>
////
 ////#define TWI_BUFFER_SIZE						32
 ////#define TWI_SLAVE_ADDRESS						0x70 
////
 ////#define TWI_WRITE(Address)						(Address << 0x01)
 ////#define TWI_READ(Address)						((Address << 0x01) | 0x01)
 ////
 ////#define TWI_ACK								0x00
 ////#define TWI_NACK								0x01
 ////
 ////typedef enum
 ////{
	 ////TWI_MASTER_REGISTER = 0x00,
	 ////TWI_MASTER_ADDRESS = 0x01,
	 ////TWI_MASTER_WRITE = 0x02,
	 ////TWI_MASTER_READ = 0x03,
	 ////TWI_MASTER_SEND = 0x04,
	 ////TWI_MASTER_RECEIVED = 0x05,
	 ////TWI_MASTER_BUFFEROVERFLOW = 0x06,
	 ////TWI_MASTER_ERROR = 0xFF,
 ////} TWI_MasterStatus_t;
////
 ////typedef enum
 ////{
	 ////TWI_SLAVE_IDLE = 0x00,
	 ////TWI_SLAVE_BUFFEROVERFLOW = 0x01,
	 ////TWI_SLAVE_ERROR = 0xFF,
 ////} TWI_SlaveStatus_t;
////
 ////typedef struct
 ////{
	 ////TWI_t* Device;
	 ////uint8_t DeviceAddress;
	 ////uint8_t Register;
	 ////uint8_t BytesWrite;
	 ////uint8_t IndexWrite;
	 ////uint8_t BytesRead;
	 ////uint8_t IndexRead;
	 ////uint8_t* BufferWrite;
	 ////uint8_t* BufferRead;
	 ////TWI_MasterStatus_t Status;
 ////} TWI_Message_t;
////
 ////typedef struct 
 ////{
	 ////TWI_t* Device;
	 ////uint8_t* Buffer;
	 ////uint8_t BytesReceived;
	 ////uint8_t BytesSend;
	 ////uint8_t WriteIndex;
	 ////uint8_t ReadIndex;
	 ////TWI_SlaveStatus_t Status;
 ////} TWI_Buffer_t;
////
 ////void TWIM_Init(void);
 ////void TWIM_InitInterrupt(void);
  ////
  ////
 //////void TWIS_Init(uint8_t* Buffer);
////
 ////void TWIM_SendAddress(uint8_t Address);
 ////void TWIM_SendData(uint8_t Data);
 ////uint8_t TWIM_ReadData(uint8_t NACK);
 ////void TWIM_SendStop(uint8_t NACK);
 ////
 ////
 ////
////
////
////
 ////void TWIM_Transmit(uint8_t DeviceAddress, uint8_t Register, unsigned char* Data, uint8_t Bytes);
////
////
 ////void TWIM_Receive(uint8_t DeviceAddress, uint8_t Register, unsigned char* Data, uint8_t Bytes);
 ////
 ////
 ////TWI_MasterStatus_t TWIM_Status(void);
 //////TWI_SlaveStatus_t TWIS_Status(void);

#endif /* TWI_H_ */