#ifndef SYSTEM_H
#define SYSTEM_H
void delay_ms(unsigned int ms);
void delay_sec(unsigned int sec);

void LCD_INIT(void);
void LCD_CMD(unsigned char cmd);
void LCD_DATA(unsigned char data);
void LCD_STR(char *str);

void I2C_INIT(void);
void EEPROM_Write_Byte(unsigned char addr, unsigned char data);
unsigned char EEPROM_Read(unsigned char addr);
void EEPROM_StorePassword(void);
unsigned char Check_Password(char *entered);

void Keypad_Init(void);
char GetKey(void);
void GetPassword(char *buf);
void GetOTP(char *buf);

void UART0_INIT(void);
void UART0_TX(unsigned char ch);
void UART0_STR(char *str);
unsigned char UART0_RX(void);
void GSM_Init(void);
void GSM_SendOTP(unsigned int otp);
void GSM_SendBreach(void);
#endif
