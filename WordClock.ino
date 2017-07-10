#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include "version.h"
#include "definitions.h"

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "update.h"
#include "ntp.h"

//default custom static IP
char static_ip[16] = "10.0.1.56";
char static_gw[16] = "10.0.1.1";
char static_sn[16] = "255.255.255.0";

//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback () {
  DBG_OUTPUT.println("Should save config");
  shouldSaveConfig = true;
}

int lastMinute;

void setup() {
  // put your setup code here, to run once:
  DBG_OUTPUT.begin(115200);

  // print the actual version number
  DBG_OUTPUT.println("SKETCH_VERSION = " SKETCH_VERSION);

  //clean FS, for testing
  //SPIFFS.format();

  //read configuration from FS json
  DBG_OUTPUT.println("mounting FS...");

  if (SPIFFS.begin()) {
    DBG_OUTPUT.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      DBG_OUTPUT.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        DBG_OUTPUT.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(DBG_OUTPUT);
        if (json.success()) {
          DBG_OUTPUT.println("\nparsed json");

          if(json["ip"]) {
            DBG_OUTPUT.println("setting custom ip from config");
            //static_ip = json["ip"];
            strcpy(static_ip, json["ip"]);
            strcpy(static_gw, json["gateway"]);
            strcpy(static_sn, json["subnet"]);

            DBG_OUTPUT.println(static_ip);
          } else {
            DBG_OUTPUT.println("no custom ip in config");
          }
        } else {
          DBG_OUTPUT.println("failed to load json config");
        }
      }
    }
  } else {
    DBG_OUTPUT.println("failed to mount FS");
  }
  //end read

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  //set static ip
  IPAddress _ip,_gw,_sn;
  _ip.fromString(static_ip);
  _gw.fromString(static_gw);
  _sn.fromString(static_sn);

  wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn);

  //reset saved settings
  //wifiManager.resetSettings();

  //fetches ssid and pass from eeprom and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "WortuhrAP"
  //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("WordClockAP", "1234WordClock5678");

  //if you get here you have connected to the WiFi
  DBG_OUTPUT.println("connected...yeey :)");

  //save the custom parameters to FS
  if (shouldSaveConfig) {
    DBG_OUTPUT.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

    json["ip"] = WiFi.localIP().toString();
    json["gateway"] = WiFi.gatewayIP().toString();
    json["subnet"] = WiFi.subnetMask().toString();

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      DBG_OUTPUT.println("failed to open config file for writing");
    }

    json.prettyPrintTo(DBG_OUTPUT);
    json.printTo(configFile);
    configFile.close();
    //end save
  }

  DBG_OUTPUT.println("local ip");
  DBG_OUTPUT.println(WiFi.localIP());
  DBG_OUTPUT.println(WiFi.gatewayIP());
  DBG_OUTPUT.println(WiFi.subnetMask());

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
