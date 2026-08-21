#ifndef DELAY_H
#define DELAY_H

#include "bbb_regs.h"
#include "hw_types.h"

int flag_timer = false;
bool flag_gpio1, flag_gpio2;

void butConfig(){
	
	HWREG(CM_PER_GPMC_A0_REGS) |= 0x2F;
	HWREG(CM_PER_GPMC_BEn1_REGS) |= 0x2F;

	HWREG(GPIO1_OE) |= 1<<button1 | 1<<button2;//habilitando recursos de saida
	
	flag_gpio1 = false;
	flag_gpio2 = false;	

	HWREG(GPIO1_IRQSTATUS_SET_0) |= 1<<button2; 	
	HWREG(GPIO1_IRQSTATUS_SET_1) |= 1<<button1;
	
	//detectando borda de subida (baixo -> alto)
	HWREG(GPIO1_RISINGDETECT) |= 1<<button1;
	HWREG(GPIO1_RISINGDETECT) |= 1<<button2;
	//HWREG(GPIO1_DEBOUNCENABLE) |= 1<<button2 | 1<<button1;
	//HWREG(GPIO1_DEBOUNCINGTIME) = 32;

}

void timerEnable(){
    	//garante que a configuraçao anterior no TCLR foi concluida antes de prosseguir
	DMTimerWaitForWrite(0x1);
    	HWREG(DMTIMER_TCLR) |= 0x1;
}

void timerDisable(){
	DMTimerWaitForWrite(0x1);
    	HWREG(DMTIMER_TCLR) &= ~(0x1);
}

//cria atrasos usando o temporizador
void delay(unsigned int mSec){//tcrr
#ifdef DELAY_USE_INTERRUPT
	//Calcula o valor que deve ser carregado no registrador de contagem (TCRR) 
    	unsigned int countVal = TIMER_OVERFLOW - (mSec * TIMER_1MS_COUNT);

	DMTimerWaitForWrite(0x2);
	HWREG(DMTIMER_TCRR) = countVal;//carrega o registrador com o valor
	
	flag_timer = false;
	HWREG(DMTIMER_IRQENABLE_SET) = 0x2;//ativa a interrupçao 
	timerEnable();

    	while(flag_timer == false);//indicar que o atraso foi concluido

	HWREG(DMTIMER_IRQENABLE_CLR) = 0x2; 
#else
    while(mSec != 0){
        DMTimerWaitForWrite(0x2);
        HWREG(DMTIMER_TCRR) = 0x0;
        timerEnable();

        while(HWREG(DMTIMER_TCRR) < TIMER_1MS_COUNT);

        HWREG(DMTIMER_TCLR) &= ~(0x00000001u);
        mSec--;
    }
#endif
}

//configura o DMTIMER7 habilitando seu clock
void timerSetup(void){
    	HWREG(CM_PER_TIMER7_CLKCTRL) |= 0x2;
    	while((HWREG(CM_PER_TIMER7_CLKCTRL) & 0x3) != 0x2);

#ifdef DELAY_USE_INTERRUPT
    	HWREG(INTC_MIR_CLEAR2) |= (1<<31);//95 --> Bit 31 
#endif
}

void gpioSetup(){
	//inicializa os clocks dos GPIO
	HWREG(CM_PER_GPIO1_CLKCTRL) = 0x40002;
	HWREG(CM_PER_GPIO2_CLKCTRL) = 0x40002;
	
    	HWREG(INTC_MIR_CLEAR3) |= (1<<2);//(98 --> Bit 2 do 4º registrador 
	HWREG(INTC_MIR_CLEAR3) |= (1<<3);//99 --> Bit 3 do 4º registrador 
}


void timerIrqHandler(void){
//irq status contem as flags das int que foram acionadas
	HWREG(DMTIMER_IRQSTATUS) = 0x2; //limpa a int que foi acionada
	flag_timer = true;
	timerDisable();
}

void gpioIsrHandlerA(){
	HWREG(GPIO1_IRQSTATUS_0) = (1<<button2);
	flag_gpio1 = true;
}

void gpioIsrHandlerB(){
	HWREG(GPIO1_IRQSTATUS_1) = (1<<button1);
	flag_gpio2 = true;

}


void ISR_Handler(void){
	unsigned int irq_number = HWREG(INTC_SIR_IRQ) & 0x7f;

	if(irq_number == 95){
		timerIrqHandler();

	} else if(irq_number == 98){
		gpioIsrHandlerA();

	} else if(irq_number == 99){
		gpioIsrHandlerB();
	}
	
	HWREG(INTC_CONTROL) = 0x1;//informa ao controlador que a int foi tratada
}
#endif
