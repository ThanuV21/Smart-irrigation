#include <lpc21xx.h>
#define lcd_d 0xff
#define rs (1 << 10)
#define e (1 << 11)
#define moisture_pin (1 << 12)   
#define relay_pin (1 << 17)      
#include "lcd.h"

void motor_on(void);
void motor_off(void);

int count=0;

void EINT0_Handler(void) __irq
{
    if ((IOPIN0 & moisture_pin) == 0)
    {
        LCD_command(0xc0);  
        LCD_str("Dry state");
        motor_on();
    }
    else 
    {
        LCD_command(0xc0);
        LCD_str("Wet state");
        motor_off();
    }

    EXTINT = 1;  
    VICVectAddr = 0;  
}

int main()
{
    IODIR0 |= relay_pin;

    LCD_init();
    LCD_scroll("SMART IRRIGATION");
    LCD_command(0x01);  
    LCD_command(0x80);  
    LCD_str("The Condition:");

    PINSEL1 |= 0x01;  
    EXTMODE = 0x01;   
    EXTPOLAR = 0x00; 


    VICIntSelect =0;  
    
	VICVectCntl0= (0x20)|14;
	VICVectAddr0= (int)EINT0_Handler;

    while (1)
    {
        count++;
    }
}

void motor_on(void)
{
    IOSET0 = relay_pin;  
}

void motor_off(void)
{
    IOCLR0 = relay_pin;  
}
