#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include "version.h"
#include "definitions.h"

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <Hash.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "ntp.h"
#include "leddisplay.h"
#include "filesystem.h"
#include "websocket.h"
#include "webserver.h"
#include "update.h"
#include "wifi.h"
#include "mdns.h"
#include <ESP8266Ping.h>

bool testDisplayOFFtime(){
  int acttime = hour() * 60 + minute();
  int offbegin = atoi(&OFFtime_begin[0]) * 60 + atoi(&OFFtime_begin[3]);
  int offend = atoi(&OFFtime_end[0]) * 60 + atoi(&OFFtime_end[3]);
  // start = end => no OFF time
  if (offbegin == offend)
    return false;
  // see if start comes before end
  if (offbegin < offend)
    return offbegin <= acttime && acttime <= offend;
  // start is after end, so do the inverse comparison
    return !(offend <= acttime && acttime <= offbegin);
}

void setup() {
  // put your setup code here, to run once:
  DBG_OUTPUT.begin(115200);

  // print the actual version number
  DBG_OUTPUT.println("SKETCH_VERSION = " SKETCH_VERSION);

  // filesystem
  FS_setup();
  
  // LED
  LEDs_setup();

  // wifi
  WIFI_setup();

  if ((WiFi.status() == WL_CONNECTED) && Ping.ping("www.google.com")) {
    // OTA and HTTP_updates
    OTA_setup();

    // NTP
    NTP_setup();

    // WebSocket
    WebSocket_setup();

    // WebServer
    WebServer_setup();

    // mDNS
    mDNS_setup();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  check_for_updates();
  check_for_config_portal_request();
  check_for_webserver_event();
  //check_for_websocket_event();     //we switched to async mode

  if (second() != lastSecond) {
    lastSecond = second();
    char sTime[14] = {0};
    sprintf(sTime,"time=%02i:%02i:%02i", hour(), minute(), second());
    webSocket.broadcastTXT(sTime);

    int iRoomBrightness = analogRead(iLightsensorPin);
    char sRoomBrightness[16] = {0};
    sprintf(sRoomBrightness,"brightness=%04i", iRoomBrightness);
    webSocket.broadcastTXT(sRoomBrightness);
    DBG_OUTPUT.printf("Lightsensor = %u", iRoomBrightness);
    DBG_OUTPUT.println("");
  }
  
  if (minute() != lastMinute) {
    lastMinute = minute();
    char sTime[14] = {0};
    sprintf(sTime,"time=%02i:%02i:%02i", hour(), minute(), second());
    DBG_OUTPUT.println(sTime);
    
    if (!testDisplayOFFtime()) {
      DBG_OUTPUT.println("Display ON");
      if ((iMode == 1) && (minute() % 5 == 0)){
        animation();
      }
      if ((iMode == 2) && (minute() % 15 == 0)){
        animation();
      }
      if ((iMode == 3) && (minute() == 0)){
        animation();
      }      
      uhrdisp();
    } else {
      clear_disp();
      DBG_OUTPUT.println("Display OFF");
    }
  }
}
