// Motor Pinout
int S1 = 3; //M1 Speed Control 
int S2 = 11; //M2 Speed Control
int MotorL = 12;
int MotorR = 13;  
int MotorLb = 9;
int MotorRb = 8;  

void stop() //Stop 
{ 
analogWrite(S1, 0); 
analogWrite(S2, 0); 
} 
void advance(int a,int b) //Move forward 
{ 
  digitalWrite(MotorL, HIGH);  
  digitalWrite(MotorR, HIGH);
  digitalWrite(MotorLb, LOW);
  digitalWrite(MotorRb, LOW);
  analogWrite (S1,a); //PWM Speed Control 
  analogWrite (S2,b); 
} 
void back_off (int a,int b) //Move backward 
{
  digitalWrite(MotorL, LOW); 
  digitalWrite(MotorR, LOW); 
  digitalWrite(MotorLb, LOW);
  digitalWrite(MotorRb, LOW);
  analogWrite (S1,a); //PWM Speed Control 
  analogWrite (S2,b);  
}   
void turn_L (int a, int b) //Turn Left 
{ 
  digitalWrite(MotorL, HIGH);
  digitalWrite(MotorR, LOW);
  digitalWrite(MotorLb, LOW);
  digitalWrite(MotorRb, LOW);
  analogWrite (S1,a); //PWM Speed Control 
  analogWrite (S2,b); 
} 

void turn_R (int a,int b) //Turn Right 
{ 
  digitalWrite(MotorL, LOW);
  digitalWrite(MotorR, HIGH);
  digitalWrite(MotorLb, LOW);
  digitalWrite(MotorRb, LOW);
  analogWrite (S1,a); //PWM Speed Control 
  analogWrite (S2,b); 
}   

// Pin Codes
const int TRIG_PIN = 6; // A2
const int ECHO_PIN = 5; // A1
// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

void setup() {
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(MotorL, OUTPUT);
  pinMode(MotorLb, OUTPUT);
  pinMode(MotorR, OUTPUT);
  pinMode(MotorRb, OUTPUT);
  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
}

void loop() {
  float dist = sensor();
  unsigned long b = 0;
  unsigned long a = 0;
  int cas = 0;
    if(dist < 20)//go left if wall dist. is less than 20 cm
    {
     turn_L (255,255); //50,255
     delay(735);//1200 1000
     advance (180,255);
     delay (270); //250
    }
   
    else{
      turn_R (255,255); //50,255
      delay(420); //200 400
      dist = sensor();
      a = millis(); 
      cas = 0; 

      while ((cas<=1250)&&(dist >= 20)) //go slow right while wall is further than 20 cm and timer isn't over
      {
       //advance (255,255);
       advance (150,255);
       b = millis();
       cas = b - a; 
       //delay (350);//40
       dist = sensor();
      }
    }
}
float sensor(){
  // Wait at least 60ms before next measurement
  delay(30);
  //---Pin Code Start---
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  //of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;
  return{cm};
}
