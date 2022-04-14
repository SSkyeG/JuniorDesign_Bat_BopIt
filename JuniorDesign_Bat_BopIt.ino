
#include <DFRobot_DF1201S.h>
#include <SoftwareSerial.h>

//Input
#define OnButton 13

#define Flex_Right A4
#define Flex_Left A5

#define AudioSensor A0

#define TiltSens 8

#define NoseButton 7

//Output
//SoftwareSerial DF1201SSerial(2, 3);  //RX  TX
//DFRobot_DF1201S DF1201S;
#define speakerPin 2
#define LEDPin 3

//variables
bool isBatOn= false;
int score = 0;
int TimeLimit = 9999;

int SoundBase = 800;
int dB_threshold= 200;

int LeftWingBase = 700;
int RightWingBase = 700;
int WingMove_threshold = 200;

int res_threshold = 5;

int timesTilted = 0;
int TiltedThres = 150;


void setup() 
{
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  pinMode(AudioSensor, INPUT);
  pinMode(Flex_Right, INPUT);
  pinMode(Flex_Left, INPUT);
  pinMode(AudioSensor, INPUT);
  pinMode(TiltSens, INPUT);
  pinMode(NoseButton, INPUT);
  pinMode(OnButton, INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(LEDPin, OUTPUT);
  //pinMode(SpeakerSound, OUTPUT);
  Serial.begin(9600); 
  randomSeed(analogRead(0));

  //Serial.begin(115200);
  //DF1201SSerial.begin(115200);
  /*while(!DF1201S.begin(DF1201SSerial)){
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);}*/
}
void dot(){
  Serial.print("Dot ");
  digitalWrite(speakerPin, HIGH);
  delay(500);
  digitalWrite(speakerPin, LOW);
  delay(500);

}
void dash()
{
  Serial.print("Dash ");
  digitalWrite(speakerPin, HIGH);
  delay(1000);
  digitalWrite(speakerPin, LOW);
  delay(500);
}
void loop() 
{
  /*
  Serial.print(analogRead(AudioSensor));
  Serial.print("  ");
  Serial.print(CheckScreamIt());
  Serial.print("\n");
  
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(AudioSensor));
  Serial.print("  ");
  Serial.print(CheckScreamIt());
  Serial.print("\n");

  
  int a = digitalRead(OnButton);
  Serial.print(a);
  
  if(a>1000)
  {
    Serial.print(analogRead(AudioSensor));
    Serial.print('\n');
  }
  getBases();
  Serial.print("Start!");
  while(true)
  {
    
    if(CheckBendIt())
    {
      Serial.print(analogRead(Flex_Right));
      Serial.print(" Bent with ");
      Serial.print(RightWingBase);
      Serial.print("!\n");
      break;
    }
  }
  
  delay(200);
  
  */
  if (digitalRead(OnButton) == HIGH && !isBatOn) 
  { 
    isBatOn= true;
    score = 0;
    Serial.print("Game ON\n");
  }
  if(isBatOn)
  {
    delay(1000);
    Serial.print("Call Com. Score: ");
    Serial.print(score);
    Serial.print("\n");
    CallCommand();
    
  }
  
  
}

bool CallCommand()
{
  if(score >= 99)
  {
    Win();
  }
  else
  {
    delay(1000);
    //Generate random number between 1-4 = x
    int randNumber = random(1, 5);
    if(randNumber ==2)
    {
      randNumber = 3;
    }
    
    //TODO: Output command for user to start;
    PlaySound(randNumber+100);
    
    //Get Base for Audio and Flex
    getBases();
    
    int Time = 0;
    timesTilted=0; //reset times tilted
    
    //In time limit...
    while(Time < TimeLimit) 
    {
      //Check to see if they do the tasks
      bool isBooped = CheckBoopIt();
      bool isLoud = CheckScreamIt();
      bool isTilted = CheckTiltIt();
      bool isBent = CheckBendIt();

      switch (randNumber)
      {
        case 1:
          if(isBooped && !(isLoud ||isTilted || isBent))
          {
            TaskCompleted();
            return true;
          }
          else if(isLoud ||isTilted || isBent)
          {
            Serial.print("Other input1. ");
            Lose();
            return false;
          }
          break;
          
        case 2:
          if(isLoud && !(isBooped ||isTilted || isBent))
          {
            TaskCompleted();
            return true;
          }
          else if(isBooped ||isTilted || isBent)
          {
            Serial.print("Other input2. ");
            Lose();
            return false;
          }
          break;
          
        case 3:
          if(isTilted && !(isBooped ||isLoud  || isBent))
          {
            TaskCompleted();
            return true;
          }
          else if(isBooped ||isLoud || isBent)
          {
            Serial.print("Other input3. ");
            Lose();
            return false;
          }
          break;
          
        case 4:
          if(isBent && !(isBooped ||isLoud  || isTilted))
          {
            TaskCompleted();
            return true;
          }
          else if(isBooped ||isLoud || isTilted)
          {
            Serial.print("Other input4. ");
            Lose();
            return false;
          }
          break;
      }
      Time++;
    }
    Serial.print("Time Up. ");
    Lose();
    return false;
  }
}



bool CheckBoopIt()
{
  //poll for if task completed
  int a = digitalRead(NoseButton);
  if(a==HIGH)
  {
    Serial.print(" Booped ");
    return true;
  }
  else
  {
    return false;
  }
}

bool CheckScreamIt()
{
  //poll for if task completed
  int soundinput = analogRead(AudioSensor);
  //Serial.print(soundinput);
  //Serial.print("\n");
  if (soundinput > SoundBase+dB_threshold)
  {
    Serial.print(" Loud ");
    Serial.print(soundinput);
    //Serial.print(soundinput);
    return true;
  }
  return false;
}

bool CheckTiltIt ()
{
  //poll for if task completed
  int movement = digitalRead(TiltSens);
  if (movement ==LOW)
  {
    timesTilted++;
    if(timesTilted>=TiltedThres)
    {
      Serial.print(" Tilted ");
      return true;
    }
  }
  return false;
}

bool CheckBendIt()
{
  //Poll for if task completed
  int RightBent = analogRead(Flex_Right);
  int LeftBent = analogRead(Flex_Left);
  
  if (LeftBent > LeftWingBase+WingMove_threshold || LeftBent < LeftWingBase-WingMove_threshold 
    || RightBent > RightWingBase+WingMove_threshold || RightBent < RightWingBase-WingMove_threshold)
  {
    Serial.print(" Bended ");
    return true;
  }
  return false;
}

void getBases()
{
  //int audioSum =0;
  int wingRSum =0;
  int wingLSum =0;
  int times=15;
  for(int i = 0; i<times; i++)
  {
    //audioSum+=analogRead(AudioSensor);
    wingRSum+=analogRead(Flex_Right);
    wingLSum+=analogRead(Flex_Left);
  }
  //SoundBase = audioSum/times;
  LeftWingBase = wingLSum/times;
  RightWingBase = wingRSum/times;
  //Serial.print(RightWingBase);
  //Serial.print("\n");
}

void Win()
{
  //Output Winner audio;
  int code=99;
  PlaySound(code);
  
  //Output score of 99 audio;
  isBatOn=false;
}

void Lose()
{
  //Output score of user;
  isBatOn=false;
  
  //Output Loser audio;
  Serial.print("LOST  ");
  Serial.print(isBatOn);
  Serial.print("\n");
  
  int code=100;
  PlaySound(code);
  PlaySound(score);
  
  
}


void TaskCompleted()
{
  score++;
  TimeLimit--;//decrease time limit to make more difficult
  PlaySound(105);
  //CallCommand(); //go back to function to generate
}




void one()
{
  dot();
  dash();
  dash();
dash();
}
void two()
{
  dot();
  dot();
  dash();
  dash();
dash();
}
void three()
{
  dot();
  dot();
  dot();
  dash();
dash();
}
void four()
{
  dot();
  dot();
  dot();
  dot();
dash();
}
void five()
{
  dot();
  dot();
  dot();
  dot();
dot();
}
void six()
{
  dash();
  dot();
  dot();
  dot();
dot();
} 
void seven()
{
  dash();
  dash();
  dot();
  dot();
dot();
}
void eight()
{
  dash();
  dash();
  dash();
  dot();
dot();
}
void nine()
{
  dash();
  dash();
  dash();
  dash();
dot();
}
void zero()
{
  dash();
  dash();
  dash();
  dash();
  dash();
}

void outputDigit(int digit)
{
   switch(digit)
   {
      case 1:
        one();
        break;
      case 2:
        two();
        break;
      case 3:
        three();
        break;
      case 4:
        four();
        break;
      case 5:
        five();
        break;
      case 6:
        six();
        break;
      case 7:
        seven();
        break;
      case 8:
        eight();
        break;
      case 9:
        nine();
        break;
      case 0:
        zero();
        break;
    }
}
 
void wrongOutput()
{
digitalWrite(speakerPin, HIGH);
digitalWrite(LEDPin, HIGH);
delay(1500);
digitalWrite(speakerPin, LOW);
digitalWrite(LEDPin, LOW);
delay(1000);
}

void winOutput()
{
digitalWrite(speakerPin, HIGH);
digitalWrite(LEDPin, HIGH);
delay(500);
digitalWrite(speakerPin, LOW);
digitalWrite(LEDPin, LOW);
delay(500);

digitalWrite(speakerPin, HIGH);
digitalWrite(LEDPin, HIGH);
delay(500);
digitalWrite(speakerPin, LOW);
digitalWrite(LEDPin, LOW);
delay(500);

digitalWrite(speakerPin, HIGH);
digitalWrite(LEDPin, HIGH);
delay(500);
digitalWrite(speakerPin, LOW);
digitalWrite(LEDPin, LOW);
delay(500);

digitalWrite(speakerPin, HIGH);
digitalWrite(LEDPin, HIGH);
delay(500);
digitalWrite(speakerPin, LOW);
digitalWrite(LEDPin, LOW);
delay(500);
} 
void PlaySound(int code)
{
  //Right LED Flash
  // Wrong solid

    
  //get score digits
  int tens =0;
  int ones = 0;
  ones= score%10;
  tens = (score - ones)/10;
  
  if(code>=0 && code<=98)
  {
    if(tens!=0)
    {
      outputDigit(tens);
      delay(200);
    }
    outputDigit(ones);
  }
  else if (code==99)
  {
    //win beeping and LED
    winOutput();
    outputDigit(tens);
    outputDigit(ones);
  }
  else if(code == 100)
  {
    //Lose Solid 
    wrongOutput();
  }
  else if(code == 105)
  {
    digitalWrite(LEDPin, HIGH);
    delay(500);
    digitalWrite(LEDPin, LOW);
    delay(500);
  }
  else
  {
    switch (code)
    {
      case 101:
        //Boop
        dot();
        break;
      case 102:
        //Clap
        break;
      case 103:
        //Tilt
        dot();
        dot();
        break;
      case 104:
        //Bend
        dot();
        dot();
        dot();
        break;
    }
  }
}
