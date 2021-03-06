uint32_t rosa = strip.Color(225, 0, 100);                 //Farben
uint32_t lila = strip.Color(100, 0, 125);
uint32_t grun = strip.Color(0, 150, 0);
uint32_t skyblue = strip.Color(0, 191, 255);
uint32_t rot = strip.Color(200, 0, 0);
uint32_t coral = strip.Color(255, 114, 86);
uint32_t blau = strip.Color(0, 0, 200);
uint32_t turkis = strip.Color(0, 200, 100);
uint32_t aus = strip.Color(0, 0, 0);
uint32_t weis = strip.Color(100, 100, 100);
uint32_t gelb = strip.Color(150, 150, 0);
uint32_t orange = strip.Color(200, 50, 0);

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
      strip.setPixelColor(i, 0, 0, 100);
  strip.show();
}

void icon_resetWiFi(){
  bool icon[] = {0,0,0,1,1,1,1,1,0,0,0,
                   0,0,1,0,0,0,0,0,1,0,0,
                   0,1,0,0,0,1,0,0,0,1,0,
                   1,0,0,0,0,1,0,0,0,0,1,
                   1,0,0,0,0,1,0,0,0,0,1,
                   1,0,0,0,0,1,0,0,0,0,1,
                   1,0,0,0,0,1,0,0,0,0,1,
                   1,0,0,1,0,0,0,1,0,0,1,
                   0,1,0,0,1,1,1,0,0,1,0,
                   0,0,1,1,0,0,0,1,1,0,0,
                       0,0,1,0,1,0,0};
  strip.clear();
  for (int i = 0; i < NEOPIXEL_NUMLEDS; i++)
    if (icon[i] == 1)
      strip.setPixelColor(i, 0, 0, 100);
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
      strip.setPixelColor(i, 0, 100, 0);
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
      strip.setPixelColor(i, 100, 0, 0);
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

void Ausgehen(){                                  //Animation: alle leuchtenden LEDs gehen der Reihe nach aus
  for(int n=0; n<117; n++){
    if(strip.getPixelColor(n) != 0) {
      strip.setPixelColor(n, strip.Color(0, 0, 0));
      strip.show();
      delay(100);
    }
  }
}

void TheaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j = j + 10) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void Schlange() {
  colorWipe(rosa, d); // rosa
  //colorWipe(turkis, d); // türkis
  colorWipe(orange, d); // orange
}

void Meeting(uint32_t farbe1, uint32_t farbe2){                //Aninmation: zwei Farben laufen zusammen, treffen sich in 
strip.clear();
  for (int b=0; b<=13; b++){                                   //der Mitte und laufen dann wieder auseinander
    for(int i = 0; i <= 4; i++) {
      if(b<=10){
        strip.setPixelColor(b + i * 22, farbe1);
        strip.setPixelColor(21 - b + i * 22, farbe2);
        strip.setPixelColor(b + 11 + i * 22, farbe2);
        strip.setPixelColor(10 - b + i * 22, farbe1);
      }
      if(b>=3){
        if(b!=0){
          strip.setPixelColor(b - 3 + i * 22, aus);
          strip.setPixelColor(21 - b + 3 + i * 22, aus);
          strip.setPixelColor(10 - b + 3 + i * 22, aus);
          strip.setPixelColor(b - 3 + 11 + i * 22, aus);
        }
      }
    }
    strip.show();
    delay(200);
  }
  strip.clear();
}

void Aufsammleroben(uint32_t farbe){                                      //Animation: es laufen vier Punkte von oben nach unten
  for(int n=117; n>=-4; n=n-1){                                           //und sammeln die Anderen auf
    if (n <= 118) {
      strip.setPixelColor(n, farbe);
    }
    if (n <= 113) {
      strip.setPixelColor(n + 4, aus);

    }
    strip.show();
    delay(50);
  }
  strip.clear();
}

void Aufsammler(uint32_t farbe){                                          //Animation: es laufen vier Punkte von unten nach oben
  for(int n=0; n<121; n++){                                               //und sammeln die Anderen auf
    if (n <= 117) {
      strip.setPixelColor(n, farbe);
    }
    if (n >= 4) {
      strip.setPixelColor(n - 4, aus);

    }
    strip.show();
    delay(100);
  }
  strip.clear();
}

