/**
 * Usage, according to documentation(https://www.firediy.fr/files/drone/HW-01-V4.pdf) : 
 *     1. Plug your Arduino to your computer with USB cable, open terminal, then type 1 to send max throttle to every ESC to enter programming mode
 *     2. Power up your ESCs. You must hear "beep1 beep2 beep3" tones meaning the power supply is OK
 *     3. After 2sec, "beep beep" tone emits, meaning the throttle highest point has been correctly confirmed
 *     4. Type 0 to send min throttle
 *     5. Several "beep" tones emits, which means the quantity of the lithium battery cells (3 beeps for a 3 cells LiPo)
 *     6. A long beep tone emits meaning the throttle lowest point has been correctly confirmed
 *     7. Type 2 to launch test function. This will send min to max throttle to ESCs to test them
 *
 * @author lobodol <grobodol@gmail.com>
 */
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

// ---------------------------------------------------------------------------
Servo ESC;
int data;
// ---------------------------------------------------------------------------
int Pulse_Length = 0;
/**
 * Initialisation routine
 */
void setup() {
  
    Serial.begin(9600);
    
    ESC.attach(2, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);


    pinMode(Button_Up, INPUT_PULLUP);
    pinMode(Button_Down, INPUT_PULLUP);

    pinMode(Charge_Discharge, INPUT);
    pinMode(Direction, INPUT);

    pinMode(Charge_Discharge_Relay, OUTPUT);
    pinMode(Rotation_Control_Relay, OUTPUT);
        
    //attachInterrupt(digitalPinToInterrupt(Button_Up), Motor_Up, FALLING);
    //attachInterrupt(digitalPinToInterrupt(Button_Down), Motor_Down, FALLING);
    
    //Serial.println("Input Pulse Time :");    
    //displayInstructions();
    delay(10000);
    ESC.writeMicroseconds(1600);
}

/**
 * Main function
 */
void loop() {

  //ESC.writeMicroseconds(Pulse_Length);

  if(digitalRead(Button_Up) == LOW)
    Motor_Up();

      if(digitalRead(Button_Down) == LOW)
    Motor_Down();
    
  if(digitalRead(Charge_Discharge) == HIGH){
    Serial.println("CHARGE");
  
    digitalWrite(Charge_Discharge_Relay, HIGH);
  }
  else 
    digitalWrite(Charge_Discharge_Relay, LOW);

    
  if(digitalRead(Direction) == HIGH){
    digitalWrite(Rotation_Control_Relay, HIGH);
    Serial.println("CHARGE");
  }
  else 
    digitalWrite(Rotation_Control_Relay, LOW);
    
  Serial.println(Pulse_Length);
  delay(100);

}

void Motor_Up(){
  delay(300);
    Serial.println("STOP");
    ESC.writeMicroseconds(0);
  delay(300);
}
void Motor_Down(){
  
    delay(300);
    Serial.println("START");
    ESC.writeMicroseconds(2000);
  delay(300);
}
//void serial(){
//    if (Serial.available()) {
//        data = Serial.read();
//
//        switch (data) {
//            // 0
//            case 48 : Serial.println("Sending minimum throttle");
//                      ESC.writeMicroseconds(MIN_PULSE_LENGTH);
//
//            break;
//
//            // 1
//            case 49 : Serial.println("Sending maximum throttle");
//                      ESC.writeMicroseconds(MAX_PULSE_LENGTH);
//
//            break;
//
//            // 2
//            case 50 : Serial.print("Running test in 3");
//                      delay(1000);
//                      Serial.print(" 2");
//                      delay(1000);
//                      Serial.println(" 1...");
//                      delay(1000);
//                      test();
//            break;
//        }
//    }
//  }

/**
 * Test function: send min throttle to max throttle to each ESC.
 */

 
void test()
{
    for (int i = MIN_PULSE_LENGTH; i <= MAX_PULSE_LENGTH; i += 5) {
        Serial.print("Pulse length = ");
        Serial.println(i);
        
        ESC.writeMicroseconds(i);

        
        delay(200);
    }

    Serial.println("STOP");
    ESC.writeMicroseconds(MIN_PULSE_LENGTH);

}

/**
 * Displays instructions to user
 */
void displayInstructions()
{  
    Serial.println("READY - PLEASE SEND INSTRUCTIONS AS FOLLOWING :");
    Serial.println("\t0 : Send min throttle");
    Serial.println("\t1 : Send max throttle");
    Serial.println("\t2 : Run test function\n");
}
