#define IO_USERNAME    "mig3linho"
#define IO_KEY         
//#define WIFI_SSID      
//#define WIFI_PASS      
#define WIFI_SSID       
#define WIFI_PASS       

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#include <AdafruitIO.h>
#include <ArduinoHttpClient.h>

int soil = 0;
int sensorValue = 0;

// set up the 'kasvikosteus' feed
AdafruitIO_Feed *kasvikosteus = io.feed("kasvikosteus");

float h;

void setup() {

  // start the serial connection
  Serial.begin(9600);

  // wait for serial monitor to open
  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens


  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.println("Connecting...");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}


void loop() {

  io.run();

  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  //map the value to a percentage
  soil = map(sensorValue, 1024, 0, 0, 100);


  Serial.print(soil);
  Serial.println("%");
  delay(60000);

  kasvikosteus->save(soil);

}




