// the right motor is motor1, and the left one is motor2

#define motor1_en 10
#define motor1_pin1 8
#define motor1_pin2 9

#define motor2_en 11
#define motor2_pin1 12
#define motor2_pin2 13

#define speed 60

// taking left to right array in order
int ir[5] = {3,4,5,6,7};  

int i;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1_en,OUTPUT);
  pinMode(motor1_pin1,OUTPUT);
  pinMode(motor1_pin2,OUTPUT);

  pinMode(motor2_en,OUTPUT);
  pinMode(motor2_pin1,OUTPUT);
  pinMode(motor2_pin2,OUTPUT);

  for(i=0;i<5;i++) pinMode(ir[i],INPUT);

  Serial.begin(9600);
}

void stop()
{
  analogWrite(motor1_en,0);
  analogWrite(motor2_en,0);
}

void ideal()
{
  analogWrite(motor1_en,speed);
  digitalWrite(motor1_pin1,HIGH);
  digitalWrite(motor1_pin2,LOW);

  analogWrite(motor2_en,speed);
  digitalWrite(motor2_pin1,HIGH);
  digitalWrite(motor2_pin2,LOW);
}

void left_curve()
{
  analogWrite(motor1_en,speed);
  digitalWrite(motor1_pin1,HIGH);
  digitalWrite(motor1_pin2,LOW);

  analogWrite(motor2_en,0);
}

void right_curve()
{
  analogWrite(motor1_en,0);

  analogWrite(motor2_en,speed);
  digitalWrite(motor2_pin1,HIGH);
  digitalWrite(motor2_pin2,LOW);

}

void sharp_left()
{
  analogWrite(motor1_en,speed);
  digitalWrite(motor1_pin1,HIGH);
  digitalWrite(motor1_pin2,LOW);

  analogWrite(motor2_en,speed);
  digitalWrite(motor2_pin1,LOW);
  digitalWrite(motor2_pin2,HIGH);
}

void sharp_right()
{
  analogWrite(motor1_en,speed);
  digitalWrite(motor1_pin1,LOW);
  digitalWrite(motor1_pin2,HIGH);

  analogWrite(motor2_en,speed);
  digitalWrite(motor2_pin1,HIGH);
  digitalWrite(motor2_pin2,LOW);
}

// if it gets reflection, it gives 1 aka white = 1 
// and 0 mean black

// some things to keep in mind, my path is too thin, so in curves specially what happens is, lets say left curve, the ir[1] sensor will be only 0, it wont hit both ir[1] and ir[2]
// casue the line is thin in respect of distance between ir sensors

// a important case is, in curve, for a moment it would miss all the sensors, all will be 1, at that moment it would go as previous direction, for that we will keep a prevDir variable
// -1 would be left, 0 would be straight, 1 would be right, -2 would be sharp left, and 2 would be sharp right, we will change it to 0 every time the ideal line hits, the ideal line is only ir[2]==0 

// and for 90 degree angle the three ir would be 0 so thats how we are gonna identify, and for 90 degree we would take a sharp turn, basically forward backward
// but for curve, we would take take soft curve, like forward and 0

String irString = "";
int prevDir=0;

void loop() {
  // put your main code here, to run repeatedly:

  // what i did here, is turn the array into a string, otherwise i would have to write a lot of digitalRead && etc in if

  irString = "";
  for (int i = 0; i < 5; i++) irString += String(digitalRead(ir[i]));  // Append each reading

  // there could be hopefullly 7 possible situations, 1 -> ideal path, ir[2]==0, everything else 1, forward
  // 2 -> all are 1, no detection, then follow prevDir and soft turn, casue its a curve
  // 3 and 4 -> ir[1] or ir[3] == 0, then soft turn since curve, and set prevDir
  // 5 and 6 - > ir[0-2] or ir[2-4] == 0, then sharp turn, and set prevDir
  // 7 -> all are 0, stop
  // and we have to set the logics in priority order, so that doesnt overlap

  Serial.println(irString);

  if(irString=="00000") 
  {
    stop();
    Serial.println("STOP");
  }
  else if(irString=="11011") 
  {
    ideal();
    prevDir=0;
    Serial.println("IDEAL");
  }
  else if(irString=="10111" || irString=="10011") 
  {
    left_curve();
    Serial.println("LEFT CURVE");
    prevDir=-1;
  }
  else if(irString=="11101" || irString=="11001") 
  {
    right_curve();
    Serial.println("RIGHT CURVE");
    prevDir=1;
  }
  else if(irString=="00011" || irString=="00111" || irString=="00001") 
  {
    sharp_left();
    Serial.println("LEFT SHARP");
    prevDir=-2;
  }
  else if(irString=="11000" || irString=="11100" || irString=="10000") 
  {
    sharp_right();
    Serial.println("RIGHT SHARP");
    prevDir=2;
  }
  else if(irString=="11111"){
    Serial.println("in 11111");
    Serial.print("PrevDir : ");
    Serial.println(prevDir);
    if(prevDir==0) 
    {
      ideal();
      Serial.print("elif0");
    }
    else if(prevDir==-1) 
    {
      Serial.print("elif-1");
      left_curve();
    }
    else if(prevDir==1) 
    {
      Serial.print("elif1");
      right_curve();
    }
    else if(prevDir==-2) 
    {
      Serial.print("elif-2");
      sharp_left();
    }
    else if(prevDir==2) 
    {
      Serial.print("elif2");
      sharp_right();
    }
  }
  else Serial.println("DONT KNOW");

  delay(20);
}
