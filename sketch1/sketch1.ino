#include <SoftwareSerial.h>
SoftwareSerial ss(7, 8);

char t;
const int buzz= 13;
int state = LOW;
int val = 0;
int sensor = 6;

int rainSensorPin = 5;
const int ldrPin = A0;
const int xInput = A0;
const int yInput = A1;
const int zInput = A2;

int motorPin1 = 9;
int motorPin2 = 10;
int motorPin3 = 11;
int motorPin4 = 12;

int RawMin = 0;
int RawMax = 1023;
const int sampleSize = 10;

void setup() {
  analogReference(EXTERNAL);
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(buzz, OUTPUT);
  pinMode(sensor,INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(12,OUTPUT);   //left motors reverse
  pinMode(11,OUTPUT);   //right motors forward
  pinMode(10,OUTPUT);   //right motors reverse
  pinMode(9,OUTPUT);}

#
void MOIST(){
  int rainValue = digitalRead(rainSensorPin);
  if (rainValue == HIGH) {
    Serial.println("Water detected.");
    }
  else {
    Serial.println("No water detected.");
  }

  delay(1000); }
 
void MOTION(){
  val = digitalRead(sensor);
  if (val == HIGH) {
    delay(100);
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }}
  else {
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }}

void GPS(){
  while (ss.available() > 0){
    // get the byte data from the GPS
    byte gpsData = ss.read();
    Serial.write(gpsData);
 }}

void LDR() {
  int ldr = analogRead(ldrPin);
  delay(250);
  Serial.print("LDR : ");
  Serial.println(ldr);}

void ACC() {
	int xRaw = ReadAxis(xInput);
	int yRaw = ReadAxis(yInput);
	int zRaw = ReadAxis(zInput);

	long xScaled = map(xRaw, RawMin, RawMax, -3000, 3000);
	long yScaled = map(yRaw, RawMin, RawMax, -3000, 3000);
	long zScaled = map(zRaw, RawMin, RawMax, -3000, 3000);

	float xAccel = xScaled / 1000.0;
	float yAccel = yScaled / 1000.0;
	float zAccel = zScaled / 1000.0;

	Serial.print("X, Y, Z  :: ");
	Serial.print(xRaw);
	Serial.print(", ");
	Serial.print(yRaw);
	Serial.print(", ");
	Serial.print(zRaw);
	Serial.print(" :: ");
	Serial.print(xAccel,0);
	Serial.print("G, ");
	Serial.print(yAccel,0);
	Serial.print("G, ");
	Serial.print(zAccel,0);
	Serial.println("G");
	delay(250);}
int ReadAxis(int axisPin){
  long reading = 0;
	analogRead(axisPin);
	delay(1);
	for (int i = 0; i < sampleSize; i++){
	reading += analogRead(axisPin);}
	return reading/sampleSize;}




void loop(){
 if(Serial.available()){
  t = Serial.read();
  Serial.println(t);}
if(t == 'F'){
digitalWrite(12,HIGH);
digitalWrite(10,HIGH);}

else if (t == 'A'){
ACC();}
 
    else if(t == 'B'){ 
  digitalWrite(11,HIGH);
  digitalWrite(9,HIGH);
  }
 
    else if(t == 'L'){ 
  digitalWrite(10,HIGH);
  }
 
    else if(t == 'R'){ 
  digitalWrite(12,HIGH);  
  }
    else {
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
}}