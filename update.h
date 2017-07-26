#include <ArduinoOTA.h>
#include <ESP8266httpUpdate.h>
#include <Ticker.h>

Ticker updateCheck;
boolean doUpdateCheck = true;

void enableUpdateCheck() {
  doUpdateCheck = true;
}

void OTA_setup(){
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

void check_for_updates() {
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
          icon_update();
          break;
      }
    }
    doUpdateCheck = false;
  }
}
