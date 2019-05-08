#include <RTClib.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Stepper.h>
#define STEPS 513

Stepper stepper(STEPS, 4, 5, 6, 7);

RTC_DS3231 rtc;

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int rightButton = 3;
int leftButton = 2;

int counter = 0;
int lastCount = 0;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  stepper.setSpeed(20);

  pinMode(rightButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);

  lcd.begin(20, 4);
  lcd.setCursor(6, 0);
  lcd.print("welcome!");

  delay(3000); // wait for console opening
  lcd.clear();

   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    lcd.print("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();

  if (digitalRead(leftButton) == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    getSekki(now.day(), now.month());
    lcd.setCursor(0, 2);
    getKo(now.day(), now.month());
  }

  if (digitalRead(rightButton) == HIGH) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Today is ");
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.setCursor(0, 1);
    lcd.print("The date is ");
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.day(), DEC);
    lcd.print(" ");
    lcd.print(now.year(), DEC);
  }

  if (counter != lastCount) {
    stepper.step(34.2);
    lastCount = counter;
  }
}

void getSekki(int Day, int Month) {
  if (Month == 2) {
    if (Day <= 3) {
      lcd.print(F("Greater Cold"));
      counter = 0;
    }
    else if (Day >= 4 && Day <= 18) {
      lcd.print(F("Beginning of Spring"));
      counter = 1;
    }
    else {
      lcd.print(F("Rainwater"));
      counter = 2;
    }
  }
  else if (Month == 3) {
    if (Day >= 1 && Day <= 5) {
      lcd.print(F("Rainwater"));
      counter = 2;
    }
    else if (Day >= 6 && Day <= 20) {
      lcd.print(F("Insects Awaken"));
      counter = 3;
    }
    else {
      lcd.print(F("Spring Equinox"));
      counter = 4;
    }
  }
  else if (Month == 4) {
    if (Day >= 1 && Day <= 4) {
      lcd.print(F("Spring Equinox"));
      counter = 4;
    }
    else if (Day >= 5 && Day <= 19) {
      lcd.print(F("Pure and Clear"));
      counter = 5;
    }
    else {
      lcd.print(F("Grain Rains"));
      counter = 6;
    }
  }
  else if (Month == 5) {
    if (Day <= 4) {
      lcd.print(F("Grain Rains"));
      counter = 6;
    }
    else if (Day >= 5 && Day <= 20) {
      lcd.print(F("Beginning of Summer"));
      counter = 7;
    }
    else {
      lcd.print(F("Lesser Ripening"));
      counter = 8;
    }
  }
  else if (Month == 6) {
    if (Day <= 5) {
      lcd.print(F("Lesser Ripening"));
      counter = 8;
    }
    else if (Day >= 6 && Day <= 20) {
      lcd.print(F("Grain Beards and Seeds"));
      counter = 9;
    }
    else {
      lcd.print(F("Summer Solstice"));
      counter = 10;
    }
  }
  else if (Month == 7) {
    if (Day <= 6) {
      lcd.print(F("Summer Solstice"));
      counter = 10;
    }
    else if (Day >= 7 && Day <= 22) {
      lcd.print(F("Lesser Heat"));
      counter = 11;
    }
    else {
      lcd.print(F("Greater Heat"));
      counter = 12;
    }
  }
  else if (Month == 8) {
    if (Day <= 7) {
      lcd.print(F("Greater Heat"));
      counter = 12;
    }
    else if (Day >= 8 && Day <= 22) {
      lcd.print(F("Beginning of Autumn"));
      counter = 13;
    }
    else {
      lcd.print(F("Manageable Heat"));
      counter = 14;
    }
  }
  else if (Month == 9) {
    if (Day <= 7) {
      lcd.print(F("Manageable Heat"));
      counter = 14;
    }
    else if (Day >= 8 && Day <= 22) {
      lcd.print(F("White Dew"));
      counter = 15;
    }
    else {
      lcd.print(F("Autumn Equinox"));
      counter = 16;
    }
  }
  else if (Month == 10) {
    if (Day <= 7) {
      lcd.print(F("Autumn Equinox"));
      counter = 16;
    }
    else if (Day >= 8 && Day <= 22) {
      lcd.print(F("Cold Dew"));
      counter = 17;
    }
    else {
      lcd.print(F("Frost Falls"));
      counter = 18;
    }
  }
  else if (Month == 11) {
    if (Day <= 6) {
      lcd.print(F("Frost Falls"));
      counter = 18;
    }
    else if (Day >= 7 && Day <= 21) {
      lcd.print(F("Beginning of Winter"));
      counter = 19;
    }
    else {
      lcd.print(F("Lesser Snow"));
      counter = 20;
    }
  }
  else if (Month == 12) {
    if (Day <= 6) {
      lcd.print(F("Lesser Snow"));
      counter = 20;
    }
    else if (Day >= 7 && Day <= 21) {
      lcd.print(F("Greater Snow"));
      counter = 21;
    }
    else {
      lcd.print(F("Winter Solstice"));
      counter = 22;
    }
  }
  else if (Month == 1) {
    if (Day <= 4) {
      lcd.print(F("Winter Solstice"));
      counter = 22;
    }
    else if (Day >= 5 && Day <= 19) {
      lcd.print(F("Lesser Cold"));
      counter = 23;
    }
    else {
      lcd.print(F("Greater Cold"));
      counter = 0;
    }
  }
}

