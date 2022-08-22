//#include "reg552.h"
//#include "definitions.h"
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include "TWI.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Delay.h"
#include "LCD.h"
#include "I2C.h"
//#include "serial.h"
#include "airlabbrm-willem.h"


unsigned char twi_data_buffer3[500];

//unsigned char CardInserted;

unsigned char I2CBufferIn[256];



unsigned char I2CStatus;
unsigned char CurrentAddress;



unsigned char I2CBuffer[256];
unsigned char I2CLength;
unsigned char I2CDataLength;
unsigned char I2CRepeat;
unsigned char I2CRepeatAddress;
unsigned char I2CByteNr;
unsigned char I2CFromAddress;
unsigned char I2CItem;
unsigned char I2CModule;

unsigned char I2CMasterReciever;
unsigned char I2CBufferOutPtrTop;
unsigned char I2CBufferInPtrTop;
unsigned char I2CBufferInPtrBottom;
unsigned char I2CBufferOutPtrBottom;
unsigned char I2CSendReady;
unsigned char I2CError;

unsigned char I2CAddressBufferOut[256];
unsigned char I2CDataBufferOut[256];

//						Aantal Bytes     // Buffer           // Teller       // vlag completed
unsigned char  twi_data_buffer[50], twi_data_buffer3[500], vlag=1;

volatile unsigned char twi_no_of_bytes, W_transfer_Interrupt_complete, R_transfer_Interrupt_complete;

uint8_t twi_data_buffer2[50];

uint16_t wacht;

WriteToEEprom(unsigned int StartAddress, unsigned char *Buffer, unsigned char NrOfBytes);

//#ifndef __I2C_H__
//#define __I2C_H__
//	I2CBufferInPtrTop = 0;
//	I2CBufferInPtrBottom = 0;
//	I2CBufferOutPtrTop = 0;
//	I2CBufferOutPtrBottom = 0;
//	I2CSendReady=1;
//	I2CMasterReciever = 0;
//	I2CError = 0;
//	CardInserted = 0;
//#endif

//void SetAddress(unsigned char I2CAddress, unsigned int StartAddress);
//void SetupSIO1();

/***************************************************************
* Setup_I2C                                                    *
***************************************************************/
//void SetupSIO1()
//{
	//
	////I2CBufferInPtrTop = 0;
	////I2CBufferInPtrBottom = 0;
	////I2CBufferOutPtrTop = 0;
	////I2CBufferOutPtrBottom = 0;
	////I2CSendReady=1;
	////I2CMasterReciever = 0;
	////I2CError = 0;
	////CardInserted = 0;
	////
	////
	////S1ADR = 0xFF;
////
	////P16 = 1;		// set I2Cports 
	////P17 = 1;
////
	////SI = 0;		// reset Serial Interrupt Flag   
	////AA = 0;		// disable masterinterrupt       
////
	////CR2 = 1;               // set bit-rate for I2C to 200kH 
	////CR1 = 1;
	////CR0 = 0;
////
	////ENS1 = 1;		// enable SIO1                   
////
	////STA = 0;		// no START, no STOP             
	////STO = 0;
////
	////ES1 = 1;
	////PS1 = 1;
//}


void init_twi()
{
	TWIE_MASTER_BAUD=0x14; //baud rate is set such that ftwi=100KHz
	TWIE_CTRL=0x00; //SDA hold time off, normal TWI operation
	TWIE_MASTER_CTRLA|=TWI_MASTER_INTLVL_gm|TWI_MASTER_RIEN_bm|TWI_MASTER_WIEN_bm|TWI_MASTER_ENABLE_bm; //enable high priority read and write interrupt, enable MASTER
	//TWIE_MASTER_CTRLA|=TWI_MASTER_ENABLE_bm;
	//PMIC_LOLVLEN_bm
	TWIE_MASTER_CTRLB=0x00; //no inactive bus timeout, no quick command and smart mode enabled
	TWIE_MASTER_CTRLC=0x00; //initially send ACK and no CMD selected
	TWIE_MASTER_STATUS|=TWI_MASTER_RIF_bm|TWI_MASTER_WIF_bm|TWI_MASTER_ARBLOST_bm|TWI_MASTER_BUSERR_bm|TWI_MASTER_BUSSTATE0_bm; //clear all flags initially and select bus state IDLE
}


