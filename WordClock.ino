#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include "version.h"
#include "definitions.h"

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <Hash.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "filesystem.h"
#include "ntp.h"
#include "leddisplay.h"
#include "update.h"
#include "wifi.h"

ESP8266WebServer webServer ( 80 );
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) {
    case WStype_DISCONNECTED:
      DBG_OUTPUT.printf("[%u] Disconnected!\n", num);
      break;

    case WStype_CONNECTED: {
        IPAddress ip = webSocket.remoteIP(num);
        DBG_OUTPUT.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        webSocket.sendTXT(num, "Connected");
      }
      break;

    case WStype_TEXT:
      DBG_OUTPUT.printf("[%u] get Text: %s\n", num, payload);

      if (payload[0] == '#') {
        // we get RGB data

        // decode rgb data
        uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);

        colorR = ((rgb >> 16) & 0xFF);
        colorG = ((rgb >> 8) & 0xFF);
        colorB = ((rgb >> 0) & 0xFF);

        if (iMode == 0)
          uhrdisp();
      }
      break;

    case WStype_BIN:
      break;

    default:
      break;
  }
}

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
  check_for_config_portal_request();

  // OTA and HTTP_updates
  OTA_setup();

  // NTP
  NTP_setup();

  // start webSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  if ( MDNS.begin ( "WordClock" ) ) {
    DBG_OUTPUT.println ( "MDNS responder started" );
  }

  // handle index
  webServer.on("/", []() {
    // send index.html
    webServer.send(200, "text/html", "<html><head><script>var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);connection.onopen = function () {  connection.send('Connect ' + new Date()); }; connection.onerror = function (error) {    console.log('WebSocket Error ', error);};connection.onmessage = function (e) {  console.log('Server: ', e.data);};function sendRGB() {  var r = parseInt(document.getElementById('r').value).toString(16);  var g = parseInt(document.getElementById('g').value).toString(16);  var b = parseInt(document.getElementById('b').value).toString(16);  if(r.length < 2) { r = '0' + r; }   if(g.length < 2) { g = '0' + g; }   if(b.length < 2) { b = '0' + b; }   var rgb = '#'+r+g+b;    console.log('RGB: ' + rgb); connection.send(rgb); }</script></head><body><div>LED Control:<br/><br/>R: <input id=\"r\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/>G: <input id=\"g\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/>B: <input id=\"b\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/></div></body></html>");
  });

  webServer.begin();

  // Add service to MDNS
  MDNS.addService("http", "tcp", 80);
  MDNS.addService("ws", "tcp", 81);
}

void loop() {
  // put your main code here, to run repeatedly:

  check_for_updates();
  check_for_config_portal_request();

  webServer.handleClient();
  webSocket.loop();

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
