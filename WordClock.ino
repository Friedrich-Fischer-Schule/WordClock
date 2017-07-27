#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include "version.h"
#include "definitions.h"

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <Hash.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "filesystem.h"
#include "ntp.h"
#include "leddisplay.h"
#include "update.h"
#include "wifi.h"
#include "websocket.h"
#include "webserver.h"
#include "mdns.h"
#include <ESP8266Ping.h>

void setup() {
  // put your setup code here, to run once:
  DBG_OUTPUT.begin(115200);

  // print the actual version number
  DBG_OUTPUT.println("SKETCH_VERSION = " SKETCH_VERSION);

  // LED
  LEDs_setup();

  // filesystem
  FS_setup();

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
  check_for_websocket_event();

  if (minute() != lastMinute) {
    lastMinute = minute();
    DBG_OUTPUT.print(hour());
    DBG_OUTPUT.print(":");
    DBG_OUTPUT.print(minute());
    DBG_OUTPUT.print(":");
    DBG_OUTPUT.println(second());

    if (iMode == 0)
      uhrdisp();

    if (iMode == 1)
      rainbow(20);

    if (iMode == 2)
      KNIGHT();

    if (iMode == 3)
      Schlange();
  }
}
