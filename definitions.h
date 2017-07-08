// Neopixel
#define NEOPIXEL_PIN 5         // PIN where neopixel / WS2811 strip is attached
#define NEOPIXEL_NUMLEDS 11    // Number of leds in the strip

// WIFI settings
#define HOSTNAME "WORDCLOCK"   // Friedly hostname

// Update settings
#define ENABLE_OTA    // If defined, enable Arduino OTA code.
#define CHECK_INTERVAL 60  // interval in seconds for auto update check

// ***************************************************************************
// Global variables / definitions
// ***************************************************************************
#define DBG_OUTPUT Serial  // Set debug output port

int brightness = 192;       // Global variable for storing the brightness (255 == 100%)

