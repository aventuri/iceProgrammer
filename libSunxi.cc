/*
 * this is the library substituting the original raspi lib for read/write GPIOs named wirikgPi
 */
#include "libSunxi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
//#include <sys/io.h>
#include <sys/mman.h>

/* for A10 based solution with bank  portG */
#define SW_PORTC_IO_BASE  0x01c20800

// this is the ptr to the whole memory map of the PORT controller.. 
char * ptr;

void wiringSunxiSetup()
{
   unsigned int PageSize = sysconf(_SC_PAGESIZE);
   unsigned int PageMask = (~(PageSize-1));
   unsigned int addr_start = SW_PORTC_IO_BASE & PageMask;
   unsigned int addr_offset = SW_PORTC_IO_BASE & ~PageMask;

   int memmap_fd = open("/dev/mem", O_RDWR);
   if(memmap_fd < 0) {
      perror("Unable to open /dev/mem");
      exit(-1);
   }
   void * pc = mmap(0, PageSize*2, PROT_READ|PROT_WRITE, MAP_SHARED, memmap_fd, addr_start);

   if(pc == MAP_FAILED) {
      perror("Unable to mmap file");
      printf("pc:%lx\n", (unsigned long)pc);
      exit(-1);
   }

   ptr = (char *)pc + addr_offset; // ptr is the static var for accessing the whole PORT controller space

	return;
}

void sunxiMode(int pinInt, int dir)
{
	enum SUNXI_GPIO pin = (enum SUNXI_GPIO) pinInt;
	short int offset = 0, pin_offset=0;
	switch (pin) {
	case PE0: case PE1: case PE2: case PE3:
	case PE4: case PE5: case PE6: case PE7:
		offset=PE_CFG0;
		pin_offset= (pin-PE0)<<2;
		break;
	case PE8: case PE9: case PE10: case PE11:
		offset=PE_CFG1;
		pin_offset= (pin-PE8)<<2;
		break;
	case PG0: case PG1: case PG2: case PG3:
	case PG4: case PG5: case PG6: case PG7:
		offset=PG_CFG0;
		pin_offset= (pin-PG0)<<2;
		break;
	case PG8: case PG9: case PG10: case PG11:
		offset=PG_CFG1;
		pin_offset= (pin-PG8)<<2;
		break;
	case PH0: case PH1: case PH2: case PH3:
	case PH4: case PH5: case PH6: case PH7:
		offset=PH_CFG0;
		pin_offset= (pin-PH0)<<2;
		break;
	case PI0: case PI1: case PI2: case PI3:
	case PI4: case PI5: case PI6: case PI7:
		offset=PI_CFG0;
		pin_offset= (pin-PI0)<<2;
		break;
	case PI8:
		offset=PI_CFG1;
		pin_offset= (pin-PI8)<<2;
		break;
	default:
		perror("pin/port not mapped, do nothing");
	}

	if (offset>0) {
		unsigned int cfg;
		cfg = *(unsigned int *)(ptr+offset);
		cfg &= ~(0x3<<pin_offset);
		if (dir)
			cfg |= dir << pin_offset;
		*(unsigned int *)(ptr+offset) = cfg;
	}

        return;
}

void sunxiWrite(int pin, int val)
{
	short int pin_offset=0, offset=0;
	switch (pin) {
	case PE0: case PE1: case PE2: case PE3:
	case PE4: case PE5: case PE6: case PE7:
	case PE8: case PE9: case PE10: case PE11:
		offset=PE_DAT;
		pin_offset= (pin-PE0);
		break;
	case PG0: case PG1: case PG2: case PG3:
	case PG4: case PG5: case PG6: case PG7:
	case PG8: case PG9: case PG10: case PG11:
		offset=PG_DAT;
		pin_offset= (pin-PG0);
		break;
	case PH0: case PH1: case PH2: case PH3:
	case PH4: case PH5: case PH6: case PH7:
		offset=PH_DAT;
		pin_offset= (pin-PH0);
		break;
	case PI0: case PI1: case PI2: case PI3:
	case PI4: case PI5: case PI6: case PI7:
	case PI8:
		offset=PI_DAT;
		pin_offset= (pin-PI0);
		break;
	default:
		perror("pin/port not mapped, do nothing");
		offset=0x0;
	}
	if (offset>0) {
		volatile unsigned int data = *(unsigned int *)(ptr+offset);
		if (val)
			data |= (1<<pin_offset);
		else
			data &= ~(1<<pin_offset);
		*(unsigned int *)(ptr+offset) = data;
	}

}

int sunxiRead(int pin)
{
	short int pin_offset=0, offset=0;
	switch (pin) {
	case PE0: case PE1: case PE2: case PE3:
	case PE4: case PE5: case PE6: case PE7:
	case PE8: case PE9: case PE10: case PE11:
		offset=PE_DAT;
		pin_offset= (pin-PE0);
		break;
	case PG0: case PG1: case PG2: case PG3:
	case PG4: case PG5: case PG6: case PG7:
	case PG8: case PG9: case PG10: case PG11:
		offset=PG_DAT;
		pin_offset= (pin-PG0);
		break;
	case PH0: case PH1: case PH2: case PH3:
	case PH4: case PH5: case PH6: case PH7:
		offset=PH_DAT;
		pin_offset= (pin-PH0);
		break;
	case PI0: case PI1: case PI2: case PI3:
	case PI4: case PI5: case PI6: case PI7:
	case PI8:
		offset=PI_DAT;
		pin_offset= (pin-PI0);
		break;
	default:
		perror("pin/port not mapped, do nothing");
		offset=0x0;
			
	
	}
	if (offset>0) {
		volatile unsigned int data = *(unsigned int *)(ptr+offset);
		data = (data>>pin_offset) & 0x1 ;
		if (data)
			return HIGH;
		else
			return LOW;
	}
	return -1;

}

/*
 * wapper fn toward the sunxi implementation
 */
void wiringPiSetup()
{
	wiringSunxiSetup();
}
void pinMode(int pinInt, int dir)
{
	sunxiMode( pinInt, dir );
}
int digitalRead(int pin)
{
	return sunxiRead(pin);
}
void digitalWrite(int pin, int val)
{
	sunxiWrite( pin, val);
}

void digitalSync(int usec_delay)
{
        usleep(usec_delay);
}
