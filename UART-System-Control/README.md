# UART-System-Control
---

## Descrição

Prática de programação bare metal na BeagleBone Black focada na configuração da interface UART (UART0) em conjunto com o periférico GPIO[cite: 5, 6]. O projeto implementa um sistema que recebe comandos via terminal de computador para acionar LEDs, além de ler interrupções geradas por três botões externos para acionar LEDs de forma dinâmica e imprimir o estado no terminal[cite: 5, 6].

---

## Funcionamento

O funcionamento do programa segue as etapas de configuração de interrupções GPIO e da interface de comunicação serial (UART0) no AM335x[cite: 5, 6]:

#### 1. Ativação do Clock e Mux (GPIO e UART)

Os módulos GPIO (GPIO0 e GPIO1) são habilitados, e o multiplexador dos pinos (Mux) é configurado para definir entradas (botões) e saídas (LEDs)[cite: 6]. Para a UART0, os clocks são ativados via `CM_WKUP_REGS` e o multiplexador é configurado (RX em `0x980`, TX em `0x984`) para permitir a comunicação serial[cite: 6].

---

#### 2. Configuração da UART0

A interface UART0 é configurada definindo o divisor de clock (Baud Rate) e o formato dos dados[cite: 6]. Através de registradores específicos como `UART0_BASE + 0xC` e os registradores de configuração de Divisor Latch, a comunicação serial é ativada para permitir enviar (transmitir - TX) e receber (receber - RX) caracteres pelo terminal[cite: 6].

---

#### 3. Configuração dos Pinos como GPIO

Os pinos utilizados são configurados como GPIO por meio dos registradores de direção `GPIO_OE`, onde 0 define saída e 1 define entrada[cite: 6]:
- **Saídas (LEDs):** GPIO1_21 (LED1 Interno USR0), GPIO0_26 (LED2 Externo Vermelho), GPIO1_17 (LED3 Externo Azul)[cite: 6].
- **Entradas (Botões):** GPIO1_28 (BOTAO1), GPIO1_16 (BOTAO2), GPIO0_27 (BOTAO3)[cite: 6].

---

#### 4. Leitura por Interrupção

O código configura interrupções baseadas em borda de subida (`GPIO_RISINGDETECT`) para os três botões[cite: 6]. Quando um botão é pressionado, o controlador AINTC identifica o número da interrupção (IRQ 96 para GPIO0B ou IRQ 98 para GPIO1B)[cite: 6]. O manipulador de interrupções (`verifica_interrupcoes`) limpa a flag pendente (`GPIO_IRQSTATUS_0`), reconhece o IRQ no controlador (`INTC_CONTROL`) e sinaliza o evento através de flags de software globais (`flag_bot1`, `flag_bot2`, `flag_bot3`)[cite: 6].

---

#### 5. Controle via UART e Hardware

O controle do sistema ocorre de duas formas simultâneas no laço principal[cite: 6]:
- **Menu UART:** Um menu é exibido no terminal[cite: 6]. O usuário pode digitar '1', '2', '3' para acionar um LED específico, ou '4' para desligar todos[cite: 6].
- **Botões (Hardware):** Ao reconhecer uma flag ativada via interrupção, o software aciona o respectivo LED usando o registrador `SETDATAOUT`, aguarda um período via *delay*, e o desliga usando o registrador `CLEARDATAOUT`[cite: 6]. Em conjunto a isso, a string indicando qual LED está piscando é transmitida de volta via UART[cite: 5, 6].

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

- *Interatividade via Terminal (UART):* O sistema exibe um menu no terminal, permitindo ao usuário digitar comandos numéricos específicos ('1', '2' ou '3') para ligar permanentemente o LED Interno, Vermelho ou Azul, ou ('4') para desligar todos os LEDs de uma vez.

- *Controle por Hardware (Botões):* A interação física com os três botões gera interrupções instantâneas capturadas pelo sistema. Ao pressionar um botão, o software aciona temporariamente o LED correspondente, aguarda um tempo programado (delay) e o desliga de forma automática.

- *Execução Concorrente:* O sistema lida paralelamente com a recepção de caracteres pela interface serial (UART) e o tratamento de interrupções de hardware (AINTC), mantendo a estabilidade do fluxo principal.