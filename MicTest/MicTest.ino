#define AudioSensor A0

void setup() {
  // put your setup code here, to run once:
  pinMode(AudioSensor, INPUT);
  Serial.begin(115200); 
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("fun\n");
  Serial.print(analogRead(AudioSensor));
  Serial.print(" h ");
  Serial.print("\n");
  delay(100);
}
