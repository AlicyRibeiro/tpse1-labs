#   Multi-LED-Control
---

##  Descrição

Prática de programação bare metal na BeagleBone Black responsável pelo controle de múltiplos LEDs, incluindo os quatro LEDs internos (USR0–USR3) e um LED externo conectado ao pino GPIO1_28.

---

##  Funcionamento

O funcionamento do programa segue as etapas de configuração e controle do GPIO no AM335x:

#### 1. Ativação do clock do GPIO1

O módulo GPIO1 é habilitado através do registrador `CM_PER_GPIO1_CLKCTRL`, permitindo o uso do periférico.

---

####  2. Configuração dos pinos como GPIO

Os pinos utilizados são configurados como GPIO por meio dos registradores de controle (PADs), colocando-os no modo 7.

Pinos utilizados:

- GPIO1_21 → USR0  
- GPIO1_22 → USR1  
- GPIO1_23 → USR2  
- GPIO1_24 → USR3  
- GPIO1_28 → LED externo  

---

#### 3. Configuração da direção dos pinos

Os pinos são configurados como saída utilizando o registrador `GPIO_OE`, zerando os bits correspondentes.

---


#### 4. Controle dos LEDs

O controle é realizado através dos registradores:

- `SETDATAOUT` → liga o LED  
- `CLEARDATAOUT` → desliga o LED  

O programa implementa uma lógica sequencial:

- O LED externo pisca continuamente  
- Apenas um LED interno permanece aceso por vez  
- Os LEDs internos são ativados em sequência (USR0 → USR1 → USR2 → USR3)  
- Entre cada troca, todos os LEDs são desligados  

---

#### 5. Delay por software

Um laço vazio é utilizado para criar o tempo entre as transições dos LEDs.

---

##  Estrutura

```text
bin/        # Binários gerados
inc/        # Headers
src/        # Código-fonte
Makefile    # Compilação
memmap.ld   # Organização de memória
start.s     # Inicialização
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

- O LED externo pisca continuamente
- Os LEDs internos (USR0–USR3) acendem em sequência
- Apenas um LED interno permanece aceso por vez
- O ciclo se repete continuamente

