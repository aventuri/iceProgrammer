#ifndef _LIBSUNXI_H
#define _LIBSUNXI_H

#  define PD_CFG0		0x006c
#  define PD_CFG1		0x0070
#  define PD_DAT		0x007c
#  define PE_CFG0		0x0090
#  define PE_CFG1		0x0094
#  define PE_DAT		0x00a0
#  define PG_CFG0		0x00d8
#  define PG_CFG1		0x00dc
#  define PG_DAT		0x00e8
#  define PH_CFG0		0x00fc
#  define PH_DAT		0x010c
#  define PI_CFG0		0x0120
#  define PI_CFG1		0x0124
#  define PI_DAT		0x0130


// UART4_TX = PG11 (U15-18)
// UART4_RX = PG10 (U15-17)
//
#if 0
#  define SUNXI_ICE_MISO	PG8  // U15-15 CS1-D4 yellow
#  define SUNXI_ICE_CLK		PG6  // U15-13 CS1-D2 orange
#  define SUNXI_ICE_CDONE	PG4  // U15-11 CS1-D0 red
#  define SUNXI_ICE_SELECT	PG2  // U15-9  CS1-HSYNC brown

#  define SUNXI_ICE_CRESET	PG9  // U15-16 CS1-D5 grey
#  define SUNXI_ICE_MOSI	PG7  // U15-14 CS1-D3 purple
#  define SUNXI_ICE_CS		PG5  // U15-12 CS1-D1 blue
#  define LOAD_FROM_FLASH	PG3  // U15-8  CS1-VSYNC green
#endif

// pinout for sunxi cubieboard
#  define SUNXI_ICE_MISO	PD3  // U14-6  LCD0-D3 blue
#  define SUNXI_ICE_CLK		PD2  // U14-3  LCD0-D2 purple
#  define SUNXI_ICE_CDONE	PD5  // U14-8  LCD0-D5 yellow
//#  define SUNXI_ICE_SELECT	PD7  // U14-10 LCD0-D7 red

#  define SUNXI_ICE_CRESET	PD4  // U14-5  LCD0-D4 green
#  define SUNXI_ICE_MOSI	PD1  // U14-4  LCD0-D1 grey
#  define SUNXI_ICE_CS		PD0  // U14-1  LCD0-D0 white
//#  define LOAD_FROM_FLASH	PD6  // U14-7  LCD0-D6 orange
// color brown is for 3v3 from breadboard!

/*
 * trying to free one UART port
 * UART3 (TX=PG6, RX=PG7)
 * UART4 (TX=PG10, RX=PG11)
 */
#  define SUNXI_D8	PI7	// U15-28 SDC3-D1
#  define SUNXI_D7	PE11	// U15-48 CSI0-D7
#  define SUNXI_D6	PE10	// U15-46 CSI0-D6
#  define SUNXI_D5	PE9	// U15-44 CSI0-D5
#  define SUNXI_D4	PE8	// U15-42 CSI0-D4
#  define SUNXI_D3	PE7	// U15-40 CSI0-D3
#  define SUNXI_D2	PE6	// U15-38 CSI0-D2
#  define SUNXI_D1	PE5	// U15-36 CSI0-D1
#  define SUNXI_D0	PE4	// U15-34 CSI0-D0
#  define SUNXI_DIR	PI5	// U15-24 SDC3-CLK
#  define SUNXI_CLK	PI8	// U15-30 SDC3-D3



# define OUTPUT 1
# define INPUT 0
# define LOW 0
# define  HIGH 1

enum SUNXI_GPIO {\
	PD0=0, PD1, PD2, PD3, PD4, PD5, PD6, PD7, PD8, PD9, PD10, PD11, \
	PE0, PE1, PE2, PE3, PE4, PE5, PE6, PE7, PE8, PE9, PE10, PE11, \
	PG0, PG1, PG2, PG3, PG4, PG5, PG6, PG7, PG8, PG9, PG10, PG11, \
	PH0, PH1, PH2, PH3, PH4, PH5, PH6, PH7, \
	PI0, PI1, PI2, PI3, PI4, PI5, PI6, PI7, PI8 \
};

void digitalSync(int);
void wiringSunxiSetup(void);
void pinMode(int pin, int dir);
void digitalWrite(int pin, int val);
int digitalRead(int pin);

#endif

