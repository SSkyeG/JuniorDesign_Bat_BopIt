
//Input
#define OnButton 1

#define Flex_Right A4
#define Flex_Left A1

#define AudioSensor A5

#define TiltSens 1

#define NoseButton 1

//Output
#define SpeakerSound 1

//variables
bool isBatOn= false;
int score = 0;
int TimeLimit = 10;

int SoundBase = 50;
int dB_threshold= 20;

int LeftWingBase = 6000;
int RightWingBase = 6000;
int WingMove_threshold = 1500;

int res_threshold = 5;


void setup() 
{
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  pinMode(AudioSensor, INPUT);
  pinMode(Flex_Right, INPUT);
  //pinMode(Flex_Left, INPUT);
  //pinMode(AudioSensor, INPUT);
  //pinMode(TiltSens, INPUT);
  //pinMode(NoseButton, INPUT);
  pinMode(8, OUTPUT);
  //pinMode(SpeakerSound, OUTPUT);
  Serial.begin(9600); 
  randomSeed(analogRead(0));
}

void loop() 
{
  // put your main code here, to run repeatedly:
  int a = analogRead(Flex_Right);
  Serial.print(analogRead(Flex_Right));
  Serial.print('\n');
  if(a>700 || a<400)
  {
    digitalWrite(8,HIGH);  
  }
  else
  {
    digitalWrite(8, LOW);
  }
  /*int button_state = digitalRead(button_pin);
  if (button_state == HIGH) 
  { 
    digitalWrite(newLED, HIGH);
    delay(10);
    digitalWrite(newLED, LOW);
    delay(5);//Sierra's Change!
  }
  */
  
  if (OnButton == HIGH && !isBatOn) 
  { 
    isBatOn= true;
    score = 0;
  }
  if(isBatOn)
  {
    isBatOn = CallCommand();
  }
  */
}

bool CallCommand()
{
  if(score >= 99)
  {
    Win();
  }
  else
  {
    //Generate random number between 1-4 = x
    int randNumber = random(1, 5);
    
    //TODO: Output command for user to start;
    PlaySound(randNumber);
    
    //Get Base for Audio and Flex
    getBases();

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
            Lose();
            return false;
          }
          break;
      }
      Time++;
    }
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
  soundinput = analogRead(AudioSensor);
  if (soundinput > SoundBase+dB_threshold)
  {
    return true;
  }
  return false;
}

bool CheckTiltIt ()
{
  //poll for if task completed
  movement = digitalRead(TiltSens);
  if (movement ==HIGH)
  {
    return true;
  }
  return false;
}

bool CheckBendIt()
{
  //Poll for if task completed
  RightBent = analogRead(Flex_Right);
  LeftBent = analogRead(Flex_Left);
  
  if (LeftBent > LeftWingBase+WingMove_threshold || LeftBent < LeftWingBase-WingMove_threshold 
    || RightBent > RightWingBase+WingMove_threshold || RightBent < RightWingBase-WingMove_threshold)
  {
    return true;
  }
  return false;
}

void getBases()
{
  int audioSum =0;
  int wingRSum =0;
  int wingLSum =0;
  int times=15;
  for(int i = 0; i<times; i++)
  {
    audioSum+=analogRead(AudioSensor);
    wingRSum+=analogRead(Flex_Right);
    wingLSum+=analogRead(Flex_Left);
  }
  SoundBase = audioSum/times;
  LeftWingBase = wingLSum/times;
  RightWingBase = wingRSum/times;
}

void Win()
{
  //Output Winner audio;
  PlaySound(code);
  
  //Output score of 99 audio;
  isBatOn=false;
}

void Lose()
{
  //Output Loser audio;
  PlaySound(code);
  
  //Output score of user;
  isBatOn=false;
}


void TaskCompleted()
{
  score++;
  TimeLimit--;//decrease time limit to make more difficult
  CallCommand(); //go back to function to generate
}

void PlaySound(code)
{
  //TODO: Send code for certain sounds to speaker
}
*/
