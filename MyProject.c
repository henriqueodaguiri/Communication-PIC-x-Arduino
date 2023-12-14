//********************************************************************************
//
//     PROGRAMA EXEMPLO: Comunicação USART entre PIC 18F e o Arduino.
// OBJETIVO: Aprender a utilizar a comunicação serial assíncrona do PIC18F4520.
//
//********************************************************************************

// --- Ligações entre PIC e LCD ---
sbit LCD_RS at RE2_bit;   // PINO 2 DO PORTD INTERLIGADO AO RS DO DISPLAY
sbit LCD_EN at RE1_bit;   // PINO 3 DO PORTD INTERLIGADO AO EN DO DISPLAY
sbit LCD_D7 at RD7_bit;  // PINO 7 DO PORTD INTERLIGADO AO D7 DO DISPLAY
sbit LCD_D6 at RD6_bit;  // PINO 6 DO PORTD INTERLIGADO AO D6 DO DISPLAY
sbit LCD_D5 at RD5_bit;  // PINO 5 DO PORTD INTERLIGADO AO D5 DO DISPLAY
sbit LCD_D4 at RD4_bit;  // PINO 4 DO PORTD INTERLIGADO AO D4 DO DISPLAY

// Selecionando direção de fluxo de dados dos pinos utilizados para a comunicação com display LCD
sbit LCD_RS_Direction at TRISE2_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 2 DO PORTD
sbit LCD_EN_Direction at TRISE1_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 3 DO PORTD
sbit LCD_D7_Direction at TRISD7_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 7 DO PORTD
sbit LCD_D6_Direction at TRISD6_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 6 DO PORTD
sbit LCD_D5_Direction at TRISD5_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 5 DO PORTD
sbit LCD_D4_Direction at TRISD4_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 4 DO PORTD

char ucRead;        // Variavel para armazenar o dado lido.
unsigned int Control = 0;  // +++++++ VARIAVEL DE CONTROLE DA COMUNICAÇÃO ++++++++
                           // LEMBRE DE ALTERAR ESSA VARIAVE TAMBEM NO ARDUINO

