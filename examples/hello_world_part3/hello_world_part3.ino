#include <LED_Matrix_Kit.h>

/*
In this example we add to part 2 and use buttons to 
change the blinking led's position on the matrix

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
         
         //read the buttons
    
         if (led_kit.buttonPressed())
         {
            int button = led_kit.buttonRead();
            int up    = 1;
            int down  = 2;
            int right = 3;
            int left  = 4;
         
            if (button == up)
            {
               //this is how you subtract 1 from row
               row = row - 1; 
            }
           else if (button == down)
           {
              row = row + 1; 
           }
         
           else if (button == right)
           {
              //this is short hand for the above
              col += 1; 
           }

           else if (button == left)
           {
             //this is short hand for the above
             col -= 1; 
           }
         }
         led_kit.turnOn(row, col, led_on_off);  
      }      
   } 
}


