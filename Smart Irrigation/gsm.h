void delay_ms(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR = 0x01;
	while(T0TC<ms);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void uart1_config(void)
{
	PINSEL0|=0x00000005;
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0x03;
}

void uart1_tx(unsigned char ch)
{	
	U0THR = ch;
	while((U0LSR>>5&1)==0); 
}
void uart1_str(unsigned char*s)
{
	while(*s)
	uart1_tx(*s++);
}
void sms_dry(void)
{
	uart1_config();
	uart1_str("AT\r\n");
	delay_ms(500);

	uart1_str("AT+CMGF=1\r\n");
	delay_ms(500);

	uart1_str("AT+CMGS=\"+919514346342\"\r\n");
	delay_ms(500);

	uart1_str("Dry state,motor on\r\n");
	//delay_ms(500);
	uart1_tx(0x1A);
}
void sms_wet(void)
{
	uart1_config();
	uart1_str("AT\r\n");
	delay_ms(500);

	uart1_str("AT+CMGF=1\r\n");
	delay_ms(500);

	uart1_str("AT+CMGS=\"+919514346342\"\r\n");
	delay_ms(500);

	uart1_str("Wet state,motor off\r\n");
	uart1_tx(0x0A);
}
