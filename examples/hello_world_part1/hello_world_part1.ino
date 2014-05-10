#include <LED_Matrix_Kit.h>
/*Including LED_Matrix_Kit imports the 'led_kit' variable*/

/*Here are the things led_kit can do:*/

//You can turn on an LED, given a row and column coordinate, the LED can be on true/false
//void turnOn(int row, int col, boolean on)

//To see if a button was pressed, you call this function
//boolean buttonPressed(void);
//After you check call this, each successive call will return false, unless another button is pressed

//To get the last button press call this function
//int buttonRead(void);
/*
UP    1
DOWN  2
RIGHT 3
LEFT  4

In fact they are #defined inside LED_Matrix_Kit.h
*/

//This function keeps track of the milliseconds that have passed since the kit powered up:
//long currentTimeMillis();





