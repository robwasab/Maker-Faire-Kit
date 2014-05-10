#include <LED_Matrix_Kit.h>

//prototype of the function draw
void draw(unsigned char img[8][8]);


//This is an array
unsigned char smile[8][8] =
{
{0,0,0,0,0,0,0,0},
{0,0,1,0,0,1,0,0},
{0,0,1,0,0,1,0,0},
{0,0,1,0,0,1,0,0},
{0,0,0,0,0,0,0,0},
{0,1,0,0,0,0,1,0},
{0,0,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0}
};

void setup()
{
}

boolean led_on_off = true;

void loop()
{
  draw(smile);
}

void draw(unsigned char img[8][8])
{
   int row, col;
   for (row = 0; row < 8; row++) 
   {
      for (col = 0; col < 8; col++)
      {
         if (img[row][col] > 0)
         {
            led_kit.turnOn(row, col, true);
         }
         else
         {
            led_kit.turnOn(row, col, false);
         }
      } 
   } 
}

