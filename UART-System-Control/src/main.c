#include "hw_types.h"
#include "soc_AM335x.h"

// --- UART0 ---
#define UART0_BASE            0x44E09000
#define UART0_THR             (*(volatile unsigned int *)(UART0_BASE + 0x00))
#define UART0_RHR             (*(volatile unsigned int *)(UART0_BASE + 0x00))
#define UART0_LSR             (*(volatile unsigned int *)(UART0_BASE + 0x14))
#define UART0_TX_EMPTY        (1 << 5)
#define UART0_RX_READY        (1 << 0)

// --- AINTC (Controlador de Interrupções) ---
#define INTC_MIR_CLEAR3       0x00E8
#define INTC_SIR_IRQ          0x0040
#define INTC_CONTROL          0x0048

// --- GPIO (Offsets) ---
#define GPIO_OE               0x134
#define GPIO_SETDATAOUT       0x194
#define GPIO_CLEARDATAOUT     0x190
#define GPIO_DATAIN           0x138
#define GPIO_IRQSTATUS_0      0x2C
#define GPIO_IRQSTATUS_SET_0  0x34
#define GPIO_RISINGDETECT     0x148

// --- LEDs ---
#define LED1_USR0         21 // GPIO1_21 (USR0)
#define LED2_EXT          26 // GPIO0_26 (P9_21)
#define LED3_EXT          17 // GPIO1_17 (P9_23)

// --- Botões ---
#define BOTAO1            28 // GPIO1_28 (P9_12) -> IRQ 98 (GPIO1B)
#define BOTAO2            16 // GPIO1_16 (P9_15) -> IRQ 98 (GPIO1B)
#define BOTAO3            27 // GPIO0_27 (P9_17) -> IRQ 96 (GPIO0B)

// Flags Globais
volatile int flag_bot1 = 0; 
volatile int flag_bot2 = 0; 
volatile int flag_bot3 = 0;

// --- Funções Auxiliares ---
void delay(volatile unsigned int t) { while (t--); }

void disable_watchdog() {                 //impede que a placa inicie sozinha
    HWREG(SOC_WDT_1_REGS + 0x48) = 0xAAAA;
    while((HWREG(SOC_WDT_1_REGS + 0x34) & (1 << 4)));
    HWREG(SOC_WDT_1_REGS + 0x48) = 0x5555;
    while((HWREG(SOC_WDT_1_REGS + 0x34) & (1 << 4)));
}

void configura_uart0() {                         //inicializa a uart
    HWREG(SOC_CM_WKUP_REGS + 0xBC) |= 0x2;
    while((HWREG(SOC_CM_WKUP_REGS + 0xBC) & 0x3) != 0x2);
    HWREG(SOC_CONTROL_REGS + 0x980) = 0x20; //configura mux do uart0_RX
    HWREG(SOC_CONTROL_REGS + 0x984) = 0x00; //configura mux do uart0_TX
    unsigned int divisor = 26;
    HWREG(UART0_BASE + 0xC) = 0x83;
    HWREG(UART0_BASE + 0x0) = divisor & 0xFF;
    HWREG(UART0_BASE + 0x4) = (divisor >> 8) & 0xFF;
    HWREG(UART0_BASE + 0xC) = 0x03;
    HWREG(UART0_BASE + 0x20) = 0x07;
    HWREG(UART0_BASE + 0x20) = 0x00;  
}

void uart_envia_char(char c) { // aguarda registrador de transmissão (THR) estar vazio
    while (!(*(volatile unsigned int *)(UART0_BASE + 0x14) & (1 << 5)));
    *(volatile unsigned int *)(UART0_BASE + 0x00) = c;
}


char uart_recebe_char() { //aguarda registrador de recepção (RHR) estar preenchido
    while (!(*(volatile unsigned int *)(UART0_BASE + 0x14) & (1 << 0)));
    return *(volatile unsigned int *)(UART0_BASE + 0x00);
}

void uart_envia_string(const char *s) {   //envia os caracteres da string s, um por um
    while (*s) uart_envia_char(*s++);
}

void habilita_clocks_e_mux() {
    // Clocks para GPIO0 e GPIO1
    HWREG(SOC_CM_PER_REGS + 0xAC) |= 0x2; // GPIO1
    HWREG(SOC_CM_PER_REGS + 0xE8) |= 0x2; // GPIO0

    // Mux para botões (Entrada, pull desabilitado, receiver ativo = 0x2F)
    HWREG(SOC_CONTROL_REGS + 0x878) = 0x2F; // BOT1 (P9_12)
    HWREG(SOC_CONTROL_REGS + 0x840) = 0x2F; // BOT2 (P9_15)
    HWREG(SOC_CONTROL_REGS + 0x95C) = 0x2F; // BOT3 (P9_17)
    
    // Mux para LEDs (Saída, pull desabilitado = 0x0F)
    HWREG(SOC_CONTROL_REGS + 0x854) = 0x0F; // LED1 (USR0)
    HWREG(SOC_CONTROL_REGS + 0x958) = 0x0F; // LED2 (P9_21)
    HWREG(SOC_CONTROL_REGS + 0x844) = 0x0F; // LED3 (P9_23)
}

