#include <LED_Matrix_Kit.h>

   #define SIZE 64
   #define TRUE 1
   #define FALSE 0
   
   int length = 3;

   struct Cord
   {
    int row; 
    int col; 
   };
   
   struct Cord snake[SIZE];
      
   int curr_dir = RIGHT;
   
   void setup() {}
   
   void loop()
   {             
      int x;
         //init the snake to all unused      
      for(x = 0; x < SIZE; x++)
      {
         snake[x].row = -1;
         snake[x].col = -1;
      }
       
      reset();
      
      long draw_time = led_kit.currentTimeMillis();
      
      long blink_time = draw_time;
      
      curr_dir = RIGHT;
            
      Cord food_cord = make_food();
      
      led_kit.turnOn(food_cord.row, food_cord.col, true);
      
      byte show_food = TRUE;
      
      int faster = 500;
      
      while(true)
      {
                  
         if (led_kit.currentTimeMillis() > (draw_time + faster))
         {
            byte gain_weight = FALSE;
            
            if (check_location(food_cord.row, food_cord.col) == TRUE)
            {
               length++;
               food_cord = make_food();   
               
               led_kit.turnOn(food_cord.row, food_cord.col, true);
               
               gain_weight = TRUE;
               
               if (faster > 100)
               {
                  faster -= 50;
               }
            }
            
            draw_time = led_kit.currentTimeMillis();
            
            //poll the buttons
            byte new_dir = led_kit.buttonRead();
            
            if (new_dir > 0)
            {
               int no_update_dir = FALSE;
               
               if (new_dir == LEFT  && curr_dir == RIGHT) no_update_dir = TRUE;
               if (new_dir == RIGHT && curr_dir == LEFT ) no_update_dir = TRUE;
               if (new_dir == UP    && curr_dir == DOWN ) no_update_dir = TRUE;
               if (new_dir == DOWN  && curr_dir == UP   ) no_update_dir = TRUE;
            
               if (no_update_dir != TRUE) curr_dir = new_dir;
            }
            
            int game_over = FALSE;
            
            game_over = move_snake(gain_weight);
            
            if (game_over == TRUE)
            {
               //System.out.println("Game over");
               
               clear();
               reset();
               food_cord = make_food();
               led_kit.turnOn(food_cord.row, food_cord.col, true);
               faster = 500;
            }   
         }

         if (led_kit.currentTimeMillis() > (blink_time + 100))
         {         
            blink_time = led_kit.currentTimeMillis();
            
            show_food ^= TRUE;
            
            if (show_food == TRUE)
            {
               led_kit.turnOn(food_cord.row, food_cord.col, true); 
            }
            else
            {
               led_kit.turnOn(food_cord.row, food_cord.col, false);
            } 
         }
      }
   }   

   struct Cord make_food()
   {
      int flag = 0;
      int i;
      int row;
      int col;
      struct Cord c;   
      do
      {
         row = random_number();
         col = random_number();
         flag = check_location(row, col);
         
      } while(flag == TRUE);
      
      c.row = row;
      c.col = col;
      return c;
   }

   byte check_location(int row, int col)
   {
      int i;
      for (i = 0; i < length; ++i)
      {
         if (snake[i].row == row && snake[i].col == col) 
         {
            return TRUE;
         }                        
      }
      return FALSE;     
   }

   int random_number()
   {  
      return random(8);
   }

   byte move_snake(int gain_weight)
   {
      int i; 
      byte game_over = TRUE;
      byte game_on = FALSE;

      if (gain_weight != TRUE)
      {
      
         //turn off last snake piece location
         led_kit.turnOn(snake[length -1].row, snake[length - 1].col, false);
      }
      
      for (i = length-1; i >= 1; i--)
      {
         snake[i].row = snake[i-1].row;
         snake[i].col = snake[i-1].col;   
         
         led_kit.turnOn(snake[i].row, snake[i].col, true);    
      }
      
      int new_head_row = snake[0].row;
      int new_head_col = snake[0].col;
      
      switch(curr_dir)
      {
         case UP:
         new_head_row -= 1;
         break;
         
         case DOWN:
         new_head_row += 1;
         break;
         
         case LEFT:
         new_head_col -= 1;
         break;
         
         case RIGHT:
         new_head_col += 1;
         break;
      }
                
      if(new_head_col < 0 || new_head_row < 0) return game_over;
  
      if(new_head_col >= 8 || new_head_row >= 8) return game_over;
      
      int hit_itself = check_location(new_head_row, new_head_col);

      if(hit_itself == TRUE) return game_over;

      snake[0].row = new_head_row;
      
      snake[0].col = new_head_col;

      led_kit.turnOn(snake[0].row, snake[0].col, true); 
      
      return game_on;
   } 
   
   void clear()
   {
      int x,y;
      for (x = 0; x < 8; x++)
      {
         for (y = 0; y < 8; y++)
         {
            led_kit.turnOn(x, y, false);
         }
      }
   }
   
   void reset()
   {  
      length = 3;
      //set the first three parts of the snake to its begining position
      snake[0].row = 4;
      snake[0].col = 4;

      snake[1].row = 4;
      snake[1].col = 3;

      snake[2].row = 4;
      snake[2].col = 3;
      
      curr_dir = RIGHT;
   }     
