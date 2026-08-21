#include "hw_types.h"
#include "soc_AM335x.h"

// --- Endereços Base ---
#define AINTC_BASE              SOC_AINTC_REGS
#define GPIO1_BASE              SOC_GPIO_1_REGS
#define CM_PER_BASE             SOC_CM_PER_REGS
#define DMTIMER7_BASE           SOC_DMTIMER_7_REGS
#define CONTROL_MODULE_BASE     SOC_CONTROL_REGS

// --- Offsets dos Registradores ---
// Clock
#define CM_PER_GPIO1_CLKCTRL_OFFSET     0xAC    //Habilita o clock do módulo GPIO1 (General Purpose IO 1).  
#define CM_PER_DMTIMER7_CLKCTRL_OFFSET  0x7C   //Habilita o clock do módulo DMTimer7 (timer 7).

// GPIO
#define GPIO_OE                         0x134
#define GPIO_SETDATAOUT                 0x194
#define GPIO_CLEARDATAOUT               0x190
#define GPIO_DATAIN                     0x138
#define GPIO_RISINGDETECT               0x148
#define GPIO_IRQSTATUS_0                0x2C
#define GPIO_IRQSTATUS_SET_0            0x34

// Timer
#define DMTIMER_TCLR              0x38  // Timer Control Register
#define DMTIMER_TCRR              0x3C  // Timer Counter Register
#define DMTIMER_TLDR              0x40  // Timer Load Register
#define DMTIMER_IRQSTATUS         0x28  // Timer IRQ Status Register
#define DMTIMER_IRQENABLE_SET     0x2C  // Timer IRQ Enable Set Register

// AINTC  usados para desmascarar (habilitar) 
#define INTC_SIR_IRQ                    0x40
#define INTC_CONTROL                    0x48
#define INTC_MIR_CLEAR2                 0xC8
#define INTC_MIR_CLEAR3                 0xE8

// --- Pin Mux (Offsets dos registradores de controle) ---
#define conf_gpmc_be1n                  0x878 // P9_12 (BOT1)
#define conf_gpmc_a0                    0x840 // P9_15 (BOT2)

// ---  pinos para LEDs externos ---
#define conf_gpmc_ad13                  0x834 // P8_11 (LED1_EXT) -> GPIO1_13
#define conf_gpmc_ad15                  0x83C // P8_15 (LED2_EXT) -> GPIO1_15
#define conf_gpmc_a1                    0x844 // P9_23 (LED3_EXT) -> GPIO1_17 


// --- Definições de Pinos, IRQs e Flags ---
#define LED1                  13 // GPIO1_13
#define LED2                  15 // GPIO1_15
#define LED3                  17 // GPIO1_17
#define ALL_LEDS              ((1 << LED1) | (1 << LED2) | (1 << LED3))

#define BOTAO1            28 // P9_12 (Seletor de LED)
#define BOTAO2            16 // P9_15 (Play/Pause)

#define IRQ_GPIO1B            98
#define IRQ_DMTIMER7          95

volatile int flag_botao1 = 0;
volatile int flag_botao2 = 0;
volatile int flag_timer  = 0;

// --- Funções de Inicialização ---
void configurar_sistema() {
    // 1. Habilita Clocks
    HWREG(CM_PER_BASE + CM_PER_GPIO1_CLKCTRL_OFFSET) |= 0x2;
    HWREG(CM_PER_BASE + CM_PER_DMTIMER7_CLKCTRL_OFFSET) |= 0x2;

    // 2. Configura Pin Mux
    HWREG(CONTROL_MODULE_BASE + conf_gpmc_be1n) = 0x2F; // Botões como entrada
    HWREG(CONTROL_MODULE_BASE + conf_gpmc_a0)   = 0x2F;
    // --- ALTERAÇÃO AQUI: Configura os novos pinos de LED ---
    HWREG(CONTROL_MODULE_BASE + conf_gpmc_ad13) = 0x0F; // LEDs como saída
    HWREG(CONTROL_MODULE_BASE + conf_gpmc_ad15) = 0x0F;
    HWREG(CONTROL_MODULE_BASE + conf_gpmc_a1)  = 0x0F;

    // 3. Configura Direção dos GPIOs
    // Todos os pinos estão no GPIO1
    unsigned int dir = HWREG(GPIO1_BASE + GPIO_OE);
    dir &= ~ALL_LEDS; // Configura os 3 pinos de LED como SAÍDA
    dir |= (1 << BOTAO1) | (1 << BOTAO2); // Configura os 2 pinos de botão como ENTRADA
    HWREG(GPIO1_BASE + GPIO_OE) = dir;
    HWREG(GPIO1_BASE + GPIO_CLEARDATAOUT) = ALL_LEDS; // Garante que LEDs comecem apagados

    // 4. Configura Geração de Interrupção no GPIO
    HWREG(GPIO1_BASE + GPIO_RISINGDETECT) |= (1 << BOTAO1) | (1 << BOTAO2);
    HWREG(GPIO1_BASE + GPIO_IRQSTATUS_SET_0) = (1 << (BOTAO1 )) | (1 << (BOTAO2));
    HWREG(GPIO1_BASE + GPIO_IRQSTATUS_0) = 0xFFFFFFFF; // Limpa flags "fantasmas"

    // 5. Habilita IRQs no Controlador (AINTC)
    HWREG(AINTC_BASE + INTC_MIR_CLEAR2) = (1 << (IRQ_DMTIMER7 - 64));
    HWREG(AINTC_BASE + INTC_MIR_CLEAR3) = (1 << (IRQ_GPIO1B - 96));
}

