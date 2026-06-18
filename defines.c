#include <LPC21xx.h>
#include <stdio.h>
#include "hw_config.h"
#include "system.h"
unsigned int row_pins[4] = {(1<<8), (1<<9), (1<<10), (1<<11)};    
unsigned int col_pins[4] = {(1<<12), (1<<13), (1<<14), (1<<15)};  

char keymap[4][4] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'C', '0', '=', '+'}
};
void delay_ms(unsigned int ms)
	{
    unsigned int i, j;           
    for (i = 0; i < ms; i++) 
		{
        for (j = 0; j < 3000; j++); 
    }
}
void delay_sec(unsigned int sec)
	{
    unsigned int i;
    for(i = 0; i < sec; i++) 
		{
        delay_ms(1000); 
    }
}

void LCD_INIT(void) {
    IODIR0 |= RS | EN | LCD_DB;      
    delay_ms(100);                    
    LCD_CMD(0x38);                                        
    LCD_CMD(0x0C);                    
    LCD_CMD(0x06);                    
    LCD_CMD(0x01);                    
    delay_ms(10);
}

void LCD_CMD(unsigned char cmd) {
    IOCLR0 = RS;                      
    IOCLR0 = LCD_DB;                  
    IOSET0 = ((unsigned int)cmd << 18);  
    IOSET0 = EN;
    delay_ms(5); 
    IOCLR0 = EN;
    delay_ms(5); 
}

void LCD_DATA(unsigned char data) {
    IOSET0 = RS;                      
    IOCLR0 = LCD_DB;                  
    IOSET0 = ((unsigned int)data << 18); 
    IOSET0 = EN;
    delay_ms(5); 
    IOCLR0 = EN;
    delay_ms(5); 
}

void LCD_STR(char *str) {
    while(*str != '\0') {
        LCD_DATA(*str);
        str++;
    }
}


void I2C_INIT(void) {
    I2SCLH   = 300;           
    I2SCLL   = 300;           
    I2CONSET = 0x40;         
    I2CONCLR = 0x2C;
}

void I2C_Start(void) {
    I2CONSET = 0x20;             
    while (!(I2CONSET & 0x08));  
    I2CONCLR = 0x20;            
}

void I2C_Write(unsigned char data) {
    I2DAT = data;               
    I2CONCLR = 0x08;            
    while (!(I2CONSET & 0x08));  
}

void I2C_Stop(void) {
    unsigned int i, j;                   

    I2CONSET = 0x10;             
    I2CONCLR = 0x08;            
    while (I2CONSET & 0x10); 
    for(i=0; i<10; i++) 
	  {        
        for(j=0; j<1000; j++);  
    }
}
unsigned char I2C_Read(unsigned char ack) {
    if(ack) I2CONSET = 0x04;     
    else I2CONCLR = 0x04;     
    I2CONCLR = 0x08;
    while(!(I2CONSET & 0x08));
    return I2DAT;
}
void EEPROM_Write_Byte(unsigned char mem_address, unsigned char data) {
    I2C_Start();
    I2C_Write(0xA0);             
    I2C_Write(mem_address);      
    I2C_Write(data);           
    I2C_Stop();                  
}
unsigned char EEPROM_Read(unsigned char addr) 
	{
    unsigned char data;
    I2C_Start();
    I2C_Write(0xA0);         
    I2C_Write(addr);         
    I2C_Start();             
    I2C_Write(0xA1);         
    data = I2C_Read(0);      
    I2C_Stop();
    return data;
}
void EEPROM_StorePassword(void)
	{
    EEPROM_Write_Byte(0, '1');
    EEPROM_Write_Byte(1, '2');
    EEPROM_Write_Byte(2, '3');
    EEPROM_Write_Byte(3, '4');
}
unsigned char Check_Password(char *entered) 
	{
    unsigned char i;
    for(i = 0; i < PASS_LEN; i++) {
        if(EEPROM_Read(i) != entered[i]) return 0;        
    }
    return 1;
 }
void Keypad_Init(void) 
	{
    
    IODIR0 |=  ((1<<8)|(1<<9)|(1<<10)|(1<<11));     
    IODIR0 &= ~((1<<12)|(1<<13)|(1<<14)|(1<<15));   
    IOSET0  =  ((1<<8)|(1<<9)|(1<<10)|(1<<11));    
}

char GetKey(void) 
	{
    unsigned char r, c;
    while(1) {
        for(r = 0; r < 4; r++) {
           
            IOSET0 = ((1<<8)|(1<<9)|(1<<10)|(1<<11)); 
            IOCLR0 = row_pins[r];           
            delay_ms(2);                   
            
            for(c = 0; c < 4; c++) {
                if(!(IOPIN0 & col_pins[c])) {
                    delay_ms(30);           
                    if(!(IOPIN0 & col_pins[c])) {
                        while(!(IOPIN0 & col_pins[c])) {
                            delay_ms(5); 
                        }
                        return keymap[r][c];
                    }
                }
            }
        }
        delay_ms(5);
    }
}

void GetPassword(char *buf) {
    unsigned char i = 0;
    char k;
    while(i < PASS_LEN) {
        k = GetKey();
        if(k >= '0' && k <= '9') {
            buf[i] = k;
            LCD_DATA(k); 
            i++;
        }
    }
    buf[PASS_LEN] = '\0';
}

void GetOTP(char *buf) {
    unsigned char i = 0;
    char k;
    while(i < PASS_LEN) {
        k = GetKey();
        if(k >= '0' && k <= '9') {
            buf[i] = k;
            LCD_DATA(k);         
            i++;
        }
    }
    buf[PASS_LEN] = '\0';
}

void UART0_INIT(void)
	{
    U0LCR   = 0x83;          
    U0DLL   = 97;            
    U0DLM   = 0;
    U0LCR   = 0x03;          
    U0FCR   = 0x07;
  }

void UART0_TX(unsigned char ch) 
	{
    while((U0LSR & (1<<5)) == 0);   
    U0THR = ch;
  }

void UART0_STR(char *str)
	{
    while(*str != '\0') {
        UART0_TX(*str);
        str++;
    }
  }

unsigned char UART0_RX(void) {
    while((U0LSR & 1) == 0);        
    return U0RBR;
}

void GSM_SendOTP(unsigned int otp) 
	{
    char msg[50];
    sprintf(msg, "Your OTP is: OTP:%04u\r\n", otp);
    UART0_STR("AT+CMGF=1\r\n");
    delay_ms(500);
    UART0_STR("AT+CMGS=\"+918888888888\"\r\n"); 
    delay_ms(500);
    UART0_STR(msg);
    UART0_TX(0x1A);
    delay_ms(500);
}

void GSM_SendBreach(void)
	{
		while(1)
		{
    UART0_STR("\r\n!!! ACCESS DENIED!!!\r\n");
    UART0_STR("Wrong password entered 3 times!\r\n");
		}
  }
	
void GSM_Init(void)
	{
    delay_ms(500);               
    UART0_STR("AT\r\n");
    delay_ms(500);
    UART0_STR("ATE0\r\n");
    delay_ms(500);
    UART0_STR("AT+CPIN?\r\n");
    delay_ms(500);
    UART0_STR("AT+CREG?\r\n");
    delay_ms(500);
    UART0_STR("AT+CMGF=1\r\n");
    delay_ms(500);
}