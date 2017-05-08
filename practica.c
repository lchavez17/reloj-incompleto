#include <18F4620.h>
#include<stdlib.h>
#USE delay(clock=4000000)        //Configurando el reloj a 32Mhz
#fuses XT, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use RS232(BAUD=9600,BITS=8,PARITY=N,XMIT=PIN_C6,RCV=PIN_C7,STOP=1) 
#use fast_io(a)
#use fast_io(b)
int8 horas=0,minutos=0,segundos=0,cont=0,led=0,delay=0;


#int_TIMER0
void TIMER0_funcion(void)
{
   cont++;
   led++;
   delay++;
}
void main(void)
{
   set_tris_b(0b00000000);
   set_tris_a(0b00001111);
      setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|T0_8_BIT);   //Configuracion de la fuente y divisor del TMR0 <<<<<<Acomodar
      enable_interrupts(int_TIMER0);  //Abilitamos la interrupcion TIMER0
      enable_interrupts(GLOBAL); //Abilitamos las interrupciones globales
      printf("hora: %i",horas);
      printf(" minutos: %i",minutos);
      printf(" segundos:%i\n\n\r\r",segundos);
      while(true)
      {
      if(led==7)
      {
      output_b(0b00000001);
      }if(led==15)
      {
      output_b(0b00000000);
      led=0;
      }
      if(input(PIN_A0))
      {
      delay_ms(20);
      segundos++;
      } 
      if(cont==15)
      {
      printf("\f");
      segundos++;
      printf("hora: %i",horas);
      printf(" minutos: %i",minutos);
      printf(" segundos:%i\n\n\r\r",segundos);
      cont=0;
      }
      if(segundos==59)
      {
      minutos++;
      segundos=0;
      }
      if(minutos==59)
      {
      horas++;
      minutos=0;
      }
      if(horas==23)horas=0;
      }
      //printf("segundos:%i\n\n\r\r\f",segundos);
      //printf("\f");
      //}
      
}
