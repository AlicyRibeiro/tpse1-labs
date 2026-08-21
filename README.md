# Praticas_BeagleBone
![UFC - QXD0149](https://img.shields.io/badge/UFC-QXD0149-black?labelColor=555555&style=for-the-badge)
---

## Descrição

Este repositório reúne as práticas de programação bare-metal desenvolvidas para a disciplina de Técnicas de Programação para Sistemas Embarcados I, do curso de Engenharia de Computação da UFC Quixadá. 

O objetivo central dos projetos aqui contidos é explorar o funcionamento de microcontroladores em baixo nível utilizando a BeagleBone Black (processador AM335x), abrangendo desde o controle de periféricos simples (GPIOs) até o tratamento assíncrono de interrupções e temporizadores de hardware.

---

## Estrutura do Repositório

Cada prática está organizada em diretórios independentes, contendo seus próprios códigos-fonte, headers, scripts de compilação (Makefile) e documentação (`README.md`).

```text
Praticas_BeagleBone/
├── blink-led/                 # Pisca o LED USR0 (GPIO1_21)
├── multi-led-control/         # Controle sequencial de 4 LEDs internos + 1 externo
├── gpio-input-control/        # Leitura de botões integrados a um circuito resistivo
├── gpio-interrupt-control/    # Tratamento de interrupções de hardware com botões
├── uart-system-control/       # Comunicação serial via UART0 com menu interativo
├── timer-interrupt-control/   # Temporização via interrupções de hardware (DMTimer)
└── rtc-interrupt-control/     # Interrupções temporizadas por segundo utilizando o RTC
```
---

## Requisitos e Ferramentas

Para compilar e executar qualquer uma das práticas deste repositório, é necessário o seguinte ambiente:

- *Toolchain ARM:* Compilador cruzado (arm-linux-gnueabihf-gcc ou similar) para gerar os binários executáveis do processador AM335x.

- *Make:* Automação do processo de compilação.

- *Servidor TFTP:* Para transferir os binários gerados para a placa via rede (/tftpboot/).

- *U-Boot:* Bootloader utilizado na BeagleBone Black para carregar e executar os binários via terminal serial.

---

## Como Utilizar

Cada pasta possui um `Makefile` configurado. De forma geral, o fluxo de execução segue os passos:

1. Navegue até o diretório da prática desejada:
   ```bash
   cd nome-da-pratica
   ```

2. Compile o código e envie para o diretório de boot:
    ```bash
    make    
    ```

3. Na interface serial da BeagleBone Black (via U-Boot), execute os comandos de carregamento de memória contidos no arquivo script.txt da respectiva prática.

4. Inicie o programa:
    ```bash
    run app    
    ```


> Para detalhes específicos de funcionamento e esquemas de montagem na protoboard, consulte o README.md dentro da pasta de cada prática.