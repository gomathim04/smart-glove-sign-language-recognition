#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SDA_PIN 21
#define SCL_PIN 22

#define BUTTON_PIN 27
#define BUZZER_PIN 13

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

void setup() {

  Serial.begin(115200);

  // I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED ERROR");
    while (1);
  }

  // Starting screen
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(20, 5);
  display.println("SMART");

  display.setCursor(20, 30);
  display.println("GLOVE");

  display.display();

  delay(1500);
}

void loop() {

  // Button pressed = LOW
  if (digitalRead(BUTTON_PIN) == LOW) {

    // Buzzer ON
    digitalWrite(BUZZER_PIN, HIGH);

    // OLED emergency alert
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(2);
    display.setCursor(10, 5);
    display.println("EMERGENCY");

    display.setCursor(38, 28);
    display.println("ALERT!");

    display.setTextSize(1);
    display.setCursor(25, 52);
    display.println("HELP NEEDED");

    display.display();

    Serial.println("!!! EMERGENCY ALERT !!!");

  }

  else {

    // Buzzer OFF
    digitalWrite(BUZZER_PIN, LOW);

    // Normal OLED screen
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(2);
    display.setCursor(25, 8);
    display.println("SYSTEM");

    display.setCursor(30, 35);
    display.println("READY");

    display.display();
  }

  delay(100);
}