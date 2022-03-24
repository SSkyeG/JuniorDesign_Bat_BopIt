//Rebecca has added a change!
#define newLED 8
#define button_pin 9

void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  pinMode(newLED, OUTPUT);
  pinMode(button_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int button_state = digitalRead(button_pin);
  if (button_state == HIGH) 
  { 
    digitalWrite(newLED, HIGH);
    delay(10);
    digitalWrite(newLED, LOW);
    delay(5);//Sierra's Change!
    delay(4); //Jack's change
  }
}
