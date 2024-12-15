#define lcd_d 0xf<<20
#define rs 1 << 17
#define rw 1<<18
#define e 1 << 19


void LCD_command(unsigned char cmd)
{
	IOCLR0=lcd_d;
	IOSET0=(cmd&0XF0)<<16;
	IOCLR0=rs;
	IOSET0=e;
	delay_ms(2);
	IOCLR0=e;

	IOCLR0=lcd_d;
	IOSET0=(cmd&0X0f)<<20;
	IOCLR0=rs;
	IOSET0=e;
	delay_ms(2);
	IOCLR0=e;
}
void LCD_data(unsigned char d)
{
	IOCLR0=lcd_d;
	IOSET0=(d&0XF0)<<16;
	IOSET0=rs;
	IOSET0=e;
	delay_ms(2);
	IOCLR0=e;

	IOCLR0=lcd_d;
	IOSET0=(d&0X0F)<<20;
	IOSET0=rs;
	IOSET0=e;
	delay_ms(2);
	IOCLR0=e;
}
void LCD_init(void)
{
	IODIR0 |= lcd_d|rs|e;
	LCD_command(0x01);
	LCD_command(0x02);
	LCD_command(0x0c);
	LCD_command(0x28);
	LCD_command(0x80);
}
void LCD_str(unsigned char *s)
{
	int i=0;
	for(i=0;s[i];i++)
		LCD_data(s[i]);
		
}

void LCD_scroll(unsigned char *s)
{
	unsigned int i=0x80;
	while(1)
	{
		LCD_command(0x01);
		LCD_command(i++);
		LCD_str(s);
		delay_ms(300);
		if(i==0x91)
		{
			break;
		}
	}
}
