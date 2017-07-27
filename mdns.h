#include <ESP8266mDNS.h>

void mDNS_setup() {
  if ( MDNS.begin ( "WordClock" ) ) {
    DBG_OUTPUT.println ( "MDNS responder started" );
  }

  // Add service to MDNS
  MDNS.addService("http", "tcp", 80);
  MDNS.addService("ws", "tcp", 81);
}

