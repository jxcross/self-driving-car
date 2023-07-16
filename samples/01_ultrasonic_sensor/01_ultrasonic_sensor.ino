int trigPin = A0;
int echoPin = A1;

void setup() {
  Serial.begin(9600);       
  pinMode(echoPin, INPUT);   
  pinMode(trigPin, OUTPUT);  
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, HIGH);                        
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);                  
  distance = ((float)(340 * duration) / 1000) / 2; 
  Serial.print("distance:");                          
  Serial.print(distance);
  Serial.println("mm");
  delay(500);
}
