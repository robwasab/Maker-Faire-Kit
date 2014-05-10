#ifndef LED_MATRIX_KIT_H
#define LED_MATRIX_KIT_H

#include "Arduino.h"
#define LED_PORT PORTB
#define LED (1 << 5)
#define LED_DIR DDRB

#define UP    1
#define DOWN  2
#define RIGHT 3
#define LEFT  4

class LED_Matrix_Kit
{
   public:
      LED_Matrix_Kit(void);
      void turnOn(int row, int col, boolean on);
      int buttonRead(void);
      boolean buttonPressed(void);
      long currentTimeMillis();
      void draw(void);
      void clear();
      void invertLED();
      
   private:
      void write_row(uint8_t row);
      void write_column(uint8_t col);
      unsigned char rows[8];
};

extern LED_Matrix_Kit led_kit;


#endif
