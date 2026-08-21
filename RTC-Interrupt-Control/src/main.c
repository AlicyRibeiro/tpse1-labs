
// === CLOCK GPIO / RTC ===
#define CM_PER_GPIO1_CLKCTRL     (*(volatile unsigned int*)0x44E000AC)
#define CM_RTC_CLKSTCTRL         (*(volatile unsigned int*)0x44E00804)
#define CM_RTC_RTC_CLKCTRL       (*(volatile unsigned int*)0x44E00800)

// === UART0 ===
#define UART0_THR                (*(volatile unsigned int*)0x44E09000)
#define UART0_RHR                (*(volatile unsigned int*)0x44E09000)
#define UART0_LSR                (*(volatile unsigned int*)0x44E09014)

// === WDT ===
#define WDT_WSPR                 (*(volatile unsigned int*)0x44E35048)
#define WDT_WWPS                 (*(volatile unsigned int*)0x44E35034)

// === GPIO1 ===
#define GPIO1_OE                 (*(volatile unsigned int*)0x4804C134)
#define GPIO1_CLEARDATAOUT       (*(volatile unsigned int*)0x4804C190)
#define GPIO1_SETDATAOUT         (*(volatile unsigned int*)0x4804C194)

// === AINTC ===
#define INTC_SIR_IRQ             (*(volatile unsigned int*)0x48200040)
#define INTC_CONTROL             (*(volatile unsigned int*)0x48200048)
#define INTC_MIR_CLEAR2          (*(volatile unsigned int*)0x482000C8)

// === RTC ===
#define SECONDS_REG              (*(volatile unsigned int*)0x44E3E000)
#define MINUTES_REG              (*(volatile unsigned int*)0x44E3E004)
#define HOURS_REG                (*(volatile unsigned int*)0x44E3E008)
#define RTC_CTRL_REG             (*(volatile unsigned int*)0x44E3E040)
#define RTC_STATUS_REG           (*(volatile unsigned int*)0x44E3E044)
#define RTC_INTERRUPTS_REG       (*(volatile unsigned int*)0x44E3E048)
#define RTC_OSC_REG              (*(volatile unsigned int*)0x44E3E054)
#define KICK0R                   (*(volatile unsigned int*)0x44E3E06C)
#define KICK1R                   (*(volatile unsigned int*)0x44E3E070)

// === CONTROL MODULE ===
#define CONTROL_MODULE_BASE      0x44E10000
#define onf_gpmc_a1              0x844  // P9_23 (GPIO1_17)

// === LEDs ===
#define LED_USR0     (1 << 21)  // Interno
#define LED_EXT      (1 << 17)  // Externo (GPIO1_17)


// === Funções ===
void disable_wdt(void){           //desliga o watchdog timer
  WDT_WSPR = 0xAAAA;
  while((WDT_WWPS & (1<<4)));
  WDT_WSPR = 0x5555;
  while((WDT_WWPS & (1<<4)));
}

void enviar_caractere_uart(unsigned char c){
  while(!(UART0_LSR & (1<<5)));
  UART0_THR = c;
}

void inicializar_rtc(void){
    CM_RTC_CLKSTCTRL   = 0x2;
    CM_RTC_RTC_CLKCTRL = 0x2;

    KICK0R = 0x83E70B13;
    KICK1R = 0x95A4F1E0;

    RTC_OSC_REG = 0x48;
    RTC_INTERRUPTS_REG = 0x4;   // interrupção por segundo
    RTC_CTRL_REG |= 0x01;

    while((RTC_STATUS_REG & 0x01));
    INTC_MIR_CLEAR2 |= (1<<11); // IRQ 75
}

void configurar_horario_rtc(void){ //Define a hora inicial do RTC, no formato BCD
    RTC_CTRL_REG &= ~(1 << 0); // Para RTC
    while (RTC_STATUS_REG & 0x01);
    
    //define a  hora
    HOURS_REG   = 0x10; 
    MINUTES_REG = 0x49;
    SECONDS_REG = 0x00;

    RTC_CTRL_REG |= (1 << 0); // Inicia RTC
    while (RTC_STATUS_REG & 0x01);
}

void inicializar_gpio_leds(){ //Habilita o clock do GPIO1.
    CM_PER_GPIO1_CLKCTRL = 0x40002;

    // Configura GPIO1_17 (LED externo) no CONTROL MODULE como GPIO
    *(volatile unsigned int*)(CONTROL_MODULE_BASE + onf_gpmc_a1) = 0x07;

    // Configura GPIO1_21 e GPIO1_17 como saída
    GPIO1_OE &= ~(LED_USR0 | LED_EXT);

    // Garante que ambos comecem desligados
    GPIO1_CLEARDATAOUT = (LED_USR0 | LED_EXT);
}

//===ligam ou desligam os LEDs 
void led_usr0_on(void)   { GPIO1_SETDATAOUT   = LED_USR0; }
void led_usr0_off(void)  { GPIO1_CLEARDATAOUT = LED_USR0; }
void led_ext_on(void)    { GPIO1_SETDATAOUT   = LED_EXT; }
void led_ext_off(void)   { GPIO1_CLEARDATAOUT = LED_EXT; }

void imprimir_horario_uart(void){
  unsigned char h = HOURS_REG;
  unsigned char m = MINUTES_REG;
  unsigned char s = SECONDS_REG;

  enviar_caractere_uart(0x30 + ((h >> 4) & 0x3));
  enviar_caractere_uart(0x30 + ((h >> 0) & 0xf));
  enviar_caractere_uart(':');

  enviar_caractere_uart(0x30 + ((m >> 4) & 0x7));
  enviar_caractere_uart(0x30 + ((m >> 0) & 0xf));
  enviar_caractere_uart(':');

  enviar_caractere_uart(0x30 + ((s >> 4) & 0x7));
  enviar_caractere_uart(0x30 + ((s >> 0) & 0xf));
  enviar_caractere_uart('\r');
}

int flg_led = 0;
void tratar_interrupcao_rtc(void){
    // Alterna estado do LED interno e externo inversamente
    if (flg_led++ & 0x1) {
        led_usr0_on();
        led_ext_off();
    } else {
        led_usr0_off();
        led_ext_on();
    }

    imprimir_horario_uart();
}

void IRQ_Handler(void){
    unsigned int irq_number = INTC_SIR_IRQ & 0x7f; 
    if(irq_number == 75){
        tratar_interrupcao_rtc();
    }
    INTC_CONTROL = 1;
}

int main(void){
    inicializar_gpio_leds();
    inicializar_rtc();
    configurar_horario_rtc();
    disable_wdt();

    const char *hello = "Hello Interrupt2!\n\r";
    const char *p = hello;
    while (*p) enviar_caractere_uart(*p++);

    while(1);
    return 0;
    
}


/*
Configura dois LEDs com alternância por segundo.
Usa o RTC da BeagleBone Black para gerar uma interrupção por segundo.
Imprime a hora atual a cada segundo pela UART.
*/
