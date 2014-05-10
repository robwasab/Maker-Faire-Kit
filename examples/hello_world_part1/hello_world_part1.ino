#include <LED_Matrix_Kit.h>
/*Including LED_Matrix_Kit imports the 'led_kit' variable*/

/*Here are the things led_kit can do:

You can turn on an LED, given a row and column coordinate, the LED can be on true/false
void turnOn(int row, int col, boolean on)

To see if a button was pressed, you call this function
>boolean buttonPressed(void);

After you check call this, each successive call will return false, unless another button is pressed

To get the last button press call this function
>int buttonRead(void);

UP    1
DOWN  2
RIGHT 3
LEFT  4

This function keeps track of the milliseconds that have passed since the kit powered up:
>long currentTimeMillis();

This function clears the display
>void clear();

*/

int led = 13;

void setup()
{
   //By including LED_Matrix_Kit, you automatically initiallize 
   //All the required pin directions
   //including arduino pin 13
}


void loop()
{
  int row = 0;
  int col = 0;

  //Try blinking the led
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

  //read the buttons
  //which returns the last button press
  int press = led_kit.buttonRead();
    
  col = press;
  
  led_kit.turnOn(row, col, true);
  
  delay(1000);               // wait for a second
  
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  
  //clear the display
  led_kit.clear();
  delay(1000);               // wait for a second


}