void configurar_timer() {
    unsigned int contagem_timer = 0xFFFF - 16384; // ~0.5s com clock de 32kHz
    HWREG(DMTIMER7_BASE + DMTIMER_TCRR) = contagem_timer;
    HWREG(DMTIMER7_BASE + DMTIMER_TLDR) = contagem_timer;
    HWREG(DMTIMER7_BASE + DMTIMER_IRQENABLE_SET) = (1 << 1); // Habilita IRQ de Overflow
    HWREG(DMTIMER7_BASE + DMTIMER_TCLR) = (1 << 1) | (1 << 0); // Autoreload, Start
}

// --- Handlers de Interrupção  ---
void gpio_isr_handler() {
    unsigned int status = HWREG(GPIO1_BASE + GPIO_IRQSTATUS_0);
    if (status & (1 << (BOTAO1))) {
        flag_botao1 = 1;
    }
    if (status & (1 << (BOTAO2))) {
        flag_botao2 = 1;
    }
    HWREG(GPIO1_BASE + GPIO_IRQSTATUS_0) = status;
}

void timer_isr_handler() {
    flag_timer = 1;
    HWREG(DMTIMER7_BASE + DMTIMER_IRQSTATUS) = (1 << 1); // Limpa a flag do timer
}

void ISR_Handler() {
    unsigned int irq = HWREG(AINTC_BASE + INTC_SIR_IRQ) & 0x7F;
    if (irq == IRQ_GPIO1B) {
        gpio_isr_handler();
    } else if (irq == IRQ_DMTIMER7) {
        timer_isr_handler();
    }
    HWREG(AINTC_BASE + INTC_CONTROL) = 0x1;
}

// --- Função Principal ---
int main(void) {
    // Array de LEDs agora usa os pinos externos ---
    unsigned int leds[] = { (1 << LED1), (1 << LED2), (1 << LED3) };
    int led_atual_idx = 0;
    int timer_ligado = 0;

    configurar_sistema();
    configurar_timer();
    
    // Para o timer inicialmente
    HWREG(DMTIMER7_BASE + DMTIMER_TCLR) &= ~(1 << 0);

    // enable_interrupts(); // Chamada para a função do start.s

    while (1) {
        if (flag_botao1) { // Botão 1: Seleciona o próximo LED
            flag_botao1 = 0;
            HWREG(GPIO1_BASE + GPIO_CLEARDATAOUT) = leds[led_atual_idx];
            led_atual_idx = (led_atual_idx + 1) % 3;
        }

        if (flag_botao2) { // Botão 2: Play/Pause do Timer
            flag_botao2 = 0;
            timer_ligado = !timer_ligado;
            if (!timer_ligado) {
                HWREG(DMTIMER7_BASE + DMTIMER_TCLR) &= ~(1 << 0); // Para o timer
                HWREG(GPIO1_BASE + GPIO_CLEARDATAOUT) = leds[led_atual_idx]; // Apaga o LED
            } else {
                HWREG(DMTIMER7_BASE + DMTIMER_TCLR) |= (1 << 0); // Inicia o timer
            }
        }

        if (flag_timer) { // Interrupção do Timer ocorreu
            flag_timer = 0;
            
            // Inverte o estado do LED selecionado (pisca)
            if (HWREG(GPIO1_BASE + GPIO_DATAIN) & leds[led_atual_idx]) {
                HWREG(GPIO1_BASE + GPIO_CLEARDATAOUT) = leds[led_atual_idx];
            } else {
                HWREG(GPIO1_BASE + GPIO_SETDATAOUT) = leds[led_atual_idx];
            }
        }
    }
    return 0;
}
