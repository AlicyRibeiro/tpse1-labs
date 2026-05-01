/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2017 20:05:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */
 
#include	"hw_types.h"
#include	"soc_AM335x.h"

#define TIME											        1000000
#define TOGGLE          										(0x01u)

#define CM_PER_GPIO1											0xAC
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE   				                        (0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK   			                                (0x00040000u)

#define CM_conf_gpmc_be1n      	 								        0x0878
#define CM_conf_gpmc_a5         								        0x0854
#define CM_conf_gpmc_a6         								        0x0858
#define CM_conf_gpmc_a7         								        0x085C
#define CM_conf_gpmc_a8         								        0x0860

#define GPIO_OE                 								        0x134
#define GPIO_CLEARDATAOUT       								        0x190
#define GPIO_SETDATAOUT         								        0x194


unsigned int flagBlink;

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay();
static void ledInit();
static void ledToggle();


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int _main(void){

	flagBlink=0;	
  	

  	ledInit();
  
  	while (1){
    	
    	ledToggle();
		delay();
		ledToggle();
		delay();
	}

	return(0);
} /* ----------  end of function main  ---------- */


/*FUNCTION*-------------------------------------------------------
*
* Function Name : Delay
* Comments      :
*END*-----------------------------------------------------------*/
static void delay(){
	volatile unsigned int ra;
	for(ra = 0; ra < TIME; ra ++);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledInit
 *  Description:  
 * =====================================================================================
 */
void ledInit( ){
	
	/*-----------------------------------------------------------------------------
	 *  configure clock GPIO in clock module
	 *-----------------------------------------------------------------------------*/
	unsigned int val_temp; 	
	
	HWREG(SOC_CM_PER_REGS+CM_PER_GPIO1) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;
	
	
	/*-----------------------------------------------------------------------------
	 * configure mux pin in control module
	 *-----------------------------------------------------------------------------*/
	 
   	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a5) |= 7;
 	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a6) |= 7;
	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a7) |= 7;
 	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a8) |= 7;
 	
 	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_be1n) |= 7;
 	
 	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	 
	val_temp = HWREG(SOC_GPIO_1_REGS+GPIO_OE);
	val_temp &= ~(1<<21);
	val_temp &= ~(1<<22);
	val_temp &= ~(1<<23);
	val_temp &= ~(1<<24);
	
	val_temp &= ~(1<<28);
	
	HWREG(SOC_GPIO_1_REGS+GPIO_OE) = val_temp;
		
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledToggle
 *  Description:  
 * =====================================================================================
 */
void ledToggle( ){
    static unsigned int estadoLED = 0;

    flagBlink ^= TOGGLE;

    if(flagBlink){
        // Liga LED externo
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (1<<28);

        // Desliga todos os LEDs internos
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) =
            (1<<21) | (1<<22) | (1<<23) | (1<<24);

        // Acende apenas um LED interno por vez usando if/else
        if (estadoLED == 0) {
            HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (1<<21); // USR0
        } else if (estadoLED == 1) {
            HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (1<<22); // USR1
        } else if (estadoLED == 2) {
            HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (1<<23); // USR2
        } else {
            HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (1<<24); // USR3
        }
    } else {
        // Desliga todos os LEDs internos e externo
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) =
            (1<<21) | (1<<22) | (1<<23) | (1<<24) | (1<<28);

        // Avança para o próximo estado
        if (estadoLED < 3) {
            estadoLED++;
        } else {
            estadoLED = 0;
        }
    }
}/* -----  end of function ledToggle  ----- */

