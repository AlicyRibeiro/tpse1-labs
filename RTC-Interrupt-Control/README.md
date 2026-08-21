# RTC-Interrupt-Control
---

## Descrição

Prática de programação bare metal na BeagleBone Black focada na configuração do periférico RTC (Real-Time Clock) para gerar interrupções temporizadas[cite: 10, 11]. O projeto configura o RTC para gerar uma interrupção por segundo, alternando o estado de dois LEDs e imprimindo o horário atual na interface UART0[cite: 10]. O Watchdog Timer (WDT) é desabilitado para o funcionamento ininterrupto do sistema[cite: 10, 11].

---

## Funcionamento

O funcionamento do programa segue as etapas de inicialização e configuração do RTC, GPIO e UART no AM335x[cite: 10, 11]:

#### 1. Ativação dos Clocks e Módulos (RTC e GPIO)

O clock do módulo GPIO1 é ativado via registrador `CM_PER_GPIO1_CLKCTRL`[cite: 11]. Os clocks específicos do RTC são ativados através dos registradores `CM_RTC_CLKSTCTRL` e `CM_RTC_RTC_CLKCTRL`[cite: 11]. O Watchdog Timer (WDT) é desabilitado escrevendo sequências específicas (`0xAAAA` e `0x5555`) no registrador `WDT_WSPR` e checando `WDT_WWPS`[cite: 11].

---

#### 2. Configuração dos Pinos como Saída

Os pinos são configurados no módulo de controle e no GPIO[cite: 11]. O registrador no offset `0x844` (`CONTROL_MODULE_BASE + onf_gpmc_a1`) é ajustado para o modo GPIO para habilitar o LED externo no pino P9_23 (GPIO1_17)[cite: 11]. A direção é configurada como saída zerando os bits correspondentes (`LED_USR0` e `LED_EXT`) no registrador de direção `GPIO1_OE`, e ambos são inicializados apagados usando o `GPIO1_CLEARDATAOUT`[cite: 11].

---

#### 3. Inicialização e Configuração do RTC

O acesso de escrita aos registradores do RTC é liberado enviando chaves de desbloqueio para os registradores `KICK0R` e `KICK1R`[cite: 11]. O oscilador do RTC é ativado (`RTC_OSC_REG`), o horário inicial em formato BCD é definido nos registradores `HOURS_REG`, `MINUTES_REG` e `SECONDS_REG`, e o módulo de contagem é iniciado ativando o bit 0 no `RTC_CTRL_REG`[cite: 11].

---

#### 4. Configuração de Interrupções do RTC

O módulo RTC é configurado no registrador `RTC_INTERRUPTS_REG` (`0x4`) para gerar uma solicitação de interrupção exatamente a cada segundo[cite: 11]. Para que o processador atenda a essa requisição, a interrupção correspondente (IRQ 75) é desmascarada no controlador de interrupções AINTC ajustando o bit 11 do registrador `INTC_MIR_CLEAR2`[cite: 11].

---

#### 5. Rotina de Serviço de Interrupção (ISR) e UART

Quando a interrupção de um segundo ocorre, a função tratadora identificada pelo IRQ 75 inverte os estados lógicos do LED interno e do LED externo de forma alternada[cite: 11]. Imediatamente após a alternância, o horário atual é lido dos registradores do RTC, convertido de formato BCD para ASCII através de operações de deslocamento de bits, e impresso no terminal via `UART0_THR`[cite: 11]. O evento é então reconhecido no registrador `INTC_CONTROL`[cite: 11].

---

## Estrutura

O repositório contém os códigos-fonte e os arquivos de compilação, organizados da seguinte forma:

```text
bin/        # Binários gerados
inc/        # Headers (.h)
src/        # Códigos-fonte (.c/.s)
Makefile    # Script de compilação
script.txt  # Comandos para execução no U-Boot
README.md   # Este arquivo
```

---

## Como Compilar

No diretório da prática, execute:

````
make
````

O processo irá:

- Compilar os arquivos fonte
- Gerar o executável (.elf)
- Converter para binário (.boot ou .bin)
- Copiar automaticamente para /tftpboot/

#### Execução

No U-Boot, execute os comandos presentes no arquivo script.txt e, em seguida:

````
run app
````

---

## Resultado Esperado

A implementação dos códigos atende aos seguintes comportamentos:

- *Controle de LEDs:* O LED interno (USR0) e o LED externo (GPIO1_17) alternam seus estados inversamente a cada exato 1 segundo gerado pela interrupção do RTC.

- *Relógio via UART:* A cada segundo, sincronizado com a inversão dos LEDs, o sistema imprime o horário em tempo real no terminal serial (UART0) formatado em HH:MM:SS.

- *Execução Contínua:* O sistema opera de forma ininterrupta, mantendo a contagem do tempo de maneira eficiente através de interrupções sem depender de laços de bloqueio.