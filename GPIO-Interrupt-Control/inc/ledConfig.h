#ifndef LEDCONFIG_H
#define LEDCONFIG_H

#include "bbb_regs.h"
#include "hw_types.h"
#include "playPong.h"

void ledConfig(){
   
	//leds externos
	HWREG(CM_PER_GPMC_OEN_REN_REGS) |= 0x7;
	HWREG(CM_PER_GPMC_WEn_REGS) 	|= 0x7;
	HWREG(CM_PER_GPMC_CLK_REGS) 	|= 0x7;
	HWREG(SOC_CONTROL_REGS+OFFSET4) |= 0x7;
	HWREG(SOC_CONTROL_REGS+OFFSET5) |= 0x7;
	HWREG(SOC_CONTROL_REGS+OFFSET6) |= 0x7;
	HWREG(SOC_CONTROL_REGS+OFFSET7) |= 0x7;
	HWREG(SOC_CONTROL_REGS+OFFSET8) |= 0x7;
	HWREG(SOC_CONTROL_REGS+OFFSET9) |= 0x7;

	HWREG(GPIO2_OE) &= ~(1<<LED1);
	HWREG(GPIO2_OE) &= ~(1<<LED2);
	HWREG(GPIO2_OE) &= ~(1<<LED3);
	HWREG(GPIO2_OE) &= ~(1<<LED4);
	HWREG(GPIO2_OE) &= ~(1<<LED5);
	HWREG(GPIO2_OE) &= ~(1<<LED6);
	HWREG(GPIO2_OE) &= ~(1<<LED7);
	HWREG(GPIO2_OE) &= ~(1<<LED8);
	HWREG(GPIO2_OE) &= ~(1<<LED9);

}

void ledOff(pinNum pin){
	switch (pin) {
		
		case PIN1:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<LED1);
		break;
		case PIN2:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<LED2);
		break;
		case PIN3:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<LED3);
		break;
		case PIN4:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<LED4);
		break;
		case PIN5:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<LED5);
		break;
		case PIN6:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<LED6);
		break;
		case PIN7:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<LED7);
		break;
		case PIN8:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<LED8);
		break;
		case PIN9:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<LED9);
		break;
		default:
		break;
	}
}

void ledOn(pinNum pin){
	
	switch (pin) {
		case PIN1:	
			HWREG(GPIO2_SETDATAOUT) |= (1<<LED1);
		break;
		case PIN2:	
			HWREG(GPIO2_SETDATAOUT) |= (1<<LED2);
		break;
		case PIN3:	
			HWREG(GPIO2_SETDATAOUT) |= (1<<LED3);
		break;
		case PIN4:	
			HWREG(GPIO2_SETDATAOUT) |= (1<<LED4);
		break;
		case PIN5:	
			HWREG(GPIO2_SETDATAOUT) |= (1<<LED5);
		break;
		case PIN6:	
			HWREG(GPIO2_SETDATAOUT) |= (1<<LED6);
		break;
		case PIN7:	
			HWREG(GPIO2_SETDATAOUT) |= (1<<LED7);
		break;
		case PIN8:	
			HWREG(GPIO2_SETDATAOUT) |= (1<<LED8);
		break;
		case PIN9:	
			HWREG(GPIO2_SETDATAOUT) |= (1<<LED9);
		break;
		default:
		break;
	}
}

void clear_leds(int leds[], int size) {
    for(int i = 0; i < size; i++) {
        HWREG(GPIO2_CLEARDATAOUT) = (1 << leds[i]);
    }
}

void set_leds(int leds[], int size) {
    for(int i = 0; i < size; i++) {
        HWREG(GPIO2_SETDATAOUT) = (1 << leds[i]);
    }
}    

/*void set1_leds(){
	HWREG(GPIO2_SETDATAOUT) |= (1<<LED1);
	HWREG(GPIO2_SETDATAOUT) |= (1<<LED2);
	HWREG(GPIO2_SETDATAOUT) |= (1<<LED3);
	HWREG(GPIO2_SETDATAOUT) |= (1<<LED4);
	HWREG(GPIO2_SETDATAOUT) |= (1<<LED5);
	HWREG(GPIO2_SETDATAOUT) |= (1<<LED6);
	HWREG(GPIO2_SETDATAOUT) |= (1<<LED7);
	HWREG(GPIO2_SETDATAOUT) |= (1<<LED8);
	HWREG(GPIO2_SETDATAOUT) |= (1<<LED9);
}

void clear1_leds(){
	HWREG(GPIO2_CLEARDATAOUT) = (1<<LED1);
	HWREG(GPIO2_CLEARDATAOUT) = (1<<LED2);
	HWREG(GPIO2_CLEARDATAOUT) = (1<<LED3);
	HWREG(GPIO2_CLEARDATAOUT) = (1<<LED4);
	HWREG(GPIO2_CLEARDATAOUT) = (1<<LED5);
	HWREG(GPIO2_CLEARDATAOUT) = (1<<LED6);
	HWREG(GPIO2_CLEARDATAOUT) = (1<<LED7);
	HWREG(GPIO2_CLEARDATAOUT) = (1<<LED8);
	HWREG(GPIO2_CLEARDATAOUT) = (1<<LED9);
}*/

#endif
