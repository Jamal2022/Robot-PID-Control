/*
Created on Sat May 23 15:32:44 2020
@author: Jamal Ali
Email : jamalabdu213@gmail.com
*/
// Varaible of the eqution PID
int error,P,I=0,D;
int Kp=50,Ki=0,Kd=0,PIDvalue,previousError=0;
const int lineFollowSensor0 = 12;
const int lineFollowSensor1 = 11;
const int lineFollowSensor2 = 10;
const int lineFollowSensor3 = 9;
const int lineFollowSensor4 = 8;
int LFSensor[5]={0, 0, 0, 0, 0};
// Varaible of the motor
int vit=100;
int vitesseM1=2;
int arriereM1=3;
int avantM1=4;
int vitesseM2=7;
int arriereM2=6;
int avantM2=5;

int mode=0;
void setup() {
 // The eqution PID
  pinMode(lineFollowSensor0,INPUT);
  pinMode(lineFollowSensor1,INPUT);
  pinMode(lineFollowSensor2,INPUT);
  pinMode(lineFollowSensor3,INPUT);
  pinMode(lineFollowSensor4,INPUT);
  Serial.begin(9600);
 // The motor
  pinMode(vitesseM1,OUTPUT);
  pinMode(arriereM1,OUTPUT);
  pinMode(avantM1,OUTPUT);
  pinMode(vitesseM2,OUTPUT);
  pinMode(arriereM2,OUTPUT);
  pinMode(avantM2,OUTPUT);
}
void readsensor(){
 // Read 
  LFSensor[0] = digitalRead(lineFollowSensor0);
  LFSensor[1] = digitalRead(lineFollowSensor1);
  LFSensor[2] = digitalRead(lineFollowSensor2);
  LFSensor[3] = digitalRead(lineFollowSensor3);
  LFSensor[4] = digitalRead(lineFollowSensor4);
  mode =1;
 // The error
  if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1)&&(LFSensor[3]== 1 )&&(LFSensor[4]== 0 )) {error = 4; mode=3;}
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1)&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0)) {mode=3;error = 4;}
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1)&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0)) {mode=3;error = 3;}
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1)&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 1)) {mode=3;error = 2;}
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1)&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 1)) {mode=3;error = 1;}
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1)&&(LFSensor[2]== 0 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1)) {mode=3;error = 0;}
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 0)&&(LFSensor[2]== 0 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1)) {mode=3;error =- 1;}
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 0)&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1)) {mode=3;error = -2;}
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0)&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1)) {mode=3;error = -3;}
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0)&&(LFSensor[2]== 0 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1)) {mode=3;error = -4;}
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1)&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1)) {mode=3;error = -4;}
  
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0)&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0 )) mode = 1;
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1)&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1)) mode = 2;
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 0)&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 1)) mode = 2;
 }
void calculatePID(){
  P = error;
  I = I + error;
  D = error-previousError;
  PIDvalue = (Kp*P) + (Ki*I) + (Kd*D);
  previousError = error;
  Serial.println(PIDvalue);
}
void loop() {
  readsensor();
  switch (mode)
  {
    case 1://stop
      motorstop();
      Serial.println("The end ");
      break;
    case 2://no line
      Serial.println("noline");
      motorBackward();
      break;
    case 3:
      calculatePID();
      motor();
      break;
 } 
}
void motor(){
  int vit1=vit-PIDvalue;
  if(error<0){
    if (error =-2){
     vit1 = 100;
    }
    Serial.println("Right");
 
    analogWrite(vitesseM1,vit1);
    digitalWrite(arriereM1,HIGH);
    digitalWrite(avantM1,LOW);
    analogWrite(vitesseM2,vit1);
    digitalWrite(arriereM2,LOW);
    digitalWrite(avantM2,HIGH);
  }
  else if (error>0){
    if (error =2){
     vit1 = 100;
    }
    Serial.println("left");
    analogWrite(vitesseM1,vit1);
    digitalWrite(arriereM1,LOW);
    digitalWrite(avantM1,HIGH);
    analogWrite(vitesseM2,vit1);
    digitalWrite(arriereM2,HIGH);
    digitalWrite(avantM2,LOW);
  }
  else if (error==0){
    Serial.println("forward");
    analogWrite(vitesseM1,vit1);
    digitalWrite(arriereM1,LOW);
    digitalWrite(avantM1,HIGH);
    analogWrite(vitesseM2,vit1);
    digitalWrite(arriereM2,LOW);
    digitalWrite(avantM2,HIGH);
  }
}
void motorstop(){
   digitalWrite(avantM1,LOW);
   digitalWrite(arriereM1,LOW);
   digitalWrite(avantM2,LOW);
   digitalWrite(arriereM2,LOW);
 }
void motorBackward(){
   analogWrite(vitesseM1,50);
   digitalWrite(avantM1,LOW);
   digitalWrite(arriereM1,HIGH);
   analogWrite(vitesseM2,100);
   digitalWrite(avantM2,LOW);
   digitalWrite(arriereM2,HIGH);
 }
