//Alunos Victor Thales  - Gustavo Scheffer - ENGENHARIA DA COMPUTAÇÃO
#include "delay.h"
#include "lcd_1602.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <dig_in.h>
#include "dig_out.h"

char writeValue[16];
int bt_inc,bt_dec,bt_menu,bt_ciclo;
int aux_up=0,aux_dwn=0,aux_enter,aux_up1=0,aux_dwn1=0,aux_up2=0,aux_dwn2=0;
int tela=0;
int agua=1,racao=3,ciclo=2, condCiclo=1;

void trocatela(int menu )
{
	switch (menu)
	{
		case 0:

			    LCD_gotoxy(0,1);
				LCD_write("   DOG FEEDER   ");
				LCD_gotoxy(0,2);
				LCD_write("      V1.0 ");
				break;
		case 1:
			    LCD_gotoxy(0,1);
				LCD_write("   Tempo Agua   ");
				LCD_gotoxy(0,2);
				sprintf(writeValue,"      %02u    ",agua);
				LCD_write(writeValue);
				tela=1;
				break;
		case 2: LCD_gotoxy(0,1);
				LCD_write("   Tempo Racao   ");
				LCD_gotoxy(0,2);
				sprintf(writeValue,"      %02u    ",racao);
				LCD_write(writeValue);
				break;
		case 3: LCD_gotoxy(0,1);
				LCD_write(" Interv de ciclo");
				LCD_gotoxy(0,2);
				sprintf(writeValue,"      %02u    ",ciclo);
				LCD_write(writeValue);
				break;
		case 4: LCD_gotoxy(0,1);
				LCD_write(" Ciclo Ligado...");
			    break;
	}

}

int main(void)
{
	//Executa a inicialização do microcontrolador
	SystemInit();

	//Executa a inicialização das funções de atraso
	DELAY_Init();

	//Executa a inicialização da biblioteca dig_in
	dig_in_Init();


	dig_out_Init();


	//Executa a inicialização do display LCD
	LCD_init();

	//Deixa apenas o display ligado, desliga cursor
	LCD_sendCMD(LCD_ON);
	LCD_sendCMD(CLEAR_LCD);
	Delayms(100);
	trocatela(0);
	Delayms(2000);
	trocatela(1);


	while (1)
	{
		//leitura das entradas digitais
		bt_inc 	 = !dig_in_Read(SW1);
		bt_dec 	 = !dig_in_Read(SW2);
		bt_menu = !dig_in_Read(SW3);
		bt_ciclo = !dig_in_Read(SW4);


		//troca do menu
		if (bt_menu==1 && aux_enter==0)
		{
			aux_enter=1;
			++tela;
			if (tela>3)
				tela=1;
			Delayms(300);
		}
		else if (bt_menu==0)
			aux_enter=0;

		//incrementa a variavel agua se for menor que 3
				if (bt_inc==1 && aux_up==0)
				{
					if (tela==1 && agua<3)
						++agua;
					aux_up=1;
					Delayms(100);
					trocatela(tela);
				}
				else if (bt_inc==0)
					aux_up=0;

				//decrementa as variavel agua se for maior que 1
				if (bt_dec==1 && aux_dwn==0)
				{
					if (tela==1 && agua>1)
						--agua;
					aux_dwn=1;
					Delayms(100);
					trocatela(tela);
				}
				else if (bt_dec==0)
					aux_dwn=0;

				//incrementa a variavel racao se for menor que 8
						if (bt_inc==1 && aux_up1==0)
						{
							if (tela==2 && racao<8)
								++racao;
							aux_up1=1;
							Delayms(100);
							trocatela(tela);
						}
						else if (bt_inc==0)
							aux_up1=0;

						//decrementa as variavel racao se for maior que 3
						if (bt_dec==1 && aux_dwn1==0)
						{
							if (tela==2 && racao>3)
								--racao;
							aux_dwn1=1;
							Delayms(100);
							trocatela(tela);
						}
						else if (bt_dec==0)
							aux_dwn1=0;

						//incrementa a variavel ciclo se for menor que 10
								if (bt_inc==1 && aux_up2==0)
								{
									if (tela==3 && ciclo<10)
										++ciclo;
									aux_up2=1;
									Delayms(100);
									trocatela(tela);
								}
								else if (bt_inc==0)
									aux_up2=0;

								//decrementa as variavel ciclo se for maior que 2
								if (bt_dec==1 && aux_dwn2==0)
								{
									if (tela==3 && ciclo>2)
										--ciclo;
									aux_dwn=1;
									Delayms(100);
									trocatela(tela);
								}
								else if (bt_dec==0)
									aux_dwn2=0;


							   //para iniciar o ciclo
								if(bt_ciclo == 1){
									LCD_sendCMD(CLEAR_LCD);
									condCiclo=0;
									trocatela(4);
									dig_out_Write(LED5, OUT_HI);
									Delayms(agua*1000);
									dig_out_Write(LED5, OUT_LO);
									dig_out_Write(LED6, OUT_HI);
									Delayms(racao*1000);
									dig_out_Write(LED6, OUT_LO);
									dig_out_Write(LED7, OUT_HI);
									Delayms(ciclo*1000);
									dig_out_Write(LED7, OUT_LO);

								}

								if(bt_ciclo==0 && condCiclo==0)
									trocatela(1);
       if(bt_ciclo==0){
		trocatela(tela);
		condCiclo =1;

	}
 }
}
