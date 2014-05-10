#include <LED_Matrix_Kit.h>

/*
In this example we demonstrate an alternative way of delaying,
using:

long current_time = led_kit.currentTimeMillis();

*/

int led = 13;

void setup()
{
}

int row = 0;
int col = 0;

boolean led_on_off = true;

void loop()
{
   long half_second = led_kit.currentTimeMillis() + 500;
   long one_second = led_kit.currentTimeMillis() + 1000;
   while(1)  //loop 
   {
      if (led_kit.currentTimeMillis() > half_second)
      {
         //if one second has passed..
         //update one_second variable
         half_second = led_kit.currentTimeMillis() + 500;
         
         //blink an LED
         led_kit.invertLED();
      }
      
      if (led_kit.currentTimeMillis() > one_second)
      {
         one_second = led_kit.currentTimeMillis() + 1000;
         if (led_on_off == true) { led_on_off = false; }
         else                    { led_on_off = true;  }
         
         led_kit.turnOn(row, col, led_on_off);  
      }
   } 
}


