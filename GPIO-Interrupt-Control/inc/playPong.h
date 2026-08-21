#ifndef PLAYPONG_H
#define PLAYPONG_H

#include "bbb_regs.h"
#include "hw_types.h"
#include "putString.h"
#include "delay.h"
#include "ledConfig.h"

void positionCurrent(int position);
void speed();
void gameOver(int player);
void win(int vencedor);

int sequence[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9};
//int sequenceWin[] = {LED1, LED3, LED5, LED7, LED9, LED2, LED4, LED6, LED8};
unsigned int contDelay = 500;

int player1 = 0, player2 = 0, ball_position, ball_direction; 

void speed(){
    if(contDelay >= 100){
        contDelay -= 50;
    }
}

void playPong() {
	while(1){
		ball_position += ball_direction;      
		if (ball_position == 1) {
		    if (flag_gpio1) {
		    	speed();
		        ball_direction = 1;  
		        flag_gpio1 = false; 
		    } else {
		        if (player2 == 4 && player1 < 4) {
		            win(2);
		        } else {
		            gameOver(1);  
		        }
		    }
		}

		if (ball_position == 9) {
		    if (flag_gpio2) {
		    	speed();
		        ball_direction = -1;  
		        flag_gpio2 = false;   
		    } else {
		        if (player1 == 4 && player2 < 4) {
		            win(1);  
		        } else {
		            gameOver(2);
		        }
		    }
		}
	 	//flag_gpio1 = false;     
	    	//flag_gpio2 = false;
	 	//putString("a\r\n", 5);
		positionCurrent(ball_position);
		delay(contDelay);
        }
}

void positionCurrent(int position) {
    clear_leds(sequence, LEDS);
	ledOn(position);
}

void gameOver(int player) {
    if (player == 1) {
    	putString("Jogador 1 perdeu!\r\n", 18);
        player2++;
        //delay(700);
        //set_leds(sequence, player1);
        //delay(400);
        ball_position = 10;   
        ball_direction = -1;  
        contDelay = 600;
    } else if (player == 2) {
    	putString("Jogador 2 perdeu!\r\n", 18);
        player1++;
        ball_position = 0;   
        ball_direction = 1;
        contDelay = 600;
        //delay(700);  
        //set_leds(sequence, player2);
        //delay(400);
    }
    while(!(flag_gpio1 || flag_gpio2));
    
    if(player1 == 4 || player2 == 4){
    	win(player = 1 ? 2 : 1);
    } 

    //speed();  
}

void win(int vencedor) {
    if (vencedor == 1) {
        putString("Jogador 1 venceu!\r\n", 18);
        ball_position = 0;   
    	ball_direction = 1; 
    } else {
        putString("Jogador 2 venceu!\r\n", 18);
        ball_position = 10;   
    	ball_direction = -1; 
    }
    while(!(flag_gpio1 || flag_gpio2));
    //set_leds(sequence, LEDS);

    flag_gpio1 = false;     
    flag_gpio2 = false;         
    contDelay = 600;
    player1 = 0;
    player2 = 0;
}

#endif
