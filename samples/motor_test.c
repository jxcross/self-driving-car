#include <SoftwareSerial.h>
#include <AFMotor.h>

AF_DCMotor motor_L(1);
AF_DCMotor motor_R(4);

void setup() {
	motor_L.setSpeed(200);
	motor_L.run(RELEASE);

	motor_R.setSpeed(200);
	motor_R.run(RELEASE);
}

void loop() {
	motor_L.run(FORWARD);
	motor_R.run(FORWARD);
	delay(2000);

	motor_L.run(RELEASE);
	motor_R.run(RELEASE);
	delay(1000);

	motor_L.run(BACKWARD);
	motor_R.run(BACKWARD);
	delay(2000);
	
	motor_L.run(RELEASE);
	motor_R.run(RELEASE);
	delay(1000);

}
