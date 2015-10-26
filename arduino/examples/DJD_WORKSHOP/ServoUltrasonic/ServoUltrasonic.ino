//Daniel Devine - Rushed together on 26/10/15

#include <NewPing.h>
#include <Servo.h> 

int TRIGGER_PIN = 12;     // Arduino pin tied to trigger pin on the ultrasonic sensor.
int ECHO_PIN = 11;        // Arduino pin tied to echo pin on the ultrasonic sensor.
int MAX_DISTANCE = 100;   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int val;                  // Value for storing distance

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Servo myservo;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  myservo.attach(9);
}

void loop() {
  delay(50);                       // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  val = sonar.ping_cm();           // Sets val to the current distance
  val = map(val, 0, 100, 0, 180);  // Maps val (zero to one hundred) to servo (zero to one hundred and eighty)
  myservo.write(val);              // Moves servo to current val
  Serial.print("Ping: ");          // For debugging
  Serial.print(val);               // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}
