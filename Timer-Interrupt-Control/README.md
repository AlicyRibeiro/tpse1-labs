# Timer-Interrupt-Control
---

## Descrição

Prática de programação bare metal na BeagleBone Black que integra o uso de interrupções para dois periféricos distintos: GPIO (botões) e DMTimer. O projeto demonstra como o processador lida com eventos assíncronos de hardware e contagem de tempo para controlar e alternar sequências de acendimento de LEDs externos.

---

## Funcionamento

O sistema consolida a configuração de entradas/saídas e o uso avançado da Tabela de Vetores de Interrupção (IVT) no AM335x, aplicando-a a GPIOs e Timers:

#### 1. Configuração do Controlador de Interrupções (INTC)

A base do sistema assíncrono ocorre no INTC[cite: 8]:
- **GPIO Interrupts:** A interrupção para o módulo GPIO utilizado é desmascarada no registrador apropriado (ex: `INTC_MIR_CLEAR3` para o módulo 1, IRQ 98)[cite: 8].
- **Timer Interrupts:** A interrupção do DMTimer (ex: DMTIMER7, IRQ 95) é desmascarada configurando o registrador `INTC_MIR_CLEAR2`[cite: 8].

---

#### 2. Configuração dos Pinos como GPIO

A direção dos pinos é definida no registrador `GPIO_OE`, utilizando uma combinação específica para a prática[cite: 8]:
- **Saídas (LEDs):** Configurados três LEDs externos (GPIO_67, GPIO_68 e GPIO_65) zerando seus respectivos bits de direção[cite: 8].
- **Entradas (Botões):** Configurados dois botões externos, sendo um com resistor de *pull-down* e outro com resistor de *pull-up*[cite: 8]. Os botões estão mapeados para os pinos GPIO_60 (gpio1_28) e GPIO_48 (gpio1_16)[cite: 8].

---

#### 3. Interrupção via GPIO (Botões)

A detecção de evento é ativada nos registradores `GPIO_IRQSTATUS_SET_n` e ajustada para bordas específicas (ex: `GPIO_RISINGDETECT`)[cite: 8].
- **Button 2 (GPIO_60):** Configurado como *pull-down*, este botão aciona uma interrupção obrigatória que alterna a sequência de *blink* (pisca) dos três LEDs[cite: 8].

---

#### 4. Interrupção via DMTimer (Atrasos Cronometrados)

Em vez de utilizar laços vazios (polling) para travar a execução, o DMTimer é configurado para gerar uma interrupção ao atingir uma contagem de tempo definida[cite: 8]:
- O valor de recarga de tempo desejado é calculado e escrito no registrador `DMTIMER_TCRR`[cite: 8].
- O Timer é habilitado (`DMTIMER_IRQENABLE_SET = 0x2`) e iniciado[cite: 8].
- Ao final da contagem, uma *flag* global avisa ao sistema que o tempo passou, e o Timer é desabilitado até a próxima chamada, criando uma função de *Delay* não-bloqueante por Hardware[cite: 8].

---

#### 5. Rotina de Serviço de Interrupção (ISR)

Uma única rotina em C (`ISR_Handler`), invocada pelo Assembly, lê o registrador `INTC_SIR_IRQ` para identificar a fonte da interrupção (IRQ 95 para Timer ou IRQ 98 para GPIO)[cite: 8]. Baseado no número:
- Se for GPIO, limpa as *flags* em `GPIO_IRQSTATUS_0` e altera o estado das variáveis de controle dos LEDs[cite: 8].
- Se for Timer, limpa as *flags* em `DMTIMER_IRQSTATUS` e sinaliza o fim do *Delay*[cite: 8].
Em ambos os casos, a IRQ é reconhecida no `INTC_CONTROL`[cite: 8].

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

A implementação dos códigos atende aos seguintes cenários práticos:

- *Controle de Sequência:* O usuário consegue alternar o padrão de blink dos três LEDs ao pressionar o Button 2 (GPIO_60), cuja leitura é feita via interrupção.

- *Temporização Híbrida (Delay):* A função de Delay utilizada no blink dos LEDs é baseada em interrupções geradas pelo DMTimer (Timer 7), demonstrando eficiência sobre atrasos convencionais por polling.

- *Controle de Menu:* O sistema exibe um menu para o usuário escolher o tempo da frequência do blink em milissegundos através da ativação do Button 1 (GPIO_48).