void SetAddress(unsigned char I2CAddress, unsigned int StartAddress)
{
	

	
	//unsigned char Address = I2CAddress | ((StartAddress>>7)&0x0E);
	//
	//
		//
	////	I2CBufferInPtrTop = 0;
	////I2CBufferInPtrBottom = 0;
	//I2CBufferOutPtrTop = 0;
	//I2CBufferOutPtrBottom = 0;
	//I2CSendReady=1;
	////I2CMasterReciever = 0;
	//I2CError = 0;
	//CardInserted = 0;
//
	//I2CAddressBufferOut[I2CBufferOutPtrTop] = Address;
	//I2CDataBufferOut[I2CBufferOutPtrTop++] = StartAddress&0xFF;
	//EA = 0;
  //if ((I2CBufferOutPtrTop != I2CBufferOutPtrBottom) && I2CSendReady)
	//{
		//I2CSendReady=0;
		//EA = 1;
		//STA = 1;
	//}
	//EA = 1;
	//while (!I2CSendReady);
	//Delay(1);
//
	//if (I2CError)
	//{
		//SetLCD(0,"\xC0");
		//if (I2CAddress==I2CAddressSmartCard)
		//{
			//CardInserted = 0;
			////SerialBufferOut[SerialBufferOutPtrTop++] = CARD_INSERTED;
			////SerialBufferOut[SerialBufferOutPtrTop++] = 0x00;
			////SerialBufferOut[SerialBufferOutPtrTop++] = 0x00;
		//}
		//else
			//SetLCD(1,"No EEPROM comm. ");
//
		//I2CError = 0;
	//}
	
	
}




/***************************************************************
* READ_DATA_I2C                                                    *
***************************************************************/
void ReadData(unsigned char I2CAddress, unsigned int StartAddress, unsigned char *Buffer, unsigned char NrOfBytes)
{
	////unsigned char cnt;
	////unsigned char Address = I2CAddress | ((StartAddress>>7)&0x0E) |0x01;
	////
	////
		////
		////I2CBufferInPtrTop = 0;
	////I2CBufferInPtrBottom = 0;
	////I2CBufferOutPtrTop = 0;
	//////I2CBufferOutPtrBottom = 0;
	////I2CSendReady=1;
	////I2CMasterReciever = 0;
	//////I2CError = 0;
	//////CardInserted = 0;
////
	////SetAddress(I2CAddress, StartAddress);
////
	////I2CMasterReciever = 1;
	////I2CDataLength = NrOfBytes;
	////I2CAddressBufferOut[I2CBufferOutPtrTop++] = Address;
	
	//EA = 0;
//
  //if (I2CSendReady)
	//{
		//I2CSendReady=0;
		//EA = 1;
		//STA = 1;  // ????
	//}
	//EA = 1;
	
	
	
	//NrOfBytes=29;

	uint8_t twi_data_count = 0;
	NrOfBytes += 4;
	unsigned char startDevice;
	
	
	while( twi_data_count < NrOfBytes )
	{
		if ( twi_data_count == 0 )
		{		
			startDevice=(StartAddress>>7)&0x0E;
			
			for (wacht=0; wacht<140; wacht++); 
			TWIE_MASTER_ADDR=RTC_ADDR|startDevice|RTC_WRITE;  // Schrijf het Device adres, gebeurd altijd als eerste, ook zonder interrupt, ack wordt ook ontvangen	 
			while ( W_transfer_Interrupt_complete != 1 );	// Wacht totdat de interrupt is uitgevoerd, klaar is , in deze regel blijft hij hangen, i2c wordt dan maar een keer verstuurd, tenzij 
			//                                             // er een interrupt aan staat want dan komt ie hier wel doorheen 
			W_transfer_Interrupt_complete = 0; 		
			twi_data_count++;
		}
	
		if ( twi_data_count == 1 )
		{
			TWIE_MASTER_DATA=StartAddress;					// readres	 	 
			while ( W_transfer_Interrupt_complete != 1 );
			W_transfer_Interrupt_complete = 0;
			twi_data_count++;
			//TWIE_MASTER_CTRLC=(1<<TWI_MASTER_ACKACT_bp)|(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp);  // Stop ik weet niet of da hier nodig is
			for (wacht=0; wacht<140; wacht++);	
		}
			
		if ( twi_data_count == 2 )
		{
			TWIE_MASTER_ADDR=RTC_ADDR|startDevice|RTC_READ;				// Read Device
			while ( R_transfer_Interrupt_complete != 1 );
			R_transfer_Interrupt_complete = 0;
			twi_data_buffer2[twi_data_count-2]=twi_data_count;  //TWIE_MASTER_DATA;  //Hier wordt de DATA in de buffer gezet
			twi_data_count++;
			//send acknowledge
			TWIE_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(0<<TWI_MASTER_CMD0_bp);
			while ( R_transfer_Interrupt_complete != 1 );
			R_transfer_Interrupt_complete = 0;			
			
		}			
			
		if ( twi_data_count > 2 )
		{						
			//send acknowledge
			TWIE_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(0<<TWI_MASTER_CMD0_bp);
			while ( R_transfer_Interrupt_complete != 1 );
			R_transfer_Interrupt_complete = 0;
			twi_data_buffer2[twi_data_count-2]=twi_data_count;  //TWIE_MASTER_DATA;  //Hier wordt de DATA in de buffer gezet
			twi_data_count++;
		}			
	}
	
	
	
	TWIE_MASTER_CTRLC=(1<<TWI_MASTER_ACKACT_bp)|(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp);   // Stop
	for (wacht=0; wacht<900; wacht++);
	
	int t;
		
	for ( t=0; t<29; t++ )
	{
		*(Buffer+t) = twi_data_buffer2[t];
		//if( t==484)
		//{
//
			//int s;
			//s=s+1;
			//for(int r=0; r<2; r++)
			//{
				//char ln='w';
			//}
		//}
		
	}
	
	
	
	
	

	//////while(!I2CSendReady);
	////I2CMasterReciever = 0;
////
	////cnt = 0;
	////while ((I2CBufferInPtrTop != I2CBufferInPtrBottom))
	////{
		////unsigned char Dummy = I2CBufferIn[I2CBufferInPtrBottom++];
		////if (cnt<NrOfBytes)
			////Buffer[cnt++] = Dummy;
	////}
}

