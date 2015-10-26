//Daniel Devine - Rushed together on 26/10/15

#include <RCSwitch.h>    // Imports the Radio library
#include <NewPing.h>     // Imports the Ultrasonic library

int TRIGGER_PIN = 12;   // Arduino pin tied to trigger pin on the ultrasonic sensor.
int ECHO_PIN = 11;      // Arduino pin tied to echo pin on the ultrasonic sensor.
int MAX_DISTANCE = 100; // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
RCSwitch mySwitch = RCSwitch();                     // 

void setup() {
  mySwitch.enableTransmit(10);  // Using Pin #10
}

void loop() {

  if ((sonar.ping_cm() > 1) && (sonar.ping_cm() < 50)){
    mySwitch.send(21, 24);  //on
    delay(10000);  
    mySwitch.send(20, 24);  //off
    delay(100);
  } 
 

}
