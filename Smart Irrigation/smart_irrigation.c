#include<LPC21xx.H>
#include "gsm.h"
#include "LCD2.H"

#define moisture_pin 1<<22
#define relay_pin 1<<20


#define dry 0
#define wet 1
int previous_state;
int current_state;
unsigned int count=0;
unsigned int sms_count=0;
void motor_on(void)
{
	IOCLR0=relay_pin;
}
void motor_off(void)
{
	IOSET0=relay_pin;
}
int main()
{
	LCD_init();	
	IODIR0|=relay_pin;
	IOSET0=relay_pin;
	LCD_scroll("Smart Irrigation");
	LCD_command(0x01);
	LCD_command(0x80);
	LCD_str("The condition:");
																																								
	while(1)
	{
			if(((IOPIN0>>22)&1)==0)
			{
			motor_off();
            LCD_command(0xc0);
            LCD_str("Sms Sent");
            delay_ms(1000);
            LCD_command(0x01);
            LCD_command(0x80);
            LCD_str("The condition:");
            LCD_command(0xc0);
            LCD_str("Wet Condition");
            delay_ms(2000);
            LCD_command(0x01);
		
					sms_wet();

			}
			else
			{
				motor_on();
				LCD_command(0xc0);
				LCD_str("Sms Sent");
				delay_ms(1000);
				LCD_command(0xc0);
				LCD_str("Dry Condition");
				delay_ms(2000);
            	LCD_command(0x01);
				
					sms_dry();
				
			}
			count++;
			delay_ms(1000);
	}
}
