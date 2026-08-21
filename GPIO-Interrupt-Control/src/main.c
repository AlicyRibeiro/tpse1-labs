#include "hw_types.h"
#include "soc_AM335x.h"

// AINTC
#define INTC_MIR_CLEAR3       0x00E8
#define INTC_SIR_IRQ          0x0040
#define INTC_CONTROL          0x0048

// GPIO
#define GPIO_OE               0x134
#define GPIO_IRQSTATUS_0      0x2C
#define GPIO_RISINGDETECT     0x148
#define GPIO_SETDATAOUT       0x194
#define GPIO_CLEARDATAOUT     0x190
#define GPIO_IRQSTATUS_SET_0  0x34

// LEDs internos USR (GPIO1)
#define USR0 21  // GPIO1_21
#define USR1 22  // GPIO1_22
#define USR2 23  // GPIO1_23
#define USR3 24  // GPIO1_24

// Botões
#define BOTAO1 28 // GPIO1_28 → P9_12 → IRQ 98
#define BOTAO2 27 // GPIO0_27 → P8_17 → IRQ 96

#define DELAY_TIME 100000000

//variaveis de comportamento
volatile int modo_fixo = 0;
volatile int modo_duplas = 0;

void delay(unsigned int count) {
    volatile unsigned int i;
    for (i = 0; i < count; i++);
}

void disable_watchdog() {         //permite que aplaca não resert depois de um tempinho
    while (HWREG(0x44E35034) != 0);
    HWREG(0x44E35048) = 0xAAAA;
    while (HWREG(0x44E35034) != 0);
    HWREG(0x44E35048) = 0x5555;
    while (HWREG(0x44E35034) != 0);
}

void habilita_clock_gpios() {
    HWREG(SOC_CM_PER_REGS + 0xAC) |= 0x2; // GPIO1
    HWREG(SOC_CM_PER_REGS + 0xA8) |= 0x2; // GPIO0
}

void configura_leds_saida() {
    unsigned int reg = HWREG(SOC_GPIO_1_REGS + GPIO_OE);
    reg &= ~((1 << USR0) | (1 << USR1) | (1 << USR2) | (1 << USR3));
    HWREG(SOC_GPIO_1_REGS + GPIO_OE) = reg;
}

void configura_botoes_entrada() {
    unsigned int reg;

    // BOTAO1 - GPIO1_28
    reg = HWREG(SOC_GPIO_1_REGS + GPIO_OE);
    reg |= (1 << BOTAO1);
    HWREG(SOC_GPIO_1_REGS + GPIO_OE) = reg;

    // BOTAO2 - GPIO0_27
    reg = HWREG(SOC_GPIO_0_REGS + GPIO_OE);
    reg |= (1 << BOTAO2);
    HWREG(SOC_GPIO_0_REGS + GPIO_OE) = reg;
}

void habilita_irq_botoes() {  // ocorre interupção
    // GPIO1 - BOTAO1
    HWREG(SOC_GPIO_1_REGS + GPIO_RISINGDETECT) |= (1 << BOTAO1);
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_SET_0) |= (1 << BOTAO1);

    // GPIO0 - BOTAO2
    HWREG(SOC_GPIO_0_REGS + GPIO_RISINGDETECT) |= (1 << BOTAO2);
    HWREG(SOC_GPIO_0_REGS + GPIO_IRQSTATUS_SET_0) |= (1 << BOTAO2);
}

void config_gpio() {
    habilita_clock_gpios();
    configura_leds_saida();
    configura_botoes_entrada();
    habilita_irq_botoes();
}

void config_aintc() {                           //desmascara
    HWREG(SOC_AINTC_REGS + INTC_MIR_CLEAR3) |= (1 << (98 - 96)) | (1 << (96 - 96));
}

// LEDs
void liga_todos_leds() {
    HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) =
        (1 << USR0) | (1 << USR1) | (1 << USR2) | (1 << USR3);
}

void desliga_todos_leds() {
    HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) =
        (1 << USR0) | (1 << USR1) | (1 << USR2) | (1 << USR3);
}

void pisca_duplas() {
    // Liga USR0 e USR1
    HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << USR0) | (1 << USR1);
    HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << USR2) | (1 << USR3);
    delay(DELAY_TIME);

    // Liga USR2 e USR3
    HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << USR2) | (1 << USR3);
    HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << USR0) | (1 << USR1);
    delay(DELAY_TIME);
}

// Interrupção
void verifica_interrupcoes() {
    unsigned int irq_num = HWREG(SOC_AINTC_REGS + INTC_SIR_IRQ) & 0x7F;

    if (irq_num == 98) {  // BOTAO1
        if (HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0) & (1 << BOTAO1)) {
            modo_fixo = !modo_fixo;
            modo_duplas = 0;
            HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0) = (1 << BOTAO1); //As interrupções são limpas após serem tratadas
        }
    } else if (irq_num == 96) { // BOTAO2
        if (HWREG(SOC_GPIO_0_REGS + GPIO_IRQSTATUS_0) & (1 << BOTAO2)) {
            modo_duplas = !modo_duplas;
            modo_fixo = 0;
            HWREG(SOC_GPIO_0_REGS + GPIO_IRQSTATUS_0) = (1 << BOTAO2);
        }
    }                                                               //Sem isso, o AINTC consideraria a interrupção ainda ativa.

    HWREG(SOC_AINTC_REGS + INTC_CONTROL) = 0x1;
}
// o numero da interupçao e buscada no manual da BBB, capitulo 6 seção 6.3
//a função deinterupção deve ser chamada no start e não na main


// ===    Main   ===
int main(void) {
    disable_watchdog();
    config_gpio();
    config_aintc();

    while (1) {
    
        if (modo_fixo) {
            liga_todos_leds();
        } else if (modo_duplas) {
            pisca_duplas();
        } else {
            desliga_todos_leds();
        }
    }

    return 0;
}



