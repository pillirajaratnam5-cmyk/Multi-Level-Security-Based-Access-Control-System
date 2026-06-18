#include <LPC21xx.h>
#include <string.h>
#include <stdio.h>
#include "hw_config.h"
#include "system.h"
int main() 
	{
    char pass[PASS_LEN + 1];        
    char otp_in[PASS_LEN + 1];      
    char otp_str[PASS_LEN + 1];     
    unsigned int otp_num;           
    unsigned char pass_try = 0;     
    unsigned char otp_try  = 0;     
    unsigned char b; 
    unsigned int i;	
   
    VPBDIV = 0x00;                  
    T0PR  = 0;
    T0TCR = 0x01; 
    
    PINSEL0 |= 0x00000055;
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;		
    IODIR0 |= LED|LED2| MOTOR_IN1 | ALL_ROWS;
    IODIR0 |= ~ALL_COLS;   
    IODIR0 &= ~SWITCH; 
    IODIR1 |= MOTOR_IN2;

    IOCLR0 = LED|LED2| MOTOR_IN1;
    IOCLR1 = MOTOR_IN2;
    IOSET0 = ALL_ROWS; 

    UART0_INIT();
    I2C_INIT();
    LCD_INIT();
    Keypad_Init();
    
    UART0_STR("\r\nDefault Password : 1234\r\n");
    GSM_Init(); 

    IOCLR0 = ROW3; 
    delay_ms(10);
			
    EEPROM_StorePassword();
    UART0_STR("Password 1234 saved to EEPROM!\r\n");
    delay_sec(2);
     
    IOSET0 = ROW3; 

    LCD_CMD(0x01); 
    LCD_CMD(0x80); 
    
   LCD_CMD(0x01); 
    LCD_CMD(0x80); 
   
    LCD_STR("Multilevel Security Based Control System");
    delay_ms(700); 
   
    for(i = 0; i < 40; i++) {
        LCD_CMD(0x18);   
        delay_ms(300);   
    }
    while(1)
			{
        pass_try = 0;   
        while(1) 
					{
            LCD_CMD(0x01);
            LCD_CMD(0x80); 
            LCD_STR("Enter Password:");
            LCD_CMD(0xC0); 
            GetPassword(pass);            
            delay_ms(500); 
            
            if(Check_Password(pass)) 
							{
                break; 	
            } 
					else 
						{
                pass_try++;
                LCD_CMD(0x01);
                LCD_CMD(0x80); 
						    LCD_STR("Wrong Password!");
                
                IOSET0 = LED2; 
						    delay_ms(400); 
						    IOCLR0 = LED2;
                delay_ms(700); 
                
                if(pass_try >= 3) {
                    LCD_CMD(0x01);
                    LCD_CMD(0x80); 
                    LCD_STR("System Locked!");
                    GSM_SendBreach(); 
                    
                    for(b = 0; b < 6; b++) { 
                        IOSET0 = LED; delay_ms(200);
                        IOCLR0 = LED; delay_ms(200);
                    } 
                    delay_sec(10);
                    pass_try = 0; 
                }
            }
        }
        LCD_CMD(0x01);
        LCD_CMD(0x80); 
        LCD_STR("Press SW for OTP");
        UART0_STR("\r\nPress Switch for OTP\r\n");
        
        while(IOPIN0 & SWITCH);        
        delay_ms(30);                  
        while(!(IOPIN0 & SWITCH));     
        otp_num = (T0TC % 9000) + 1000;    
        sprintf(otp_str, "%04u", otp_num); 
        
        UART0_STR("Send OTP Successfully\r\n");
        GSM_SendOTP(otp_num);

        otp_try = 0;
        while(1) {
            LCD_CMD(0x01);
            LCD_CMD(0x80); 
            LCD_STR("Enter OTP:");
            LCD_CMD(0xC0); 
            GetOTP(otp_in);              
            delay_ms(500); 
            
            if(strcmp(otp_in, otp_str) == 0) {
                LCD_CMD(0x01);
                LCD_CMD(0x80);
                LCD_STR("ACCESS GRANTED");
                UART0_STR("ACCESS GRANTED\r\n");
                IOSET0 = (1<<4);            
                
                IOSET0 = MOTOR_IN1;
                IOCLR0 = MOTOR_IN2; 
                delay_sec(500);    
                IOCLR0 = MOTOR_IN1;
                IOCLR0 = MOTOR_IN2;     
                IOCLR0 = (1<<4);           
                break;
            }
            else 
							{
                otp_try++;
                LCD_CMD(0x01);
                LCD_CMD(0x80); 
                LCD_STR("Wrong  OTP!");
                IOSET0 = LED2; 
                delay_ms(400); 
                IOCLR0 = LED2;
                
                delay_ms(700); 
                
                if(otp_try >= 3) {
                    LCD_CMD(0x01);
                    LCD_CMD(0x80); LCD_STR("OTP Expired!");
                    delay_sec(2);
                    break; 
                }
            }
        }
    } 
}