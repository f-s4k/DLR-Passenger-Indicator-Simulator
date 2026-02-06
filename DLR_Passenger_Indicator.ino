#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// DLR Route
const char* stations[] = {
  "Tower Gateway",
  "Shadwell",
  "Limehouse",
  "Westferry Circus",
  "Poplar",
  "Blackwall",
  "East India",
  "Canning Town",
  "Royal Victoria",
  "Custom House",
  "Prince Regent",
  "Royal Albert",
  "Beckton Park",
  "Cyprus",
  "Gallions Reach",
  "Beckton"
};

const int totalStations = 16;

// Train state
int currentStation = 0;      // ALWAYS the station we are at
bool goingForward = true;

// Timing
unsigned long lastMillis = 0;
const int scrollDelay = 200;
const int stationHoldTime = 3000;
const int terminusHoldTime = 10000;

// Display FSM
enum DisplayMode { SCROLL, STATION, TERMINUS_HOLD };
DisplayMode mode = SCROLL;

// Scroll data
String message;
int scrollIndex = 0;

// Helper func 

int nextStation() {
  return goingForward ? currentStation + 1 : currentStation - 1;
}

bool nextIsTerminus() {         // Terminus cases
  return (goingForward && currentStation == totalStations - 2) ||
         (!goingForward && currentStation == 1);
}

bool atTerminus() {
  return currentStation == 0 || currentStation == totalStations - 1;
}

// Message

void buildMessage() {
  const char* destination = goingForward ? "Beckton" : "Tower Gateway";

  if (nextIsTerminus()) {
    message = "Next stop is ";
    message += destination;
    message += " where this train terminates.   ";
  } else {
    message = "Train is for ";
    message += destination;
    message += ". Next stop is ";
    message += stations[nextStation()];
    message += "   ";
  }

  scrollIndex = 0;
  mode = SCROLL;
}

// Display

void scrollMessage() {
  lcd.setCursor(0, 0);
  String padded = message + "                ";
  lcd.print(padded.substring(scrollIndex, scrollIndex + 16));

  scrollIndex++;  // After scrolling, switching mode

  if (scrollIndex > padded.length() - 16) {
    lcd.clear();
    lcd.setCursor(0, 0);

    // Showing arriving station name
    lcd.print(stations[nextStation()]);
    lastMillis = millis();

    if (nextIsTerminus()) {
      mode = TERMINUS_HOLD;
    } else {
      mode = STATION;
    }
  }
}

// Core func

void setup() {
  lcd.init();
  lcd.backlight();

  // Start service NOT announcing starting terminus lol
  if (atTerminus()) {
    currentStation = goingForward ? 0 : totalStations - 1;
  }

  buildMessage();
}

void loop() {
  unsigned long now = millis();

  if (mode == SCROLL) {
    scrollMessage();
    delay(scrollDelay);
  }

  else if (mode == STATION) {
    if (now - lastMillis >= stationHoldTime) {
      currentStation = nextStation();   // moving ONE station
      buildMessage();
    }
  }

  else if (mode == TERMINUS_HOLD) {
    if (now - lastMillis >= terminusHoldTime) {

      // We are now AT the terminus!
      currentStation = nextStation();

      // Reversing order
      goingForward = !goingForward;

      buildMessage();
    }
  }
}
