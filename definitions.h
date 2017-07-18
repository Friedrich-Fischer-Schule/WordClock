// Neopixel
#define NEOPIXEL_PIN 5         // PIN where neopixel / WS2811 strip is attached
#define NEOPIXEL_NUMLEDS 11    // Number of leds in the strip

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
#define CHECK_INTERVAL 60  // interval in seconds for auto update check

// ***************************************************************************
// Global variables / definitions
// ***************************************************************************
#define DBG_OUTPUT Serial  // Set debug output port

int brightness = 192;       // Global variable for storing the brightness (255 == 100%)

