// ---------------------------------------------------------------------------
#include <Servo.h>
// ---------------------------------------------------------------------------
// Customize here pulse lengths as needed
#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000 // Maximum pulse length in µs
#define Button_Up 14
#define Button_Down 16
#define Charge_Discharge 7
#define Direction 5
#define Rotation_Control_Relay 8
#define Charge_Discharge_Relay 9

#define INT0 3
#define INT1 2
//#define INT2 0
//#define INT3 1
//#define INT4 7

#define tx_pin 1
#define rx_pin 0

#define ESC_PowerOn_Relay 10

// ---------------------------------------------------------------------------
Servo ESC;
int data;
// ---------------------------------------------------------------------------
int Pulse_Length = 0;
bool ESC_ON = 0;
//   Initialisation routine
//*/
void setup() {

  Serial.begin(9600);

  ESC.attach(2, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);


  pinMode(Button_Up, INPUT_PULLUP);
  pinMode(Button_Down, INPUT_PULLUP);

  pinMode(Charge_Discharge, INPUT);
  pinMode(Direction, INPUT);

  pinMode(Charge_Discharge_Relay, OUTPUT);
  pinMode(Rotation_Control_Relay, OUTPUT);

  pinMode(ESC_PowerOn_Relay, OUTPUT);

  //attachInterrupt(digitalPinToInterrupt(INT0), ESC_TOGGLE, RISING);

  //attachInterrupt(digitalPinToInterrupt(Button_Up), Motor_Up, FALLING);
  //attachInterrupt(digitalPinToInterrupt(Button_Down), Motor_Down, FALLING);

  //Serial.println("Input Pulse Time :");
  //displayInstructions();
  //digitalWrite(ESC_PowerOn_Relay, HIGH);
  digitalWrite(ESC_PowerOn_Relay, LOW);

  delay(1000);
  
  //ESC.writeMicroseconds(1600);
}
/**
   Main function
*/
void loop() {

  //ESC.writeMicroseconds(Pulse_Length);

  if (digitalRead(Button_Up) == LOW){
    Motor_Start();
    //digitalWrite(ESC_PowerOn_Relay, HIGH);
  }
  else
    //digitalWrite(ESC_PowerOn_Relay, LOW);
    
    

  if (digitalRead(Button_Down) == LOW){
    Motor_Stop();
    //digitalWrite(ESC_PowerOn_Relay, LOW);
  }
    
    

  if (digitalRead(Charge_Discharge) == HIGH) {
    Serial.println("DISCHARGE");
    digitalWrite(Charge_Discharge_Relay, HIGH);
    digitalWrite(ESC_PowerOn_Relay, LOW);
  }
  else
    Serial.println("CHARGE");

    digitalWrite(Charge_Discharge_Relay, LOW);
    digitalWrite(ESC_PowerOn_Relay, HIGH);


  if (digitalRead(Direction) == HIGH) {
    digitalWrite(Rotation_Control_Relay, HIGH);
    Serial.println("RotationChange");
  }
  else
    digitalWrite(Rotation_Control_Relay, LOW);

  //Serial.println(Pulse_Length);
  //delay(100);

}
void Motor_Start(){
  delay(300);
    Serial.println("START");
    Pulse_Length = 1700;
    ESC.writeMicroseconds(Pulse_Length);
  delay(300);
}
void Motor_Stop(){
  
    delay(300);
    Serial.println("STOP");
    Pulse_Length = 0;
    ESC.writeMicroseconds(Pulse_Length);
  delay(300);
}
void ESC_TOGGLE(){

}
