#include "mbed.h"
#include "keypad.h"
//DigitalOut myled(LED1);
#include "TextLCD.h"

//#include "mbed2/336/platform/mbed_wait_api.h"
//#include "mbed2/336/platform/mbed_wait_api.h"

#include "ultrasonic.h"
           //  c0   c1   c2   c3  r0   r1   r2   r3    

TextLCD lcd(p5, p6, p7, p8, p19, p20);        // 4bit bus: rs, e, d4-d7
//DigitalIn alarm(p29, PullUp);

/*
void dist(int distance){
    //wait_ms(1);
    
    lcd.setAddress(9, 0);
    lcd.printf("%d\n", distance/10);
    wait_ms(500);
     lcd.setAddress(9, 0);
    lcd.printf("     ");
   
    
}
*/
//ultrasonic mjr(p8, p9, .1, 1, &dist);
InterruptIn PIR(p21);

int PIR_Detected = 0;
void irq_handler(void)
{
    PIR_Detected = 1;
}

int calibrationTime = 30;

int photocell_Detected = 0;
//AnalogIn photocell(p15);
InterruptIn photocell(p15);
void photocell_handler(void)
{
    photocell_Detected = 1;
}

int main() {  
    Keypad keypad( p11,p12,p13,p14,p15,p16,p17,p18 );
    keypad.enablePullUp();
   // char key = ' ';
    char password[4] = {'1', '2', '3','4'};
    char enteredPassword [4] = {} ;
    PIR.rise(&irq_handler);
    PIR.rise(&irq_handler);
         lcd.cls();
         lcd.setAddress(0, 0);
         lcd.printf("Activating: ");
         for (int i = 0; i < calibrationTime; i++){
         lcd.setAddress(12, 0);
         lcd.printf(".");
         wait(0.25);
         lcd.printf(".");
         wait(0.25);
         lcd.printf(".");
         wait(0.25);
         lcd.printf(".");
         wait(0.25);
         lcd.setAddress(12, 0);
         lcd.printf("    ");
         }
         lcd.cls();
         lcd.setAddress(0, 0);
         lcd.printf("Done");
         lcd.setAddress(0, 1);
         lcd.printf("System Active");
         wait_ms(2000);
         lcd.cls();
   // wait_ms(2000);
system:  
    while(1){
    
   AnalogIn photocell(p15);
   double      ph = photocell;

     if (PIR_Detected == 1  ) {
         lcd.cls();
         lcd.setAddress(0, 0);
         lcd.printf("R1: Detected\nph: %f", ph);
            PIR_Detected = 0;
            wait_ms(7500);
            lcd.cls();
        } else if ( ph < 1) {
         lcd.cls();
         lcd.setAddress(0, 0);
         lcd.printf("R2: Detected\nph: %f", ph);
            PIR_Detected = 0;
            wait_ms(2000);
            lcd.cls();
        }
				
	else {
         lcd.cls();
         lcd.setAddress(0, 0);
         lcd.printf("R1&2: Safe\nph: %f", ph);
         wait_ms(50);
	 //    wait_ms(1000);		//for warming up time
		}

       
   
}

}