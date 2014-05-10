#include <LED_Matrix_Kit.h>

//prototype of the function draw
void draw(unsigned char img[][8]);
boolean check_row(unsigned char row[]);
boolean check_col(unsigned char col[]);
void move_down(unsigned char img[][8]);
void move_up(unsigned char img[][8]);
void move_left(unsigned char img[][8]);
void move_right(unsigned char img[][8]);


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
  if (led_kit.buttonPressed())
  {
     int dir = led_kit.buttonRead();
     shift_array(smile, dir); 
  }
}

void shift_array(unsigned char img[][8], int dir)
{
   //This time use #defines declared inside 
   //LED_Matrix_Kit
   int row, col;
   switch(dir)
   {
     case UP:
        move_up(img);
        break;
        
     case DOWN:
        move_down(img);
        break;
     case RIGHT:
        move_right(img);
        break;
     case LEFT:
        move_left(img);
        break;
   }
}

void move_up(unsigned char img[][8])
{
   int row, col;
   if (check_row(img[0])) return;
        
   for (row = 0; row < 7; row++)
   {
      for (col = 0; col < 8; col++)
      {
         img[row][col] = img[row + 1][col]; 
      }
    }
    for (col = 0; col < 7; col++) img[7][col] = 0;
}

void move_down(unsigned char img[][8])
{
   int row, col;
   if (check_row(img[7])) return;
        
   for (row = 7; row > 0; row--)
   {
      for (col = 0; col < 8; col++)
      {
         img[row][col] = img[row - 1][col]; 
      }
    }
    for (col = 0; col < 7; col++) img[0][col] = 0;
}

void move_right(unsigned char img[][8])
{
   int row, col;
   if (check_col(img, 7)) return;
   
   for (row = 0; row < 8; row++)
   {
      for (col = 7; col > 0; col--)
      {
         img[row][col] = img[row][col-1];
      } 
      img[row][0] = 0;
   }
}

void move_left(unsigned char img[][8])
{
   int row, col;
   if (check_col(img, 0)) return;
   
   for (row = 0; row < 8; row++)
   {
      for (col = 0; col < 8; col++)
      {
         img[row][col] = img[row][col+1];
      } 
      img[row][7] = 0;
   }
}


boolean check_col(unsigned char img[][8], int col)
{
   int row;
   for (row = 0; row < 8; row++)
   {
      if (img[row][col]) return true; 
   }
   return false;
}

boolean check_row(unsigned char row[])
{
   int i;
   for (i = 0; i < 8; i++)
   {
      if (row[i]) return true;
   }
   return false;
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

