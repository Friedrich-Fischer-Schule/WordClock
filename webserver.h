#include <ESP8266WebServer.h>

ESP8266WebServer webServer ( 80 );

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
        "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
  <head>
    <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
    <style type="text/css">
      #container {
        position: absolute;
        width: 98%;
        min-height: 100%;
        left: 0;
        top: 0;
        padding: 1%;
        background-color: #bfbaba;
      }
      input[type=range] {
        -webkit-appearance: none;
        width: 90%;
        margin: 22px auto 22px 0;
      }
      input[type=range]:focus {
        outline: none;
      }
      input[type=range]::-webkit-slider-runnable-track {
        width: 100%;
        height: 20.3px;
        cursor: pointer;
        box-shadow: 1px 1px 1px #0a0000, 0px 0px 1px #240000;
        border-radius: 10px;
        border: 0.8px solid #010101;
      }
      input[type=range]::-webkit-slider-thumb {
        box-shadow: 1px 1px 1px #000000, 0px 0px 1px #0d0d0d;
        border: 1px solid #000000;
        height: 36px;
        width: 16px;
        border-radius: 7px;
        background: #ffffff;
        cursor: pointer;
        -webkit-appearance: none;
        margin-top: -8.65px;
      }
      input[type=range]:focus::-webkit-slider-runnable-track {
        background: #ff1a1a;
      }
      input[type=range]::-moz-range-track {
        width: 100%;
        height: 20.3px;
        cursor: pointer;
        box-shadow: 1px 1px 1px #0a0000, 0px 0px 1px #240000;
        border-radius: 10px;
        border: 0.8px solid #010101;
      }
      input[type=range]::-moz-range-thumb {
        box-shadow: 1px 1px 1px #000000, 0px 0px 1px #0d0d0d;
        border: 1px solid #000000;
        height: 36px;
        width: 16px;
        border-radius: 7px;
        background: #ffffff;
        cursor: pointer;
      }
      input[type=range]::-ms-track {
        width: 100%;
        height: 20.3px;
        cursor: pointer;
        background: transparent;
        border-color: transparent;
        color: transparent;
      }
      input[type=range]::-ms-fill-lower {
        background: #e60000;
        border: 0.8px solid #010101;
        border-radius: 20px;
        box-shadow: 1px 1px 1px #0a0000, 0px 0px 1px #240000;
      }
      input[type=range]::-ms-fill-upper {
        background: #ff0000;
        border: 0.8px solid #010101;
        border-radius: 20px;
        box-shadow: 1px 1px 1px #0a0000, 0px 0px 1px #240000;
      }
      input[type=range]::-ms-thumb {
        box-shadow: 1px 1px 1px #000000, 0px 0px 1px #0d0d0d;
        border: 1px solid #000000;
        height: 36px;
        width: 16px;
        border-radius: 7px;
        background: #ffffff;
        cursor: pointer;
        height: 20.3px;
      }
      input[type=range]:focus::-ms-fill-lower {
        background: #ff0000;
      }
      input[type=range]:focus::-ms-fill-upper {
        background: #ff1a1a;
      }
      #sliderR::-webkit-slider-runnable-track {
        background: #ff0000;
      }
      #sliderG::-webkit-slider-runnable-track {
        background: #00ff00;
      }
      #sliderB::-webkit-slider-runnable-track {
        background: #0000ff;
      }
      #sliderR::-moz-range-track {
        background: #ff0000;
      }
      #sliderG::-moz-range-track {
        background: #00ff00;
      }
      #sliderB::-moz-range-track {
        background: #0000ff;
      }
      #sliderR::-ms-fill-upper {
        background: #ff0000;
      }
      #sliderG::-ms-fill-upper {
        background: #00ff00;
      }
      #sliderB::-ms-fill-upper {
        background: #0000ff;
      }
      #sliderR::-ms-fill-lower {
        background: #ff0000;
      }
      #sliderG::-ms-fill-lower {
        background: #00ff00;
      }
      #sliderB::-ms-fill-lower {
        background: #0000ff;
      }
      .Button {
        font-size: 35px;
      }
      .colorButton {
        font-size: 24px;
        width: 15%;
        height: 30px;
        margin: 2px;
      }
      h2 {
        float: left;
      }
      #sliders {
        width: 80%;
        height: 100%;
        float: left;
      }
      #colorbox {
        width: 12%;
        min-height: 140px;
        float: left;
        margin: 2%;
        padding: 0%;
        background: red;
      }
    </style>
  </head>
  <body>
    <div id=container>
      <div id="header" style="float: left; width: 100%; text-align: center; font-size: 40px; font-weight: bold; margin-bottom: 20px;">
        WordClock Settings:
      </div>
      <div style="float: left; width: 100%;">
        <button style="background: #ff0000" class="colorButton" id="RED" type="button" onclick="setColor('#ff0000');"></button>
        <button style="background: #00ff00" class="colorButton" id="GREEN" type="button" onclick="setColor('#00ff00');"></button>
        <button style="background: #0000ff" class="colorButton" id="BLUE" type="button" onclick="setColor('#0000ff');"></button>
        <button style="background: #ffff00" class="colorButton" id="YELLOW" type="button" onclick="setColor('#ffff00');"></button>
        <button style="background: #00ffff" class="colorButton" id="CYAN" type="button" onclick="setColor('#00ffff');"></button>
        <button style="background: #ff00ff" class="colorButton" id="MAGENTA" type="button" onclick="setColor('#ff00ff');"></button>
        <button style="background: #ffa500" class="colorButton" id="ORANGE" type="button" onclick="setColor('#ffa500');"></button>
        <button style="background: #ff1493" class="colorButton" id="DeepPink" type="button" onclick="setColor('#ff1493');"></button>
        <button style="background: #a020f0" class="colorButton" id="PURPLE" type="button" onclick="setColor('#a020f0');"></button>
        <button style="background: #ffd700" class="colorButton" id="GOLD" type="button" onclick="setColor('#ffd700');"></button>
        <button style="background: #ee82ee" class="colorButton" id="VIOLET" type="button" onclick="setColor('#ee82ee');"></button>
        <button style="background: #ffffff" class="colorButton" id="WHITE" type="button" onclick="setColor('#ffffff');"></button>
      </div>    
      <div style="margin-top: 20px; min-height: 250px; float: left; width: 100%;">
        <div id="sliders">
          <div><input id="sliderR" type="range" min="0" max="255" step="1" oninput="sendRGB();" onchange="sendRGB();" /></div>
          <div><input id="sliderG" type="range" min="0" max="255" step="1" oninput="sendRGB();" onchange="sendRGB();" /></div>
          <div><input id="sliderB" type="range" min="0" max="255" step="1" oninput="sendRGB();" onchange="sendRGB();" /></div>
        </div>
        <div id="colorbox"> </div>
      </div>
      <div id="brightness" style="float: left; width: 90%; font-size: 20px; font-weight: bold; margin-bottom: 10px; padding: 10px; border:1px solid black;">
          Umgebungslicht =
      </div>
      <div style="float: left; width: 90%; font-size: 20px; font-weight: bold; margin-bottom: 10px; padding: 10px; border:1px solid black;">
          <a>Animations Modus:</a>
          <input type="radio" id="mode0" name="animode" onclick="handleModeClick(this);" value="0">
          <label for="mode0"> ohne</label>
          <input type="radio" id="mode1" name="animode" onclick="handleModeClick(this);" value="1">
          <label for="mode1"> alle 5 Minuten</label>
          <input type="radio" id="mode2" name="animode" onclick="handleModeClick(this);" value="2">
          <label for="mode2"> alle 15 Minuten</label>
          <input type="radio" id="mode3" name="animode" onclick="handleModeClick(this);" value="3">
          <label for="mode2"> jede Stunde</label>
      </div>
      <div id="off-time" style="float: left; width: 90%; font-size: 20px; font-weight: bold; margin-bottom: 10px; padding: 10px; border:1px solid black;">
           <a>Uhr aus von </a> <input type="time" id="off_time_begin" onchange="sendOFFtime();"> <a> bis </a> <input type="time" id="off_time_end" onchange="sendOFFtime();">
      </div>
      <div style="margin-top: 20px; min-height: 40px; float: left; width: 100%;">
        <button class="Button" onclick="sendSaveSettings();"> Default Farbe speichern </button>
        <button class="Button" onclick="sendTestLED();"> Teste LEDs </button>
        <button class="Button" onClick="if(confirm('Uhr neu starten?.')) resetClock(); else return false;">Uhr neu starten</button>
        <button class="Button" onClick="if(confirm('Alle Einstellungen löschen, sind Sie sicher?.')) resetAll(); else return false;">Alle Einstellungen löschen</button>
        <button class="Button" onClick="if(confirm('WLAN Daten löschen, sind Sie sicher?.')) resetWifi(); else return false;">WLAN Daten löschen</button>
      </div>
      <div style="margin-top: 20px; float: left; width: 90%; font-size: 20px; font-weight: bold; margin-bottom: 10px; padding: 10px; border:1px solid black;">
          <a>LED Pin:</a>
          <input type="radio" id="LEDpin2" name="ledpin" onclick="handleLEDPinClick(this);" value="2">
          <label for="LEDpin2"> 2</label>
          <input type="radio" id="LEDpin5" name="ledpin" onclick="handleLEDPinClick(this);" value="5">
          <label for="LEDpin5"> 5</label>
      </div>
    </div>
    <script type="text/javascript">
      var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);
      var versionnumber = ""; 
      var brightness = "";
      connection.onopen = function () {
        connection.send('Connect ' + new Date());
      }
      connection.onerror = function (error) {
        console.log('WebSocket Error ', error);
      }
      connection.onmessage = function (e) {
        console.log('Server: ', e.data);
        if (e.data[0] == '#') {
          var rgb = parseInt(e.data.substring(1), 16);
          document.getElementById('sliderR').value=((rgb >> 16) & 0xFF);
          document.getElementById('sliderG').value=((rgb >> 8) & 0xFF);
          document.getElementById('sliderB').value=((rgb >> 0) & 0xFF);
          document.getElementById('colorbox').style.background=e.data;
        }
        if (e.data[0] == '~') {
          var iMode = parseInt(e.data.substring(1), 10);
          var elem = 'mode' + iMode;
          document.getElementById(elem).checked = true;
        }
        if (e.data[0] == '+') {
          var iLEDPin = parseInt(e.data.substring(1), 10);
          var elem = 'LEDpin' + iLEDPin;
          document.getElementById(elem).checked = true;
        }
        if (strncmp(e.data, "time=", 5) == 0) {
          document.getElementById('header').innerHTML = "WordClock (Ver." + versionnumber + "): " + e.data.substring(5);
        }
        if (strncmp(e.data, "version=", 8) == 0) {
          versionnumber = e.data.substring(8);
        }
        if (strncmp(e.data, "brightness=", 11) == 0) {
          brightness = e.data.substring(11);
          document.getElementById('brightness').innerHTML = "Umgebungslicht = " + brightness;
        }
        if (strncmp(e.data, "OFFtime=", 8) == 0) {
          var OFFbegin = e.data.substring(8,13);
          var OFFend = e.data.substring(14,19);
          document.getElementById('off_time_begin').value = OFFbegin;
          document.getElementById('off_time_end').value = OFFend;
        }
      }

      function strncmp(str1, str2, n) {
        str1 = str1.substring(0, n);
        str2 = str2.substring(0, n);
        return ( ( str1 == str2 ) ? 0 : (( str1 > str2 ) ? 1 : -1 ));
      }

      function sendOFFtime() {
        var OFFbegin = document.getElementById('off_time_begin').value;
        var OFFend = document.getElementById('off_time_end').value;
        var OFFtime = 'OFFtime=' + OFFbegin + '-' + OFFend;
        console.log(OFFtime);
        connection.send(OFFtime);
      }
    
      function sendRGB() {
        var r = parseInt(document.getElementById('sliderR').value).toString(16);
        var g = parseInt(document.getElementById('sliderG').value).toString(16);
        var b = parseInt(document.getElementById('sliderB').value).toString(16);
        if(r.length < 2) {
          r = '0' + r;
        }
        if(g.length < 2) { 
          g = '0' + g;
        }
        if(b.length < 2) {
          b = '0' + b;
        }
        var rgb = '#'+r+g+b;
        console.log('send RGB: ' + rgb);
        document.getElementById('colorbox').style.background=rgb;
        document.getElementById('colorbox').innerHTML = rgb;
        connection.send(rgb);
      }
    
      function setColor(color) {
        var rgb = parseInt(color.substring(1), 16);
        document.getElementById('sliderR').value=((rgb >> 16) & 0xFF);
        document.getElementById('sliderG').value=((rgb >> 8) & 0xFF);
        document.getElementById('sliderB').value=((rgb >> 0) & 0xFF);
        sendRGB();
      }

      function sendSaveSettings() {
        console.log('send saveSettings');
        connection.send("saveSettings");
      }

      function resetWifi() {
        if (confirm('Bist du 100% sicher?')) {
          console.log('send resetWiFi');
          connection.send("resetWiFi");
        } else {
          console.log('send resetWiFi ABORDED!');
        }
      }

      function resetAll() {
        if (confirm('Bist du 100% sicher?')) {
          console.log('send resetAll');
          connection.send("resetAll");
        } else {
          console.log('send resetAll ABORDED!');
        }
      }

      function resetClock() {
        if (confirm('Bist du 100% sicher?')) {
          console.log('send resetClock');
          connection.send("resetClock");
        } else {
          console.log('send resetClock ABORDED!');
        }
      }
      
      function handleModeClick(modeRadio) {
        var aniMode = '~' + modeRadio.value;
        console.log(aniMode);
        connection.send(aniMode);
      }

      function handleLEDPinClick(pinRadio) {
        var setLEDPin = '+' + pinRadio.value;
        console.log(setLEDPin);
        connection.send(setLEDPin);
      }
      
      function sendTestLED() {
        console.log('send TestLED');
        connection.send("testLED");
      }
      
      function sendTest() {
        console.log('send Test');
      }
    </script>
  </body>
</html>
)=====";

void WebServer_setup() {
  // handle index
  webServer.on("/", []() {
    // send index.html
    String s = MAIN_page;
    webServer.send(200, "text/html", s);
  });

  webServer.begin();
}

void check_for_webserver_event() {
  webServer.handleClient();
}

