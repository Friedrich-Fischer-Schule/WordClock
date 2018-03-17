#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson

bool readConfigFile() {
  // this opens the config file in read-mode
  File f = SPIFFS.open(CONFIG_FILE, "r");

  if (!f) {
    DBG_OUTPUT.println("Configuration file not found");
    return false;
  } else {
    // we could open the file
    size_t size = f.size();
    // Allocate a buffer to store contents of the file.
    std::unique_ptr<char[]> buf(new char[size]);

    // Read and store file contents in buf
    f.readBytes(buf.get(), size);
    // Closing file
    f.close();
    // Using dynamic JSON buffer which is not the recommended memory model, but anyway
    // See https://github.com/bblanchon/ArduinoJson/wiki/Memory%20model
    DynamicJsonBuffer jsonBuffer;
    // Parse JSON string
    JsonObject& json = jsonBuffer.parseObject(buf.get());
    // Test if parsing succeeds.
    if (!json.success()) {
      DBG_OUTPUT.println("JSON parseObject() failed");
      return false;
    }
    json.printTo(DBG_OUTPUT);
    DBG_OUTPUT.println("");

    // Parse all config file parameters, override
    // local config variables with parsed values

    if (json.containsKey("useDHCP")) {
      useDHCP = json["useDHCP"];
    }

    if (json["ip"]) {
      DBG_OUTPUT.println("setting custom ip from config");
      //static_ip = json["ip"];
      strcpy(static_ip, json["ip"]);
      strcpy(static_gw, json["gateway"]);
      strcpy(static_sn, json["subnet"]);

      DBG_OUTPUT.println(static_ip);
    } else {
      DBG_OUTPUT.println("no custom ip in config");
    }

    if (json.containsKey("colorR")) {
      colorR = json["colorR"];
      colorG = json["colorG"];
      colorB = json["colorB"];
      brightness = json["brightness"];
    }

    if (json.containsKey("autoDimm")) {
      autoDimm = (bool) json["autoDimm"];
    }

    if (json.containsKey("BrightUpper")) {
      BrightUpper = json["BrightUpper"];
      BrightLower = json["BrightLower"];
    }
    
    if (json.containsKey("OFFtime_begin")) {
      strcpy(OFFtime_begin, json["OFFtime_begin"]);
      strcpy(OFFtime_end, json["OFFtime_end"]);
    }

    if (json.containsKey("NEOPIXEL_PIN")) {
      NEOPIXEL_PIN = json["NEOPIXEL_PIN"];
    } else {
      // check if a lightsensor is available, if it is it is the new hardware
      if (analogRead(iLightsensorPin) > 100) {
        NEOPIXEL_PIN = 2;
      }
    }
  }
  DBG_OUTPUT.println("\nConfig file was successfully parsed");
  return true;
}

bool writeConfigFile() {
  DBG_OUTPUT.println("Saving config file");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();

  // JSONify local configuration parameters
  json["ip"] = WiFi.localIP().toString();
  json["gateway"] = WiFi.gatewayIP().toString();
  json["subnet"] = WiFi.subnetMask().toString();

  json["useDHCP"] = useDHCP;

  json["colorR"] = colorR;
  json["colorG"] = colorG;
  json["colorB"] = colorB;
  json["brightness"] = brightness;
  json["BrightUpper"] = BrightUpper;
  json["BrightLower"] = BrightLower;
  json["autoDimm"] = autoDimm;

  json["OFFtime_begin"] = OFFtime_begin;
  json["OFFtime_end"] = OFFtime_end;

  json["NEOPIXEL_PIN"] = NEOPIXEL_PIN;

  // Open file for writing
  File f = SPIFFS.open(CONFIG_FILE, "w");
  if (!f) {
    DBG_OUTPUT.println("Failed to open config file for writing");
    return false;
  }

  json.prettyPrintTo(DBG_OUTPUT);
  // Write data to file and close it
  json.printTo(f);
  f.close();

  DBG_OUTPUT.println("\nConfig file was successfully saved");
  return true;
}

void FS_setup() {

  SPIFFS.begin();
  
  //clean FS, for testing
  //SPIFFS.format();

  if (!readConfigFile()) {
    DBG_OUTPUT.println("Failed to read configuration file, using default values");
    // check if a lightsensor is available, if it is it is the new hardware
    if (analogRead(iLightsensorPin) > 100) {
      NEOPIXEL_PIN = 2;
    }
  }
}
