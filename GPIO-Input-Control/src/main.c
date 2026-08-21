#include "hw_types.h"
#include "soc_AM335x.h"

#define ATRASO 100000

// Clock
#define CLK_GPIO1         0xAC
#define CLK_EN            (0x2 | (1 << 18))  // ativar módulo + GDBCLK
  
// Registradores do GPIO1
#define REG_DIR           0x134
#define REG_ENTRADA       0x138
#define REG_LIGA          0x194
#define REG_DESLIGA       0x190

// MUX dos pinos
#define conf_gpmc_be1n      0x878  // P9_12 (GPIO1_28) - MUX_BOT1
#define conf_gpmc_a0        0x840  // P9_15 (GPIO1_16) - MUX_BOT2
#define conf_gpmc_a5        0x854  // USR0 (GPIO1_21)  - MUX_L0
#define conf_gpmc_a6        0x858  // USR1 (GPIO1_22)  - MUX_L1
#define conf_gpmc_a7        0x85C  // USR2 (GPIO1_23)  - MUX_L2
#define conf_gpmc_a8        0x860  // USR3 (GPIO1_24) - MUX_L3
#define conf_gpmc_a1        0x844  // LED externo (GPIO1_17) - MUX_LE

// Máscaras dos GPIOs
#define BOT1    (1 << 28)
#define BOT2    (1 << 16)
#define L0      (1 << 21)
#define L1      (1 << 22)
#define L2      (1 << 23)
#define L3      (1 << 24)
#define LE      (1 << 17)
#define TODOS   (L0 | L1 | L2 | L3)

// Atraso simples
void atraso(unsigned int t) { while(t--); }

// Inicialização dos GPIOs e MUX
void iniciar() {
    HWREG(SOC_CM_PER_REGS + CLK_GPIO1) |= CLK_EN;

    HWREG(SOC_CONTROL_REGS + conf_gpmc_be1n) = 0x2F;
    HWREG(SOC_CONTROL_REGS + conf_gpmc_a0)   = 0x2F;
    HWREG(SOC_CONTROL_REGS + conf_gpmc_a5)   = 0x0F;
    HWREG(SOC_CONTROL_REGS + conf_gpmc_a6)   = 0x0F;
    HWREG(SOC_CONTROL_REGS + conf_gpmc_a7)   = 0x0F;
    HWREG(SOC_CONTROL_REGS + conf_gpmc_a8)   = 0x0F;
    HWREG(SOC_CONTROL_REGS + conf_gpmc_a1)   = 0x0F;

    unsigned int dir = HWREG(SOC_GPIO_1_REGS + REG_DIR);
    dir |= BOT1 | BOT2;         // botões como entrada
    dir &= ~(TODOS | LE);       // leds como saída
    HWREG(SOC_GPIO_1_REGS + REG_DIR) = dir;

    HWREG(SOC_GPIO_1_REGS + REG_DESLIGA) = TODOS | LE;
}

// Liga/desliga leds
void liga(unsigned int l)   { HWREG(SOC_GPIO_1_REGS + REG_LIGA) = l; }
void desliga(unsigned int l){ HWREG(SOC_GPIO_1_REGS + REG_DESLIGA) = l; }

// Leitura dos botões
int pressionado(unsigned int bot) {
    return HWREG(SOC_GPIO_1_REGS + REG_ENTRADA) & bot;
}

// Apaga todos os LEDs internos
void apagaTudo() { desliga(TODOS); }

// Padrão 1: um por um
void sequencia1() {
    unsigned int leds[] = {L0, L1, L2, L3};
    for (int i = 0; i < 4; i++) {
        if (pressionado(BOT1)) break;
        liga(leds[i]); atraso(600000); desliga(leds[i]);
    }
}

// Padrão 2: todos piscam
void sequencia2() {
    if (pressionado(BOT1)) return;
    liga(TODOS); atraso(600000);
    desliga(TODOS); atraso(600000);
}

// Padrão 3: pares alternados
void sequencia3() {
    if (pressionado(BOT1)) return;
    liga(L0 | L1); desliga(L2 | L3); atraso(600000);
    if (pressionado(BOT1)) { apagaTudo(); return; }
    desliga(L0 | L1); liga(L2 | L3); atraso(600000);
    apagaTudo();
}

// Função principal
int _main(void) {
    iniciar();

    int padrao = 0;
    int ultimo1 = 0;
    int ultimo2 = 0;
    int estadoLE = 0;

    while (1) {
        // Botão 1 muda padrão de LEDs internos
        if (pressionado(BOT1) && !ultimo1) {
            atraso(10000);
            if (pressionado(BOT1)) {
                padrao = (padrao + 1) % 3;
                apagaTudo();
                while (pressionado(BOT1)) atraso(10000);
            }
        }
        ultimo1 = pressionado(BOT1);

        // Botão 2 alterna LED externo
        if (pressionado(BOT2) && !ultimo2) {
            atraso(10000);
            if (pressionado(BOT2)) {
                estadoLE ^= 1;
                if (estadoLE) liga(LE);
                else desliga(LE);
                while (pressionado(BOT2)) atraso(10000);
            }
        }
        ultimo2 = pressionado(BOT2);

        // Executa o padrão atual com switch
        switch (padrao) {
            case 0: sequencia1(); break;
            case 1: sequencia2(); break;
            case 2: sequencia3(); break;
        }

        if (!pressionado(BOT1) && !pressionado(BOT2))
            atraso(10000);
    }
}

