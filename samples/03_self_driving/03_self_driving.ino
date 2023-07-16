/* 이 소스는 에듀이노(Eduino)에 의해서 번역, 수정, 작성되었고 소유권 또한 에듀이노의 것입니다.
    소유권자의 허락을 받지 않고 무단으로 수정, 삭제하여 배포할 시 법적인 처벌을 받을 수도 있습니다.
  Copyright belongs to Eduino
*/

#include <SoftwareSerial.h>
#include <AFMotor.h>
AF_DCMotor motor_L(1);
AF_DCMotor motor_R(4);

int Lspeed = 170;        
int Rspeed = 200;        

int TrigPin = A0;       
int EchoPin = A1;
long duration, distance;

void Obstacle_Check();
void Distance_Measurement();
void Forward();
void Backward();
void Right();
void Left();
void Stop();

void setup() {
  Serial.begin(9600);                         
  Serial.println("Eduino Smart Car Start!");

  pinMode(EchoPin, INPUT);                    
  pinMode(TrigPin, OUTPUT);                   

  motor_L.setSpeed(Lspeed);                  
  motor_L.run(RELEASE);
  motor_R.setSpeed(Rspeed);                  
  motor_R.run(RELEASE);
}

void loop() {
  Forward();
  delay(50);
  Obstacle_Check();
}

void Obstacle_Check() {
  int val = random(2);
  Distance_Measurement();
  delay(50);
  
  Serial.println(distance);

  while (distance < 300) {
    if (distance < 150) {
      Backward();
      delay(800);
      Stop();
      delay(50);
      Distance_Measurement();
      delay(100);
    }
    else {
      if (val == 0) {
        Right();
        delay(400);
      }
      else if (val == 1) {
        Left();
        delay(400);
      }
      Distance_Measurement();
      delay(100);
    }
  }
}

void Distance_Measurement() {
  digitalWrite(TrigPin, LOW);
  delay(2);
  digitalWrite(TrigPin, HIGH);       
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH); 
  distance = ((float)(340 * duration) / 1000) / 2;
  delay(50);
}

void Forward() {
  motor_L.run(FORWARD);  motor_R.run(FORWARD);
  motor_L.setSpeed(Lspeed);  motor_R.setSpeed(Rspeed);
}
void Backward() {
  motor_L.run(BACKWARD);  motor_R.run(BACKWARD);
  motor_L.setSpeed(Lspeed);  motor_R.setSpeed(Rspeed);
}
void Right() {
  motor_L.run(FORWARD);  motor_R.run(BACKWARD);
  motor_L.setSpeed(Lspeed);  motor_R.setSpeed(Rspeed*0.5);
}
void Left() {
  motor_L.run(BACKWARD);  motor_R.run(FORWARD);
  motor_L.setSpeed(Lspeed*0.5);  motor_R.setSpeed(Rspeed);
}
void Stop() {
  motor_L.run(RELEASE);       motor_R.run(RELEASE);
  motor_L.setSpeed(0);  motor_R.setSpeed(0);
}