void main(){
     unsigned int number1 = 0;
     unsigned int number2 = 0;
     unsigned int number3 = 0;
     unsigned int number4 = 0;
     unsigned int trava1 = 0;
     unsigned int trava2 = 0;
     unsigned int trava3 = 0;
     unsigned int trava4 = 0;
     unsigned int trava5 = 0;

     TRISB.RB3 = 1;   //definindo a porta RB3 como entrada
     TRISB.RB4 = 1;   //definindo a porta RB4 como entrada
     TRISB.RB5 = 1;   //definindo a porta RB5 como entrada
     TRISA.RA5 = 1;   //definindo a porta RA5 como entrada
     TRISB.RB0 = 1;   //definindo a porta RB0 como entrada
     TRISB.RB7 = 0;   //definindo a porta RB6 como saida

     PORTB.RB3 = 0;   //definindo o estado inicial da porta RB3  como baixo
     PORTB.RB4 = 0;   //definindo o estado inicial da porta RB4   como baixo
     PORTB.RB5 = 0;   //definindo o estado inicial da porta RB5  como baixo
     PORTA.RA5 = 1;   //definindo o estado inicial da porta RA5  como baixo
     PORTB.RB0 = 1;   //definindo o estado inicial da porta RB0  como baixo
     PORTB.RB7 = 0;   //definindo o estado inicial da porta RB6   como baixo

   ADCON1  = 0x0E;                           //Configura os pinos do PORTB como digitais, e RA0 (PORTA) como analógico

   Lcd_Init();                               //Inicializa módulo LCD
   Lcd_Cmd(_LCD_CURSOR_OFF);                 //Apaga cursor
   Lcd_Cmd(_LCD_CLEAR);                      //Limpa display

   UART1_Init(9600);  // Utiliza bibliotecas do compilador para configuração o Baud rate.

   while(1){  // SELECIONE A VARIAVEL DE CONTROLE (CONTROL) DECLARADA ACIMA.
     if((PORTB.RB3==0)&&(trava1==0)){// Incrementa somente uma vez quando a tecla for pressionada.
           number1++;  //incrementa no contador do bot?o b0
           if(number1 == 10)
                       number1 = 0;
           trava1 =1;   //trava para n?o incrementar mais de uma vez
     }
     if((PORTB.RB3==1)&&(trava1==1)){   // Volta a disponibilizar a opcao de incremento quando a tecla for solta.
           trava1=0;
     }

     if((PORTB.RB4==0)&&(trava2==0)){// Incrementa somente uma vez quando a tecla for pressionada.
           number2++;  //incrementa no contador do bot?o b0
           if(number2 == 10)
                       number2 = 0;
           trava2 = 1;   //trava para n?o incrementar mais de uma vez
     }
     if((PORTB.RB4==1)&&(trava2==1)){   // Volta a disponibilizar a opcao de incremento quando a tecla for solta.
           trava2=0;
     }

     if((PORTB.RB5==0)&&(trava3==0)){// Incrementa somente uma vez quando a tecla for pressionada.
           number3++;  //incrementa no contador do bot?o b0
           if(number3 == 10)
                       number3 = 0;
           trava3 =1;   //trava para n?o incrementar mais de uma vez
     }
     if((PORTB.RB5==1)&&(trava3==1)){   // Volta a disponibilizar a opcao de incremento quando a tecla for solta.
           trava3=0;
     }

     if((PORTA.RA5==0)&&(trava4==0)){// Incrementa somente uma vez quando a tecla for pressionada.
           number4++;  //incrementa no contador do bot?o b0
           if(number4 == 10)
                       number4 = 0;
           trava4 = 1;   //trava para n?o incrementar mais de uma vez
     }
     if((PORTA.RA5==1)&&(trava4 == 1)){   // Volta a disponibilizar a opcao de incremento quando a tecla for solta.
           trava4=0;
     }

     if((PORTB.RB0==0)&&(trava5==0)){// Incrementa somente uma vez quando a tecla for pressionada.
           if(number1 == 2 && number2 == 0 && number3 == 2 && number4 == 3){
                UART1_Write('A'); // Transmite o caracter para o Arduino
                number1 = 0;
                number2 = 0;
                number3 = 0;
                number4 = 0;
                lcd_out(1,1,"Senha correta      ");
                lcd_out(2,1,"                    ");
                PORTB.RB7 = 1;
                 Delay_ms(1000);
                 PORTB.RB7 = 0;
                 Delay_ms(1000);
                 PORTB.RB7 = 1;
                 Delay_ms(1000);
                 PORTB.RB7 = 0;
                 Delay_ms(1000);
                 PORTB.RB7 = 1;
                 Delay_ms(1000);
                 PORTB.RB7 = 0;
           }
           else{
                lcd_out(1,1,"Senha errada      ");
                lcd_out(2,1,"                   ");
                Delay_ms(2000);
                UART1_Write('D'); // Transmite o caracter para o Arduino
                number1 = 0;
                number2 = 0;
                number3 = 0;
                number4 = 0;
           }
           trava5 =1;   //trava para n?o incrementar mais de uma vez
     }
     if((PORTB.RB0==1)&&(trava5==1)){   // Volta a disponibilizar a opcao de incremento quando a tecla for solta.
           trava5=0;
     }

     lcd_out(1,1,"Digite a senha:");
     lcd_out(2,1,"**** [RB0]Enviar");
     //lcd_out(2,1,"Send = T");
     Delay_ms(50);

     if (Control == 1){   // O PIC (Control = 0) envia um caracter e o Arduino responde com outro caracter.
       UART1_Write('T'); // Transmite o caracter para o Arduino
       lcd_out(1,1,"PIC Send/Receive");
       lcd_out(2,1,"Send = T");
       Delay_ms(50);
       if(UART1_Data_Ready()){  // Verifica se um dado foi recebido no buffer
         ucRead = UART1_Read(); // Lê o dado recebido do buffer.
         Delay_ms(50);   // Pausa de 50ms.
         if (ucRead == 'S'){
          lcd_out(2,10,"Rec.= ");
          lcd_chr_cp (ucRead);
          }
       }
     }

     if (Control == 1){   // O PIC (Control = 1) recebe um caracter do Arduino e responde com outro caracter.
       if(UART1_Data_Ready()){  // Verifica se um dado foi recebido no buffer
         ucRead = UART1_Read(); // Lê o dado recebido do buffer.
         Delay_ms(50);   // Pausa de 50ms.
         if (ucRead == 'M'){
          lcd_out(1,1,"PIC Receive/Send");
          lcd_out(2,1,"Rec.= ");
          lcd_chr_cp (ucRead);
         }
       UART1_Write('P');
       lcd_out(2,9,"Send = P");
       Delay_ms(50);
       }
     }
   }
}
