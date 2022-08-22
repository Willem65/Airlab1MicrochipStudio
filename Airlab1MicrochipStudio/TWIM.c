/*
 * TWIM.c
 *
 */

#include "TWI.h"

//						Aantal Bytes     // Buffer           // Teller       // vlag completed
unsigned char  twi_data_buffer[50], twi_data_buffer2[500], twi_data_buffer3[500], twi_data_count, vlag=1;

unsigned char twi_no_of_bytes, W_transfer_Interrupt_complete, R_transfer_Interrupt_complete;

uint16_t wacht;


//void init_twi()
//{
	//TWIE_MASTER_BAUD=0x14; //baud rate is set such that ftwi=100KHz	
	//TWIE_CTRL=0x00; //SDA hold time off, normal TWI operation 	
	//TWIE_MASTER_CTRLA|=TWI_MASTER_INTLVL_gm|TWI_MASTER_RIEN_bm|TWI_MASTER_WIEN_bm|TWI_MASTER_ENABLE_bm; //enable high priority read and write interrupt, enable MASTER
	////TWIE_MASTER_CTRLA|=TWI_MASTER_ENABLE_bm;
	////PMIC_LOLVLEN_bm	
	//TWIE_MASTER_CTRLB=0x00; //no inactive bus timeout, no quick command and smart mode enabled	
	//TWIE_MASTER_CTRLC=0x00; //initially send ACK and no CMD selected	
	//TWIE_MASTER_STATUS|=TWI_MASTER_RIF_bm|TWI_MASTER_WIF_bm|TWI_MASTER_ARBLOST_bm|TWI_MASTER_BUSERR_bm|TWI_MASTER_BUSSTATE0_bm; //clear all flags initially and select bus state IDLE
