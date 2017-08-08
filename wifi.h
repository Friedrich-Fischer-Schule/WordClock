
// Indicates whether ESP has WiFi credentials saved from previous session
bool initialConfig = false;
char customhtml[24] = "type=\"checkbox\"";

void WIFI_setup() {

  //Remove this line if you do not want to see WiFi password printed
  //WiFi.printDiag(DBG_OUTPUT);

  if (WiFi.SSID() == "") {
    DBG_OUTPUT.println("We haven't got any access point credentials, so get them now");
    initialConfig = true;
  } else {
    WiFi.mode(WIFI_STA); // Force to station mode because if device was switched off while in access point mode it will start up next time in access point mode.

    if (useDHCP) {
      strcat(customhtml, " checked");
    } else {    //set static ip
      IPAddress _ip, _gw, _sn;
      _ip.fromString(static_ip);
      _gw.fromString(static_gw);
      _sn.fromString(static_sn);
      WiFi.config(_ip, _gw, _sn);
    }
    unsigned long startedAt = millis();
    DBG_OUTPUT.print("After waiting ");
    int connRes = WiFi.waitForConnectResult();
    float waited = (millis() - startedAt);
    DBG_OUTPUT.print(waited / 1000);
    DBG_OUTPUT.print(" secs in setup() connection result is ");
    DBG_OUTPUT.println(connRes);
  }

  if (WiFi.status() != WL_CONNECTED) {
    DBG_OUTPUT.println("Failed to connect, finishing setup anyway");
    smiley_NOK();
    delay(5000);
    // TODO: start wifi in AP mode here and use internal RTC set over webinterface
  } else {
    DBG_OUTPUT.print("Local ip: ");
    DBG_OUTPUT.println(WiFi.localIP());
    smiley_OK();
    delay(5000);
  }

  pinMode(TRIGGER_PIN, INPUT_PULLUP);
}

void check_for_config_portal_request() {
  // is configuration portal requested?
  if ((digitalRead(TRIGGER_PIN) == LOW) || initialConfig) {
    DBG_OUTPUT.println("Configuration portal requested");
    //Local intialization. Once its business is done, there is no need to keep it around

    webServer.close();
    // Initialize WiFIManager
    WiFiManager wifiManager;

    // Extra parameters to be configured
    // After connecting, parameter.getValue() will get you the configured value
    // Format: <ID> <Placeholder text> <default value> <length> <custom HTML> <label placement>

    //set static ip
    IPAddress _ip, _gw, _sn;
    _ip.fromString(static_ip);
    _gw.fromString(static_gw);
    _sn.fromString(static_sn);

    // DHCP or not - bool parameter visualized using checkbox, so couple of things to note
    // - value is always 'T' for true. When the HTML form is submitted this is the value that will be
    //   sent as a parameter. When unchecked, nothing will be sent by the HTML standard.
    // - customhtml must be 'type="checkbox"' for obvious reasons. When the default is checked
    //   append 'checked' too
    // - labelplacement parameter is WFM_LABEL_AFTER for checkboxes as label has to be placed after the input field

    char customhtml[24] = "type=\"checkbox\"";
    if (useDHCP) {
      strcat(customhtml, " checked");
    }
    WiFiManagerParameter p_useDHCP("useDHCP", "DHCP", "T", 2, customhtml);
    wifiManager.addParameter(&p_useDHCP);

    if (!useDHCP)
      wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn);

    // Just a quick hint
    WiFiManagerParameter p_hint("<small>*Hint: if you want to reuse the currently active WiFi credentials, leave SSID and Password fields empty</small>");

    // Sets timeout in seconds until configuration portal gets turned off.
    // If not specified device will remain in configuration mode until
    // switched off via webserver or device is restarted.
    // wifiManager.setConfigPortalTimeout(600);

    // It starts an access point
    // and goes into a blocking loop awaiting configuration.
    // Once the user leaves the portal with the exit button
    // processing will continue
    if (!wifiManager.startConfigPortal("WordClockAP", "1234WordClock5678")) {
      DBG_OUTPUT.println("Not connected to WiFi but continuing anyway.");
    } else {
      // If you get here you have connected to the WiFi
      DBG_OUTPUT.println("Connected...yeey :)");
    }

    useDHCP = (strncmp(p_useDHCP.getValue(), "T", 1) == 0);

    // Writing JSON config file to flash for next boot
    writeConfigFile();

    ESP.reset(); // This is a bit crude. For some unknown reason webserver can only be started once per boot up
    // so resetting the device allows to go back into config mode again when it reboots.
    delay(5000);
  }
}