/***************************************************************
* READ_DATA_I2C                                                    *
***************************************************************/
/*
ReadData(unsigned char I2CAddress, unsigned int StartAddress, unsigned char *Buffer, unsigned char NrOfBytes)
{

//	TWIM_Receive(I2CAddress, StartAddress, Buffer, NrOfBytes);
	//while(!((TWIM_Status() == TWI_MASTER_RECEIVED) || (TWIM_Status() == TWI_MASTER_ERROR)));
	
	twi_read(StartAddress, Buffer, NrOfBytes);







	
	
	//if ( NrOfBytes > 16)
	//{
		////NrOfBytes -= 13;
		//TWIM_Receive(I2CAddress, StartAddress, Buffer, NrOfBytes-13);
		//while(!((TWIM_Status() == TWI_MASTER_RECEIVED) || (TWIM_Status() == TWI_MASTER_ERROR)));
					//
		//StartAddress += 16;
		////Buffer += 16;
		////NrOfBytes -= 16;
//
		//TWIM_Receive(I2CAddress, StartAddress, Buffer+16, NrOfBytes-16);
		//while(!((TWIM_Status() == TWI_MASTER_RECEIVED) || (TWIM_Status() == TWI_MASTER_ERROR)));
		//StartAddress += 13;
		//
	//}
	//else
	//{
		//TWIM_Receive(I2CAddress, StartAddress, Buffer, NrOfBytes);
		//while(!((TWIM_Status() == TWI_MASTER_RECEIVED) || (TWIM_Status() == TWI_MASTER_ERROR)));
	//}	
	
	
	
	
	
	
	
	////	
	////unsigned char cnt;
	////unsigned char Address = I2CAddress | ((StartAddress>>7)&0x0E) |0x01;
////
	////SetAddress(I2CAddress, StartAddress);
////
	////I2CMasterReciever = 1;
	////I2CDataLength = NrOfBytes;
	////I2CAddressBufferOut[I2CBufferOutPtrTop++] = Address;
	////EA = 0;
////
	////if (I2CSendReady)
	////{
		////I2CSendReady=0;
		////EA = 1;
		////STA = 1;  //????
	////}
	////EA = 1;
////
	////while(!I2CSendReady);
	////I2CMasterReciever = 0;
////
	////cnt = 0;
	////while ((I2CBufferInPtrTop != I2CBufferInPtrBottom))
	////{
		////unsigned char Dummy = I2CBufferIn[I2CBufferInPtrBottom++];
		////if (cnt<NrOfBytes)
		////Buffer[cnt++] = Dummy;
	////}
	////
	
}

*/

