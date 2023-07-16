#include <SoftwareSerial.h>
#include <AFMotor.h>

AF_DCMotor motor_L(1);
AF_DCMotor motor_R(4);

int Lspeed = 170;
int Rspeed = 200;

int TrigPin = A0;
int EchoPin = A1;

long duration;
long distance;

void Obstacle_Check();
void Distance_Measurement();
void Forward();
void Backward();
void Right();
void Left();
void Stop();

void setup() {
	Serial.begin(9600);
	Serial.println("Start Self-Driving Car!");

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

void Forward() {
	motor_L.run(FORWARD);
	motor_R.run(FORWARD);
	motor_L.setSpeed(Lspeed);
	motor_R.setSpeed(Rspeed);
}

void Backward() {
	motor_L.run(BACKWARD);
	motor_R.run(BACKWARD);
	motor_L.setSpeed(Lspeed);
	motor_R.setSpeed(Rspeed);
}

void Right() {
	motor_L.run(FORWARD);
	motor_R.run(BACKWARD);
	motor_L.setSpeed(Lspeed);
	motor_R.setSpeed(Rspeed*0.5);
}

void Left() {
	motor_L.run(BACKWARD);
	motor_R.run(FORWARD);
	motor_L.setSpeed(Lspeed*0.5);
	motor_R.setSpeed(Rspeed);
}

void Stop() {
	motor_L.run(RELEASE);
	motor_R.run(RELEASE);
	motor_L.setSpeed(0);
	motor_R.setSpeed(0);
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

void Obstacle_Check() {
	int val = random(2);  // 0(right) or 1(left)

	Distance_Measurement();
	delay(50);

	Serial.println(distance);

	while (distance < 300) {
		if (distance < 150) {
			Backward();
			delay(800);
			Stop();
			delay(50);

			val = random(2);
			if (val == 0) {
				Right();
				delay(400);
			}
			else {
				Left();
				delay(400);
			}
		}
		Distance_Measurement();
		delay(100);
	}
}

