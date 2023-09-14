#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo;

SoftwareSerial bluetoothSerial(2, 3);             //RX,TX

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

char value;
int led1=A0,led2=A1,led3=A2; 
int buzzpin=A3;
int trigPin=A4,echoPin=A5; 
long duration;
int distance,distanceR,distanceL;

void setup() {
 bluetoothSerial.begin(9600);
 
 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
 pinMode(buzzpin,OUTPUT);

 pinMode(trigPin,OUTPUT);
 pinMode(echoPin,INPUT);
  
 myservo.attach(10);  
 myservo.write(115);
}

void loop() {
  if(bluetoothSerial.available()>0)
  {
    value = bluetoothSerial.read();
    bluetoothSerial.println(value);
  }

  if(value=='F')                                       //FORWARD
  {
    distance=readPing();

    if(distance<=20){
      digitalWrite(buzzpin,HIGH);
      Stop();
      delay(100);
      moveBackward();
      delay(500);
      Stop();
      delay(100);
      digitalWrite(buzzpin,LOW);
    }
    else {
    motor1.setSpeed(220);
    motor1.run(FORWARD);
    motor2.setSpeed(220);
    motor2.run(FORWARD);
    motor3.setSpeed(220);
    motor3.run(FORWARD);
    motor4.setSpeed(220);
    motor4.run(FORWARD);
    }
  }
  if(value=='B')                                               //BACKWARD
  {
    motor1.setSpeed(220);
    motor1.run(BACKWARD);
    motor2.setSpeed(220);
    motor2.run(BACKWARD);
    motor3.setSpeed(220);
    motor3.run(BACKWARD);
    motor4.setSpeed(220);
    motor4.run(BACKWARD);
  }
  if(value=='R')                                                //RIGHT
  {
    motor1.setSpeed(220);
    motor1.run(BACKWARD);
    motor2.setSpeed(220);
    motor2.run(FORWARD);
    motor3.setSpeed(220);
    motor3.run(FORWARD);
    motor4.setSpeed(220);
    motor4.run(BACKWARD);
  }
  if(value=='L')                                                 //LEFT 
  {
    motor1.setSpeed(220);
    motor1.run(FORWARD);
    motor2.setSpeed(220);
    motor2.run(BACKWARD);
    motor3.setSpeed(220);
    motor3.run(BACKWARD);
    motor4.setSpeed(220);
    motor4.run(FORWARD);
  }

  if (value=='r')                                                 //NORTH-EAST
  {
    motor1.setSpeed(70);
    motor1.run(FORWARD);
    motor2.setSpeed(220);
    motor2.run(FORWARD);
    motor3.setSpeed(220);
    motor3.run(FORWARD);
    motor4.setSpeed(70);
    motor4.run(FORWARD);
  }

  if (value=='l')                                                   //NORTH-WEST
  {
    motor1.setSpeed(220);
    motor1.run(FORWARD);
    motor2.setSpeed(70);
    motor2.run(FORWARD);
    motor3.setSpeed(70);
    motor3.run(FORWARD);
    motor4.setSpeed(220);
    motor4.run(FORWARD);
  }

  if (value=='n')                                                 //SOUTH-EAST
  {
    Obstacle();
  }

  if (value=='m')                                                   //SOUTH-WEST
  {
    motor1.setSpeed(220);
    motor1.run(BACKWARD);
    motor2.setSpeed(70);
    motor2.run(BACKWARD);
    motor3.setSpeed(70);
    motor3.run(BACKWARD);
    motor4.setSpeed(220);
    motor4.run(BACKWARD);
  }
  
  if(value=='Y')                                           //LED ON
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
  }
  if(value=='y')                                           //LED OFF
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
  }
  if(value=='Z')
  {
    digitalWrite(buzzpin,HIGH);
  }
  if(value=='S')
  {
    digitalWrite(buzzpin,LOW);
    motor1.setSpeed(0);
    motor1.run(RELEASE);
    motor2.setSpeed(0);
    motor2.run(RELEASE);
    motor3.setSpeed(0);
    motor3.run(RELEASE);
    motor4.setSpeed(0);
    motor4.run(RELEASE);
  }
}

void Obstacle(){
    distance=readPing();

    if(distance<=15){
      digitalWrite(buzzpin,HIGH);
      Stop();
      delay(100);
      moveBackward();
      delay(500);
      Stop();
      delay(100);
      digitalWrite(buzzpin,LOW);
      distanceR=lookRight();
      delay(200);
      distanceL=lookLeft();
      delay(200);
  
      if(distanceR > distanceL) {
        moveRight();
      }
      else moveLeft();
    }
    else moveForward();  
}

int readPing() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

void Stop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward() {
  motor1.setSpeed(220);
  motor1.run(FORWARD);
  motor2.setSpeed(220);
  motor2.run(FORWARD);
  motor3.setSpeed(220);
  motor3.run(FORWARD);
  motor4.setSpeed(220);
  motor4.run(FORWARD);
}

void moveBackward() {
  motor1.setSpeed(220);
  motor1.run(BACKWARD);
  motor2.setSpeed(220);      
  motor2.run(BACKWARD);
  motor3.setSpeed(220);
  motor3.run(BACKWARD);
  motor4.setSpeed(220);
  motor4.run(BACKWARD);  
}

void moveRight() {
  motor1.setSpeed(220);
  motor1.run(BACKWARD);
  motor2.setSpeed(220);
  motor2.run(FORWARD);
  motor3.setSpeed(220);
  motor3.run(FORWARD); 
  motor4.setSpeed(220);
  motor4.run(BACKWARD);
  delay(500);

  motor1.setSpeed(220);
  motor1.run(FORWARD);
  motor2.setSpeed(220);
  motor2.run(FORWARD);
  motor3.setSpeed(220);
  motor3.run(FORWARD);
  motor4.setSpeed(220);
  motor4.run(FORWARD);
}

void moveLeft() {
  motor1.setSpeed(220);
  motor1.run(FORWARD);
  motor2.setSpeed(220);
  motor2.run(BACKWARD);
  motor3.setSpeed(220);
  motor3.run(BACKWARD);
  motor4.setSpeed(220);
  motor4.run(FORWARD);
  delay(500);

  motor1.setSpeed(220);
  motor1.run(FORWARD);
  motor2.setSpeed(220);
  motor2.run(FORWARD);
  motor3.setSpeed(220);
  motor3.run(FORWARD);
  motor4.setSpeed(220);
  motor4.run(FORWARD);
}

int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}
