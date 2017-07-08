#include "version.h"
#include "definitions.h"

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "update.h"
#include "ntp.h"

int lastMinute;

void setup() {
  // put your setup code here, to run once:
  DBG_OUTPUT.begin(115200);

  // print the actual version number
  DBG_OUTPUT.println("SKETCH_VERSION = " SKETCH_VERSION);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset saved settings
  //wifiManager.resetSettings();

  //fetches ssid and pass from eeprom and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "WortuhrAP"
  //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("WordClockAP", "1234WordClock5678");

  //if you get here you have connected to the WiFi
  DBG_OUTPUT.println("connected...yeey :)");

  // OTA and HTTP_updates
  OTA_setup();

  // NTP
  NTP_setup();
}

void loop() {
  // put your main code here, to run repeatedly:

  check_for_updates();

  if (minute() != lastMinute) {
    lastMinute = minute();
    DBG_OUTPUT.print(hour());
    DBG_OUTPUT.print(":");
    DBG_OUTPUT.print(minute());
    DBG_OUTPUT.print(":");
    DBG_OUTPUT.println(second());
  }
}
