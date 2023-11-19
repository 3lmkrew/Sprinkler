//Made by 3lmkrew on 11/19/2023
#include <Wire.h>  // Include the Wire library for I2C communication
#include <LiquidCrystal_I2C.h>  // Include the LiquidCrystal_I2C library for the LCD
#include <RTClib.h>  // Include the RTClib library for the DS3231 RTC

RTC_DS3231 rtc;  // Create an RTC_DS3231 object

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address and size (you might need to change the address)

const int relayPins[] = {2, 3, 4, 5};
const int NUM_RELAYS = 4;
const long SPRINKLER_DURATION = 180000;  // 5 minutes in milliseconds
bool sprinklersActivatedToday = false;  // Flag to prevent multiple activations in a day

void setup() {
  Wire.begin();  // Initialize I2C communication
  lcd.init();  // Initialize the LCD
  lcd.backlight();  // Turn on the LCD backlight
  
  
  if (!rtc.begin()) {
    lcd.print("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    lcd.print("RTC lost power, set the time!");
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  Serial.begin(9600);

  // Initialize all relay pins
  for (int i = 0; i < NUM_RELAYS; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);  // Initialize as OFF
  }
}

void loop() {
  DateTime now = rtc.now();  // Get the current date and time from the RTC

  // Update the time on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  displayDate(now);
  
  // Check if it's 8:00 AM and the sprinklers haven't been activated today
  if (now.hour() == 8 && now.minute() == 00) {
    for (int i = 0; i < NUM_RELAYS; i++) {
      activateSprinkler(relayPins[i], i + 1);  // Pass the current index + 1 for display purposes
      delay(SPRINKLER_DURATION);  // Wait for 3 minutes
      deactivateSprinkler(relayPins[i]);
    }
    //sprinklersActivatedToday = true;  // Set the flag to true after activation

    // After all sprinklers are deactivated, display the date again
    displayDate(now);
  }

  // Reset the flag at midnight to allow for activation the next day
  if (now.hour() == 0 && now.minute() == 0 && sprinklersActivatedToday) {
    sprinklersActivatedToday = false;
  }
}

void activateSprinkler(int pin, int index) {
  digitalWrite(pin, LOW);  // Assume LOW activates the relay
  lcd.setCursor(0, 1);
  lcd.print("Sprinkler ");
  lcd.print(index);
  lcd.print(" ON  ");  // Extra spaces to clear any previous text

}

void deactivateSprinkler(int pin) {
  digitalWrite(pin, HIGH);  // Assume HIGH deactivates the relay
}

void displayDate(DateTime now) {
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);
  lcd.print("    ");  // Clear any extra characters
}