void getKo(int Day, int Month) {
  if (Month == 2) {
    if (Day <= 3) {
      lcd.print(F("hens start laying eggs"));
    }
    else if (Day >= 4 && Day <= 8) {
      lcd.print(F("east wind melts the ice"));
    }
    else if (Day >= 9 && Day <= 13){
      lcd.print(F("bush warblers start singing in the mountains"));
    }
    else if (Day >= 14 && Day <= 18){
      lcd.print(F("fish emerge from the ice"));
    }
    else if (Day >= 19 && Day <= 23){
      lcd.print(F("rain moistens the soil"));
    }
    else{
      lcd.print(F("mist starts to linger"));
    }
  }
  else if (Month == 3) {
    if (Day <= 5) {
      lcd.print(F("grass sprouts, trees bud"));
    }
    else if (Day >= 6 && Day <= 10) {
      lcd.print(F("hibernating insects surface"));
    }
    else if (Day >= 11 && Day <= 15){
      lcd.print(F("first peach blossoms"));
    }
    else if (Day >= 16 && Day <= 20){
      lcd.print(F("caterpillars become butterflies"));
    }
    else if (Day >= 21 && Day <= 25){
      lcd.print(F("sparrows start to nest"));
    }
    else if (Day >= 26 && Day <= 30){
      lcd.print(F("first cherry blossoms"));
    }
    else{
      lcd.print(F("distant thunder"));
    }
  }
  else if (Month == 4) {
    if (Day <= 4) {
      lcd.print(F("distant thunder"));
    }
    else if (Day >= 5 && Day <= 9) {
      lcd.print(F("swallos return"));
    }
    else if (Day >= 10 && Day <= 14){
      lcd.print(F("wild geese fly north"));
    }
    else if (Day >= 15 && Day <= 19){
      lcd.print(F("first rainbows"));
    }
    else if (Day >= 20 && Day <= 24){
      lcd.print(F("first reeds sprout"));
    }
    else if(Day >= 25 && Day <= 29){
      lcd.print(F("last frost, rice seedlings grow"));
    }
    else{
      lcd.print(F("peonies bloom"));
    }
  }
  else if (Month == 5) {
    if (Day <= 4) {
      lcd.print(F("peonies bloom"));
    }
    else if (Day >= 5 && Day <= 9) {
      lcd.print(F("frogs start singing"));
    }
    else if (Day >= 10 && Day <= 14) {
      lcd.print(F("worms surface"));
    }
    else if (Day >= 15 && Day <= 20){
      lcd.print(F("bamboo shoots sprout"));
    }
    else if (Day >= 21 && Day <= 25){
      lcd.print(F("silkworms start festing on mulberry leaves"));
    }
    else if (Day >=26 && Day <= 30){
      lcd.print(F("safflowers bloom"));
    }
    else{
      lcd.print(F("wheat ripens and is harvested"));
    }
  }
  else if (Month == 6) {
    if (Day <= 5) {
      lcd.print(F("wheat ripens and is harvested"));
    }
    else if (Day >= 6 && Day <= 10) {
      lcd.print(F("praying mantises hatch"));
    }
    else if (Day >= 11 && Day <= 15){
      lcd.print(F("rotten grass becomes fireflies"));
    }
    else if (Day >= 16 && Day <= 20){
      lcd.print(F("plums turn yellow"));
    }
    else if (Day >= 21 && Day <= 26){
      lcd.print(F("self-heal withers"));
    }
    else{
      lcd.print(F("irises bloom"));
    }
  }
  else if (Month == 7) {
    if (Day <= 1) {
      lcd.print(F("irises bloom"));
    }
    else if (Day >= 2 && Day <= 6) {
      lcd.print(F("crow-dipper sprouts"));
    }
    else if (Day >= 7 && Day <= 11){
      lcd.print(F("warm winds blow"));
    }
    else if (Day >= 12 && Day <= 16){
      lcd.print(F("first lotus blossoms"));
    }
    else if (Day >= 17 && Day <= 22){
      lcd.print(F("hawks learn to fly"));
    }
    else if (Day >= 23 && Day <= 28){
      lcd.print(F("paulownia trees produce seeds"));
    }
    else{
      lcd.print(F("earth is damp, air is humid"));
    }
  }
  else if (Month == 8) {
    if (Day <= 2) {
      lcd.print(F("earth is damp, air is humid"));
    }
    else if (Day >= 3 && Day <= 7) {
      lcd.print(F("great rains sometimes fall"));
    }
    else if (Day >= 8 && Day <= 12){
      lcd.print(F("cool winds blow"));
    }
    else if (Day >= 13 && Day <= 17){
      lcd.print(F("evening cicadas sing"));
    }
    else if (Day >= 18 && Day <= 22){
      lcd.print(F("thick fog descends"));
    }
    else if (Day >= 23 && Day <= 27){
      lcd.print(F("cotton flowers bloom"));
    }
    else{
      lcd.print(F("heat starts to die down"));
    }
  }
  else if (Month == 9) {
    if (Day <= 1) {
      lcd.print(F("heat starts to die down"));
    }
    else if (Day >= 2 && Day <= 7) {
      lcd.print(F("rice ripens"));
    }
    else if (Day >= 8 && Day <= 12){
      lcd.print(F("dew glistens white on grass"));
    }
    else if (Day >= 13 && Day <= 17){
      lcd.print(F("wagtails sing"));
    }
    else if (Day >= 18 && Day <= 22){
      lcd.print(F("swallows leave"));
    }
    else if (Day >= 23 && Day <= 27){
      lcd.print(F("thunder ceases"));
    }
    else{
      lcd.print(F("insects hole up underground"));
    }
  }
  else if (Month == 10) {
    if (Day <= 2) {
      lcd.print(F("insects hole up underground"));
    }
    else if (Day >= 3 && Day <= 7) {
      lcd.print(F("farmers drain fields"));
    }
    else if (Day >= 8 && Day <= 12){
      lcd.print(F("wild geese return"));
    }
    else if (Day >= 13 && Day <= 17){
      lcd.print(F("chrysanthemums bloom"));
    }
    else if (Day >= 18 && Day <= 22){
      lcd.print(F("crickets chirp around the door"));
    }
    else if (Day >= 23 && Day <= 27){
      lcd.print(F("frist frost"));
    }
    else{
      lcd.print(F("light rains sometimes fall"));
    }
  }
  else if (Month == 11) {
    if (Day <= 1) {
      lcd.print(F("light rains sometimes fall"));
    }
    else if (Day >= 2 && Day <= 6) {
      lcd.print(F("maple leaves and ivy turn yellow"));
    }
    else if (Day >= 7 && Day <= 11){
      lcd.print(F("camellias bloom"));
    }
    else if (Day >= 12 && Day <= 16){
      lcd.print(F("land starts to freeze"));
    }
    else if (Day >= 17 && Day <= 21){
      lcd.print(F("daffodils bloom"));
    }
    else if (Day >= 22 && Day <= 26){
      lcd.print(F("rainbows hide"));
    }
    else{
      lcd.print(F("north wind blows the leaves from the trees"));
    }
  }
  else if (Month == 12) {
    if (Day <= 1) {
      lcd.print(F("north wind blows the leaves from the trees"));
    }
    else if (Day >= 2 && Day <= 6) {
      lcd.print(F("tachibana citrus tree leaves start to turn yellow"));
    }
    else if (Day >= 7 && Day <= 11){
      lcd.print(F("cold sets in, winter begins"));
    }
    else if (Day >= 12 && Day <= 16){
      lcd.print(F("bears start hibernating in their dens"));
    }
    else if (Day >= 17 && Day <= 21){
      lcd.print(F("salmon gather and swim upstream"));
    }
    else if (Day >= 22 && Day <= 26){
      lcd.print(F("self-heal sprouts"));
    }
    else{
      lcd.print(F("deer shed antlers"));
    }
  }
  else if (Month == 1) {
    if (Day <= 4) {
      lcd.print(F("wheat sprouts under snow"));
    }
    else if (Day >= 5 && Day <= 9) {
      lcd.print(F("parsely flourishes"));
    }
    else if (Day >= 10 && Day <= 14){
      lcd.print(F("springs thaw"));
    }
    else if (Day >= 15 && Day <= 19){
      lcd.print(F("pheasants start to call"));
    }
    else if (Day >= 20 && Day <= 24){
      lcd.print(F("butterburs bud"));
    }
    else if (Day >= 25 && Day <= 29){
      lcd.print(F("ice thickens on streams"));
    }
    else{
      lcd.print(F("hens start laying eggs"));
    }
  }
}