/***************************************************************
* WRITE_DATA_I2C                                                    *
***************************************************************/
void WriteData(unsigned char I2CAddress, unsigned int StartAddress, unsigned char* Buffer, unsigned char NrOfBytes)
{
	//unsigned char cntByte = 0;
	////unsigned char Address = I2CAddress | ((StartAddress>>7)&0x0E);
//
	//while (cntByte<NrOfBytes)
	//{
//
		//
		//
		////I2CAddressBufferOut[I2CBufferOutPtrTop] = Address;
		//
		//I2CDataBufferOut[I2CBufferOutPtrTop++] = StartAddress&0xFF;		
		////WriteToEEprom( StartAddress, I2CDataBufferOut[I2CBufferOutPtrTop++], 0);
		//
		////I2CAddressBufferOut[I2CBufferOutPtrTop] = Address;
		//
		//I2CDataBufferOut[I2CBufferOutPtrTop++] = Buffer[cntByte];
		////WriteToEEprom( StartAddress, I2CDataBufferOut[I2CBufferOutPtrTop++], 0);	
			//
		////WriteToEEprom( StartAddress, *I2CDataBufferOut, 16);
		//
		//StartAddress++;
		//cntByte++;
////                          16                         15
		//while ((cntByte<NrOfBytes) && (StartAddress&0x000F))
		//{
			////I2CAddressBufferOut[I2CBufferOutPtrTop] = Address;
			//
			//I2CDataBufferOut[I2CBufferOutPtrTop++] = Buffer[cntByte];
			//WriteToEEprom( StartAddress, I2CDataBufferOut[I2CBufferOutPtrTop++], 0);			
			//
			//
			//StartAddress++;
			//cntByte++;
		//}
	//
	//}
	unsigned char buff[32];
	

	
	
	if ( NrOfBytes > 16)
	{
		
		for ( int t=2; t<18; t++)
		buff[t]=6; //Buffer[t-2];
		
		//NrOfBytes -= 13;
//									16            0       29-13=16
		//WriteToEEprom( StartAddress, *I2CDataBufferOut, NrOfBytes-13);
		//WriteToEEprom( StartAddress, 1, NrOfBytes);
		WriteToEEprom( StartAddress, buff, NrOfBytes-13);

	
		StartAddress += 16;
		//buff += 16;
		//NrOfBytes -= 16;
		
		for ( int t=15; t<28; t++)
		buff[t-13]=7; //Buffer[t+1];
		
	//
////		                           16+16=32      0+16=16    29-16=13
		////WriteToEEprom( StartAddress, *I2CDataBufferOut+16, NrOfBytes-16);
		////WriteToEEprom( StartAddress, 1, NrOfBytes);
		WriteToEEprom( StartAddress, buff, NrOfBytes-16);
//
		//StartAddress += 13;
	}
	else
	{		
		//for ( int t=2; t<18; t++)
		for ( int t=2; t<28; t++)
		buff[t]=5; //Buffer[t-2];
			
		WriteToEEprom( StartAddress, buff, NrOfBytes);
	}
		
		
				////////////if ( NrOfBytes > 16)
				////////////{
				//////////////NrOfBytes -= 13;
				//////////////							16            0       29-13=16
				////////////twi_write( StartAddress, Buffer, NrOfBytes-13);
				//////////////while(!((TWIM_Status() == TWI_MASTER_SEND) || (TWIM_Status() == TWI_MASTER_ERROR)));
				////////////
				////////////StartAddress += 16;
				//////////////Buffer += 16;
				//////////////NrOfBytes -= 16;
				////////////
				//////////////                           16+16=32      0+16=16    29-16=13
				////////////twi_write( StartAddress, Buffer+16, NrOfBytes-16);
				//////////////while(!((TWIM_Status() == TWI_MASTER_SEND) || (TWIM_Status() == TWI_MASTER_ERROR)));
				////////////StartAddress += 13;
				////////////}
				////////////else
				////////////{
				////////////twi_write( StartAddress, Buffer, NrOfBytes);
				//////////////while(!((TWIM_Status() == TWI_MASTER_SEND) || (TWIM_Status() == TWI_MASTER_ERROR)));
				////////////}		
		
		
		
}

