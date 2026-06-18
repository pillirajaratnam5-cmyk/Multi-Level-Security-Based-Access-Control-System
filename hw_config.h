#ifndef HW_CONFIG_H
#define HW_CONFIG_H

#define PASS_LEN      4

#define ROW0          (1 << 8)     
#define ROW1          (1 << 9)     
#define ROW2          (1 << 10)     
#define ROW3          (1 << 11)    
#define ALL_ROWS      (ROW0 | ROW1 | ROW2 | ROW3)

#define COL0          (1 << 12)   
#define COL1          (1 << 13)     
#define COL2          (1 << 14)     
#define COL3          (1 << 15)     
#define ALL_COLS      (COL0 | COL1 | COL2 | COL3)

#define RS            (1 << 16)     
#define EN            (1 << 17)     
#define LCD_DB        (0xFF << 18)  

#define LED           (1 << 4)     
#define LED2          (1 << 27)
#define SWITCH        (1 << 28)     
#define MOTOR_IN1     (1 << 29)     
#define MOTOR_IN2     (1 << 30)     

#endif
