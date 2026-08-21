#ifndef PUTSTRING_H
#define PUTSTRING_H

//void putString(char *str, unsigned int length);
void clearBuffer();
/*char in[15] = "___________\r\n";
char input[15] = "|PING PONG|\r\n";
char iniButtonRed[] = "Aperte o Botao vermelho para o jogador 1 iniciar\r\n";
char iniButtonBlu[] = "Ou o Botao azul para o jogador 2\r\n";

void printUart() {
    clearBuffer(); // Limpa o buffer
    putString(in, 19);
    putString(input, 15);
    putString(in, 19);
    putString(iniButtonRed, 52);
    putString(iniButtonBlu, 36);
    clearBuffer();
}*/
void putCh(char c){
	while(!(HWREG(UART0_LSR) & (1<<5)));
	HWREG(UART0_THR) = c;
}

char getCh(){
	while(!(HWREG(UART0_LSR) & (1<<0)));
	return(HWREG(UART0_RHR));
}

int putString(char *str, unsigned int length){
	for(int i = 0; i < length; i++){
    		putCh(str[i]);
	}
	return(length);
}

int getString(char *buf, unsigned int length){
	for(int i = 0; i < length; i ++){
    		buf[i] = getCh();
   	}
	return(length);
}

void clearBuffer(){
  	while((HWREG(UART0_LSR) & (1<<0))){
    		HWREG(UART0_RHR);
  	}
}
#endif
