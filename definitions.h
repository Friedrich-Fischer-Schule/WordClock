// Neopixel
#include <Adafruit_NeoPixel.h>
int NEOPIXEL_PIN = 5;        // PIN where neopixel / WS2811 strip is attached
#define NEOPIXEL_NUMLEDS 117  // Number of leds in the strip
int colorR = 30;        // ROT variable
int colorG = 100;       // GRÜN
int colorB = 155;       // BLAU 
int brightness = 192;   // Global variable for storing the brightness (255 == 100%)
bool autoDimm = 0;
int BrightLower = 200;
int BrightUpper = 320;
int iRoomBrightness = 0;
char OFFtime_begin[6] = "00:00";
char OFFtime_end[6] = "00:00";

#define d 50 //delay variable

int iMode = 0;
  // 0 = Uhr
  // 1 = Uhr + animation every 5 minutes
  // 2 = Uhr + animation every 15 minutes
  // 3 = Uhr + animation every hour
  
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEOPIXEL_NUMLEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Light sensor settings
int iLightsensorPin = 0;

// WIFI settings
#define HOSTNAME "WORDCLOCK"   // Friedly hostname
//default custom static IP
char static_ip[16] = "10.0.1.56";
char static_gw[16] = "10.0.1.1";
char static_sn[16] = "255.255.255.0";
bool useDHCP = true;

// FILESYSTEM settings
const char* CONFIG_FILE = "/config.json";

// Update settings
#define ENABLE_OTA    // If defined, enable Arduino OTA code.
#define CHECK_INTERVAL 3600  // interval in seconds for auto update check
/*Trigger for inititating config mode is Pin D3 and also flash button on NodeMCU
   Flash button is convenient to use but if it is pressed it will stuff up the serial port device driver
   until the computer is rebooted on windows machines.
*/
const int TRIGGER_PIN = 0; // D3 on NodeMCU and WeMos.

// ***************************************************************************
// Global variables / definitions
// ***************************************************************************
#define DBG_OUTPUT Serial  // Set debug output port
// ***************************************************************************
//#define DBG_OUTPUT // disable debug output