void Staffellauf(uint32_t farbe1, uint32_t farbe2){
  strip.clear();
  for (int b=0; b<=14; b++){                              //Animationen: zwei Farben laufen entgegengesetzt von der einen auf die andere Seite
    for(int i = 0; i <=4; i++) {
      if(b<=10){
        strip.setPixelColor(b + i * 22, farbe1);
        strip.setPixelColor(b + 11 + i * 22, farbe2);
      }
      if(b>=4){
        strip.setPixelColor(b-4 + i * 22, aus);
        strip.setPixelColor(b + 11 - 4 + i * 22, aus);
      }
    }
    strip.show();
    delay(100);
  }
  for (int b=0; b<=14; b++){
    for(int i = 0; i <=4; i++) {
      if(b<=10){
        strip.setPixelColor(b + i * 22, farbe2);
        strip.setPixelColor(b + 11 + i * 22, farbe1);
      }
      if(b>=4){
        strip.setPixelColor(b-4 + i * 22, aus);
        strip.setPixelColor(b + 11 - 4 + i * 22, aus);
      }
    }
    strip.show();
    delay(200);
  }
  strip.clear();
}

void KNIGHT() {

  int t;

  for (int i = 0; i < 11; i++) {
    for (int z = 0; z < 10; z++)
      strip.setPixelColor(i + z * 11, strip.Color( colorR, colorG, colorB));

    t = i ;
    if (t < 0) t = strip.numPixels() - 1;
    for (int z = 0; z < 10; z++)
      strip.setPixelColor(t + z * 11, strip.Color( colorR, colorG, colorB));

    strip.show();
    delay(200);
  }
  for (int i = 10; i >= 0; i--) {
    for (int z = 0; z < 10; z++)
      strip.setPixelColor(i + z * 11, strip.Color( colorR, colorG, colorB));
    t = i;
    if (t >= strip.numPixels()) t = 0;
    for (int z = 0; z < 10; z++)
      strip.setPixelColor(t + z * 11, strip.Color( 0, 0, 0));
    strip.show();
    delay(200);
  }
}

void es() {
  strip.setPixelColor(108, colorR, colorG, colorB);
  strip.setPixelColor(109, colorR, colorG, colorB);
}

void ist() {
  strip.setPixelColor(104, colorR, colorG, colorB);
  strip.setPixelColor(105, colorR, colorG, colorB);
  strip.setPixelColor(106, colorR, colorG, colorB);
}

void funf() {
  strip.setPixelColor(99, colorR, colorG, colorB);
  strip.setPixelColor(100, colorR, colorG, colorB);
  strip.setPixelColor(101, colorR, colorG, colorB);
  strip.setPixelColor(102, colorR, colorG, colorB);
}

void zehn() {
  strip.setPixelColor(88, colorR, colorG, colorB);
  strip.setPixelColor(89, colorR, colorG, colorB);
  strip.setPixelColor(90, colorR, colorG, colorB);
  strip.setPixelColor(91, colorR, colorG, colorB);
}

void zwanzig() {
  strip.setPixelColor(92, colorR, colorG, colorB);
  strip.setPixelColor(93, colorR, colorG, colorB);
  strip.setPixelColor(94, colorR, colorG, colorB);
  strip.setPixelColor(95, colorR, colorG, colorB);
  strip.setPixelColor(96, colorR, colorG, colorB);
  strip.setPixelColor(97, colorR, colorG, colorB);
  strip.setPixelColor(98, colorR, colorG, colorB);
}

void viertel() {
  strip.setPixelColor(77, colorR, colorG, colorB);
  strip.setPixelColor(78, colorR, colorG, colorB);
  strip.setPixelColor(79, colorR, colorG, colorB);
  strip.setPixelColor(80, colorR, colorG, colorB);
  strip.setPixelColor(81, colorR, colorG, colorB);
  strip.setPixelColor(82, colorR, colorG, colorB);
  strip.setPixelColor(83, colorR, colorG, colorB);
}

