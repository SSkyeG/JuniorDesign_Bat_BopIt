#define AudioSensor A0

void setup() {
  // put your setup code here, to run once:
  pinMode(AudioSensor, INPUT);
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("fun\n");
}
