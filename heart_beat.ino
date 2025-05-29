#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <PulseSensorPlayground.h>

// OLED configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pulse Sensor configuration
#define PULSE_INPUT A0   // Pulse Sensor connected to A0
#define THRESHOLD 530    // Adjust this based on your environment
PulseSensorPlayground pulseSensor;

// Variables
int bpm = 0;

void setup() {
  // Serial monitor
  Serial.begin(9600);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED allocation failed");
    while (true); // Halt if OLED fails
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();
  delay(2000);

  // Initialize Pulse Sensor
  pulseSensor.analogInput(PULSE_INPUT);
  pulseSensor.setThreshold(THRESHOLD);
  pulseSensor.begin();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Pulse Sensor Ready!");
  display.display();
  delay(2000);
}

void loop() {
  // Read BPM
  bpm = pulseSensor.getBeatsPerMinute();

  // Check if a beat is detected and the BPM is valid
  if (pulseSensor.sawStartOfBeat()) {
    Serial.print("Heartbeat detected! BPM: ");
    Serial.println(bpm);
  }

  // Display BPM on OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Heart Rate");
  display.setTextSize(3);
  display.setCursor(0, 25);

  if (bpm > 30 && bpm < 220) { // Ensure BPM is within a valid range
    display.println(bpm);
  } else {
    display.println("...");
  }

  display.setTextSize(1);
  display.setCursor(0, 55);
  display.println("BPM");
  display.display();

  delay(20); // Small delay for smooth updates
}
