#include "PinDefinitionsAndMore.h" //Define macros for input and output pin etc.
#include <IRremote.hpp>


int buttonPressedPin = 10;

IRsend irSender;
void setup()
{
    Serial.begin(9600);

    pinMode(buttonPressedPin, INPUT);

    
    /*
     * The IR library setup. That's all!
     */
//    IrSender.begin(); // Start with IR_SEND_PIN as send pin and if NO_LED_FEEDBACK_CODE is NOT defined, enable feedback LED at default feedback LED pin

    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);

}

void loop()
{
  if(digitalRead(buttonPressedPin) == HIGH){

            irSender.sendNEC(0x7E8154AB, 32);
            delay(3000);
  }
}
