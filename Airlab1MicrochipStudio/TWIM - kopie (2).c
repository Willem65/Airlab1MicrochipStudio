/*
 * TWIM.c
 *
 *  Copyright (C) Daniel Kampert, 2020
 *	Website: www.kampis-elektroecke.de
 *  File info: Driver for XMega master mode TWI.
 */

#include "TWI.h"


void TWIM_InitInterrupt(void)
{
	TWIE.MASTER.CTRLB = 0x00;
	TWIE.MASTER.BAUD = 0x14;
	TWIE.MASTER.CTRLA = TWI_MASTER_INTLVL_LO_gc | TWI_MASTER_RIEN_bm | TWI_MASTER_WIEN_bm | TWI_MASTER_ENABLE_bm;
	//TWIE.MASTER.CTRLA = TWI_MASTER_ENABLE_bm;
	TWIE.MASTER.CTRLB = 0x00;

	// Set the state machine into idle state
	TWIE.MASTER.STATUS |= TWI_MASTER_BUSSTATE_IDLE_gc;
}

/*
 typedef struct
 {
	 TWI_t* Device;
	 uint8_t DeviceAddress;
	 uint8_t Register;
	 uint8_t BytesWrite;
	 uint8_t IndexWrite;
	 uint8_t BytesRead;
	 uint8_t IndexRead;
	 uint8_t* BufferWrite;
	 uint8_t* BufferRead;
	 TWI_MasterStatus_t Status;
 } TWI_Message_t;
*/
 //        ^     
 //        |
 //        |
static TWI_Message_t Message;
volatile uint16_t wacht;



static void TWIM_ErrorHandler(void)
{
	Message.Status = TWI_MASTER_ERROR;
	Message.Device->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
}

static void TWIM_ArbitrationLostHandler(void)
{
	TWIM_ErrorHandler();
}

void TWIM_Receive(uint8_t DeviceAddress, uint8_t Register, unsigned char* Data, uint8_t Bytes)
{
	Message.BufferWrite = 0x00;
	Message.BytesWrite = 0x00;

	Message.IndexRead = 0x00;
	Message.BufferRead = Data;
	Message.BytesRead = Bytes;
	Message.Device = &TWIE;
	Message.DeviceAddress = DeviceAddress;
	
	///* TWIM_Receive single byte */
	Message.Register = Register;
	Message.Status = TWI_MASTER_REGISTER;
	///* Start the transmission by writing the address */
	Message.Device->MASTER.ADDR = TWI_WRITE(Message.DeviceAddress);
	
	///* TWIM_ReceiveBytes sequential*/
	//Message.Register = 0x00;
	//Message.Status = TWI_MASTER_READ;
	///* Start the transmission by READ the address */
	//Message.Device->MASTER.ADDR = TWI_READ(Message.DeviceAddress);
	////(&TWIE)->MASTER.ADDR = TWI_READ(Message.DeviceAddress);   // willem, adres waar het device zich bevind  // ( Begin van I2C Start + 0x70 + ACK )

}

void TWIM_Transmit(uint8_t DeviceAddress, uint8_t Register, unsigned char* Data, uint8_t Bytes)
{
	
	
	Message.BufferRead = 0x00;
	Message.BytesRead = 0x00;

	Message.IndexWrite = 0x00;
	Message.BufferWrite = Data;
	Message.BytesWrite = Bytes;
	Message.Device = &TWIE;
	Message.DeviceAddress = DeviceAddress;
	
	/* Single Byte */
	Message.Register = Register;
	Message.Status = TWI_MASTER_REGISTER;
	
	///* Byte sequetial */
	//Message.Register = 0x00;
	//Message.Status = TWI_MASTER_WRITE;
	

	// Start the transmission by writing the address
	Message.Device->MASTER.ADDR = TWI_WRITE(Message.DeviceAddress);

	for (wacht=0; wacht<8000; wacht++);
}

static void TWIM_WriteHandler(void)
{
	// Abort transmission if slave has send an NACK
	if(Message.Device->MASTER.STATUS & TWI_MASTER_RXACK_bm)
	{
		for (wacht=0; wacht<20; wacht++);
		// Slave send NACK instead of ACK - abort transmission
		TWIM_ErrorHandler();
	}
	else
	{
		for (wacht=0; wacht<20; wacht++);
		if(Message.Status == TWI_MASTER_REGISTER)
		{
			for (wacht=0; wacht<20; wacht++);
			Message.Device->MASTER.DATA = Message.Register;

			if(Message.BytesRead > 0x00)
			{
				for (wacht=0; wacht<20; wacht++);
				Message.Status = TWI_MASTER_ADDRESS;
			}
			else
			{
				for (wacht=0; wacht<20; wacht++);
				Message.Status = TWI_MASTER_WRITE;
			}
		}
		else if(Message.Status == TWI_MASTER_ADDRESS)
		{
			for (wacht=0; wacht<20; wacht++);
			Message.Device->MASTER.ADDR = TWI_READ(Message.DeviceAddress);
			Message.Status = TWI_MASTER_READ;
		}
		else if(Message.Status == TWI_MASTER_WRITE)
		{
			if ( Message.IndexWrite  < Message.BytesWrite  )
			{
				for (wacht=0; wacht<20; wacht++);
				Message.Device->MASTER.DATA = Message.BufferWrite[ Message.IndexWrite++];
				
			}
			else
			{
				for (wacht=0; wacht<20; wacht++);
				Message.Device->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
				Message.Status = TWI_MASTER_SEND;
			}
		}
	}
}


static void TWIM_ReadHandler(void)
{
	for (wacht=0; wacht<20; wacht++);
	if(Message.Status == TWI_MASTER_READ)
	{
		if ( Message.IndexRead == Message.BytesRead-1 )
		{
			Message.Device->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;
		}
		if(Message.Status == TWI_MASTER_READ)
		{
			// Check for buffer overflow
			if(Message.IndexRead < TWI_BUFFER_SIZE)
			{
				Message.BufferRead[Message.IndexRead++] = Message.Device->MASTER.DATA;
			}
			else
			{
				Message.Device->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;
				Message.Status = TWI_MASTER_BUFFEROVERFLOW;
			}
		
			if(Message.IndexRead < Message.BytesRead)
			{
				Message.Device->MASTER.CTRLC = TWI_MASTER_CMD_RECVTRANS_gc;
			}
			else
			{
				Message.Device->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;
				Message.Status = TWI_MASTER_RECEIVED;
			}
		}
		else
		{
			TWIM_ErrorHandler();
		}
	}
}

TWI_MasterStatus_t TWIM_Status(void)
{
	return Message.Status;
}

ISR(TWIE_TWIM_vect)
{
	uint8_t Status = Message.Device->MASTER.STATUS;

	/*
		Arbitration lost
	*/
	if(Status & TWI_MASTER_ARBLOST_bm)
	{
		TWIM_ArbitrationLostHandler();
	}
	/*
		Write interrupt
	*/
	else if(Status & TWI_MASTER_WIF_bm)
	{	
		TWIM_WriteHandler();
	}
	/*
		Read interrupt
	*/
	else if(Status & TWI_MASTER_RIF_bm)
	{
		TWIM_ReadHandler();
	}
	/*
		Error
	*/
	else
	{
		TWIM_ErrorHandler();
	}
}