/***************************************************************
* WRITE_WriteToEEprom                                                *
***************************************************************/
WriteToEEprom(unsigned int StartAddress, unsigned char *Buffer, unsigned char NrOfBytes)
{
	uint8_t twi_data_count=0;
	NrOfBytes += 2;
	unsigned char startDevice;
		 
	while( twi_data_count < NrOfBytes )
	{
		if ( twi_data_count == 0 )
		{
			startDevice=(StartAddress>>7)&0x0E;
			
			TWIE_MASTER_ADDR=RTC_ADDR|startDevice|RTC_WRITE;			
			//TWIE_MASTER_ADDR=RTC_ADDR|RTC_WRITE;  // Schrijf het Device adres, gebeurd altijd als eerste, ook zonder interrupt, ack wordt ook ontvangen
			while ( W_transfer_Interrupt_complete != 1 );	// Wacht totdat de interrupt is uitgevoerd, klaar is , in deze regel blijft hij hangen, i2c wordt dan maar een keer verstuurd, tenzij
			//                                             // er een interrupt aan staat want dan komt ie hier wel weer opnieuw in terug
			W_transfer_Interrupt_complete = 0;
			twi_data_count++;
		}
			 
		if ( twi_data_count == 1 )
		{
			TWIE_MASTER_DATA=StartAddress;  // readres
			while ( W_transfer_Interrupt_complete != 1 );
			W_transfer_Interrupt_complete = 0;
			twi_data_count++;
		}
			 
		if ( twi_data_count > 1 )
		{
			//TWIE_MASTER_DATA = (twi_data_buffer3[twi_data_count]) & 0x01;
			TWIE_MASTER_DATA = Buffer[twi_data_count];
			//TWIE_MASTER_DATA= 2;
			//TWIE_MASTER_DATA= twi_data_count;                              // Hier even dit laten staan om de EEprom bewust te vullen met allemaal eenen of nullen
			while ( W_transfer_Interrupt_complete != 1 );
			W_transfer_Interrupt_complete = 0;
			twi_data_count++;
		}
	}
	//send stop condition if all bytes are transferred
	TWIE_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp);
	for (wacht=0; wacht<8000; wacht++);		
}

/***************************************************************
* WRITE_DATA_I2C                                                    *
***************************************************************/
/*

void WriteData(unsigned char I2CAddress, unsigned int StartAddress, unsigned char* Buffer, unsigned char NrOfBytes)
{
		
		 twi_data_count=0;
		 NrOfBytes += 2;
		 
		 unsigned int t, j;
		 
		 for ( t=0; t<16; t++ )
		 {
			twi_data_buffer3[t] = Buffer[t];
			
				for ( j=0; j<29; j++ )
				{
					 twi_data_buffer3[j] = Buffer[j];   // &(Buffer[0]);   // (Buffer+t);
				}
		 }
		 
		 while( twi_data_count < NrOfBytes )
		 {
			 if ( twi_data_count == 0 )
			 {
				 TWIE_MASTER_ADDR=RTC_ADDR|RTC_WRITE;  // Schrijf het Device adres, gebeurd altijd als eerste, ook zonder interrupt, ack wordt ook ontvangen
				 while ( W_transfer_Interrupt_complete != 1 );	// Wacht totdat de interrupt is uitgevoerd, klaar is , in deze regel blijft hij hangen, i2c wordt dan maar een keer verstuurd, tenzij
				 //                                             // er een interrupt aan staat want dan komt ie hier wel weer opnieuw in terug
				 W_transfer_Interrupt_complete = 0;
				 twi_data_count++;
			 }
			 
			 if ( twi_data_count == 1 )
			 {
				 TWIE_MASTER_DATA=StartAddress;  // readres
				 while ( W_transfer_Interrupt_complete != 1 );
				 W_transfer_Interrupt_complete = 0;
				 twi_data_count++;
			 }
			 
			 if ( twi_data_count > 1 )
			 {
				 TWIE_MASTER_DATA= (twi_data_buffer3[twi_data_count]) & 0x01;
				 //TWIE_MASTER_DATA= 1;                              // Hier even dit laten staan om de EEprom bewust te vullen met allemaal eenen of nullen
				 while ( W_transfer_Interrupt_complete != 1 );
				 W_transfer_Interrupt_complete = 0;
				 twi_data_count++;
			 }
		 }
		 //send stop condition if all bytes are transferred
		 TWIE_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp);
		 for (wacht=0; wacht<20000; wacht++);
	

    */








	
	
	//TWIM_Transmit(I2CAddress, StartAddress, Buffer, NrOfBytes);
	//while(!((TWIM_Status() == TWI_MASTER_SEND) || (TWIM_Status() == TWI_MASTER_ERROR)));
	
	
	//
	//uint8_t buff[500];
	//
	//for ( int t=0; t<500; t++)
	//{
		//buff[t]=&(Buffer[t]);
	//}
	


			//for (int p=0; p<16; p++)
			//{
				//EEread[p]=0x1;
			//}
			//
			//
			//TWIM_Transmit(I2CAddressEEProm, StartAddress, EEread, 16);
			//while(!((TWIM_Status() == TWI_MASTER_SEND) || (TWIM_Status() == TWI_MASTER_ERROR)));
			//
			//
			//for (int p=0; p<13; p++)
			//{
				//EEread[p]=0x1;
			//}
			//
			//StartAddress += 16;
			//TWIM_Transmit(I2CAddressEEProm, StartAddress, EEread, 13);
			//while(!((TWIM_Status() == TWI_MASTER_SEND) || (TWIM_Status() == TWI_MASTER_ERROR)));			
			//StartAddress += 13;

				////////////if ( NrOfBytes > 16)
				////////////{
					//////////////NrOfBytes -= 13;
					//////////////							16            0       29-13=16
					////////////twi_write( StartAddress, Buffer, NrOfBytes-13);
					//////////////while(!((TWIM_Status() == TWI_MASTER_SEND) || (TWIM_Status() == TWI_MASTER_ERROR)));
					////////////
					////////////StartAddress += 16;
					//////////////Buffer += 16;
					//////////////NrOfBytes -= 16;
					////////////
				    //////////////                           16+16=32      0+16=16    29-16=13 
					////////////twi_write( StartAddress, Buffer+16, NrOfBytes-16);
					//////////////while(!((TWIM_Status() == TWI_MASTER_SEND) || (TWIM_Status() == TWI_MASTER_ERROR)));
					////////////StartAddress += 13;
				////////////}
				////////////else
				////////////{
					////////////twi_write( StartAddress, Buffer, NrOfBytes);
					//////////////while(!((TWIM_Status() == TWI_MASTER_SEND) || (TWIM_Status() == TWI_MASTER_ERROR)));
				////////////}

