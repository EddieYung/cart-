#include <SoftwareSerial.h>
#include <Wire.h> 
 
 
 
SoftwareSerial SoftSerial(11, 10);
unsigned char buffer[64];       // buffer array for data receive over serial port
int count = 0;                    // counter for buffer array
 const unsigned int MAX_MESSAGE_LENGTH = 14;
 byte n,o;
 void setup()
{
   
 
 
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
  
}

 
