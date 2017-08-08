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
        width: 100%;
        min-height: 100%;
        left: 0;
        top: 0;
        padding-top: 30px;
        padding-left: 30px;
        padding-right: 30px;
        padding-bottom: 30px;
        background-color: #bfbaba;
      }
      input[type=range] {
        -webkit-appearance: none;
        width: 90%;
        margin: 30px 30px;
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
      button {
        font-size: 24px;
      }
      h2 {
        float: left;
      }
    </style>
  </head>
  <body>
    <div id=container>
      <div><div><h1>WordClock color:</h1></div><div><button id="Save" type="button" onclick="sendSaveSettings();"> Save default color </button></div></div>
      <div><h2>R: </h2><input id="sliderR" type="range" min="0" max="255" step="1" oninput="sendRGB();" onchange="sendRGB();" /></div>
      <div><h2>G: </h2><input id="sliderG" type="range" min="0" max="255" step="1" oninput="sendRGB();" onchange="sendRGB();" /></div>
      <div><h2>B: </h2><input id="sliderB" type="range" min="0" max="255" step="1" oninput="sendRGB();" onchange="sendRGB();" /></div>
    </div>
    <script type="text/javascript">
      var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);
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
        }
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
        console.log('RGB: ' + rgb);
        connection.send(rgb);
      }

      function sendSaveSettings() {
        console.log('send saveSettings');
        connection.send("saveSettings");
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