void configura_gpio() {
    // Configura direção dos pinos
    // GPIO1
    unsigned int dir1 = HWREG(SOC_GPIO_1_REGS + GPIO_OE);
    dir1 &= ~((1 << LED1_USR0) | (1 << LED3_EXT)); // Saídas
    dir1 |= (1 << BOTAO1) | (1 << BOTAO2);       // Entradas
    HWREG(SOC_GPIO_1_REGS + GPIO_OE) = dir1;
    // GPIO0
    unsigned int dir0 = HWREG(SOC_GPIO_0_REGS + GPIO_OE);
    dir0 &= ~(1 << LED2_EXT); // Saída
    dir0 |= (1 << BOTAO3);  // Entrada
    HWREG(SOC_GPIO_0_REGS + GPIO_OE) = dir0;

    // Configura interrupções por borda de subida
    HWREG(SOC_GPIO_1_REGS + GPIO_RISINGDETECT) |= (1 << BOTAO1) | (1 << BOTAO2);
    HWREG(SOC_GPIO_0_REGS + GPIO_RISINGDETECT) |= (1 << BOTAO3);
    
    // Habilita IRQs nos módulos GPIO corretos
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_SET_0) = (1 << (BOTAO1)) | (1 << (BOTAO2));
    HWREG(SOC_GPIO_0_REGS + GPIO_IRQSTATUS_SET_0) = (1 << (BOTAO3));

    // Habilita IRQs 98 (GPIO1B) e 96 (GPIO0B) no AINTC
    HWREG(SOC_AINTC_REGS + INTC_MIR_CLEAR3) = (1 << (98 - 96)) | (1 << (96 - 96));  //desmacara
}


//FUNÇÕES PARA LIGAR E DESLIGAR LEDs conectados a placa
void liga(unsigned int base, unsigned int pin) {  //ligar o pino GPIo0 indicado
    HWREG(base + GPIO_SETDATAOUT) = (1 << pin); // ativa apenas os btis desejados sem afetar os outros
    
}
void desliga(unsigned int base, unsigned int pin) { //desliga o pino GPIO0 indicado
    HWREG(base + GPIO_CLEARDATAOUT) = (1 << pin); //limpa somente o bit desejado (opera como AND com mascara invertida)
}


// === função que estar sendo chamada no start ===
void verifica_interrupcoes() {
    unsigned int irq = HWREG(SOC_AINTC_REGS + INTC_SIR_IRQ) & 0x7F;

    if (irq == 98) {
        unsigned int status = HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0);
        if (status & (1 << (BOTAO1))) {
            flag_bot1 = 1;
            HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0) = (1 << (BOTAO1));
        }
        if (status & (1 << (BOTAO2))) {
            flag_bot2 = 1;
            HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0) = (1 << (BOTAO2)); 
        }
    } else if (irq == 96) {
        unsigned int status = HWREG(SOC_GPIO_0_REGS + GPIO_IRQSTATUS_0);
        if (status & (1 << (BOTAO3))) {
            flag_bot3 = 1;
            HWREG(SOC_GPIO_0_REGS + GPIO_IRQSTATUS_0) = (1 << (BOTAO3)); //Ela limpa a interrupção pendente do botão 3 (BOTAO3), que está conectado no GPIO0.
        }
    }
                                                                   //Sem isso, o AINTC consideraria a interrupção ainda ativa.
    HWREG(SOC_AINTC_REGS + INTC_CONTROL) = 0x1;
}

void exibir_menu() {
    uart_envia_string("\r\n=== MENU UART ===\r\n");
    uart_envia_string("1 - Ligar Interno (USR0)\r\n");
    uart_envia_string("2 - Ligar Vermelho\r\n");
    uart_envia_string("3 - Ligar Azul \r\n");
    uart_envia_string("4 - Desligar todos os LEDs\r\n");
    uart_envia_string("> ");
}

int main(void) {
    disable_watchdog();
    habilita_clocks_e_mux(); // Corrigido de "habilita_clocks_e_mux_gpio"
    configura_uart0();
    configura_gpio();

    exibir_menu();

    while (1) {
        // if(condição) verifica_interrupcoes(); 
   
   if (flag_bot1) {
            flag_bot1 = 0;
            liga(SOC_GPIO_1_REGS, LED1_USR0); delay(50000000);
            desliga(SOC_GPIO_1_REGS, LED1_USR0);
        }

        if (flag_bot2) {
            flag_bot2 = 0;
            liga(SOC_GPIO_0_REGS, LED2_EXT); delay(50000000);
            desliga(SOC_GPIO_0_REGS, LED2_EXT);
        }
        if (flag_bot3) {
            flag_bot3 = 0;
            liga(SOC_GPIO_1_REGS, LED3_EXT); delay(50000000);
            desliga(SOC_GPIO_1_REGS, LED3_EXT);
        }

        if (*(volatile unsigned int *)(UART0_BASE + 0x14) & (1 << 0)) {
            char op = uart_recebe_char();
            uart_envia_char(op);
            switch (op) {
                case '1': liga(SOC_GPIO_1_REGS, LED1_USR0); break;
                case '2': liga(SOC_GPIO_0_REGS, LED2_EXT); break;
                case '3': liga(SOC_GPIO_1_REGS, LED3_EXT); break;
                case '4':
                    desliga(SOC_GPIO_1_REGS, LED1_USR0);
                    desliga(SOC_GPIO_0_REGS, LED2_EXT);
                    desliga(SOC_GPIO_1_REGS, LED3_EXT);
                    break;
            }
            exibir_menu();
        }
    }
    return 0;
}

/*
Inicializa a UART0 para receber comandos via terminal.

Inicializa os GPIOs: 3 LEDs e 3 botões.

Configura interrupções para os botões.

Dentro da interrupção, ativa uma flag para indicar que um botão foi pressionado.

No loop principal, se alguma flag for ativada:
    Acende o LED correspondente.
    Aguarda com delay.
    Apaga o LED.

Também permite ligar/desligar LEDs pela UART, com um menu.

*/
