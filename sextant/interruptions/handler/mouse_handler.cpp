/*
 * mouse_handler.cpp
 *
 *  Created on: 16 nov. 2008
 *      Author: Marc Noblet
 */

#include <hal/fonctionsES.h>
#include <sextant/interruptions/irq.h>
#include "mouse_handler.h"
#include <drivers/EcranV.h>

unsigned char mouse_cycle=0;    //unsigned char
signed char mouse_byte[3];    	//signed char
signed char mouse_x=0;        	//signed char
signed char mouse_y=0;        	//signed char
signed char mouse_clic=0;		//signed char

#include <drivers/EcranP.h>
extern EcranP *ecranP;


//extern Ecran ecran;

//Mouse functions
void mouse_handler(int irq) //struct regs *a_r (not used but just there)
{

	switch(mouse_cycle)
	  {
	    case 0:	mouse_byte[0]=lireOctet(0x60);
				mouse_cycle++ ;					break;
	    case 1:	mouse_byte[1]=lireOctet(0x60);
				mouse_cycle++;					break;
	    case 2:	mouse_byte[2]=lireOctet(0x60);
				mouse_cycle=0;

				mouse_clic=mouse_byte[1];
				mouse_x=mouse_byte[2];
				mouse_y=mouse_byte[0];			break;
	  }

//	ecranP->setEcran(0);

}

inline void mouse_wait(unsigned char a_type) //unsigned char
{
  int _time_out=100000; //unsigned int
  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((lireOctet(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((lireOctet(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

inline void mouse_write(unsigned char a_write) //unsigned char
{
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  ecrireOctet(0xD4, 0x64);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  ecrireOctet( a_write,0x60);
}

unsigned char mouse_read()
{
  //Get's response from mouse
  mouse_wait(0);

  return lireOctet(0x60);
}

void mouse_install()
{
    unsigned char _status;  //unsigned char

  //Enable the auxiliary mouse device
  mouse_wait(1);
  ecrireOctet(0x64, 0xA8);

  //Enable the interrupts
  mouse_wait(1);
  ecrireOctet( 0x20,0x64);
  mouse_wait(0);
  _status=(lireOctet(0x60) | 2);
  mouse_wait(1);
  ecrireOctet( 0x60,0x64);
  mouse_wait(1);
  ecrireOctet( _status,0x60);

  //Tell the mouse to use default settings
  mouse_write(0xF6);
  mouse_read();  //Acknowledge

  // 0xF3 (Set Sample Rate)
  mouse_write(0xF3);
  mouse_read();  //Acknowledge
  // 10 samples/sec
  mouse_write(10);
  mouse_read();  //Acknowledge

  //Enable the mouse
  mouse_write(0xF4);
  mouse_read();  //Acknowledge

  //Setup the mouse handler
  irq_set_routine(12, mouse_handler);

}
