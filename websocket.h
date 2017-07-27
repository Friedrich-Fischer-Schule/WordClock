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
        webSocket.sendTXT(num, "OK");

        if (iMode == 0)
          uhrdisp();
      }

      // $ ==> Set Clock mode.
      if (payload[0] == '~') {
        iMode = (uint8_t) strtol((const char *) &payload[1], NULL, 10);
        iMode = constrain(iMode, 0, 255);
        DBG_OUTPUT.printf("WS: received new iMode=%i\n", iMode);
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

