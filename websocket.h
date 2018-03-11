#define WEBSOCKETS_NETWORK_TYPE NETWORK_ESP8266_ASYNC
#include <WebSocketsServer.h>

WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) {
    case WStype_DISCONNECTED:
      DBG_OUTPUT.printf("WS:[%u] Disconnected!\n", num);
      break;

    case WStype_CONNECTED: {
        IPAddress ip = webSocket.remoteIP(num);
        DBG_OUTPUT.printf("WS:[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        webSocket.sendTXT(num, "Connected");
        char dataString[20] = {0};
        sprintf(dataString,"#%02X%02X%02X",colorR,colorG,colorB);
        webSocket.sendTXT(num, dataString);
        sprintf(dataString,"OFFtime=%s-%s",OFFtime_begin,OFFtime_end);
        webSocket.sendTXT(num, dataString);
        sprintf(dataString,"version=%s", SKETCH_VERSION);
        webSocket.broadcastTXT(dataString);
        sprintf(dataString,"~%i", iMode);
        webSocket.broadcastTXT(dataString);      
        sprintf(dataString,"+%i", NEOPIXEL_PIN);
        webSocket.broadcastTXT(dataString);  
      }
      break;

    case WStype_TEXT:
      DBG_OUTPUT.printf("WS:[%u] get Text: %s\n", num, payload);

      // # ==> Set Clock color.
      if (payload[0] == '#') {
        // we get RGB data
        // decode rgb data
        uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);

        colorR = ((rgb >> 16) & 0xFF);
        colorG = ((rgb >> 8) & 0xFF);
        colorB = ((rgb >> 0) & 0xFF);
        DBG_OUTPUT.printf("WS: received RGB data R=%i G=%i B=%i\n", colorR, colorG, colorB);
        //webSocket.sendTXT(num, "OK");
        for(uint8_t i = 0; i < WEBSOCKETS_SERVER_CLIENT_MAX; i++) {
          if(i != num) {
            webSocket.sendTXT(i, payload);
          }
        }
        uhrdisp();
      }

      // $ ==> Set Clock mode.
      if (payload[0] == '~') {
        iMode = (uint8_t) strtol((const char *) &payload[1], NULL, 10);
        iMode = constrain(iMode, 0, 10);
        DBG_OUTPUT.printf("WS: received new iMode=%i\n", iMode);
        writeConfigFile();        
        webSocket.sendTXT(num, "OK");
        for(uint8_t i = 0; i < WEBSOCKETS_SERVER_CLIENT_MAX; i++) {
          if(i != num) {
            webSocket.sendTXT(i, payload);
          }
        }
      }

      // $ ==> Set LED pin.
      if (payload[0] == '+') {
        NEOPIXEL_PIN = (uint8_t) strtol((const char *) &payload[1], NULL, 10);
        NEOPIXEL_PIN = constrain(NEOPIXEL_PIN, 0, 10);
        DBG_OUTPUT.printf("WS: received new LEDPin number=%i\n", NEOPIXEL_PIN);
        writeConfigFile();
        LEDs_setup();
        webSocket.sendTXT(num, "OK");
        for(uint8_t i = 0; i < WEBSOCKETS_SERVER_CLIENT_MAX; i++) {
          if(i != num) {
            webSocket.sendTXT(i, payload);
          }
        }
      }

      // OFFtime ==> save the on and off time (display).
      if (strncmp((char*)payload, "OFFtime=", 8) == 0) {
        strncpy ( OFFtime_begin, (char*)payload+8, 5 );
        strncpy ( OFFtime_end, (char*)payload+14, 5 );
        DBG_OUTPUT.printf("WS: received OFFtime command %s\n", payload);
        writeConfigFile();
        webSocket.sendTXT(num, "OK");
        for(uint8_t i = 0; i < WEBSOCKETS_SERVER_CLIENT_MAX; i++) {
          if(i != num) {
            webSocket.sendTXT(i, payload);
          }
        }
      }

      // testLED ==> test all LEDs with rainbow theme.
      if (strncmp((char*)payload, "testLED", 7) == 0) {
        DBG_OUTPUT.printf("WS: received testLED command\n");
        rainbow(50);
        uhrdisp();
        webSocket.sendTXT(num, "OK");
      }

      // saveSettings ==> save all settings (colors, brightness ...).
      if (strncmp((char*)payload, "saveSettings", 12) == 0) {
        DBG_OUTPUT.printf("WS: received saveSettings command\n");
        writeConfigFile();
        webSocket.sendTXT(num, "OK");
      }

      // resetWiFi ==> reset Wifi SSID and passphrase.
      if (strncmp((char*)payload, "resetWiFi", 9) == 0) {
        DBG_OUTPUT.printf("WS: received resetWiFi command\n");
        WiFiManager wifiManager;
        wifiManager.resetSettings();
        icon_resetWiFi();
        useDHCP = true;
        writeConfigFile();
        webSocket.sendTXT(num, "OK");
        delay(2000);
        ESP.reset();
      }

      // resetAll ==> delete SPIFFS.
      if (strncmp((char*)payload, "resetAll", 8) == 0) {
        DBG_OUTPUT.printf("WS: received resetAll command\n");
        SPIFFS.format();
        webSocket.sendTXT(num, "OK");
        delay(2000);
        ESP.reset();
      }

      // resetClock ==> reset clock.
      if (strncmp((char*)payload, "resetClock", 9) == 0) {
        DBG_OUTPUT.printf("WS: received resetClock command\n");
        webSocket.sendTXT(num, "OK");
        delay(1000);
        ESP.reset();
      }
      
      break;

    case WStype_BIN:
      break;

    default:
      break;
  }
}

void WebSocket_setup() {
  // start webSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void check_for_websocket_event() {
  webSocket.loop();
}

