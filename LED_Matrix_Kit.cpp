#include "LED_Matrix_Kit.h"
#include <stdint.h>

//Button Defines

#define UP_DIR  DDRD
#define UP_IN   PIND
#define UP_PORT PORTD
#define UP_PIN  (1 << 7)

#define DOWN_DIR  DDRB
#define DOWN_IN   PINB 
#define DOWN_PORT PORTB
#define DOWN_PIN (1 << 0)

#define RIGHT_DIR  DDRB
#define RIGHT_IN   PINB
#define RIGHT_PORT PORTB
#define RIGHT_PIN  (1 << 2)

#define LEFT_DIR  DDRB
#define LEFT_IN   PINB
#define LEFT_PORT PORTB
#define LEFT_PIN   (1 << 3)

//Shift Register Defines

#define SH_CP_PORT PORTD
#define SH_CP_DDR  DDRD
#define SH_CP_PIN  4 //Shift register clock pulse

#define ST_CP_PORT PORTD  //Storage register clock pulse
#define ST_CP_DDR  DDRD
#define ST_CP_PIN  5

#define DIN_PORT PORTD   //Data
#define DIN_DDR  DDRD
#define DIN_PIN  6

#define X_OE 1
#define X_OE_PORT PORTB
#define X_OE_DDR DDRB


void HC595_init(void);
void HC595_write(uint8_t byte);

volatile long ms_elapsed = 0;
LED_Matrix_Kit led_kit;


LED_Matrix_Kit::LED_Matrix_Kit()
{        
    //set these to outputs
    //This is the indicator LED
    LED_DIR |= LED;
    
    //These are columns 0-5
    DDRC |= 0x3f;
    DDRD |= (1 << 2) | (1 << 3);
    
    //the rows are controlled by a shift register
    //All 8 of them
    //init the shift register
    HC595_init();

    UP_DIR    &= ~UP_PIN;
    DOWN_DIR  &= ~DOWN_PIN;
    RIGHT_DIR &= ~RIGHT;
    LEFT_DIR  &= ~LEFT_PIN;
    
    //enable pull up resistors
    UP_PORT    |= UP_PIN;
    DOWN_PORT  |= DOWN_PIN;
    RIGHT_PORT |= RIGHT_PIN;
    LEFT_PORT  |= LEFT_PIN;

    
    //Enable the Pin Change Interrupts
    //Enable Vector 0 and 2
    PCICR |= (1 << PCIE2) | (1 << PCIE0);
    
    //Corresponds to UP
    PCMSK2 |= (1 << PCINT23);
    
    PCMSK0 |= (1 << PCINT0) | (1 << PCINT2) | (1 << PCINT3);
    
    //configure Timer1
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS10);
    OCR1A = 16000-1;
    TIMSK1 = (1 << OCIE1A);
    sei();
}

ISR(TIMER1_COMPA_vect)
{
   ms_elapsed++;   
   
   static uint8_t count = 0;
   ++ count;
   if (count > 10) { count = 0; led_kit.draw(); }
}


long LED_Matrix_Kit::currentTimeMillis()
{
   return ms_elapsed;
}


volatile int last_button = 0;
volatile boolean button_pressed = false;

ISR(PCINT0_vect)
{
   uint8_t in = PINB;
   
   delay(10);
   
   in &= (DOWN_PIN | RIGHT_PIN | LEFT_PIN);
   
   //make it simple
   if (!(in & DOWN_PIN)) 
   {
      last_button   = DOWN;
      button_pressed = true;
      return;
   }
   if (!(in & RIGHT_PIN))
   {
      last_button   = RIGHT;
      button_pressed = true;
      return;
   }
   if (!(in & LEFT_PIN))
   {
      last_button   = LEFT;
      button_pressed = true;
      return;
   }
}

ISR(PCINT2_vect)
{
   delay(10);
   if (!(UP_IN & UP_PIN))
   { 
      last_button = UP;
      button_pressed = true;
   }
}

void LED_Matrix_Kit::turnOn(int row, int col, boolean on)
{   
   cli();
   if (row > 7 || col > 7 ) return;
   
   if (on)
   {
      rows[col] |= (1 << row);
   }
   else
   {
      rows[col] &= ~(1 << row);
   }
   sei();
}


void LED_Matrix_Kit::draw()
{
   uint8_t i,j;
   uint8_t data;
   
   for (i = 0; i < 8; ++i)
   {
      write_column(~(1 << i));
      
      for (j = 0; j < 8; ++j)
      {
         data = (1 << j) & rows[i];
         if (data)
         {
            write_row(data);
            delayMicroseconds(100);
         }
      }
      write_row(0);
   }
}

void LED_Matrix_Kit::clear()
{
   uint8_t i;
   
   for (i = 0; i < 8; ++i)
   {
      rows[i] = 0;
   }
}

boolean LED_Matrix_Kit::buttonPressed(void)
{
   boolean temp = button_pressed;
   button_pressed = false;
   return temp;
}

int LED_Matrix_Kit::buttonRead()
{
   return last_button;
}

void inline LED_Matrix_Kit::write_row(uint8_t row)
{
   HC595_write(row);
}

void LED_Matrix_Kit::write_column(uint8_t col)
{
   PORTC &= ~0x3f;
   PORTC |= 0x3f & col;
   PORTD &= ~((1 << 2) | (1 << 3));
   PORTD |= ((1 << 2) | (1 << 3) ) & (col >> 4);
}

void HC595_init(void)
{
   DIN_DDR   |= (1 << DIN_PIN);
   SH_CP_DDR |= (1 << SH_CP_PIN);
   ST_CP_DDR |= (1 << ST_CP_PIN);
   X_OE_DDR  |= (1 << X_OE);
   
   X_OE_PORT &= ~(1 << X_OE);
}

void HC595_write(uint8_t byte) 
{
   char i;
   for (i = 7; i >= 0; --i) {
      if ( byte & (1 << i) ) DIN_PORT |=  (1 << DIN_PIN);
      else                   DIN_PORT &= ~(1 << DIN_PIN);
      SH_CP_PORT |=  (1 << SH_CP_PIN);
      SH_CP_PORT &=  ~(1 << SH_CP_PIN);
   }
   ST_CP_PORT |= (1 << ST_CP_PIN); 
   ST_CP_PORT &= ~(1 << ST_CP_PIN); 
}

void LED_Matrix_Kit::invertLED()
{
   LED_PORT ^= LED;
}
