#include<LPC21xx.H>
#include "gsm.h"
//#include "lcd.h"
#include "LCD2.H"

#define moisture_pin 1<<22
#define relay_pin 1<<20
unsigned int msg_sent=0;
int previous_state;
int current_state;
unsigned int count=0;
unsigned int sms_count=0;
void condition_isr(void) __irq
{
	EXTINT=0x01;
	if(((IOPIN0>>12)&1)==0)
	{
		msg_sent=0;
	}
	else
	{
		msg_sent=0;
	}
	VICVectAddr=0;
}
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
	PINSEL0|=0x20000000;
	VICIntSelect=0;
	VICVectCntl0=(0x20)|15;
	VICVectAddr0=(int)condition_isr;
	EXTMODE=0x01;
	EXTPOLAR=0x00;
	VICIntEnable=(1<<15);
																																								
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
				if(!msg_sent)
				{
					sms_wet();
					msg_sent=1;
				}
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
				if(!msg_sent)
				{
					sms_dry();
					msg_sent=1;
				}
			}
			delay_ms(1000);
	}
}
