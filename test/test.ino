int buttonPressedPin = 10;

int data;

void setup()
{
    Serial.begin(9600);

    pinMode(buttonPressedPin, INPUT);
}

void loop()
{
  data = digitalRead(buttonPressedPin);
  if(data == HIGH) Serial.println("HIGH");
    else Serial.println("LOW");

  delay(500);
}
