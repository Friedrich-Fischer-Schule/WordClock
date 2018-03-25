#include <TimeLib.h>
#include <WiFiUdp.h>

int lastMinute;
int lastSecond;

// NTP Servers:
static const char ntpServerName[] = "de.pool.ntp.org";
//static const char ntpServerName[] = "time.nist.gov";
//static const char ntpServerName[] = "time-a.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-b.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-c.timefreq.bldrdoc.gov";

const int timeZone = 1;     // Central European Time
//const int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)

time_t getNtpTime();
void sendNTPpacket(IPAddress &address);

WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

int dstOffset (unsigned long unixTime)
{
  //Receives unix epoch time and returns seconds of offset for local DST
  //Last Sunday in March and Last Sunday in October
  //Code idea from doughboy @ "http://forum.arduino.cc/index.php?PHPSESSID=uoj11hu5j72556mk3gh0ba5ok3&topic=197637.0"
  //Get epoch times @ "http://www.epochconverter.com/" for testing
  //DST update wont be reflected until the next time sync
  time_t t = unixTime;
  tmElements_t te;
  te.Year = year(t)-1970;
  te.Month = 3;
  te.Day = 31;
  te.Hour = 0;
  te.Minute = 0;
  te.Second = 0;
  time_t dstStart, dstEnd, current;
  dstStart = makeTime(te);
  dstStart = previousSunday(dstStart);  //Last Sunday in March
  dstStart += 1 * SECS_PER_HOUR;  // 1AM
  te.Month = 10;
  dstEnd = makeTime(te);
  dstEnd = previousSunday(dstEnd);  //Last Sunday in October
  dstEnd += 1 * SECS_PER_HOUR;  // 1AM
  DBG_OUTPUT.printf("dstStart = %i.%i.%i %i:%i:%i", day(dstStart), month(dstStart), year(dstStart), hour(dstStart), minute(dstStart), second(dstStart));
  DBG_OUTPUT.println("");
  DBG_OUTPUT.printf("dstEnd = %i.%i.%i %i:%i:%i", day(dstEnd), month(dstEnd), year(dstEnd), hour(dstEnd), minute(dstEnd), second(dstEnd));
  DBG_OUTPUT.println("");
  DBG_OUTPUT.printf("dstAct = %i.%i.%i %i:%i:%i", day(t), month(t), year(t), hour(t), minute(t), second(t));
  DBG_OUTPUT.println("");
  if (t>=dstStart && t<dstEnd) {
    DBG_OUTPUT.println("Summertime");
    return (3600);  //Add back in one hours worth of seconds - DST in effect
  }
  else {
    DBG_OUTPUT.println("Wintertime"); 
    return (0);  //NonDST
  }
}

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  DBG_OUTPUT.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  DBG_OUTPUT.print(ntpServerName);
  DBG_OUTPUT.print(": ");
  DBG_OUTPUT.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      DBG_OUTPUT.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      unsigned long epoch = secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
      return epoch + dstOffset(epoch);  //Adjust for DLT
    }
  }
  DBG_OUTPUT.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

void NTP_status() {
  switch (timeStatus()) {
  case timeNotSet:
    DBG_OUTPUT.println("Time's clock has not been set.  The time & date are unknown.");
    break;
  case timeSet:
    DBG_OUTPUT.println("Time's clock has been set.");
    break;
  case timeNeedsSync:
    DBG_OUTPUT.println("Time's clock is set, but the sync has failed, so it may not be accurate.");
    break;
  }
}

void NTP_setup(){
  Udp.begin(localPort);
  setSyncProvider(getNtpTime);
  setSyncInterval(300);
  delay(1000);
  NTP_status();
}
