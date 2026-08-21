/*=================================================================================================================
* NESSE HEADER CONTEM TODOS OS OFFSETS UTILIZADOS NAS PRATICAS
*
==================================================================================================================*/
#ifndef OFFSETS_H
#define OFFSETS_H
/*=================================================================================================================
*   GPIOs
==================================================================================================================*/
/******************************************************************MODULO DE CLOCK*/
/*Macros da configuracao do modulo de clock gpio1*/
#define CM_PER_GPIO1_CLKCTRL (0x0AC)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK (1<<18)
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE (0x02u)

/*Macros da configuracao do modulo de clock gpio2*/
#define CM_PER_GPIO2_CLKCTRL (0xB0)
#define CM_PER_GPIO2_CLKCTRL_OPTFCLKEN_GPIO_2_GDBCLK  (1<<18)
#define CM_PER_GPIO2_CLKCTRL_MODULEMODE (0x02u)

/******************************************************************MODULO DE CONTROLE*/
/*Grupo 1 - leds internos*/
#define conf_gpmc_a5  (0x0854)
#define conf_gpmc_a6  (0x0858)
#define conf_gpmc_a7  (0x085C)
#define conf_gpmc_a8  (0x0860)

/*Pinos externos: 12-P9 = gpio1_28; 18-P8 = pgio2_1; 25-P9 = gpio3_21; 27-P9 = gpio3_19*/
#define conf_gpmc_be1n (0x0878) //led 12-P9 = gpio1_28
#define conf_gpmc_ad12 (0x0830)//button0 12-P8 = gpio1_12
#define conf_gpmc_clk (0x088C) //led 18-P8 = pgio2_1
#define conf_gpmc_oen_ren (0x0894)//led gpio2_3 => 8-P8
#define conf_gpmc_advn_ale (0x0890)//button1 || gpio2_2 || 7-P8
#define conf_mcasp0_ahclkx (0x09AC) //pin button2 || 25-P9 = gpio3_21 || INTC - GPIOINT3B
//#define conf_mcasp0_fsr (0x09A4) //pin button2 || 27-P9 = gpio3_19   || INTC - GPIOINT3B


/*Para usar o modo gpio dos pinos*/
#define multiplexacao (0x07)

/***********************************************************************MODULO DE GPIO*/
#define GPIOs_GPIO_IRQSTATUS_0      (0x02C)
#define GPIOs_GPIO_IRQSTATUS_1      (0x030)
#define GPIOs_GPIO_IRQSTATUS_SET_0  (0x034)
#define GPIOs_GPIO_IRQSTATUS_SET_1  (0x038)
#define GPIOs_GPIO_IRQSTATUS_CLR_1  (0x040)
#define GPIOs_GPIO_OE               (0x0134)
#define GPIOs_GPIO_DATAIN           (0X0138)
#define GPIOs_GPIO_LEVELDETECT0     (0x0140)
#define GPIOs_GPIO_LEVELDETECT1     (0x0144)
#define GPIOs_GPIO_RISINGDETECT     (0x0148)
#define GPIOs_GPIO_FALLINGDETECT    (0x014C)
#define GPIOs_GPIO_DEBOUNCENABLE    (0x0150)
#define GPIOs_GPIO_DEBOUNCINGTIME   (0x0154)
#define GPIOs_GPIO_CLEARDATAOUT     (0x0190)
#define GPIOs_GPIO_SETDATAOUT       (0x0194)

/*Mascaras dos pinos dos modulos GPIO*/
#define mask_pinos_gpio1 (0x11E01000)
#define mask_pinos_gpio2 (0x0000000A)
#define mask_pinos_gpio3 (0x00200000)

/*Botao*/
//MACROS
#define BUTTON0 HWREG(SOC_GPIO_1_REGS + GPIOs_GPIO_DATAIN) & (1<<12) //12-P8
#define BUTTON1 HWREG(SOC_GPIO_2_REGS + GPIOs_GPIO_DATAIN) & (1<<2) //7-p8
#define BUTTON2 HWREG(SOC_GPIO_3_REGS + GPIOs_GPIO_DATAIN) & (1<<21) //27-P9
/*INTC*/
#define BINTC 1

/*=================================================================================================================
*   TIMER
==================================================================================================================*/
#define CM_PER_TIMER2_CLKCTRL (0x80)
#define CM_PER_TIMER7_CLKCTRL (0x7C)

#define IRQSTATUS     (0x028)
#define IRQSTATUS_SET (0x02C)
#define IRQSTATUS_CLR (0x030)
#define TCLR  (0x038)
#define TCRR  (0x03C)
#define TWPS  (0x048)
#define TSICR (0x054)

#define W_PEND_TCLR 0
#define W_PEND_TCRR 1
#define W_PEND_TLDR 2

#define TEMP_1MS (0x5DC0u)
#define TIMER_OVERFLOW (0xFFFFFFFF) 
#define TIMER_INTC 0

/*=================================================================================================================
*   UART
==================================================================================================================*/
#define UART0_RHR  								0x44E09000
#define UART0_THR  								0x44E09000
#define UART0_LSR  								0x44E09014
/*=================================================================================================================
*   INTERRUPCAO
==================================================================================================================*/
#define INTC_SYSCONFIG (0x10)
#define INTC_SYSSTATUS (0x14)
#define INTC_CONTROL (0x48)
#define INTC_SIR_IRQ (0x40)
#define INTC_THRESHOLD (0x68)
//#define INTC_MIR_CLEAR(n) (0x088 + ( (n) * 0x20))
#define INTC_MIR_CLEAR0 (0x88)
#define INTC_MIR_CLEAR1 (0xA8)
#define INTC_MIR_CLEAR2 (0xC8)
#define INTC_MIR_CLEAR3 (0xE8)

/*INTERRUPCOES ARM A8*/
#define A8_GPIOINT2A    (32)
#define A8_GPIOINT3B    (63)
#define A8_TINT7        (95)
#define A8_GPIOINT1A    (98)
/*================================================================================================================
*WATCHDOG
================================================================================================================*/
#define WDT_WWPS (0x034)
#define WDT_WSPR (0x048)

/*=================================================================================================================
*   INICIALIZAR FUNCOES
==================================================================================================================*/
void active_clock_gpio1();
void active_clock_gpio2();
void active_ContM_leds();
void active_ContM_button1();
void active_ContM_button2();
void direction_gpio1();
void direction_gpio2();
void direction_gpio3();
void init_leds();
void on_led(unsigned int grupo, unsigned int bit);
void off_led(unsigned int grupo, unsigned int bit);
void on_leds_inter();
void off_leds_inter();
void mask_intc_gpio1();
void mask_intc_gpio3();
void config_int_input();
void init_buttons();
//int check_button1();
//int check_button2();
void gpioIrqHandler();
void button2IrqHander();
void button1IrqHander();
char getButton();
char getButton1();
char getButton2();
void init_timer7();
void delay(unsigned int);
void timerIrqHandler();
bool getTimer();
void putCh(char c);
char getCh();
int putString(char *str, unsigned int length);
int getString(char *buf, unsigned int length);
void clearBuffer();
void init_interrupt();
void ISR_Handler();
void desable_wtd();
//MENUS
void menuFreq();
void menuModeEx();
void menuModeIn();

#endif
