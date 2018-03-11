#include "Wire.h"
#define DS3231_ADDRESSE 0x68

void rtc_setup() {
  Wire.begin();
}

float rtc_gettemp() {
  // Die Temperatur des DS3231 auslesen  
  float temp;
  int msb, lsb;
  Wire.beginTransmission(DS3231_ADDRESSE);
  Wire.write(0x11); // DS3231 Register zu 11h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESSE, 2); // 2 Byte Daten vom DS3231 holen
  msb = Wire.read();
  lsb = Wire.read();
  temp=((msb << 2) + (lsb >> 6) ) /4.0;
  return temp;
}

void leseDS3231zeit(byte *sekunde, byte *minute,byte *stunde, byte *wochentag, byte *tag, byte *monat, byte *jahr) {
  Wire.beginTransmission(DS3231_ADDRESSE);
  Wire.write(0); // DS3231 Register zu 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESSE, 7); // 7 Byte Daten vom DS3231 holen
  *sekunde = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *stunde = bcdToDec(Wire.read() & 0x3f);
  *wochentag = bcdToDec(Wire.read());
  *tag = bcdToDec(Wire.read());
  *monat = bcdToDec(Wire.read());
  *jahr = bcdToDec(Wire.read());
}

void zeigeZeit(){
  byte sekunde, minute, stunde, wochentag, tag, monat, jahr;
  leseDS3231zeit(&sekunde, &minute, &stunde, &wochentag, &tag, &monat, &jahr);   // Daten vom DS3231 holen
  if (tag < 10) { DBG_OUTPUT.print("0");} 
  DBG_OUTPUT.print(tag); // ausgeben T.M.J H:M:S
  DBG_OUTPUT.print(":");
  if (monat < 10) { DBG_OUTPUT.print("0");}
  DBG_OUTPUT.print(monat);
  DBG_OUTPUT.print(":20");
  DBG_OUTPUT.print(jahr);
  DBG_OUTPUT.print(" ");
  if (stunde < 10) { DBG_OUTPUT.print("0");}
  DBG_OUTPUT.print(stunde, DEC); // byte in Dezimal zur Ausgabe
  DBG_OUTPUT.print(":");
  if (minute < 10) { DBG_OUTPUT.print("0");}
  DBG_OUTPUT.print(minute, DEC);
  DBG_OUTPUT.print(":");
  if (sekunde < 10) { DBG_OUTPUT.print("0"); }
  DBG_OUTPUT.println(sekunde, DEC);
}

void einstellenDS3231zeit(byte sekunde, byte minute, byte stunde, byte wochentag, byte tag, byte monat, byte jahr) {
  // Datum und Uhrzeit einstellen
  Wire.beginTransmission(DS3231_ADDRESSE);
  Wire.write(0);
  Wire.write(decToBcd(sekunde)); // Sekunden einstellen
  Wire.write(decToBcd(minute)); // Minuten einstellen
  Wire.write(decToBcd(stunde));
  Wire.write(decToBcd(wochentag)); // 1=Sonntag ... 7=Samstag
  Wire.write(decToBcd(tag));
  Wire.write(decToBcd(monat));
  Wire.write(decToBcd(jahr)); // 0...99
  Wire.endTransmission();
}

byte decToBcd(byte val) {
// Dezimal Zahl zu binary coded decimal (BCD) umwandeln
  return((val/10*16) + (val%10));
}

byte bcdToDec(byte val) {
// BCD (binary coded decimal) in Dezimal Zahl umwandeln
  return((val/16*10) + (val%16));
}
