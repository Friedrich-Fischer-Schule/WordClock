void LEDs_setup(){
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void icon_update(){
  bool icon[] = {0,0,0,1,1,1,1,1,0,0,0,
                   0,0,1,0,0,0,0,0,1,0,0,
                   0,1,0,0,0,0,0,0,0,1,0,
                   1,0,0,0,0,0,0,0,0,0,1,
                   1,0,0,0,0,1,0,0,0,0,1,
                   1,0,0,0,1,1,1,0,0,0,1,
                   1,0,0,0,0,1,0,0,0,0,1,
                   1,0,0,0,0,0,0,0,0,0,1,
                   0,1,0,0,0,0,0,0,0,1,0,
                   0,0,1,1,0,0,0,1,1,0,0,
                       0,0,1,0,1,0,0};
  strip.clear();
  for (int i = 0; i < NEOPIXEL_NUMLEDS; i++)
    if (icon[i] == 1)
      strip.setPixelColor(i, 0, 0, 255);
  strip.show();
}

void smiley_OK(){
  bool smiley[] = {0,0,0,1,1,1,1,1,0,0,0,
                   0,0,1,0,0,0,0,0,1,0,0,
                   0,1,0,0,1,1,1,0,0,1,0,
                   1,0,0,1,0,0,0,1,0,0,1,
                   1,0,0,0,0,0,0,0,0,0,1,
                   1,0,0,0,0,0,0,0,0,0,1,
                   1,0,0,1,1,0,1,1,0,0,1,
                   1,0,0,1,1,0,1,1,0,0,1,
                   0,1,0,0,0,0,0,0,0,1,0,
                   0,0,1,1,0,0,0,1,1,0,0,
                       0,0,1,0,1,0,0};
  strip.clear();
  for (int i = 0; i < NEOPIXEL_NUMLEDS; i++)
    if (smiley[i] == 1)
      strip.setPixelColor(i, 0, 255, 0);
  strip.show();
}

void smiley_NOK(){
  bool smiley[] = {0,0,0,1,1,1,1,1,0,0,0,
                   0,0,1,0,0,0,0,0,1,0,0,
                   0,1,0,0,0,0,0,0,0,1,0,
                   1,0,0,1,0,0,0,1,0,0,1,
                   1,0,0,0,1,1,1,0,0,0,1,
                   1,0,0,0,0,0,0,0,0,0,1,
                   1,0,0,1,1,0,1,1,0,0,1,
                   1,0,0,1,1,0,1,1,0,0,1,
                   0,1,0,0,0,0,0,0,0,1,0,
                   0,0,1,1,0,0,0,1,1,0,0,
                       0,0,1,0,1,0,0};
  strip.clear();
  for (int i = 0; i < NEOPIXEL_NUMLEDS; i++)
    if (smiley[i] == 1)
      strip.setPixelColor(i, 255, 0, 0);
  strip.show();
}

uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void Schlange() {

  colorWipe(strip.Color(255, 0, 0), d); // Red
  colorWipe(strip.Color(0, 255, 0), d); // Green
  colorWipe(strip.Color(0, 0, 250), d); // Blue
  colorWipe(strip.Color(100, 44, 65), d); // rosa
  colorWipe(strip.Color(33, 100, 100), d); // türkis
  colorWipe(strip.Color(255, 127, 36), d); // orange
  colorWipe(strip.Color(25, 25, 112), d); // Red
  colorWipe(strip.Color(173, 255, 47), d); // gelb
  colorWipe(strip.Color(153, 50, 204), d); // magenta
  colorWipe(strip.Color(48, 255, 159), d); // minze
}

void KNIGHT() {

  int t;

  for (int i = 0; i < 11; i++) {
    for (int z = 0; z < 10; z++)
      strip.setPixelColor(i + z * 11, strip.Color( R, G, B));

    t = i ;
    if (t < 0) t = strip.numPixels() - 1;
    for (int z = 0; z < 10; z++)
      strip.setPixelColor(t + z * 11, strip.Color( R, G, B));

    strip.show();
    delay(50);
  }
  for (int i = 10; i >= 0; i--) {
    for (int z = 0; z < 10; z++)
      strip.setPixelColor(i + z * 11, strip.Color( R, G, B));
    t = i;
    if (t >= strip.numPixels()) t = 0;
    for (int z = 0; z < 10; z++)
      strip.setPixelColor(t + z * 11, strip.Color( 0, 0, 0));
    strip.show();
    delay(50);
  }
}

void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void es() {
  strip.setPixelColor(108, R, G, B);
  strip.setPixelColor(109, R, G, B);
}

void ist() {
  strip.setPixelColor(104, R, G, B);
  strip.setPixelColor(105, R, G, B);
  strip.setPixelColor(106, R, G, B);
}

void funf() {
  strip.setPixelColor(99, R, G, B);
  strip.setPixelColor(100, R, G, B);
  strip.setPixelColor(101, R, G, B);
  strip.setPixelColor(102, R, G, B);
}

void zehn() {
  strip.setPixelColor(88, R, G, B);
  strip.setPixelColor(89, R, G, B);
  strip.setPixelColor(90, R, G, B);
  strip.setPixelColor(91, R, G, B);
}

void zwanzig() {
  strip.setPixelColor(92, R, G, B);
  strip.setPixelColor(93, R, G, B);
  strip.setPixelColor(94, R, G, B);
  strip.setPixelColor(95, R, G, B);
  strip.setPixelColor(96, R, G, B);
  strip.setPixelColor(97, R, G, B);
  strip.setPixelColor(98, R, G, B);
}

void viertel() {
  strip.setPixelColor(77, R, G, B);
  strip.setPixelColor(78, R, G, B);
  strip.setPixelColor(79, R, G, B);
  strip.setPixelColor(80, R, G, B);
  strip.setPixelColor(81, R, G, B);
  strip.setPixelColor(82, R, G, B);
  strip.setPixelColor(83, R, G, B);
}

void dreiviertel() {
  strip.setPixelColor(77, R, G, B);
  strip.setPixelColor(78, R, G, B);
  strip.setPixelColor(79, R, G, B);
  strip.setPixelColor(80, R, G, B);
  strip.setPixelColor(81, R, G, B);
  strip.setPixelColor(82, R, G, B);
  strip.setPixelColor(83, R, G, B);
  strip.setPixelColor(84, R, G, B);
  strip.setPixelColor(85, R, G, B);
  strip.setPixelColor(86, R, G, B);
  strip.setPixelColor(87, R, G, B);
}

void vor() {
  strip.setPixelColor(66, R, G, B);
  strip.setPixelColor(67, R, G, B);
  strip.setPixelColor(68, R, G, B);
}

void und() {
  strip.setPixelColor(70, R, G, B);
  strip.setPixelColor(71, R, G, B);
  strip.setPixelColor(72, R, G, B);
}

void nach() {
  strip.setPixelColor(73, R, G, B);
  strip.setPixelColor(74, R, G, B);
  strip.setPixelColor(75, R, G, B);
  strip.setPixelColor(76, R, G, B);
}

void halb() {
  strip.setPixelColor(62, R, G, B);
  strip.setPixelColor(63, R, G, B);
  strip.setPixelColor(64, R, G, B);
  strip.setPixelColor(65, R, G, B);
}

void elf() {
  strip.setPixelColor(58, R, G, B);
  strip.setPixelColor(59, R, G, B);
  strip.setPixelColor(60, R, G, B);
}

void funf2() {
  strip.setPixelColor(55, R, G, B);
  strip.setPixelColor(56, R, G, B);
  strip.setPixelColor(57, R, G, B);
  strip.setPixelColor(58, R, G, B);
}

void eins() {
  strip.setPixelColor(44, R, G, B);
  strip.setPixelColor(45, R, G, B);
  strip.setPixelColor(46, R, G, B);
  strip.setPixelColor(47, R, G, B);
}
void ein() {
  strip.setPixelColor(44, R, G, B);
  strip.setPixelColor(45, R, G, B);
  strip.setPixelColor(46, R, G, B);
}

void zwei() {
  strip.setPixelColor(51, R, G, B);
  strip.setPixelColor(52, R, G, B);
  strip.setPixelColor(53, R, G, B);
  strip.setPixelColor(54, R, G, B);
}

void drei() {
  strip.setPixelColor(40, R, G, B);
  strip.setPixelColor(41, R, G, B);
  strip.setPixelColor(42, R, G, B);
  strip.setPixelColor(43, R, G, B);
}

void vier() {
  strip.setPixelColor(33, R, G, B);
  strip.setPixelColor(34, R, G, B);
  strip.setPixelColor(35, R, G, B);
  strip.setPixelColor(36, R, G, B);
}

void sechs() {
  strip.setPixelColor(22, R, G, B);
  strip.setPixelColor(23, R, G, B);
  strip.setPixelColor(24, R, G, B);
  strip.setPixelColor(25, R, G, B);
  strip.setPixelColor(26, R, G, B);
}

void acht() {
  strip.setPixelColor(29, R, G, B);
  strip.setPixelColor(30, R, G, B);
  strip.setPixelColor(31, R, G, B);
  strip.setPixelColor(32, R, G, B);
}

void sieben() {
  strip.setPixelColor(16, R, G, B);
  strip.setPixelColor(17, R, G, B);
  strip.setPixelColor(18, R, G, B);
  strip.setPixelColor(19, R, G, B);
  strip.setPixelColor(20, R, G, B);
  strip.setPixelColor(21, R, G, B);
}

void zwolf() {
  strip.setPixelColor(11, R, G, B);
  strip.setPixelColor(12, R, G, B);
  strip.setPixelColor(13, R, G, B);
  strip.setPixelColor(14, R, G, B);
  strip.setPixelColor(15, R, G, B);
}

void zehn2() {
  strip.setPixelColor(0, R, G, B);
  strip.setPixelColor(1, R, G, B);
  strip.setPixelColor(2, R, G, B);
  strip.setPixelColor(3, R, G, B);
}

void neun() {
  strip.setPixelColor(3, R, G, B);
  strip.setPixelColor(4, R, G, B);
  strip.setPixelColor(5, R, G, B);
  strip.setPixelColor(6, R, G, B);
}

void uhr() {
  strip.setPixelColor(8, R, G, B);
  strip.setPixelColor(9, R, G, B);
  strip.setPixelColor(10, R, G, B);
}

void ersterpunkt() {
  strip.setPixelColor(110, R, G, B);
}

void zweiterpunkt() {
  strip.setPixelColor(110, R, G, B);
  strip.setPixelColor(112, R, G, B);

}

void dritterpunkt() {
  strip.setPixelColor(110, R, G, B);
  strip.setPixelColor(112, R, G, B);
  strip.setPixelColor(114, R, G, B);
}

void vierterpunkt() {
  strip.setPixelColor(110, R, G, B);
  strip.setPixelColor(112, R, G, B);
  strip.setPixelColor(114, R, G, B);
  strip.setPixelColor(116, R, G, B);
}

void keinpunkt() {

}

void uhrdisp() {
  strip.clear();

  es();
  ist();

  int x = minute() % 5;

  if ( x == 1) {
    ersterpunkt();
  }

  if ( x == 2) {
    zweiterpunkt();
  }

  if ( x == 3) {
    dritterpunkt();
  }

  if ( x == 4) {
    vierterpunkt();
  }

  if ( x == 0) {
    keinpunkt();
  }

  if (minute() >= 5 && minute() < 10) {
    funf();
    nach();
  }
  if (minute() >= 10 && minute() < 15) {
    zehn();
    nach();
  }
  if (minute() >= 15 && minute() < 20) {
    viertel();
  }
  if (minute() >= 20 && minute() < 25) {
    zwanzig();
    nach();
  }
  if (minute() >= 25 && minute() < 30) {
    funf();
    vor();
    halb();
  }
  if (minute() >= 30 && minute() < 35) {
    halb();
  }
  if (minute() >= 35 && minute() < 40) {
    funf();
    nach();
    halb();
  }
  if (minute() >= 40 && minute() < 45) {
    zwanzig();
    vor();
  }
  if (minute() >= 45 && minute() < 50) {
    dreiviertel();
  }
  if (minute() >= 50 && minute() < 55) {
    zehn();
    vor();
  }
  if (minute() >= 55 && minute() < 60) {
    funf();
    vor();
  }

  if (hour() == 13 && minute() < 5 || hour() == 1 && minute() < 5) { //ein uhr oder dreizehn
    ein();
    uhr();
  }
  if (hour() == 13 && minute() >= 5 && minute() < 15 || hour() == 1 && minute() >= 5 && minute() < 15 ) {
    eins();
  }
  if (hour() == 13 && minute() >= 15 && minute() < 20 || hour() == 1 && minute() >= 15 && minute() < 20 ) {
    zwei();
  }
  if (hour() == 13 && minute() >= 20 && minute() < 25 || hour() == 1 && minute() >= 20 && minute() < 25 ) {
    eins();
  }
  if (hour() == 13 && minute() >= 25 && minute() < 60 || hour() == 1 && minute() >= 25 && minute() < 60 ) {
    zwei();
  }


  if (hour() == 14 && minute() < 5 || hour() == 2 && minute() < 5) {              //zwei uhr oder vierzehn
    zwei();
    uhr();
  }
  if (hour() == 14 && minute() >= 5 && minute() < 15 || hour() == 2 && minute() >= 5 && minute() < 15 ) {
    zwei();
  }
  if (hour() == 14 && minute() >= 15 && minute() < 20 || hour() == 2 && minute() >= 15 && minute() < 20 ) {
    drei();
  }
  if (hour() == 14 && minute() >= 20 && minute() < 25 || hour() == 2 && minute() >= 20 && minute() < 25 ) {
    zwei();
  }
  if (hour() == 14 && minute() >= 25 && minute() < 60 || hour() == 2 && minute() >= 25 && minute() < 60 ) {
    drei();
  }


  if (hour() == 15 && minute() < 5 || hour() == 3 && minute() < 5) {    //drei uhr oder funfzehn
    drei();
    uhr();
  }
  if (hour() == 15 && minute() >= 5 && minute() < 15 || hour() == 3 && minute() >= 5 && minute() < 15 ) {
    drei();
  }
  if (hour() == 15 && minute() >= 15 && minute() < 20 || hour() == 3 && minute() >= 15 && minute() < 20 ) {
    vier();
  }
  if (hour() == 15 && minute() >= 20 && minute() < 25 || hour() == 3 && minute() >= 20 && minute() < 25 ) {
    drei();
  }
  if (hour() == 15 && minute() >= 25 && minute() < 60 || hour() == 3 && minute() >= 25 && minute() < 60 ) {
    vier();
  }



  if (hour() == 16 && minute() < 5 || hour() == 4 && minute() < 5) {        // vier uhr oder sechzehn
    vier();
    uhr();
  }
  if (hour() == 16 && minute() >= 5 && minute() < 15 || hour() == 4 && minute() >= 5 && minute() < 15 ) {
    vier();
  }
  if (hour() == 16 && minute() >= 15 && minute() < 20 || hour() == 4 && minute() >= 15 && minute() < 20 ) {
    funf2();
  }
  if (hour() == 16 && minute() >= 20 && minute() < 25 || hour() == 4 && minute() >= 20 && minute() < 25 ) {
    vier();
  }
  if (hour() == 16 && minute() >= 25 && minute() < 60 || hour() == 4 && minute() >= 25 && minute() < 60 ) {
    funf2();
  }




  if (hour() == 17 && minute() < 5 || hour() == 5 && minute() < 5) {                //funf uhr oder siebzehn
    funf2();
    uhr();
  }
  if (hour() == 17 && minute() >= 5 && minute() < 15 || hour() == 5 && minute() >= 5 && minute() < 15 ) {
    funf2();
  }
  if (hour() == 17 && minute() >= 15 && minute() < 20 || hour() == 5 && minute() >= 15 && minute() < 20 ) {
    sechs();
  }
  if (hour() == 17 && minute() >= 20 && minute() < 25 || hour() == 5 && minute() >= 20 && minute() < 25 ) {
    funf2();
  }
  if (hour() == 17 && minute() >= 25 && minute() < 60 || hour() == 5 && minute() >= 25 && minute() < 60 ) {
    sechs();
  }




  if (hour() == 18 && minute() < 5 || hour() == 6 && minute() < 5) {            // sechs uhr oder achtzehn
    sechs();
    uhr();
  }
  if (hour() == 18 && minute() >= 5 && minute() < 15 || hour() == 6 && minute() >= 5 && minute() < 15 ) {
    sechs();
  }
  if (hour() == 18 && minute() >= 15 && minute() < 20 || hour() == 6 && minute() >= 15 && minute() < 20 ) {
    sieben();
  }
  if (hour() == 18 && minute() >= 20 && minute() < 25 || hour() == 6 && minute() >= 20 && minute() < 25 ) {
    sechs();
  }
  if (hour() == 18 && minute() >= 25 && minute() < 60 || hour() == 6 && minute() >= 25 && minute() < 60 ) {
    sieben();
  }




  if (hour() == 19 && minute() < 5 || hour() == 7 && minute() < 5) {              // sieben uhr oder neunzehn
    sieben();
    uhr();
  }
  if (hour() == 19 && minute() >= 5 && minute() < 15 || hour() == 7 && minute() >= 5 && minute() < 15 ) {
    sieben();
  }
  if (hour() == 19 && minute() >= 15 && minute() < 20 || hour() == 7 && minute() >= 15 && minute() < 20 ) {
    acht();
  }
  if (hour() == 19 && minute() >= 20 && minute() < 25 || hour() == 7 && minute() >= 20 && minute() < 25 ) {
    sieben();
  }
  if (hour() == 19 && minute() >= 25 && minute() < 60 || hour() == 7 && minute() >= 25 && minute() < 60 ) {
    acht();
  }


  if (hour() == 20 && minute() < 5 || hour() == 8 && minute() < 5) {    // acht uhr oder zwanzig
    acht();
    uhr();
  }
  if (hour() == 20 && minute() >= 5 && minute() < 15 || hour() == 8 && minute() >= 5 && minute() < 15 ) {
    acht();
  }
  if (hour() == 20 && minute() >= 15 && minute() < 20 || hour() == 8 && minute() >= 15 && minute() < 20 ) {
    neun();
  }
  if (hour() == 20 && minute() >= 20 && minute() < 25 || hour() == 8 && minute() >= 20 && minute() < 25 ) {
    acht();
  }
  if (hour() == 20 && minute() >= 25 && minute() < 60 || hour() == 8 && minute() >= 25 && minute() < 60 ) {
    neun();
  }



  if (hour() == 21 && minute() < 5 || hour() == 9 && minute() < 5) {      //  neun uhr oder einundzwanzig
    neun();
    uhr();
  }
  if (hour() == 21 && minute() >= 5 && minute() < 15 || hour() == 9 && minute() >= 5 && minute() < 15 ) {
    neun();
  }
  if (hour() == 21 && minute() >= 15 && minute() < 20 || hour() == 9 && minute() >= 15 && minute() < 20 ) {
    zehn2();
  }
  if (hour() == 21 && minute() >= 20 && minute() < 25 || hour() == 9 && minute() >= 20 && minute() < 25 ) {
    neun();
  }
  if (hour() == 21 && minute() >= 25 && minute() < 60 || hour() == 9 && minute() >= 25 && minute() < 60 ) {
    zehn2();
  }



  if (hour() == 22 && minute() < 5 || hour() == 10 && minute() < 5) {                        // zehn  uhr oder zweiundzwanzig
    zehn2();
    uhr();
  }
  if (hour() == 22 && minute() >= 5 && minute() < 15 || hour() == 10 && minute() >= 5 && minute() < 15 ) {
    zehn2();
  }
  if (hour() == 22 && minute() >= 15 && minute() < 20 || hour() == 10 && minute() >= 15 && minute() < 20 ) {
    elf();
  }
  if (hour() == 22 && minute() >= 20 && minute() < 25 || hour() == 10 && minute() >= 20 && minute() < 25 ) {
    zehn2();
  }
  if (hour() == 22 && minute() >= 25 && minute() < 60 || hour() == 10 && minute() >= 25 && minute() < 60 ) {
    elf();
  }



  if (hour() == 23 && minute() < 5 || hour() == 11 && minute() < 5) {                  // elf uhr oder dreiundzwanzig
    elf();
    uhr();
  }
  if (hour() == 23 && minute() >= 5 && minute() < 15 || hour() == 11 && minute() >= 5 && minute() < 15 ) {
    elf();
  }
  if (hour() == 23 && minute() >= 15 && minute() < 20 || hour() == 11 && minute() >= 15 && minute() < 20 ) {
    zwolf();
  }
  if (hour() == 23 && minute() >= 20 && minute() < 25 || hour() == 11 && minute() >= 20 && minute() < 25 ) {
    elf();
  }
  if (hour() == 23 && minute() >= 25 && minute() < 60 || hour() == 11 && minute() >= 25 && minute() < 60 ) {
    zwolf();
  }


  if (hour() == 24 && minute() < 5 || hour() == 12 && minute() < 5) {                    // zwolf uhr oder vierundzwanzig
    zwolf();
    uhr();
  }
  if (hour() == 24 && minute() >= 5 && minute() < 15 || hour() == 12 && minute() >= 5 && minute() < 15 ) {
    zwolf();
  }
  if (hour() == 24 && minute() >= 15 && minute() < 20 || hour() == 12 && minute() >= 15 && minute() < 20 ) {
    eins();
  }
  if (hour() == 24 && minute() >= 20 && minute() < 25 || hour() == 12 && minute() >= 20 && minute() < 25 ) {
    zwolf();
  }
  if (hour() == 24 && minute() >= 25 && minute() < 60 || hour() == 12 && minute() >= 25 && minute() < 60 ) {
    eins();
  }

  strip.show();
}

