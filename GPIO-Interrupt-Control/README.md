# GPIO-Interrupt-Control
---

## Descrição

Prática de programação bare metal na BeagleBone Black focada na implementação de interrupções (Interrupts) para o periférico GPIO. O projeto utiliza uma Tabela de Vetores de Interrupção (IVT) e rotinas de serviço de interrupção (ISR) para ler eventos assíncronos de botões, alterando a lógica do programa de maneira priorizada.

---

## Funcionamento

O funcionamento do programa segue as etapas de configuração e controle de interrupções do GPIO no AM335x:[cite: 4]

#### 1. Tabela de Vetores de Interrupção (IVT) e Assembly

O sistema é inicializado configurando o endereço do manipulador de interrupção (`.irq_handler`) na memória[cite: 4]. O código em Assembly captura o snapshot dos registradores atuais e inicializa o ponteiro da pilha (stack pointer) antes de invocar a rotina em C[cite: 4].

---

#### 2. Configuração do Controlador de Interrupções (INTC)

O mapeamento da interrupção é realizado identificando o número correspondente (como a Interrupção 98 para o grupo `GPIOINT1A` do módulo 1) e desmascarando-a no registrador `INTC_MIR_CLEARn` (por exemplo, setando o bit 2 de `INTC_MIR_CLEAR3`)[cite: 4].

---

#### 3. Configuração dos Pinos e Geração de Eventos (GPIO)

A interrupção é habilitada no pino específico através do registrador `GPIO_IRQSTATUS_SET_n`[cite: 4]. O tipo de transição que acionará o evento (como uma borda de subida) é definido configurando os registradores `GPIO_RISINGDETECT` ou `GPIO_FALLINGDETECT`[cite: 4].

---

#### 4. Rotina de Serviço de Interrupção (ISR)

Quando o evento ocorre, o processador invoca a ISR, que verifica a interrupção ativa no registrador `INTC_SIR_IRQ`[cite: 4]. O status da requisição é reconhecido e a flag de interrupção é limpa no registrador `GPIO_IRQSTATUS_0`, permitindo atualizar variáveis e alterar o fluxo do código principal[cite: 4].

---

#### 5. Configuração do Circuito de Hardware

Os botões são montados na protoboard e conectados aos pinos dos expansores P8 ou P9 em conjunto com resistores de pull-down (10K)[cite: 4]. Essa montagem previne curtos-circuitos e garante que a tensão seja lida pelo pino de entrada apenas quando o circuito do botão for fechado[cite: 4].

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

A execução deste código demonstra o tratamento simultâneo e prioritário de múltiplas interrupções de hardware. O sistema reage aos eventos assíncronos da seguinte forma:

- **Estado Inicial:** O sistema inicia em repouso, mantendo os quatro LEDs internos (USR0–USR3) apagados.
- **Acionamento do Botão 1 (Modo Fixo):** Conectado ao pino P9_12 (GPIO1_28), o pressionamento deste botão aciona uma interrupção (IRQ 98) que liga todos os quatro LEDs simultaneamente e de forma estática. Um novo acionamento retorna o sistema ao estado desligado.
- **Acionamento do Botão 2 (Modo Duplas):** Conectado ao pino P8_17 (GPIO0_27), este botão aciona uma interrupção (IRQ 96) que ativa um padrão de pisca alternado em pares (USR0/USR1 acendem enquanto USR2/USR3 apagam, invertendo após o *delay*).
- **Exclusividade de Estados:** O tratamento das *flags* dentro da rotina de verificação de interrupções garante que os modos operem de maneira mutuamente exclusiva. Ao pressionar um botão, o comportamento do outro é imediatamente cancelado, garantindo uma transição limpa e em tempo real entre aceso, piscando ou desligado.