void dreiviertel() {
  strip.setPixelColor(77, colorR, colorG, colorB);
  strip.setPixelColor(78, colorR, colorG, colorB);
  strip.setPixelColor(79, colorR, colorG, colorB);
  strip.setPixelColor(80, colorR, colorG, colorB);
  strip.setPixelColor(81, colorR, colorG, colorB);
  strip.setPixelColor(82, colorR, colorG, colorB);
  strip.setPixelColor(83, colorR, colorG, colorB);
  strip.setPixelColor(84, colorR, colorG, colorB);
  strip.setPixelColor(85, colorR, colorG, colorB);
  strip.setPixelColor(86, colorR, colorG, colorB);
  strip.setPixelColor(87, colorR, colorG, colorB);
}

void vor() {
  strip.setPixelColor(66, colorR, colorG, colorB);
  strip.setPixelColor(67, colorR, colorG, colorB);
  strip.setPixelColor(68, colorR, colorG, colorB);
}

void und() {
  strip.setPixelColor(70, colorR, colorG, colorB);
  strip.setPixelColor(71, colorR, colorG, colorB);
  strip.setPixelColor(72, colorR, colorG, colorB);
}

void nach() {
  strip.setPixelColor(73, colorR, colorG, colorB);
  strip.setPixelColor(74, colorR, colorG, colorB);
  strip.setPixelColor(75, colorR, colorG, colorB);
  strip.setPixelColor(76, colorR, colorG, colorB);
}

void halb() {
  strip.setPixelColor(62, colorR, colorG, colorB);
  strip.setPixelColor(63, colorR, colorG, colorB);
  strip.setPixelColor(64, colorR, colorG, colorB);
  strip.setPixelColor(65, colorR, colorG, colorB);
}

void elf() {
  strip.setPixelColor(58, colorR, colorG, colorB);
  strip.setPixelColor(59, colorR, colorG, colorB);
  strip.setPixelColor(60, colorR, colorG, colorB);
}

void funf2() {
  strip.setPixelColor(55, colorR, colorG, colorB);
  strip.setPixelColor(56, colorR, colorG, colorB);
  strip.setPixelColor(57, colorR, colorG, colorB);
  strip.setPixelColor(58, colorR, colorG, colorB);
}

void eins() {
  strip.setPixelColor(44, colorR, colorG, colorB);
  strip.setPixelColor(45, colorR, colorG, colorB);
  strip.setPixelColor(46, colorR, colorG, colorB);
  strip.setPixelColor(47, colorR, colorG, colorB);
}
void ein() {
  strip.setPixelColor(44, colorR, colorG, colorB);
  strip.setPixelColor(45, colorR, colorG, colorB);
  strip.setPixelColor(46, colorR, colorG, colorB);
}

void zwei() {
  strip.setPixelColor(51, colorR, colorG, colorB);
  strip.setPixelColor(52, colorR, colorG, colorB);
  strip.setPixelColor(53, colorR, colorG, colorB);
  strip.setPixelColor(54, colorR, colorG, colorB);
}

void drei() {
  strip.setPixelColor(40, colorR, colorG, colorB);
  strip.setPixelColor(41, colorR, colorG, colorB);
  strip.setPixelColor(42, colorR, colorG, colorB);
  strip.setPixelColor(43, colorR, colorG, colorB);
}

void vier() {
  strip.setPixelColor(33, colorR, colorG, colorB);
  strip.setPixelColor(34, colorR, colorG, colorB);
  strip.setPixelColor(35, colorR, colorG, colorB);
  strip.setPixelColor(36, colorR, colorG, colorB);
}

void sechs() {
  strip.setPixelColor(22, colorR, colorG, colorB);
  strip.setPixelColor(23, colorR, colorG, colorB);
  strip.setPixelColor(24, colorR, colorG, colorB);
  strip.setPixelColor(25, colorR, colorG, colorB);
  strip.setPixelColor(26, colorR, colorG, colorB);
}

void acht() {
  strip.setPixelColor(29, colorR, colorG, colorB);
  strip.setPixelColor(30, colorR, colorG, colorB);
  strip.setPixelColor(31, colorR, colorG, colorB);
  strip.setPixelColor(32, colorR, colorG, colorB);
}

