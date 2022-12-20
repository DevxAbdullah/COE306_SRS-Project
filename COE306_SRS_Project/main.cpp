#include "mbed.h"
#include "keypad.h"
//DigitalOut myled(LED1);
#include "TextLCD.h"
  

TextLCD lcd(p5, p6, p7, p8, p19, p20);        // 4bit bus: rs, e, d4-d7
//DigitalIn alarm(p29, PullUp);


InterruptIn PIR(p22);

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
void check(void);
  PwmOut b(p23); 
PwmOut r(p24); 
PwmOut g(p25); 
int main() {  
     g.write(1.0);
     r.write(0.5);
     b.write(0.0);
        float pr = r;
        float pg = r;
        float pb = r;
        
         LPC_GPIO2->FIODIR |= 1<<5;
         LPC_GPIO2->FIOPIN = 0<<5;
   
    PIR.rise(&irq_handler);
    PIR.rise(&irq_handler);
         lcd.cls();
         lcd.setAddress(0, 0);
         lcd.printf("Welcome ... :)");
check();

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
   
    g.write(1.0);
    r.write(0.0);
    b.write(1.0);
   AnalogIn photocell(p18);
   double      ph = photocell;

     if (PIR_Detected == 1  ) {
         lcd.cls();
         lcd.setAddress(0, 0);
         lcd.printf("R1: Detected");
                LPC_GPIO2->FIODIR |= 1<<0;
        LPC_GPIO2->FIOPIN = 1<<0;  
            PIR_Detected = 0;
            g.write(0.0);
            r.write(1.0);
            b.write(0.0);
            wait_ms(3000);

            check();
        LPC_GPIO2->FIOPIN = 0<<0;  
                    } 
    else if ( ph < 0.25) {
         lcd.cls();
         lcd.setAddress(0, 0);
         lcd.printf("R2: Detected");
                LPC_GPIO2->FIODIR |= 1<<0;
        LPC_GPIO2->FIOPIN = 1<<0;  
           PIR_Detected = 0;
         g.write(0.0);
    r.write(1.0);
    b.write(0.0);
            wait_ms(1500);

            check();
        LPC_GPIO2->FIOPIN = 0<<0;  
       
        }
				
	else {
     
  
         lcd.cls();
         lcd.setAddress(0, 0);
         lcd.printf("R1&2: Safe\nph: %f", ph);
         wait_ms(50);

       
		}

       
   
}

}
void check(){
    LPC_GPIO2->FIODIR |= 1<<5;

//  c0   c1   c2   c3  r0   r1   r2   r3    
    Keypad keypad( p9,p10,p11,p12,p13,p14,p15,p16 );
       
    keypad.enablePullUp();
    char key;
             
    char pass[] = {'1','9','6','3'};

    int number =0;
    int    p1=0;
    int    p2=0;
    int    p3=0;
    int    p4=0;
    int    p5=1;
    
         lcd.setAddress(0, 1);
         lcd.printf("Enter the Pass:");
        for(int i = 0; i < 16;i++ ){
            lcd.setAddress(i, 1);
            wait(0.09);
            lcd.printf(".");
        }
         lcd.setAddress(0, 1);
         lcd.printf("Pass:           ");


    while (p5) 
    {
    
         key = keypad.getKey();
         char k = key;    
         if(key != KEY_RELEASED)
         {
                             
         lcd.setAddress((number+6), 1);
         lcd.printf("*"); 
          number=number+1;
            LPC_GPIO2->FIOPIN = 1<<5;
        wait(0.030);
        LPC_GPIO2->FIOPIN = 0<<5;
          if(number == 1){

              if(key==pass[0])
                p1=1;
                else
                p1=0;
              }
            if(number == 2){
 
              if(key==pass[1])
                p2=1;
                else
                p2=0; 
              }
            if(number == 3){
                
              if(key==pass[2])
                p3=1;
                else
                p3=0;
              }
            if(number == 4){
              if(key==pass[3])
                p4=1;
                else
                p4=0;
              }
 
           if(key == 'D'){
               number=0;
                if(p1 ==1 &  p2 == 1 & p3 == 1 & p4 == 1){
                lcd.cls();
        lcd.setAddress(0, 1);
        lcd.printf("Password Checked");  
        LPC_GPIO2->FIOPIN = 1<<5;
        wait(0.030);
        LPC_GPIO2->FIOPIN = 0<<5; 
        wait(0.05);         
        LPC_GPIO2->FIOPIN = 1<<5;
        wait(0.030);
        LPC_GPIO2->FIOPIN = 0<<5;
        wait(1.5);

                    p1=0;
                    p2=0;
                    p3=0;
                    p4=0;
                    p5=0;
                
               }else{
                lcd.cls();
         lcd.setAddress(0, 1);
         lcd.printf("Password Wrong:(");
         for(int i= 0 ; i<4 ; i++){
            LPC_GPIO2->FIOPIN = 1<<5;
            wait(0.070);
            LPC_GPIO2->FIOPIN = 0<<5;
            wait(0.070);
         }
         wait(1.2);
               
               lcd.cls();
         lcd.setAddress(0, 1);
         lcd.printf("Pass:");
         
                    p1=0;
                    p2=0;
                    p3=0;
                    p4=0;
               }  
           }
             wait(0.6);
         }
    }

  
}