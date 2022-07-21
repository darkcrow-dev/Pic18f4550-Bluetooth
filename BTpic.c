#include <BTpic.h>
#include <string.h>

#use delay(clock=8000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

char dato = 0;
long bandera = 0;

void accion();

#int_RDA
void  RDA_isr() 
{
   dato = getc();
   
   bandera = 1;   
}

void main()
{
   set_tris_B(0b00000000);
   output_low(PIN_B0);
   
   setup_adc_ports(AN0|VSS_VDD);
   setup_adc(ADC_OFF);

   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   setup_oscillator(OSC_8MHZ|OSC_INTRC|OSC_31250|OSC_PLL_OFF);

   // TODO: USER CODE!!
   
   while(TRUE)
   {
      accion();
   }
}

void accion()
{
      if(bandera == 1)
      {
      switch(dato)
        {
         case '1':   //Si le llega el dato 1 entonces se prende el led de b0
         output_high(PIN_B0);
         bandera = 0;
         break;
   
         case '2':   //Si le llega el dato 2 entonces se apaga el led de b0
         output_low(PIN_B0);
         bandera = 0;
         break;
         
         default:
         bandera = 0;
        }
      }
}
