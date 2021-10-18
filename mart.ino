#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x26,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display 
SoftwareSerial SoftSerial(11, 10);
unsigned char buffer[64];       // buffer array for data receive over serial port
int count = 0;                    // counter for buffer array
 const unsigned int MAX_MESSAGE_LENGTH = 14;
 byte n,o;
 void setup()
{
    lcd.init();
  lcd.backlight();
 
start();
    SoftSerial.begin(9600);     // the SoftSerial baud rate
    Serial.begin(9600);         // the Serial port of Arduino baud rate.
}
 
void loop()
{
     while (SoftSerial.available() > 0)
 {
  static char message[MAX_MESSAGE_LENGTH];
   static unsigned int message_pos = 0;

   //Read the next available byte in the serial receive buffer
   char inByte = SoftSerial.read();

   //Message coming in (check not terminating character) and guard for over message size
   if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
   {
     //Add the incoming byte to our message
     message[message_pos] = inByte;
     message_pos++;
   }
   //Full message received...
   else
   {
     //Add null character to string
     message[message_pos] = '\0';

     //Print the message (or do other things)
     Serial.println(message);

     //Reset for the next message
     message_pos = 0;
   }
 }
 if (Serial.available() >0){
     char info = Serial.read();
       if (info == '1'){
      lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("Product Added!");
      delay(1200);
       lcd.clear();
       start();
       info= '0';
      }

      if(info == '2'){
        del();
        delay(1200);
        start();
        }
        
        if(info == '3'){
        alr();
        delay(1200);
        start();
        }

        if(info == '4'){
        inc();
        delay(1200);
        start();
        }
        if(info == '5'){
        nic();
        delay(1200);
        start();
        }
   }
  
}

void start(){
   lcd.setCursor(4,0);
  lcd.print("WELCOME!");
  lcd.setCursor(0,1);
  lcd.print("SWIPE TO ADD NOW");
  
  }
void del(){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("");
  lcd.setCursor(0,1);
  lcd.print("Product Delete!");
  
  }
void basket(int val){
   lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("CART in GHS");
  lcd.setCursor(0,1);
  lcd.print(val);
  }
void alr(){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("");
  lcd.setCursor(0,1);
  lcd.print("Already in Cart");
  }
  void inc(){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("");
  lcd.setCursor(0,1);
  lcd.print("Not Registered!");
  }
  void nic(){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("");
  lcd.setCursor(0,1);
  lcd.print("Not in Cart");
  }
