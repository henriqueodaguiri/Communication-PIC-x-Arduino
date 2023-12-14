
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

int Control = 0;
//UART1_Init(9600);



void main() {
char input;
int isPressed = 0;
int counter = 0;
int i; //contador de loop qualquer (irrelevante, ignore)
int temperature = 0;  //valor da temperatura lido do sensor LM35 do PIC
char password[4];
UART1_Init(9600);
Lcd_Init();                               //Inicializa módulo LCD
 Lcd_Cmd(_LCD_CURSOR_OFF);                 //Apaga cursor
 Lcd_Cmd(_LCD_CLEAR);
TRISB = 0;      //define portB como saida

TRISD.RD3 = 1;
TRISD.RD2 = 1;
TRISD.RD1 = 1;
TRISD.RD0 = 1;

PORTD.RD3 = 1;
PORTD.RD2 = 1;
PORTD.RD1 = 1;
PORTD.RD0 = 1;


   while(1){
      switch(Control){
         case 0:
         while(1){    // the objective is to stop entering this loop only when user types 4 keys which is password size
         
         if(counter == 4) break;
         
            PORTB.RB2 = 0;  //habilita primeira coluna do teclado

            if(Button(&PORTD,3,50,0) && PORTB.RB2 ==0 && isPressed == 0){ isPressed = 1; while(PORTD.f3 == 0){counter = counter;} input = '3'; counter++; break; }
            if(Button(&PORTD,2,50,0) && PORTB.RB2 ==0 && isPressed == 0){ isPressed = 1; while(PORTD.f2 == 0){counter = counter;} input = '6'; counter++; break; }
            if(Button(&PORTD,1,50,0) && PORTB.RB2 ==0 && isPressed == 0){ isPressed = 1; while(PORTD.f1 == 0){counter = counter;} input = '9'; counter++; break; }

            PORTB.RB2 = 1;
            PORTB.RB1 = 0;  //habilita segunda coluna do teclado

            if(Button(&PORTD,3,50,0) && PORTB.RB1 ==0 && isPressed == 0){ isPressed = 1; while(PORTD.f3 == 0){counter = counter;} input = '2'; counter++; break; }
            if(Button(&PORTD,2,50,0) && PORTB.RB1 ==0 && isPressed == 0){ isPressed = 1; while(PORTD.f2 == 0){counter = counter;} input = '5'; counter++; break; }
            if(Button(&PORTD,1,50,0) && PORTB.RB1 ==0 && isPressed == 0){ isPressed = 1; while(PORTD.f1 == 0){counter = counter;} input = '8'; counter++; break; }
            if(Button(&PORTD,0,50,0) && PORTB.RB1 ==0 && isPressed == 0){ isPressed = 1; while(PORTD.f0 == 0){counter = counter;} input = '0'; counter++; break; }


            PORTB.RB1 = 1;
            PORTB.RB0 = 0;  //habilita terceira coluna do teclado
              if(Button(&PORTD,3,50,0) && PORTB.RB0 ==0 && isPressed == 0){ isPressed = 1; while(PORTD.f3 == 0){counter = counter;} input = '1'; counter++; break; }
              if(Button(&PORTD,2,50,0) && PORTB.RB0 ==0 && isPressed == 0){ isPressed = 1; while(PORTD.f2 == 0){counter = counter;} input = '4'; counter++; break; }
              if(Button(&PORTD,1,50,0) && PORTB.RB0 ==0 && isPressed == 0){ isPressed = 1; while(PORTD.f1 == 0){counter = counter;} input = '7'; counter++; break; }
            PORTB.RB0 = 1;

               }

              if(input == '0' ){Lcd_Out_Cp("0"); }
              if(input == '1' ){Lcd_Out_Cp("1"); }
              if(input == '2' ){Lcd_Out_Cp("2"); }
              if(input == '3' ){Lcd_Out_Cp("3"); }
              if(input == '4' ){Lcd_Out_Cp("4"); }
              if(input == '5' ){Lcd_Out_Cp("5"); }
              if(input == '6' ){Lcd_Out_Cp("6"); }
              if(input == '7' ){Lcd_Out_Cp("7"); }
              if(input == '8' ){Lcd_Out_Cp("8"); }
              if(input == '9' ){Lcd_Out_Cp("9"); }

              password[counter-1] = input;

              isPressed = 0;

              if(counter == 4){ counter = 0; Control = 1;}  //Now that the password was typed, we send it to Arduino.
              
          break;
              
          case 1:       //manda a password para o arduino fazer a verificação
               for(i=0; i<4; i++){
                       UART1_Write(password[i]);
               }
                       Control = 2;
          break;
          
          case 2:
               TRISC.RC2 = 0;  //define o pino da ventoinha ventoinha como saida, isto é CCP1 pode ser usado para mandar um sinal pwm
               PWM1_Init(4000);
          
               ADCON0 = 0b00001001;  //bit 1 is set to 1 manually to start conversion and when conversion finishes it is automatically set to 0
               ADCON1 = 0b00001100;  //seta quais dos pinos receberão dados digitais ou analogicos.
               ADCON2 = 0b10000000;  //justificado á direita para usarmos apenas o ADRESL
               TRISA.RA2 = 1; //AN2 é entrada pois recebe a temperatura do sensor LM35
               
               while(1){
                  ADCON0 = 0b00001011;
                  while(ADCON0 == 0b00001011);
                  temperature = ADRES ;
                  
                  //if(temperature > 200){  //se a temperatura passa de um threshold arbitrario entao a ventoinha roda conforme a regra abaixo estabelecida, considerando que o valor da temperatura varia de 0 a 1024 apos a conversao com resolucao de 10 bits.
                     PWM1_Set_Duty((temperature/1024)*255);
                     PWM1_Start();
                     Delay_ms(500);
                     PWM1_Stop();
                  //}
               }

               
          break;
          
        }

      }





}