//}



///************************************************************************
//       Interrupt on recieving I2C                                                                                                                      *
//************************************************************************/
//void Int_I2C(void) //interrupt 5 using 3 
//{
//}

/************************************************************************
*       Interrupt on recieving I2C                                                                                                                      *
************************************************************************/
 ISR(TWIE_TWIM_vect)
 {
	 //If TWI arbitration is lost send STOP
	 if(TWIE_MASTER_STATUS & (1<<TWI_MASTER_ARBLOST_bp))
	 {
		 TWIE_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp); //send stop condition
	 }
	 
	 //If TWI bus error flag is set or NACK received then send STOP
	 if((TWIE_MASTER_STATUS & (1<<TWI_MASTER_BUSERR_bp))||(TWIE_MASTER_STATUS & (1<<TWI_MASTER_RXACK_bp)))
	 {
		 TWIE_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp); //send stop condition
	 }
	 
	 
	 //If TWI write interrupt flag is set
	 if(TWIE_MASTER_STATUS & (1<<TWI_MASTER_WIF_bp))
	 {
		 if(!(TWIE_MASTER_STATUS & (1<<TWI_MASTER_RXACK_bp))) //check whether acknowledge is received or not
		 {
			 //TWIE_MASTER_DATA=twi_data_buffer[twi_data_count++];
			 W_transfer_Interrupt_complete = 1;
			 PORTA_OUTTGL |= 0x80;  // om als trigger puls te gebruiken voor de oscilloscoop
		 }
	 }
	 else
	 {
		 W_transfer_Interrupt_complete = 0;
	 }
	 

	 //If read interrupt flag is set
	 if(TWIE_MASTER_STATUS & (1<<TWI_MASTER_RIF_bp)) //Check whether read interrupt flag is set or not
	 {
		 ////twi_data_buffer2[twi_data_count++]=TWIE_MASTER_DATA;  //Hier wordt de DATA in de buffer gezet
		 R_transfer_Interrupt_complete = 1;
		 PORTA_OUTTGL |= 0x80;  // om als trigger puls te gebruiken voor de oscilloscoop
	 }
	 else
	 {
		 R_transfer_Interrupt_complete = 0;
	 }
 }