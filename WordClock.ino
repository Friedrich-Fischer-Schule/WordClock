#include "version.h"

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <ArduinoOTA.h>
#include <ESP8266httpUpdate.h>
#include <Ticker.h>

#include "definitions.h"

Ticker updateCheck;
boolean doUpdateCheck = true;

void enableUpdateCheck() {
  doUpdateCheck = true;
}

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

  ArduinoOTA.onStart([]() {
    DBG_OUTPUT.println("OTA Start");
  });
  ArduinoOTA.onEnd([]() {
    DBG_OUTPUT.println("\nOTA End");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    DBG_OUTPUT.printf("OTA Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    DBG_OUTPUT.printf("OTA Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) DBG_OUTPUT.println("OTA Auth Failed");
    else if (error == OTA_BEGIN_ERROR) DBG_OUTPUT.println("OTA Begin Failed");
    else if (error == OTA_CONNECT_ERROR) DBG_OUTPUT.println("OTA Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) DBG_OUTPUT.println("OTA Receive Failed");
    else if (error == OTA_END_ERROR) DBG_OUTPUT.println("OTA End Failed");
  });
  ArduinoOTA.begin();

  // don't wanna miss a thing... Check every CHECK_INTERVAL seconds
  updateCheck.attach(CHECK_INTERVAL, enableUpdateCheck);
}

void loop() {
  // put your main code here, to run repeatedly:
  ArduinoOTA.handle();

  if (doUpdateCheck) {
    DBG_OUTPUT.println("Going to update firmware...");
    if ((WiFi.status() == WL_CONNECTED)) {

      DBG_OUTPUT.println("Checking for Update. Current version: " SKETCH_VERSION);
      t_httpUpdate_return ret = ESPhttpUpdate.update("http://www.friedmann-elektronik.de/Arduino/WordClock/firmware.php?tag=" SKETCH_VERSION);

      switch (ret) {
        case HTTP_UPDATE_FAILED:
          DBG_OUTPUT.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          break;

        case HTTP_UPDATE_NO_UPDATES:
          DBG_OUTPUT.println("HTTP_UPDATE_NO_UPDATES");
          break;

        case HTTP_UPDATE_OK:
          DBG_OUTPUT.println("HTTP_UPDATE_OK");
          break;
      }
    }
    doUpdateCheck = false;
  }
}
