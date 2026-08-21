# GPIO-Input-Control
---

## Descrição

Prática de programação bare metal na BeagleBone Black focada na configuração do periférico GPIO como entrada (INPUT). O projeto realiza a leitura de botões (push-buttons) integrados a um circuito resistivo para alterar dinamicamente o comportamento e o sequenciamento dos LEDs.

---

## Funcionamento

O funcionamento do programa segue as etapas de configuração e controle do GPIO no AM335x para a leitura de dados:

#### 1. Ativação do clock do GPIO

O módulo GPIO1 (e outros módulos utilizados) é habilitado através do registrador `CM_PER_GPIO1_CLKCTRL`, permitindo o uso do periférico.

---

#### 2. Configuração dos pinos como GPIO

Os pinos utilizados são configurados como GPIO por meio dos registradores de controle (PADs), colocando-os no modo 7.

Exemplos de pinos utilizados:
- Pinos dos LEDs internos (GPIO1_21 a GPIO1_24 → USR0 a USR3)
- Pinos para os botões via barramento expansor P8/P9 (ex: GPIO1_28 referenciado no pino 12 do expansor P9)

---

#### 3. Configuração da direção dos pinos

A direção dos pinos é definida no registrador `GPIO_OE`:
- **Saídas (LEDs):** Zerando os bits correspondentes.
- **Entradas (Botões):** Setando os bits correspondentes (nível lógico 1).

---

#### 4. Leitura dos botões e Controle dos LEDs

A leitura do estado lógico do botão é realizada através do registrador `DATAIN`. Quando o botão é pressionado (fechado), a corrente flui para o pino de entrada, permitindo a leitura da voltagem. Com base nessa leitura, a lógica do programa aciona os LEDs utilizando:
- `SETDATAOUT` → liga o LED
- `CLEARDATAOUT` → desliga o LED

---

#### 5. Configuração do Circuito de Hardware

Os botões são montados na protoboard e conectados aos pinos do barramento expansor em conjunto com resistores de *pull-down* (1kΩ ou 10kΩ). Essa configuração garante que a corrente siga para o GND quando o botão não for pressionado, resultando em uma leitura limpa e evitando curtos-circuitos.

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

A execução deste código demonstra o controle de entradas e saídas digitais via *polling*, implementando lógica de *debouncing* por software para garantir leituras estáveis dos botões. O sistema reage da seguinte forma:

- **Controle dos LEDs Internos (Botão 1):** O pressionamento do Botão 1 (conectado ao pino P9_12) atua como um seletor de modos, alternando ciclicamente entre três padrões de animação para os quatro LEDs internos da placa (USR0–USR3):
  1. **Modo Sequencial:** Os LEDs acendem e apagam um por vez em sequência (efeito *running light*).
  2. **Modo Piscante Global:** Todos os quatro LEDs acendem e apagam simultaneamente.
  3. **Modo Alternado em Pares:** Os LEDs alternam o acendimento em duplas (USR0/USR1 acendem enquanto USR2/USR3 apagam, e vice-versa).
- **Controle do LED Externo (Botão 2):** Operando de forma totalmente independente da animação principal, o pressionamento do Botão 2 (conectado ao pino P9_15) atua como um interruptor (função *toggle*), alternando o estado do LED externo (pino P9_23) entre ligado e desligado a cada clique.
- **Responsividade de Interrupção por Software:** As lógicas de atraso (*delay*) dentro de cada sequência de LEDs possuem verificações ativas do estado do Botão 1. Isso garante que a transição de um padrão para outro ocorra de maneira imediata ao clique, sem forçar o usuário a esperar o término do ciclo atual da animação.