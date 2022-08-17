#include "PinDefinitionsAndMore.h" //Define macros for input and output pin etc.
#include <IRremote.hpp>

#define NUMBER_OF_SHIFT_CHIPS   3
#define DATA_WIDTH   NUMBER_OF_SHIFT_CHIPS * 8

int LoadPin    = 0;
int buttonPressedPin = 1;
int DataPin    = 2;
int ClockPin   = 3;
int testPin = 4;
long int pinValues;

IRsend irSender;
void setup()
{
    Serial.begin(9600);

    pinMode(testPin, OUTPUT);
    pinMode(LoadPin, OUTPUT);
    pinMode(buttonPressedPin, INPUT);
    pinMode(ClockPin, OUTPUT);
    pinMode(DataPin, INPUT);

    digitalWrite(ClockPin, LOW);
    digitalWrite(LoadPin, HIGH);

    
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

    pinValues = read_shift_regs();

        Serial.print("Du tryckte knapp nr. ");
        Serial.println(pinValues); 

        switch (pinValues) {
          case 16:
            irSender.sendNEC(0x7E8154AB, 32);
            break;
          case 9:
            irSender.sendNEC(0x5EA1C43A, 32);
            break;
          case 8:
            irSender.sendNEC(0x5EA1F806, 32);
            break;
          case 10:
            irSender.sendNEC(0x5EA158A7, 32);
            break;
          case 11:
            irSender.sendNEC(0x5EA1D827, 32);
            break;
        }
    delay(1500);
  }
}

unsigned long read_shift_regs()
{
    long bitVal;
    unsigned long bytesVal = 0;

    digitalWrite(LoadPin, LOW);
    delayMicroseconds(5);
    digitalWrite(LoadPin, HIGH);

    int i = 0;
    while( (digitalRead(DataPin) == LOW) && i < 24) {
        digitalWrite(ClockPin, HIGH);
        delayMicroseconds(5);
        digitalWrite(ClockPin, LOW);
        i++;
    }
    return(i);
}