void sieben() {
  strip.setPixelColor(16, colorR, colorG, colorB);
  strip.setPixelColor(17, colorR, colorG, colorB);
  strip.setPixelColor(18, colorR, colorG, colorB);
  strip.setPixelColor(19, colorR, colorG, colorB);
  strip.setPixelColor(20, colorR, colorG, colorB);
  strip.setPixelColor(21, colorR, colorG, colorB);
}

void zwolf() {
  strip.setPixelColor(11, colorR, colorG, colorB);
  strip.setPixelColor(12, colorR, colorG, colorB);
  strip.setPixelColor(13, colorR, colorG, colorB);
  strip.setPixelColor(14, colorR, colorG, colorB);
  strip.setPixelColor(15, colorR, colorG, colorB);
}

void zehn2() {
  strip.setPixelColor(0, colorR, colorG, colorB);
  strip.setPixelColor(1, colorR, colorG, colorB);
  strip.setPixelColor(2, colorR, colorG, colorB);
  strip.setPixelColor(3, colorR, colorG, colorB);
}

void neun() {
  strip.setPixelColor(3, colorR, colorG, colorB);
  strip.setPixelColor(4, colorR, colorG, colorB);
  strip.setPixelColor(5, colorR, colorG, colorB);
  strip.setPixelColor(6, colorR, colorG, colorB);
}

void uhr() {
  strip.setPixelColor(8, colorR, colorG, colorB);
  strip.setPixelColor(9, colorR, colorG, colorB);
  strip.setPixelColor(10, colorR, colorG, colorB);
}

void ersterpunkt() {
  strip.setPixelColor(110, colorR, colorG, colorB);
}

void zweiterpunkt() {
  strip.setPixelColor(110, colorR, colorG, colorB);
  strip.setPixelColor(112, colorR, colorG, colorB);

}

void dritterpunkt() {
  strip.setPixelColor(110, colorR, colorG, colorB);
  strip.setPixelColor(112, colorR, colorG, colorB);
  strip.setPixelColor(114, colorR, colorG, colorB);
}

void vierterpunkt() {
  strip.setPixelColor(110, colorR, colorG, colorB);
  strip.setPixelColor(112, colorR, colorG, colorB);
  strip.setPixelColor(114, colorR, colorG, colorB);
  strip.setPixelColor(116, colorR, colorG, colorB);
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


  if (hour() == 0 && minute() < 5 || hour() == 12 && minute() < 5) {                    // zwolf uhr oder vierundzwanzig
    zwolf();
    uhr();
  }
  if (hour() == 0 && minute() >= 5 && minute() < 15 || hour() == 12 && minute() >= 5 && minute() < 15 ) {
    zwolf();
  }
  if (hour() == 0 && minute() >= 15 && minute() < 20 || hour() == 12 && minute() >= 15 && minute() < 20 ) {
    eins();
  }
  if (hour() == 0 && minute() >= 20 && minute() < 25 || hour() == 12 && minute() >= 20 && minute() < 25 ) {
    zwolf();
  }
  if (hour() == 0 && minute() >= 25 && minute() < 60 || hour() == 12 && minute() >= 25 && minute() < 60 ) {
    eins();
  }

  strip.show();
}

void LEDs_setup(){
  strip.setPin(NEOPIXEL_PIN);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void clear_disp(){
  strip.clear();
  strip.show();
}

void animation() {
  int i = random(1, 11);
  switch (i) {
  case 1:
    rainbow(30);
    break;
  case 2:
    Schlange();
    break;
  case 3:
    KNIGHT();
    break;
  case 4:
    Ausgehen();
    break;
  case 5:
    colorWipe(41120, 100);
    break;
  case 6:
    TheaterChaseRainbow(100);
    break;
  case 7:
    Meeting(gelb, lila);
    break;
  case 8:
    Staffellauf(coral, skyblue);
    break;
  case 9:
    Aufsammleroben(rosa);
    break;
  case 10:
    Aufsammler(lila);
    break;
  default:
    rainbow(30);
  }
}
