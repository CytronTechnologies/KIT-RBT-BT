#include "pitches.h"

#define BT_TX 3
#define BT_RX 4
#include "SoftwareSerial.h"
SoftwareSerial BTSerial(BT_TX, BT_RX); // Maker UNO RX, TX

#define BUTTON  2
#define L293N_ENA 5
#define L293N_ENB 6
#define L293N_IN1 7
#define L293N_IN2 9
#define L293N_IN3 10
#define L293N_IN4 11

boolean BTConnect = false;
char inChar;
String inString;

void setup()
{
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(L293N_ENA, OUTPUT);
  pinMode(L293N_ENB, OUTPUT);
  pinMode(L293N_IN1, OUTPUT);
  pinMode(L293N_IN2, OUTPUT);
  pinMode(L293N_IN3, OUTPUT);
  pinMode(L293N_IN4, OUTPUT);

  Serial.begin(9600);
  BTSerial.begin(9600);

  delay(1000);
}

void loop()
{
  if (BTSerial.available()) {

    if (BTConnect == false) {
      BTConnect = true;
      playBtConnectMelody();
    }

//    delay(100);
    inString = "";
    while (BTSerial.available()) {
      inChar = BTSerial.read();
      inString = inString + inChar;
    }
    Serial.println(inString);

    if (inString == "#b=0#") {
      robotStop();
    }
    else if (inString == "#b=9#" ||
             inString == "#b=19#" ||
             inString == "#b=29#" ||
             inString == "#b=39#" ||
             inString == "#b=49#") {
      robotBreak();
    }
    else if (inString == "#b=1#") {
      robotForward(200);
    }
    else if (inString == "#b=2#") {
      robotReverse(200);
    }
    else if (inString == "#b=3#") {
      robotTurnLeft(150);
    }
    else if (inString == "#b=4#") {
      robotTurnRight(150);
    }
    else if (inString.startsWith("+DISC")) {
      BTConnect = false;
      delay(1000);
      while (HC06Serial.available()) {
        HC06Serial.read();
      }
      playBtDisconnectMelody();
    }
  }
}

void robotStop()
{
  digitalWrite(L293N_ENA, LOW);
  digitalWrite(L293N_IN1, LOW);
  digitalWrite(L293N_IN2, LOW);

  digitalWrite(L293N_ENB, LOW);
  digitalWrite(L293N_IN3, LOW);
  digitalWrite(L293N_IN4, LOW);
}

void robotBreak()
{
  digitalWrite(L293N_ENA, HIGH);
  digitalWrite(L293N_IN1, HIGH);
  digitalWrite(L293N_IN2, HIGH);

  digitalWrite(L293N_ENB, HIGH);
  digitalWrite(L293N_IN3, HIGH);
  digitalWrite(L293N_IN4, HIGH);
}

void robotForward(int motorSpeed)
{
  analogWrite(L293N_ENA, motorSpeed);
  digitalWrite(L293N_IN1, LOW);
  digitalWrite(L293N_IN2, HIGH);

  analogWrite(L293N_ENB, motorSpeed);
  digitalWrite(L293N_IN3, HIGH);
  digitalWrite(L293N_IN4, LOW);
}

void robotReverse(int motorSpeed)
{
  analogWrite(L293N_ENA, motorSpeed);
  digitalWrite(L293N_IN1, HIGH);
  digitalWrite(L293N_IN2, LOW);

  analogWrite(L293N_ENB, motorSpeed);
  digitalWrite(L293N_IN3, LOW);
  digitalWrite(L293N_IN4, HIGH);
}

void robotTurnRight(int motorSpeed)
{
  analogWrite(L293N_ENA, motorSpeed);
  digitalWrite(L293N_IN1, HIGH);
  digitalWrite(L293N_IN2, LOW);

  analogWrite(L293N_ENB, motorSpeed);
  digitalWrite(L293N_IN3, HIGH);
  digitalWrite(L293N_IN4, LOW);
}

void robotTurnLeft(int motorSpeed)
{
  analogWrite(L293N_ENA, motorSpeed);
  digitalWrite(L293N_IN1, LOW);
  digitalWrite(L293N_IN2, HIGH);

  analogWrite(L293N_ENB, motorSpeed);
  digitalWrite(L293N_IN3, LOW);
  digitalWrite(L293N_IN4, HIGH);
}