//}

 
 // I2CAddress, StartAddress, Buffer, NrOfBytes
 void twi_write(unsigned char reg_addr,unsigned char* reg_data, unsigned char NrOfBytes)
 { 
	 //twi_data_count=0;
	 //NrOfBytes += 2;
	 //
	 	//for ( int t=0; t<485; t++ )
	 	//twi_data_buffer3[t] = *(reg_data);
	 //
	 //while( twi_data_count < NrOfBytes )
	 //{
		//if ( twi_data_count == 0 )
		//{
			//TWIE_MASTER_ADDR=RTC_ADDR|RTC_WRITE;  // Schrijf het Device adres, gebeurd altijd als eerste, ook zonder interrupt, ack wordt ook ontvangen
			//while ( W_transfer_Interrupt_complete != 1 );	// Wacht totdat de interrupt is uitgevoerd, klaar is , in deze regel blijft hij hangen, i2c wordt dan maar een keer verstuurd, tenzij
			////                                             // er een interrupt aan staat want dan komt ie hier wel weer opnieuw in terug
			//W_transfer_Interrupt_complete = 0;
			//twi_data_count++;
		//}
		//
		//if ( twi_data_count == 1 )
		//{
			//TWIE_MASTER_DATA=reg_addr;  // readres
			//while ( W_transfer_Interrupt_complete != 1 );
			//W_transfer_Interrupt_complete = 0;
			//twi_data_count++;
		//}
		//
		//if ( twi_data_count > 1 )
		//{		
			//TWIE_MASTER_DATA= (twi_data_buffer3[twi_data_count-2]) & 0x01;  
			////TWIE_MASTER_DATA= 1;                              // Hier even dit laten staan om de EEprom bewust te vullen met allemaal eenen of nullen
			//while ( W_transfer_Interrupt_complete != 1 );
			//W_transfer_Interrupt_complete = 0;
			//twi_data_count++;
		//}
	 //}
	////send stop condition if all bytes are transferred
	//TWIE_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp);	 
	//for (wacht=0; wacht<20000; wacht++);

 }
 
 
 
 void twi_read(unsigned char StartAddress, unsigned char* Data, unsigned char NrOfBytes)
 {
	
	//twi_data_count = 0;
	//NrOfBytes += 3;
	//
	//
	//while( twi_data_count < NrOfBytes )
	//{
		//if ( twi_data_count == 0 )
		//{	 
			//TWIE_MASTER_ADDR=RTC_ADDR|RTC_WRITE;  // Schrijf het Device adres, gebeurd altijd als eerste, ook zonder interrupt, ack wordt ook ontvangen	 
			//while ( W_transfer_Interrupt_complete != 1 );	// Wacht totdat de interrupt is uitgevoerd, klaar is , in deze regel blijft hij hangen, i2c wordt dan maar een keer verstuurd, tenzij 
			////                                             // er een interrupt aan staat want dan komt ie hier wel doorheen 
			//W_transfer_Interrupt_complete = 0; 		
			//twi_data_count++;
		//}
	//
		//if ( twi_data_count == 1 )
		//{
			//TWIE_MASTER_DATA=StartAddress;					// readres	 	 
			//while ( W_transfer_Interrupt_complete != 1 );
			//W_transfer_Interrupt_complete = 0;
			//twi_data_count++;
		//}
			//
		//if ( twi_data_count == 2 )
		//{
			//TWIE_MASTER_ADDR=RTC_ADDR|RTC_READ;				// Read Device
			//while ( R_transfer_Interrupt_complete != 1 );
			//R_transfer_Interrupt_complete = 0;
			//twi_data_count++;
		//}			
			//
		//if ( twi_data_count > 2 )
		//{						
			////send acknowledge
			//TWIE_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(0<<TWI_MASTER_CMD0_bp);
			//while ( R_transfer_Interrupt_complete != 1 );
			//R_transfer_Interrupt_complete = 0;
			//twi_data_buffer2[twi_data_count-3]=TWIE_MASTER_DATA;  //Hier wordt de DATA in de buffer gezet
			//twi_data_count++;
		//}			
	//}
	//
	//TWIE_MASTER_CTRLC=(1<<TWI_MASTER_ACKACT_bp)|(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp);	
	//for ( int t=0; t<485; t++ )
	//*(Data+t) = twi_data_buffer2[t];
 }


 
 
 //ISR(TWIE_TWIM_vect)
 //{
	 ////If TWI arbitration is lost send STOP
	 //if(TWIE_MASTER_STATUS & (1<<TWI_MASTER_ARBLOST_bp))
	 //{
		 //TWIE_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp); //send stop condition
	 //}
	 //
	 ////If TWI bus error flag is set or NACK received then send STOP 
	 //if((TWIE_MASTER_STATUS & (1<<TWI_MASTER_BUSERR_bp))||(TWIE_MASTER_STATUS & (1<<TWI_MASTER_RXACK_bp)))
	 //{
		 //TWIE_MASTER_CTRLC=(1<<TWI_MASTER_CMD1_bp)|(1<<TWI_MASTER_CMD0_bp); //send stop condition
	 //}
	 //
	  //
	 ////If TWI write interrupt flag is set	 
	 //if(TWIE_MASTER_STATUS & (1<<TWI_MASTER_WIF_bp))
	 //{ 
		 //if(!(TWIE_MASTER_STATUS & (1<<TWI_MASTER_RXACK_bp))) //check whether acknowledge is received or not
		 //{			 
			////TWIE_MASTER_DATA=twi_data_buffer[twi_data_count++];
			//W_transfer_Interrupt_complete = 1;
			//PORTA_OUTTGL |= 0x80;  // om als trigger puls te gebruiken voor de oscilloscoop		 
		 //} 
	 //}
	 //else
	 //{
		 	//W_transfer_Interrupt_complete = 0;
	 //}
	 //
//
	 ////If read interrupt flag is set 
	 //if(TWIE_MASTER_STATUS & (1<<TWI_MASTER_RIF_bp)) //Check whether read interrupt flag is set or not
	 //{	 
		 //////twi_data_buffer2[twi_data_count++]=TWIE_MASTER_DATA;  //Hier wordt de DATA in de buffer gezet
		//R_transfer_Interrupt_complete = 1;
		//PORTA_OUTTGL |= 0x80;  // om als trigger puls te gebruiken voor de oscilloscoop
	 //}
	 //else
	 //{
		//R_transfer_Interrupt_complete = 0;
	 //}
 //}

