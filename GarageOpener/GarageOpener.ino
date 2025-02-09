#define BLYNK_TEMPLATE_ID "BLYNK_TEMPLATE_ID"         //just my template ID from the Blynk Service
#define BLYNK_TEMPLATE_NAME "ESP32 S3"                //Adafruit QT Py ESP32-S3 (with the onboard storage and RAM) is the board I used.
#define BLYNK_AUTH_TOKEN "BLYNK_AUTH_KEY"

#define BLYNK_PRINT Serial                            //Redefines the Blynk 'status prints' to print out to a Serial monitor port of your choice


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "WiFi_NAME";
char pass[] = "WiFi_PASSWORD";

#define RELAY_PIN A0

BLYNK_WRITE(V0) {                                     //Using Virtual Pin 0 to capture and relay signal
  if (param.asInt() == 1) {                           //param.asInt() used to grab input from V0
    digitalWrite(RELAY_PIN, HIGH);                    //Activate relay
    //Serial.println("🔴 Relay Activated (Garage Door Opening)"); //Debug through Console
    delay(500);                                       //hold for 0.5 sec
    digitalWrite(RELAY_PIN, LOW);                     //Deactivate relay
    //Serial.println("⚪ Relay Deactivated (Garage Door Closed)"); //Debug through Console
  }
}

void setup() {
  Serial.begin(115200);                               //Setting BAUD rate to 115200

  //Serial.println("🚀 Starting Virtual Garage Door Controller...");

  pinMode(RELAY_PIN, OUTPUT);                         //Pin configuration, letting it be set as either Input or Output. For the purposes of this project, it is in Output mode.
  digitalWrite(RELAY_PIN, LOW);                       //Starts on LOW


  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);          //Starts talking with Blink Service through the passed-in parameters
}

void loop() {
  Blynk.run();                                        //Runs the Blink Service
}
